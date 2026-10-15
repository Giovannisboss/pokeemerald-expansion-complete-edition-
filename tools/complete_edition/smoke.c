// Headless visual smoke test. Host dependency: libmgba-dev.
#include <mgba/core/core.h>
#include <mgba/core/config.h>
#include <mgba/core/log.h>
#include <stdio.h>
#include <stdlib.h>

static void QuietLog(struct mLogger *logger, int category, enum mLogLevel level, const char *format, va_list args)
{
    (void)logger; (void)category; (void)level; (void)format; (void)args;
}

int main(int argc, char **argv)
{
    if (argc < 4) {
        fprintf(stderr, "usage: %s ROM OUTPUT.ppm FRAMES [KEY_MASK] [KEY_END_FRAME] [KEY_START_FRAME]\n", argv[0]);
        return 2;
    }
    struct mLogger logger = {.log = QuietLog};
    mLogSetDefaultLogger(&logger);
    struct mCore *core = mCoreFind(argv[1]);
    if (!core || !core->init(core)) return 3;
    mCoreInitConfig(core, "complete-edition-smoke");
    mCoreConfigSetIntValue(&core->config, "mute", 1);
    mCoreConfigSetIntValue(&core->config, "skipBios", 1);
    core->loadConfig(core, &core->config);
    unsigned w, h;
    core->desiredVideoDimensions(core, &w, &h);
    color_t *pixels = calloc(w * h, sizeof(*pixels));
    if (!pixels || !mCoreLoadFile(core, argv[1])) return 4;
    core->setVideoBuffer(core, pixels, w);
    core->reset(core);
    unsigned frames = strtoul(argv[3], NULL, 0);
    unsigned keys = argc > 4 ? strtoul(argv[4], NULL, 0) : 0;
    unsigned keyEnd = argc > 5 ? strtoul(argv[5], NULL, 0) : frames;
    unsigned keyStart = argc > 6 ? strtoul(argv[6], NULL, 0) : 180;
    for (unsigned i = 0; i < frames; i++) {
        core->setKeys(core, i > keyStart && i < keyEnd && i % 60 < 2 ? keys : 0);
        core->runFrame(core);
    }
    FILE *out = fopen(argv[2], "wb");
    if (!out) return 5;
    fprintf(out, "P6\n%u %u\n255\n", w, h);
    for (unsigned i = 0; i < w * h; i++) {
        unsigned char rgb[3] = {pixels[i] & 255, (pixels[i] >> 8) & 255, (pixels[i] >> 16) & 255};
        fwrite(rgb, 1, 3, out);
    }
    fclose(out);
    printf("Rendered %u frames (%ux%u) to %s\n", core->frameCounter(core), w, h, argv[2]);
    mCoreConfigDeinit(&core->config);
    core->deinit(core);
    free(pixels);
    return 0;
}
