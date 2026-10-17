#include "global.h"
#include "data.h"
#include "decompress.h"
#include "malloc.h"
#include "test/test.h"

// Compare the resources selected by the real trainer-picture accessors against
// uncompressed image data generated independently of the production .smol stream.
// This catches an incorrect table entry, invalid compression header, blank output,
// corrupt decompression, palette mismatch, and writes beyond the 64x64 buffer.
static const u32 sRaw_falkner[] = INCGFX_U32("graphics/trainers/front_pics/ce_falkner.png", ".4bpp");
static const u16 sPalette_falkner[] = INCGFX_U16("graphics/trainers/front_pics/ce_falkner.png", ".gbapal");
static const u32 sRaw_bugsy[] = INCGFX_U32("graphics/trainers/front_pics/ce_bugsy.png", ".4bpp");
static const u16 sPalette_bugsy[] = INCGFX_U16("graphics/trainers/front_pics/ce_bugsy.png", ".gbapal");
static const u32 sRaw_whitney[] = INCGFX_U32("graphics/trainers/front_pics/ce_whitney.png", ".4bpp");
static const u16 sPalette_whitney[] = INCGFX_U16("graphics/trainers/front_pics/ce_whitney.png", ".gbapal");
static const u32 sRaw_morty[] = INCGFX_U32("graphics/trainers/front_pics/ce_morty.png", ".4bpp");
static const u16 sPalette_morty[] = INCGFX_U16("graphics/trainers/front_pics/ce_morty.png", ".gbapal");
static const u32 sRaw_chuck[] = INCGFX_U32("graphics/trainers/front_pics/ce_chuck.png", ".4bpp");
static const u16 sPalette_chuck[] = INCGFX_U16("graphics/trainers/front_pics/ce_chuck.png", ".gbapal");
static const u32 sRaw_jasmine[] = INCGFX_U32("graphics/trainers/front_pics/ce_jasmine.png", ".4bpp");
static const u16 sPalette_jasmine[] = INCGFX_U16("graphics/trainers/front_pics/ce_jasmine.png", ".gbapal");
static const u32 sRaw_pryce[] = INCGFX_U32("graphics/trainers/front_pics/ce_pryce.png", ".4bpp");
static const u16 sPalette_pryce[] = INCGFX_U16("graphics/trainers/front_pics/ce_pryce.png", ".gbapal");
static const u32 sRaw_clair[] = INCGFX_U32("graphics/trainers/front_pics/ce_clair.png", ".4bpp");
static const u16 sPalette_clair[] = INCGFX_U16("graphics/trainers/front_pics/ce_clair.png", ".gbapal");
static const u32 sRaw_roark[] = INCGFX_U32("graphics/trainers/front_pics/ce_roark.png", ".4bpp");
static const u16 sPalette_roark[] = INCGFX_U16("graphics/trainers/front_pics/ce_roark.png", ".gbapal");
static const u32 sRaw_gardenia[] = INCGFX_U32("graphics/trainers/front_pics/ce_gardenia.png", ".4bpp");
static const u16 sPalette_gardenia[] = INCGFX_U16("graphics/trainers/front_pics/ce_gardenia.png", ".gbapal");
static const u32 sRaw_maylene[] = INCGFX_U32("graphics/trainers/front_pics/ce_maylene.png", ".4bpp");
static const u16 sPalette_maylene[] = INCGFX_U16("graphics/trainers/front_pics/ce_maylene.png", ".gbapal");
static const u32 sRaw_crasher_wake[] = INCGFX_U32("graphics/trainers/front_pics/ce_crasher_wake.png", ".4bpp");
static const u16 sPalette_crasher_wake[] = INCGFX_U16("graphics/trainers/front_pics/ce_crasher_wake.png", ".gbapal");
static const u32 sRaw_fantina[] = INCGFX_U32("graphics/trainers/front_pics/ce_fantina.png", ".4bpp");
static const u16 sPalette_fantina[] = INCGFX_U16("graphics/trainers/front_pics/ce_fantina.png", ".gbapal");
static const u32 sRaw_byron[] = INCGFX_U32("graphics/trainers/front_pics/ce_byron.png", ".4bpp");
static const u16 sPalette_byron[] = INCGFX_U16("graphics/trainers/front_pics/ce_byron.png", ".gbapal");
static const u32 sRaw_candice[] = INCGFX_U32("graphics/trainers/front_pics/ce_candice.png", ".4bpp");
static const u16 sPalette_candice[] = INCGFX_U16("graphics/trainers/front_pics/ce_candice.png", ".gbapal");
static const u32 sRaw_volkner[] = INCGFX_U32("graphics/trainers/front_pics/ce_volkner.png", ".4bpp");
static const u16 sPalette_volkner[] = INCGFX_U16("graphics/trainers/front_pics/ce_volkner.png", ".gbapal");
static const u32 sRaw_gold[] = INCGFX_U32("graphics/trainers/front_pics/ce_gold.png", ".4bpp");
static const u16 sPalette_gold[] = INCGFX_U16("graphics/trainers/front_pics/ce_gold.png", ".gbapal");
static const u32 sRaw_silver[] = INCGFX_U32("graphics/trainers/front_pics/ce_silver.png", ".4bpp");
static const u16 sPalette_silver[] = INCGFX_U16("graphics/trainers/front_pics/ce_silver.png", ".gbapal");

