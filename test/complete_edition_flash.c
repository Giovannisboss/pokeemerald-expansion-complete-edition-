#include "global.h"
#include "battle.h"
#include "pokemon.h"
#include "complete_edition.h"
#include "event_data.h"
#include "load_save.h"
#include "pokemon_storage_system.h"
#include "save.h"
#include "test/test.h"
#include "main.h"

// Production flash programming borrows Timer 2. The native test runner uses
// the same timer for its watchdog; restore it before handing back control.
struct FlashTestClock
{
    IntrFunc handler;
    u16 interruptEnable;
    u16 timerLow;
    u16 timerHigh;
};

static struct FlashTestClock BeginFlashTest(void)
{
    struct FlashTestClock clock = {gIntrTable[7], REG_IE, REG_TM2CNT_L, REG_TM2CNT_H};
    CheckForFlashMemory();
    return clock;
}

static void EndFlashTest(const struct FlashTestClock *clock)
{
    u16 ime = REG_IME;
    REG_IME = 0;
    REG_TM2CNT_H = 0;
    gIntrTable[7] = clock->handler;
    REG_TM2CNT_L = clock->timerLow;
    REG_IF = INTR_FLAG_TIMER2;
    REG_IE = clock->interruptEnable;
    REG_TM2CNT_H = clock->timerHigh;
    REG_IME = ime;
}

TEST("Complete Edition: flash save restores trained party, final PC slot, and capture flags")
{
    struct FlashTestClock clock = BeginFlashTest();
    EXPECT(gFlashMemoryPresent);
    Save_ResetSaveCounters();
    ClearSaveData();
    ZeroPlayerPartyMons();
    struct Pokemon *mon = &gParties[B_TRAINER_PLAYER][0];
    CreateMonWithIVs(mon, SPECIES_GARCHOMP, 55, 0x11223344, OTID_STRUCT_PRESET(0x55667788), 31);
    gPartiesCount[B_TRAINER_PLAYER] = 1;
    EXPECT(CompleteEditionSetNature(mon, NATURE_JOLLY));
    EXPECT_EQ(CompleteEditionSetEV(mon, STAT_ATK, 252), CE_SERVICE_OK);
    EXPECT_EQ(CompleteEditionSetEV(mon, STAT_SPEED, 252), CE_SERVICE_OK);
    EXPECT_EQ(CompleteEditionSetEV(mon, STAT_HP, 4), CE_SERVICE_OK);
    gPokemonStoragePtr->boxes[TOTAL_BOXES_COUNT - 1][IN_BOX_COUNT - 1] = mon->box;
    FlagSet(FLAG_CE_STARTER_PIPLUP);
    EXPECT_EQ(TrySavingData(SAVE_NORMAL), SAVE_STATUS_OK);

    ZeroPlayerPartyMons();
    gPartiesCount[B_TRAINER_PLAYER] = 0;
    memset(gPokemonStoragePtr, 0, sizeof(*gPokemonStoragePtr));
    FlagClear(FLAG_CE_STARTER_PIPLUP);
    EXPECT_EQ(LoadGameSave(SAVE_NORMAL), SAVE_STATUS_OK);
    EXPECT_EQ(gPartiesCount[B_TRAINER_PLAYER], 1);
    EXPECT_EQ(GetMonData(mon, MON_DATA_SPECIES), SPECIES_GARCHOMP);
    EXPECT_EQ(GetMonData(mon, MON_DATA_PERSONALITY), 0x11223344);
    EXPECT_EQ(GetMonData(mon, MON_DATA_OT_ID), 0x55667788);
    EXPECT_EQ(GetMonData(mon, MON_DATA_HIDDEN_NATURE), NATURE_JOLLY);
    EXPECT_EQ(GetMonData(mon, MON_DATA_ATK_EV), 252);
    EXPECT_EQ(GetMonData(mon, MON_DATA_SPEED_EV), 252);
    EXPECT_EQ(GetMonData(mon, MON_DATA_HP_EV), 4);
    EXPECT(IsMonShiny(mon));
    struct BoxPokemon *boxed = &gPokemonStoragePtr->boxes[TOTAL_BOXES_COUNT - 1][IN_BOX_COUNT - 1];
    EXPECT_EQ(GetBoxMonData(boxed, MON_DATA_SPECIES), SPECIES_GARCHOMP);
    EXPECT_EQ(GetBoxMonData(boxed, MON_DATA_HIDDEN_NATURE), NATURE_JOLLY);
    EXPECT_EQ(GetBoxMonData(boxed, MON_DATA_ATK_EV), 252);
    EXPECT_EQ(GetBoxMonData(boxed, MON_DATA_SPEED_IV), 31);
    EXPECT(GetBoxMonData(boxed, MON_DATA_IS_SHINY));
    EXPECT(FlagGet(FLAG_CE_STARTER_PIPLUP));
    EndFlashTest(&clock);
}

#include "agb_flash.h"
#include "gba/flash_internal.h"
#include "pokedex.h"

static u32 StorageHash(void)
{
    const u8 *bytes = (const u8 *)gPokemonStoragePtr;
    u32 hash = 2166136261u;
    for (u32 i = 0; i < sizeof(*gPokemonStoragePtr); i++)
        hash = (hash ^ bytes[i]) * 16777619u;
    return hash;
}

