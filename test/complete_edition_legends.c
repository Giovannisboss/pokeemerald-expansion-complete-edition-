#include "global.h"
#include "pokemon.h"
#include "complete_edition_legends.h"
#include "event_data.h"
#include "pokedex.h"
#include "malloc.h"
#include "script_menu.h"
#include "test/test.h"

static void PrepareLegendTest(u32 index)
{
    for (u32 i = 0; i < CE_LEGEND_COUNT; i++)
        FlagSet(gCELegends[i].caughtFlag);
    FlagClear(gCELegends[index].caughtFlag);
    FlagSet(FLAG_BADGE07_GET);
    FlagSet(FLAG_SYS_GAME_CLEAR);
    ZeroPlayerPartyMons();
    CreateRandomMon(&gParties[B_TRAINER_PLAYER][0], SPECIES_REGIROCK, 50);
    CreateRandomMon(&gParties[B_TRAINER_PLAYER][1], SPECIES_REGICE, 50);
    CreateRandomMon(&gParties[B_TRAINER_PLAYER][2], SPECIES_REGISTEEL, 50);
    CalculatePlayerPartyCount();
}

TEST("Complete Edition: 29 legendary trails enforce gates and create real shiny encounters")
{
    u32 index = 0;
    for (u32 i = 0; i < CE_LEGEND_COUNT; i++)
        PARAMETRIZE_LABEL("trail %u", i) { index = i; }
    const struct CELegend *legend = &gCELegends[index];
    EXPECT(SpeciesToNationalPokedexNum(legend->species) <= 493);
    EXPECT(legend->level >= 50 && legend->level <= 80);
    PrepareLegendTest(index);
    FlagClear(FLAG_BADGE07_GET);
    EXPECT(!CompleteEditionLegendIsReady(index));
    FlagSet(FLAG_BADGE07_GET);
    FlagClear(FLAG_SYS_GAME_CLEAR);
    EXPECT_EQ(CompleteEditionLegendIsReady(index), !legend->needsChampion);
    FlagSet(FLAG_SYS_GAME_CLEAR);
    EXPECT(CompleteEditionLegendIsReady(index));
    gSpecialVar_0x8005 = index;
    Script_CEPrepareLegend();
    EXPECT_EQ(gSpecialVar_Result, TRUE);
    struct Pokemon *mon = &gParties[B_TRAINER_OPPONENT_A][0];
    EXPECT_EQ(GetMonData(mon, MON_DATA_SPECIES), legend->species);
    EXPECT_EQ(GetMonData(mon, MON_DATA_LEVEL), legend->level);
    EXPECT(IsMonShiny(mon));
    EXPECT(!FlagGet(legend->caughtFlag)); // Preparation is not capture.
    EXPECT(CompleteEditionLegendIsReady(index)); // Flee/KO never consumes a trail.
    FlagSet(legend->caughtFlag);
    EXPECT(!CompleteEditionLegendIsReady(index));
    Script_CEPrepareLegend();
    EXPECT_EQ(gSpecialVar_Result, FALSE);
}

TEST("Complete Edition: legendary quest chains require every preceding trail")
{
    u32 index = 0;
    for (u32 i = 0; i < CE_LEGEND_COUNT; i++)
        if (gCELegends[i].prerequisites)
            PARAMETRIZE_LABEL("trail %u", i) { index = i; }
    PrepareLegendTest(index);
    for (u32 i = 0; i < CE_LEGEND_COUNT; i++)
    {
        if (!(gCELegends[index].prerequisites & (1u << i)))
            continue;
        FlagClear(gCELegends[i].caughtFlag);
        EXPECT(!CompleteEditionLegendIsReady(index));
        FlagSet(gCELegends[i].caughtFlag);
        EXPECT(CompleteEditionLegendIsReady(index));
    }
}

TEST("Complete Edition: Regigigas requires three real Regis together")
{
    u32 index = 0;
    for (u32 i = 0; i < CE_LEGEND_COUNT; i++)
        if (gCELegends[i].needsRegis)
            index = i;
    PrepareLegendTest(index);
    EXPECT(CompleteEditionLegendIsReady(index));
    for (u32 slot = 0; slot < 3; slot++)
    {
        bool32 egg = TRUE;
        SetMonData(&gParties[B_TRAINER_PLAYER][slot], MON_DATA_IS_EGG, &egg);
        EXPECT(!CompleteEditionLegendIsReady(index));
        egg = FALSE;
        SetMonData(&gParties[B_TRAINER_PLAYER][slot], MON_DATA_IS_EGG, &egg);
        EXPECT(CompleteEditionLegendIsReady(index));
    }
    ZeroMonData(&gParties[B_TRAINER_PLAYER][2]);
    EXPECT(!CompleteEditionLegendIsReady(index));
}

TEST("Complete Edition: legendary hints have unique cancel-safe entries")
{
    Script_CELegendHintsMenu();
    EXPECT_EQ(MultichoiceDynamic_StackSize(), CE_LEGEND_COUNT);
    for (u32 i = 0; i < CE_LEGEND_COUNT; i++)
    {
        const struct ListMenuItem *item = MultichoiceDynamic_PeekElementAt(i);
        EXPECT_EQ(item->id, 1024 + i);
        Free((void *)item->name);
    }
    MultichoiceDynamic_DestroyStack();
    EXPECT(!CompleteEditionLegendIsReady(CE_LEGEND_COUNT));
    gSpecialVar_0x8005 = 0xFFFF;
    Script_CEPrepareLegend();
    EXPECT_EQ(gSpecialVar_Result, FALSE);
}