static const struct
{
    enum TrainerPicID id;
    const u32 *pixels;
    u32 size;
    const u16 *palette;
} sPortraits[] =
{
    {TRAINER_PIC_CE_FALKNER, sRaw_falkner, sizeof(sRaw_falkner), sPalette_falkner},
    {TRAINER_PIC_CE_BUGSY, sRaw_bugsy, sizeof(sRaw_bugsy), sPalette_bugsy},
    {TRAINER_PIC_CE_WHITNEY, sRaw_whitney, sizeof(sRaw_whitney), sPalette_whitney},
    {TRAINER_PIC_CE_MORTY, sRaw_morty, sizeof(sRaw_morty), sPalette_morty},
    {TRAINER_PIC_CE_CHUCK, sRaw_chuck, sizeof(sRaw_chuck), sPalette_chuck},
    {TRAINER_PIC_CE_JASMINE, sRaw_jasmine, sizeof(sRaw_jasmine), sPalette_jasmine},
    {TRAINER_PIC_CE_PRYCE, sRaw_pryce, sizeof(sRaw_pryce), sPalette_pryce},
    {TRAINER_PIC_CE_CLAIR, sRaw_clair, sizeof(sRaw_clair), sPalette_clair},
    {TRAINER_PIC_CE_ROARK, sRaw_roark, sizeof(sRaw_roark), sPalette_roark},
    {TRAINER_PIC_CE_GARDENIA, sRaw_gardenia, sizeof(sRaw_gardenia), sPalette_gardenia},
    {TRAINER_PIC_CE_MAYLENE, sRaw_maylene, sizeof(sRaw_maylene), sPalette_maylene},
    {TRAINER_PIC_CE_CRASHER_WAKE, sRaw_crasher_wake, sizeof(sRaw_crasher_wake), sPalette_crasher_wake},
    {TRAINER_PIC_CE_FANTINA, sRaw_fantina, sizeof(sRaw_fantina), sPalette_fantina},
    {TRAINER_PIC_CE_BYRON, sRaw_byron, sizeof(sRaw_byron), sPalette_byron},
    {TRAINER_PIC_CE_CANDICE, sRaw_candice, sizeof(sRaw_candice), sPalette_candice},
    {TRAINER_PIC_CE_VOLKNER, sRaw_volkner, sizeof(sRaw_volkner), sPalette_volkner},
    {TRAINER_PIC_CE_GOLD, sRaw_gold, sizeof(sRaw_gold), sPalette_gold},
    {TRAINER_PIC_CE_SILVER, sRaw_silver, sizeof(sRaw_silver), sPalette_silver},
};

TEST("Complete Edition: custom portraits decompress exactly through production accessors")
{
    u32 portrait = 0;
    for (u32 i = 0; i < ARRAY_COUNT(sPortraits); i++)
        PARAMETRIZE_LABEL("portrait %u", sPortraits[i].id) { portrait = i; }

    enum TrainerPicID id = sPortraits[portrait].id;
    const u32 *compressed;
    const u16 *palette;
    struct GuardedPortrait
    {
        u32 before[4];
        u32 pixels[64 * 64 / 8];
        u32 after[4];
    };
    struct GuardedPortrait *decoded;
    bool32 guardsIntact = TRUE;
    bool32 matchesSource = TRUE;
    bool32 nonempty = FALSE;
    bool32 paletteMatches = TRUE;

    EXPECT(id < TRAINER_PIC_COUNT);
    EXPECT(gTrainerPicInfo[id].frontPic != NULL);
    compressed = GetTrainerFrontPicData(id);
    palette = GetTrainerFrontPicPalette(id);
    EXPECT(compressed != NULL);
    EXPECT(palette != NULL);
    EXPECT_EQ((uintptr_t)compressed & 3, 0);
    EXPECT_EQ((uintptr_t)palette & 1, 0);
    EXPECT_EQ(sPortraits[portrait].size, sizeof(decoded->pixels));
    EXPECT_EQ(GetDecompressedDataSize(compressed), sizeof(decoded->pixels));
    EXPECT(IsCompressedData(compressed));

    // The function-test runner initializes the shared heap before each test.
    // Smol decompression uses that heap for its own temporary decoding vectors.
    decoded = Alloc(sizeof(*decoded));
    EXPECT(decoded != NULL);
    for (u32 i = 0; i < ARRAY_COUNT(decoded->before); i++)
    {
        decoded->before[i] = 0xA5A5A5A5;
        decoded->after[i] = 0x5A5A5A5A;
    }
    for (u32 i = 0; i < ARRAY_COUNT(decoded->pixels); i++)
        decoded->pixels[i] = 0xFFFFFFFF;

    // This is the same decode call used by DecompressPic for trainer front pics.
    DecompressDataWithHeaderWram(compressed, decoded->pixels);

    for (u32 i = 0; i < ARRAY_COUNT(decoded->before); i++)
        guardsIntact &= decoded->before[i] == 0xA5A5A5A5
                    && decoded->after[i] == 0x5A5A5A5A;
    for (u32 i = 0; i < ARRAY_COUNT(decoded->pixels); i++)
    {
        matchesSource &= decoded->pixels[i] == sPortraits[portrait].pixels[i];
        nonempty |= decoded->pixels[i] != 0;
    }
    for (u32 i = 0; i < 16; i++)
        paletteMatches &= palette[i] == sPortraits[portrait].palette[i];

    Free(decoded);
    EXPECT(guardsIntact);
    EXPECT(nonempty);
    EXPECT(matchesSource);
    EXPECT(paletteMatches);
}

