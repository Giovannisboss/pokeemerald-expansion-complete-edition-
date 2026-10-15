#include "global.h"
#include "battle.h"
#include "pokemon.h"
#include "complete_edition.h"
#include "item.h"
#include "pokedex.h"
#include "test/test.h"

TEST("Complete Edition: all 493 species are shiny with every original-trainer method")
{
    u32 dex = 1, method = 0;
    struct Pokemon mon;
    for (u32 d = 1; d <= 493; d++)
        for (u32 m = 0; m < 3; m++)
            PARAMETRIZE_LABEL("dex %u, OT method %u", d, m) { dex = d; method = m; }
    enum Species species = NationalPokedexNumToSpecies(dex);
    EXPECT_NE(species, SPECIES_NONE);
    if (method == 0)
        CreateMon(&mon, species, 50, 0xABCD1234, OTID_STRUCT_PLAYER_ID);
    else if (method == 1)
        CreateMon(&mon, species, 50, 0xABCD1234, OTID_STRUCT_RANDOM_NO_SHINY);
    else
        CreateMon(&mon, species, 50, 0xABCD1234, OTID_STRUCT_PRESET(0x98765432));
    EXPECT(IsMonShiny(&mon));
    bool32 notShiny = FALSE;
    SetMonData(&mon, MON_DATA_IS_SHINY, &notShiny);
    EXPECT(IsMonShiny(&mon)); // Trainer-template overrides cannot disable the policy.
    EXPECT_EQ(GetMonData(&mon, MON_DATA_PERSONALITY), 0xABCD1234);
}

TEST("Complete Edition: battle nature preserves identity and IVs")
{
    struct Pokemon mon;
    CreateMonWithIVs(&mon, SPECIES_PIKACHU, 50, 12345, OTID_STRUCT_PRESET(54321), 10);
    u32 gender = GetMonGender(&mon);
    EXPECT(CompleteEditionSetNature(&mon, NATURE_MODEST));
    EXPECT_EQ(GetMonData(&mon, MON_DATA_HIDDEN_NATURE), NATURE_MODEST);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_PERSONALITY), 12345);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_OT_ID), 54321);
    EXPECT_EQ(GetMonGender(&mon), gender);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_HP_IV), 10);
    EXPECT(IsMonShiny(&mon));
    EXPECT(!CompleteEditionSetNature(&mon, NUM_NATURES));
}

TEST("Complete Edition: Silver Cap changes one IV and is consumed exactly once")
{
    struct Pokemon mon;
    CreateMonWithIVs(&mon, SPECIES_PIKACHU, 50, 12345, OTID_STRUCT_PRESET(0), 10);
    EXPECT(AddBagItem(ITEM_BOTTLE_CAP, 1));
    EXPECT_EQ(CompleteEditionTrainIV(&mon, STAT_ATK, FALSE), CE_SERVICE_OK);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_ATK_IV), 31);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_HP_IV), 10);
    EXPECT(!CheckBagHasItem(ITEM_BOTTLE_CAP, 1));
    EXPECT_EQ(CompleteEditionTrainIV(&mon, STAT_DEF, FALSE), CE_SERVICE_NO_CAP);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_DEF_IV), 10);
    EXPECT_EQ(CompleteEditionTrainIV(&mon, STAT_ATK, FALSE), CE_SERVICE_NO_CHANGE);
}

TEST("Complete Edition: Gold Cap changes all six IVs and rejects Eggs")
{
    struct Pokemon mon;
    CreateMonWithIVs(&mon, SPECIES_TOGEPI, 50, 12345, OTID_STRUCT_PRESET(0), 10);
    EXPECT(AddBagItem(ITEM_GOLD_BOTTLE_CAP, 2));
    bool32 isEgg = TRUE;
    SetMonData(&mon, MON_DATA_IS_EGG, &isEgg);
    EXPECT_EQ(CompleteEditionTrainIV(&mon, 0, TRUE), CE_SERVICE_INVALID);
    EXPECT(CheckBagHasItem(ITEM_GOLD_BOTTLE_CAP, 2));
    isEgg = FALSE;
    SetMonData(&mon, MON_DATA_IS_EGG, &isEgg);
    EXPECT_EQ(CompleteEditionTrainIV(&mon, 0, TRUE), CE_SERVICE_OK);
    for (u32 i = 0; i < NUM_STATS; i++)
        EXPECT_EQ(GetMonData(&mon, MON_DATA_HP_IV + i), 31);
    EXPECT(CheckBagHasItem(ITEM_GOLD_BOTTLE_CAP, 1));
    EXPECT(!CheckBagHasItem(ITEM_GOLD_BOTTLE_CAP, 2));
    EXPECT_EQ(CompleteEditionTrainIV(&mon, 0, TRUE), CE_SERVICE_NO_CHANGE);
    EXPECT(CheckBagHasItem(ITEM_GOLD_BOTTLE_CAP, 1));
}

TEST("Complete Edition: EV allocation enforces 252 per stat and 510 total atomically")
{
    struct Pokemon mon;
    CreateRandomMon(&mon, SPECIES_PIKACHU, 50);
    EXPECT_EQ(CompleteEditionSetEV(&mon, STAT_ATK, 252), CE_SERVICE_OK);
    EXPECT_EQ(CompleteEditionSetEV(&mon, STAT_SPEED, 252), CE_SERVICE_OK);
    EXPECT_EQ(CompleteEditionSetEV(&mon, STAT_HP, 4), CE_SERVICE_OK);
    EXPECT_EQ(CompleteEditionSetEV(&mon, STAT_DEF, 4), CE_SERVICE_EV_LIMIT);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_DEF_EV), 0);
    EXPECT_EQ(CompleteEditionSetEV(&mon, STAT_ATK, 253), CE_SERVICE_INVALID);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_ATK_EV), 252);
    EXPECT_EQ(CompleteEditionSetEV(&mon, NUM_STATS, 0), CE_SERVICE_INVALID);
    CompleteEditionResetEVs(&mon);
    for (u32 i = 0; i < NUM_STATS; i++)
        EXPECT_EQ(GetMonData(&mon, MON_DATA_HP_EV + i), 0);
}

