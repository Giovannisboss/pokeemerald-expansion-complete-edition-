#include "global.h"
#include "bg.h"
#include "berry_fix_program.h"
#include "event_data.h"
#include "reset_rtc_screen.h"
#include "clear_save_data_menu.h"
#include "dma3.h"
#include "gpu_regs.h"
#include "main.h"
#include "main_menu.h"
#include "menu.h"
#include "malloc.h"
#include "palette.h"
#include "scanline_effect.h"
#include "sound.h"
#include "sprite.h"
#include "task.h"
#include "text.h"
#include "window.h"
#include "constants/rgb.h"
#include "constants/songs.h"

// 600 8bpp tiles (38,400 bytes) + a 2 KiB tilemap. Text has its own
// 4bpp charblock; all graphics fit Mode 0's ordinary GBA background VRAM.
static const u32 sArtwork[] = INCGFX_U32("graphics/title_screen/complete_edition.png", ".8bpp");
static const u16 sArtworkPalette[] = INCGFX_U16("graphics/title_screen/complete_edition.png", ".gbapal");
static const u16 sTextPalette[16] = {RGB_BLACK, RGB(31, 30, 23), RGB(1, 8, 9), RGB(31, 25, 8)};
static const u8 sPokemon[] = _("POKéMON");
static const u8 sEmerald[] = _("EMERALD");
static const u8 sEdition[] = _("COMPLETE EDITION");
static const u8 sStart[] = _("PRESS START");
static const u8 sFanMade[] = _("FAN-MADE EDITION");
static const struct BgTemplate sBackgrounds[] = {
    {.bg = 0, .charBaseIndex = 0, .mapBaseIndex = 31, .screenSize = 0, .paletteMode = 1, .priority = 1},
    {.bg = 1, .charBaseIndex = 3, .mapBaseIndex = 30, .screenSize = 0, .paletteMode = 0, .priority = 0},
};
static const struct WindowTemplate sWindows[] = {
    {.bg = 1, .tilemapLeft = 0, .tilemapTop = 0, .width = 30, .height = 7, .paletteNum = 15, .baseBlock = 1},
    {.bg = 1, .tilemapLeft = 6, .tilemapTop = 17, .width = 18, .height = 3, .paletteNum = 15, .baseBlock = 211},
    DUMMY_WIN_TEMPLATE,
};

static void VBlank(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

static void CenterText(u32 window, u32 font, const u8 *text, u32 y, bool32 gold)
{
    u8 colors[3] = {0, gold ? 3 : 1, 2};
    u32 width = window == 0 ? 240 : 144;
    AddTextPrinterParameterized3(window, font, (width - GetStringWidth(font, text, 0)) / 2, y, colors, TEXT_SKIP_DRAW, text);
}

static void Main(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    UpdatePaletteFade();
}

static void Task_Title(u8 taskId)
{
    s16 *data = gTasks[taskId].data;
    if (gPaletteFade.active)
        return;
    if (data[1])
    {
        FreeAllWindowBuffers();
        switch (data[1])
        {
        case 2: SetMainCallback2(CB2_InitClearSaveDataScreen); break;
        case 3: SetMainCallback2(CB2_InitResetRtcScreen); break;
        case 4: SetMainCallback2(CB2_InitBerryFixProgram); break;
        default: SetMainCallback2(CB2_InitMainMenu); break;
        }
        DestroyTask(taskId);
        return;
    }
    if (JOY_NEW(A_BUTTON | START_BUTTON))
        data[1] = 1;
    else if (JOY_HELD(B_BUTTON | SELECT_BUTTON | DPAD_UP) == (B_BUTTON | SELECT_BUTTON | DPAD_UP))
        data[1] = 2;
    else if (JOY_HELD(B_BUTTON | SELECT_BUTTON | DPAD_LEFT) == (B_BUTTON | SELECT_BUTTON | DPAD_LEFT) && CanResetRTC())
        data[1] = 3;
    else if (JOY_HELD(B_BUTTON | SELECT_BUTTON) == (B_BUTTON | SELECT_BUTTON))
        data[1] = 4;
    if (data[1])
    {
        FadeOutBGM(4);
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
        return;
    }
    if ((++data[0] % 30) == 0)
    {
        FillWindowPixelBuffer(1, PIXEL_FILL(0));
        if ((data[0] / 30) & 1)
            CenterText(1, FONT_NORMAL, sStart, 0, FALSE);
        CenterText(1, FONT_SMALL, sFanMade, 14, FALSE);
        CopyWindowToVram(1, COPYWIN_FULL);
    }
    // The title theme loops; retain the screen until the player presses a button.
    if (IsBGMStopped())
        PlayBGM(MUS_TITLE);
}

void CB2_InitCompleteEditionTitle(void)
{
    SetVBlankCallback(NULL);
    SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_FORCED_BLANK);
    ScanlineEffect_Stop();
    ResetTasks();
    ResetSpriteData();
    FreeAllSpritePalettes();
    ResetPaletteFade();
    ResetBgsAndClearDma3BusyFlags(0);
    InitBgsFromTemplates(0, sBackgrounds, ARRAY_COUNT(sBackgrounds));
    DmaFill16(3, 0, (void *)VRAM, VRAM_SIZE);
    DmaFill32(3, 0, (void *)OAM, OAM_SIZE);
    DmaCopy16(3, sArtwork, (void *)BG_CHAR_ADDR(0), sizeof(sArtwork));
    u16 *map = (u16 *)BG_SCREEN_ADDR(31);
    for (u32 y = 0; y < 20; y++)
        for (u32 x = 0; x < 30; x++)
            map[y * 32 + x] = y * 30 + x;
    LoadPalette(sArtworkPalette, 0, 240 * sizeof(u16));
    LoadPalette(sTextPalette, 240, sizeof(sTextPalette));
    InitWindows(sWindows);
    DeactivateAllTextPrinters();
    FillWindowPixelBuffer(0, PIXEL_FILL(0));
    FillWindowPixelBuffer(1, PIXEL_FILL(0));
    CenterText(0, FONT_NORMAL, sPokemon, 1, TRUE);
    CenterText(0, FONT_NORMAL, sEmerald, 16, FALSE);
    CenterText(0, FONT_SMALL, sEdition, 32, TRUE);
    CenterText(1, FONT_NORMAL, sStart, 0, FALSE);
    CenterText(1, FONT_SMALL, sFanMade, 14, FALSE);
    PutWindowTilemap(0);
    PutWindowTilemap(1);
    CopyWindowToVram(0, COPYWIN_FULL);
    CopyWindowToVram(1, COPYWIN_FULL);
    SetGpuReg(REG_OFFSET_BLDCNT, 0);
    SetGpuReg(REG_OFFSET_BLDALPHA, 0);
    SetGpuReg(REG_OFFSET_BLDY, 0);
    SetGpuReg(REG_OFFSET_WIN0H, 0);
    SetGpuReg(REG_OFFSET_WIN0V, 0);
    SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_MODE_0);
    SetGpuReg(REG_OFFSET_BG0HOFS, 0);
    SetGpuReg(REG_OFFSET_BG0VOFS, 0);
    SetGpuReg(REG_OFFSET_BG1HOFS, 0);
    SetGpuReg(REG_OFFSET_BG1VOFS, 0);
    ShowBg(0);
    ShowBg(1);
    BeginNormalPaletteFade(PALETTES_ALL, 0, 16, 0, RGB_BLACK);
    SetVBlankCallback(VBlank);
    CreateTask(Task_Title, 0);
    PlayBGM(MUS_TITLE);
    SetMainCallback2(Main);
}
