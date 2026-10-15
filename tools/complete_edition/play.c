// Interactive headless mGBA controller for reproducible, button-only play QA.
// Host build: gcc -O2 -Wall -Wextra play.c -lmgba -o ce-play
// Commands: run KEY_MASK FRAMES, pulse KEY_MASK FRAMES, shot PATH,
// save PATH, load PATH, read HEX_ADDRESS BYTE_COUNT, position HEX_POINTER, quit.
#include <mgba/core/core.h>
#include <mgba/core/config.h>
#include <mgba/core/log.h>
#include <mgba/core/serialize.h>
#include <mgba-util/vfs.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void QuietLog(struct mLogger *l, int c, enum mLogLevel v, const char *f, va_list a)
{ (void)l; (void)c; (void)v; (void)f; (void)a; }

int main(int argc, char **argv)
{
    if (argc < 2 || argc > 3) { fprintf(stderr, "usage: %s ROM [COMMAND_JOURNAL]\n", argv[0]); return 2; }
    FILE *journal = argc == 3 ? fopen(argv[2], "a") : NULL;
    if (argc == 3 && !journal) { perror(argv[2]); return 2; }
    struct mLogger logger = {.log = QuietLog};
    mLogSetDefaultLogger(&logger);
    struct mCore *core = mCoreFind(argv[1]);
    if (!core || !core->init(core)) return 3;
    mCoreInitConfig(core, "complete-edition-play");
    mCoreConfigSetIntValue(&core->config, "mute", 1);
    mCoreConfigSetIntValue(&core->config, "skipBios", 1);
    core->loadConfig(core, &core->config);
    unsigned w, h;
    core->desiredVideoDimensions(core, &w, &h);
    color_t *pixels = calloc(w * h, sizeof(*pixels));
    if (!pixels || !mCoreLoadFile(core, argv[1])) return 4;
    core->setVideoBuffer(core, pixels, w);
    core->reset(core);
    char line[2048], command[32], path[1900];
    puts("READY"); fflush(stdout);
    while (fgets(line, sizeof(line), stdin)) {
        if (journal) { fprintf(journal, "%u %s", core->frameCounter(core), line); fflush(journal); }
        unsigned keys, frames, address, count;
        if (sscanf(line, "%31s", command) != 1) continue;
        if (!strcmp(command, "quit")) break;
        if ((!strcmp(command, "run") || !strcmp(command, "pulse"))
            && sscanf(line, "%*s %u %u", &keys, &frames) == 2) {
            if (frames > 36000) { puts("ERROR frame limit 36000"); fflush(stdout); continue; }
            for (unsigned i = 0; i < frames; i++) {
                core->setKeys(core, !strcmp(command, "pulse") ? (i % 30 < 8 ? keys : 0) : keys);
                core->runFrame(core);
            }
            core->setKeys(core, 0);
        } else if (!strcmp(command, "shot") && sscanf(line, "%*s %1899s", path) == 1) {
            FILE *out = fopen(path, "wb");
            if (!out) { perror(path); continue; }
            fprintf(out, "P6\n%u %u\n255\n", w, h);
            for (unsigned i = 0; i < w * h; i++) {
                unsigned char rgb[] = {pixels[i] & 255, (pixels[i] >> 8) & 255, (pixels[i] >> 16) & 255};
                fwrite(rgb, 1, 3, out);
            }
            fclose(out);
        } else if ((!strcmp(command, "save") || !strcmp(command, "load"))
                   && sscanf(line, "%*s %1899s", path) == 1) {
            int save = !strcmp(command, "save");
            struct VFile *vf = VFileOpen(path, save ? O_WRONLY | O_CREAT | O_TRUNC : O_RDONLY);
            int ok = vf && (save ? mCoreSaveStateNamed(core, vf, SAVESTATE_ALL)
                               : mCoreLoadStateNamed(core, vf, SAVESTATE_ALL));
            if (vf) vf->close(vf);
            if (!ok) puts("ERROR state operation failed");
        } else if (!strcmp(command, "read") && sscanf(line, "%*s %x %u", &address, &count) == 2 && count <= 256) {
            for (unsigned i = 0; i < count; i++) printf("%02x", core->busRead8(core, address + i));
            putchar('\n');
        } else if (!strcmp(command, "position") && sscanf(line, "%*s %x", &address) == 1) {
            unsigned sb = core->busRead32(core, address);
            printf("POSITION %d %d MAP %u %u\n", (int16_t)core->busRead16(core, sb),
                   (int16_t)core->busRead16(core, sb + 2), core->busRead8(core, sb + 4), core->busRead8(core, sb + 5));
        } else puts("ERROR unknown command");
        printf("FRAME %u\n", core->frameCounter(core)); fflush(stdout);
    }
    mCoreConfigDeinit(&core->config);
    core->deinit(core); free(pixels);
    if (journal) fclose(journal);
    return 0;
}
