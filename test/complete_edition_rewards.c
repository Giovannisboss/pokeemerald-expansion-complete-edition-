#include "global.h"
#include "complete_edition_tournament.h"
#include "event_data.h"
#include "item.h"
#include "test/test.h"

TEST("Complete Edition: tournament prize survives a full Bag and can be collected once after making room")
{
    ClearBag();
    FlagSet(FLAG_CE_TOURNAMENT_REWARD_PENDING);
    // Fill every Items-pocket slot through the real inventory API.
    for (u32 i = 0; i < BAG_ITEMS_COUNT; i++)
        EXPECT(AddBagItem(ITEM_POTION, MAX_BAG_ITEM_CAPACITY));
    EXPECT(!CheckBagHasSpace(ITEM_GOLD_BOTTLE_CAP, 1));
    Script_CEClaimTournamentReward();
    EXPECT_EQ(gSpecialVar_Result, FALSE);
    EXPECT(FlagGet(FLAG_CE_TOURNAMENT_REWARD_PENDING));
    EXPECT(!CheckBagHasItem(ITEM_GOLD_BOTTLE_CAP, 1));

    // Removing only part of a different stack does not free an item slot.
    EXPECT(RemoveBagItem(ITEM_POTION, 1));
    Script_CEClaimTournamentReward();
    EXPECT_EQ(gSpecialVar_Result, FALSE);
    EXPECT(FlagGet(FLAG_CE_TOURNAMENT_REWARD_PENDING));
    EXPECT(RemoveBagItem(ITEM_POTION, MAX_BAG_ITEM_CAPACITY - 1));
    EXPECT(CheckBagHasSpace(ITEM_GOLD_BOTTLE_CAP, 1));
    Script_CEClaimTournamentReward();
    EXPECT_EQ(gSpecialVar_Result, TRUE);
    EXPECT(!FlagGet(FLAG_CE_TOURNAMENT_REWARD_PENDING));
    EXPECT(CheckBagHasItem(ITEM_GOLD_BOTTLE_CAP, 1));
    EXPECT(!CheckBagHasItem(ITEM_GOLD_BOTTLE_CAP, 2));

    Script_CEClaimTournamentReward();
    EXPECT_EQ(gSpecialVar_Result, FALSE);
    EXPECT(!CheckBagHasItem(ITEM_GOLD_BOTTLE_CAP, 2));
}

TEST("Complete Edition: tournament prize cannot be claimed before winning")
{
    ClearBag();
    FlagClear(FLAG_CE_TOURNAMENT_REWARD_PENDING);
    Script_CEClaimTournamentReward();
    EXPECT_EQ(gSpecialVar_Result, FALSE);
    EXPECT(!CheckBagHasItem(ITEM_GOLD_BOTTLE_CAP, 1));
}

TEST("Complete Edition: tournament prize fills an existing Gold Bottle Cap stack in a full pocket")
{
    ClearBag();
    EXPECT(AddBagItem(ITEM_GOLD_BOTTLE_CAP, MAX_BAG_ITEM_CAPACITY - 1));
    for (u32 i = 1; i < BAG_ITEMS_COUNT; i++)
        EXPECT(AddBagItem(ITEM_POTION, MAX_BAG_ITEM_CAPACITY));
    // No empty slot remains, but the existing prize stack has room for one.
    EXPECT(!CheckBagHasSpace(ITEM_POTION, 1));
    EXPECT(CheckBagHasSpace(ITEM_GOLD_BOTTLE_CAP, 1));
    FlagSet(FLAG_CE_TOURNAMENT_REWARD_PENDING);

    Script_CEClaimTournamentReward();
    EXPECT_EQ(gSpecialVar_Result, TRUE);
    EXPECT(!FlagGet(FLAG_CE_TOURNAMENT_REWARD_PENDING));
    EXPECT_EQ(CountTotalItemQuantityInBag(ITEM_GOLD_BOTTLE_CAP), MAX_BAG_ITEM_CAPACITY);
    EXPECT(!CheckBagHasSpace(ITEM_GOLD_BOTTLE_CAP, 1));

    Script_CEClaimTournamentReward();
    EXPECT_EQ(gSpecialVar_Result, FALSE);
    EXPECT_EQ(CountTotalItemQuantityInBag(ITEM_GOLD_BOTTLE_CAP), MAX_BAG_ITEM_CAPACITY);
}

TEST("Complete Edition: a capped Gold Bottle Cap stack retains the prize until stack space is freed")
{
    ClearBag();
    EXPECT(AddBagItem(ITEM_GOLD_BOTTLE_CAP, MAX_BAG_ITEM_CAPACITY));
    for (u32 i = 1; i < BAG_ITEMS_COUNT; i++)
        EXPECT(AddBagItem(ITEM_POTION, MAX_BAG_ITEM_CAPACITY));
    EXPECT(!CheckBagHasSpace(ITEM_GOLD_BOTTLE_CAP, 1));
    FlagSet(FLAG_CE_TOURNAMENT_REWARD_PENDING);

    Script_CEClaimTournamentReward();
    EXPECT_EQ(gSpecialVar_Result, FALSE);
    EXPECT(FlagGet(FLAG_CE_TOURNAMENT_REWARD_PENDING));
    EXPECT_EQ(CountTotalItemQuantityInBag(ITEM_GOLD_BOTTLE_CAP), MAX_BAG_ITEM_CAPACITY);

    // Keep every slot occupied: reducing the cap stack alone permits delivery.
    EXPECT(RemoveBagItem(ITEM_GOLD_BOTTLE_CAP, 1));
    EXPECT(!CheckBagHasSpace(ITEM_POTION, 1));
    EXPECT(CheckBagHasSpace(ITEM_GOLD_BOTTLE_CAP, 1));
    Script_CEClaimTournamentReward();
    EXPECT_EQ(gSpecialVar_Result, TRUE);
    EXPECT(!FlagGet(FLAG_CE_TOURNAMENT_REWARD_PENDING));
    EXPECT_EQ(CountTotalItemQuantityInBag(ITEM_GOLD_BOTTLE_CAP), MAX_BAG_ITEM_CAPACITY);

    Script_CEClaimTournamentReward();
    EXPECT_EQ(gSpecialVar_Result, FALSE);
    EXPECT_EQ(CountTotalItemQuantityInBag(ITEM_GOLD_BOTTLE_CAP), MAX_BAG_ITEM_CAPACITY);
}

TEST("Complete Edition: a newly earned tournament prize can be collected after an earlier prize")
{
    ClearBag();
    FlagClear(FLAG_CE_TOURNAMENT_REWARD_PENDING);
    for (u32 win = 1; win <= 2; win++)
    {
        // The final-round script sets this flag after each completed tournament.
        FlagSet(FLAG_CE_TOURNAMENT_REWARD_PENDING);
        Script_CEClaimTournamentReward();
        EXPECT_EQ(gSpecialVar_Result, TRUE);
        EXPECT(!FlagGet(FLAG_CE_TOURNAMENT_REWARD_PENDING));
        EXPECT_EQ(CountTotalItemQuantityInBag(ITEM_GOLD_BOTTLE_CAP), win);

        Script_CEClaimTournamentReward();
        EXPECT_EQ(gSpecialVar_Result, FALSE);
        EXPECT_EQ(CountTotalItemQuantityInBag(ITEM_GOLD_BOTTLE_CAP), win);
    }
}