TEST("Complete Edition: trade evolutions work locally and consume their held item")
{
    struct Pokemon mon;
    bool32 canStop = TRUE;
    CreateRandomMon(&mon, SPECIES_KADABRA, 37);
    EXPECT_EQ(GetEvolutionTargetSpecies(&mon, EVO_MODE_NORMAL, ITEM_NONE, NULL, &canStop, DO_EVO), SPECIES_ALAKAZAM);
    CreateRandomMon(&mon, SPECIES_ONIX, 20);
    enum Item item = ITEM_METAL_COAT;
    SetMonData(&mon, MON_DATA_HELD_ITEM, &item);
    EXPECT_EQ(GetEvolutionTargetSpecies(&mon, EVO_MODE_NORMAL, ITEM_NONE, NULL, &canStop, DO_EVO), SPECIES_STEELIX);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_HELD_ITEM), ITEM_NONE);
}

#include "complete_edition_research.h"
#include "event_data.h"

TEST("Complete Edition: every research encounter is a real shiny Gen 1-4 Pokemon")
{
    u32 dex = 1;
    for (u32 i = 1; i <= 493; i++)
        PARAMETRIZE_LABEL("dex %u", i) { dex = i; }
    EXPECT(!CompleteEditionCanResearch(dex, FALSE));
    EXPECT(CompleteEditionCanResearch(dex, TRUE));
    FlagClear(FLAG_SYS_GAME_CLEAR);
    FlagSet(FLAG_BADGE07_GET);
    gSpecialVar_Result = dex + 1024;
    Script_CEPrepareEncounter();
    EXPECT_EQ(gSpecialVar_Result, TRUE);
    struct Pokemon *mon = &gParties[B_TRAINER_OPPONENT_A][0];
    EXPECT_EQ(GetMonData(mon, MON_DATA_SPECIES), NationalPokedexNumToSpecies(dex));
    EXPECT_EQ(GetMonData(mon, MON_DATA_LEVEL), 50);
    EXPECT(IsMonShiny(mon));
}

TEST("Complete Edition: research rejects out-of-range species")
{
    EXPECT(!CompleteEditionCanResearch(0, TRUE));
    EXPECT(!CompleteEditionCanResearch(494, TRUE));
    EXPECT(!CompleteEditionCanResearch(0xFFFFFFFF, TRUE));
}

#include "script_menu.h"
#include "malloc.h"

static void FreeResearchTestMenu(void)
{
    for (u32 i = 0; i < MultichoiceDynamic_StackSize(); i++)
        Free((void *)MultichoiceDynamic_PeekElementAt(i)->name);
    MultichoiceDynamic_DestroyStack();
}

TEST("Complete Edition: research menus cover all 493 species without cancel collisions")
{
    const u32 starts[] = {1, 152, 252, 387};
    const u32 ends[] = {151, 251, 386, 493};
    for (u32 region = 0; region < 4; region++)
    {
        gSpecialVar_0x8005 = region;
        Script_CEResearchMenu();
        EXPECT_EQ(MultichoiceDynamic_StackSize(), ends[region] - starts[region] + 1);
        for (u32 i = 0; i < MultichoiceDynamic_StackSize(); i++)
        {
            u32 id = MultichoiceDynamic_PeekElementAt(i)->id;
            EXPECT_EQ(id, starts[region] + i + 1024);
            EXPECT_NE(id, MULTI_B_PRESSED);
        }
        FreeResearchTestMenu();
    }
}

TEST("Complete Edition: EV menu permits every value from 0 to 252 without cancel collisions")
{
    Script_CEEVAmountMenu();
    EXPECT_EQ(MultichoiceDynamic_StackSize(), 253);
    for (u32 i = 0; i < 253; i++)
    {
        u32 id = MultichoiceDynamic_PeekElementAt(i)->id;
        EXPECT_EQ(id, i + 1024);
        EXPECT_NE(id, MULTI_B_PRESSED);
    }
    FreeResearchTestMenu();
}

TEST("Complete Edition: catalogue unlocks with the seventh badge before becoming Champion")
{
    u32 badges = 0;
    for (u32 i = 0; i <= 8; i++)
        PARAMETRIZE { badges = i; }
    FlagClear(FLAG_SYS_GAME_CLEAR);
    for (u32 i = 0; i < 8; i++)
        FlagClear(FLAG_BADGE01_GET + i);
    for (u32 i = 0; i < badges; i++)
        FlagSet(FLAG_BADGE01_GET + i);
    CreateRandomMon(&gParties[B_TRAINER_OPPONENT_A][0], SPECIES_SENTRET, 5);
    gSpecialVar_Result = 493 + 1024;
    Script_CEPrepareEncounter();
    EXPECT_EQ(gSpecialVar_Result, badges >= 7);
    EXPECT_EQ(GetMonData(&gParties[B_TRAINER_OPPONENT_A][0], MON_DATA_SPECIES), badges >= 7 ? SPECIES_ARCEUS : SPECIES_SENTRET);
    EXPECT(!FlagGet(FLAG_SYS_GAME_CLEAR));
}