TEST("Complete Edition: all 510 PC slots survive flash saves and corrupted-slot recovery")
{
    u32 corruption = 0;
    PARAMETRIZE { corruption = 0; } // PC data in footer chunk, formerly unchecked upstream.
    PARAMETRIZE { corruption = 1; } // Invalid sector ID must never index outside the layout.
    struct FlashTestClock clock = BeginFlashTest();
    EXPECT(gFlashMemoryPresent);
    Save_ResetSaveCounters();
    ClearSaveData();
    ResetPokemonStorageSystem();
    struct Pokemon mon;
    for (u32 i = 0; i < TOTAL_BOXES_COUNT * IN_BOX_COUNT; i++)
    {
        enum Species species = NationalPokedexNumToSpecies(i % 493 + 1);
        CreateMonWithIVs(&mon, species, 50, 0xBEEF0000 + i, OTID_STRUCT_PRESET(0x12345678 + i), i % 32);
        u32 ev = i % 253;
        SetMonData(&mon, MON_DATA_HP_EV, &ev);
        ev = i % NUM_NATURES;
        SetMonData(&mon, MON_DATA_HIDDEN_NATURE, &ev);
        gPokemonStoragePtr->boxes[i / IN_BOX_COUNT][i % IN_BOX_COUNT] = mon.box;
    }
    // Include metadata and every byte of the engine's reserved fusion storage.
    gPokemonStoragePtr->currentBox = TOTAL_BOXES_COUNT - 1;
    for (u32 i = 0; i < MAX_FUSION_STORAGE; i++)
        gPokemonStoragePtr->fusions[i] = mon;
    u32 oldHash = StorageHash();
    FlagSet(FLAG_CE_STARTER_PIPLUP);
    EXPECT_EQ(TrySavingData(SAVE_NORMAL), SAVE_STATUS_OK);
    memset(gPokemonStoragePtr, 0, sizeof(*gPokemonStoragePtr));
    EXPECT_EQ(LoadGameSave(SAVE_NORMAL), SAVE_STATUS_OK);
    EXPECT_EQ(StorageHash(), oldHash);
    for (u32 i = 0; i < 493; i++)
        EXPECT_EQ(GetBoxMonData(&gPokemonStoragePtr->boxes[i / IN_BOX_COUNT][i % IN_BOX_COUNT], MON_DATA_SPECIES), NationalPokedexNumToSpecies(i + 1));

    // Newer snapshot differs in both normal data and the extended PC tail.
    CreateRandomMon(&mon, SPECIES_ARCEUS, 100);
    gPokemonStoragePtr->boxes[TOTAL_BOXES_COUNT - 1][IN_BOX_COUNT - 1] = mon.box;
    FlagClear(FLAG_CE_STARTER_PIPLUP);
    EXPECT_EQ(TrySavingData(SAVE_NORMAL), SAVE_STATUS_OK);
    u32 newerSector = gLastWrittenSector + NUM_SECTORS_PER_SLOT * (gSaveCounter % NUM_SAVE_SLOTS);
    ReadFlash(newerSector, 0, (u8 *)&gSaveDataBuffer, SECTOR_SIZE);
    if (corruption == 0)
        gSaveDataBuffer.saveBlock3Chunk[4] ^= 1;
    else
        gSaveDataBuffer.id = 0xFFFF;
    EXPECT_EQ(ProgramFlashSectorAndVerify(newerSector, (u8 *)&gSaveDataBuffer), 0);
    memset(gPokemonStoragePtr, 0, sizeof(*gPokemonStoragePtr));
    EXPECT_EQ(LoadGameSave(SAVE_NORMAL), SAVE_STATUS_ERROR); // Previous snapshot recovered.
    EXPECT_EQ(StorageHash(), oldHash);
    EXPECT(FlagGet(FLAG_CE_STARTER_PIPLUP));
    EndFlashTest(&clock);
}

TEST("Complete Edition: Frontier partial save preserves a consistent PC snapshot")
{
    struct FlashTestClock clock = BeginFlashTest();
    EXPECT(gFlashMemoryPresent);
    Save_ResetSaveCounters();
    ClearSaveData();
    ResetPokemonStorageSystem();
    struct Pokemon mon;
    CreateRandomMon(&mon, SPECIES_PIPLUP, 5);
    gPokemonStoragePtr->boxes[0][0] = mon.box;
    gPokemonStoragePtr->boxes[TOTAL_BOXES_COUNT - 1][IN_BOX_COUNT - 1] = mon.box;
    u32 savedHash = StorageHash();
    EXPECT_EQ(TrySavingData(SAVE_NORMAL), SAVE_STATUS_OK);
    // PC edits are deliberately not part of SAVE_LINK's partial snapshot, as upstream.
    CreateRandomMon(&mon, SPECIES_ARCEUS, 100);
    gPokemonStoragePtr->boxes[0][0] = mon.box;
    gPokemonStoragePtr->boxes[TOTAL_BOXES_COUNT - 1][IN_BOX_COUNT - 1] = mon.box;
    FlagSet(FLAG_CE_STARTER_PIPLUP);
    EXPECT_EQ(TrySavingData(SAVE_LINK), SAVE_STATUS_OK);
    memset(gPokemonStoragePtr, 0, sizeof(*gPokemonStoragePtr));
    EXPECT_EQ(LoadGameSave(SAVE_NORMAL), SAVE_STATUS_OK);
    EXPECT_EQ(StorageHash(), savedHash);
    EXPECT(FlagGet(FLAG_CE_STARTER_PIPLUP));
    EndFlashTest(&clock);
}
