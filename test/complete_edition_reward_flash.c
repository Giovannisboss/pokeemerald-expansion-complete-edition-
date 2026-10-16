#include "global.h"
#include "complete_edition_tournament.h"
#include "event_data.h"
#include "item.h"
#include "load_save.h"
#include "main.h"
#include "save.h"
#include "test/test.h"

// Match complete_edition_flash.c: production flash programming borrows the
// Timer 2 interrupt used by the native runner's watchdog.
struct RewardFlashTestClock
{
    IntrFunc handler;
    u16 interruptEnable;
    u16 timerLow;
    u16 timerHigh;
};

static struct RewardFlashTestClock BeginRewardFlashTest(void)
{
    struct RewardFlashTestClock clock = {gIntrTable[7], REG_IE, REG_TM2CNT_L, REG_TM2CNT_H};
    CheckForFlashMemory();
    return clock;
}

static void EndRewardFlashTest(const struct RewardFlashTestClock *clock)
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

TEST("Complete Edition: pending tournament prize survives flash reload and a saved claim cannot duplicate")
{
    // Native tests run against the test emulator's disposable flash image.
    struct RewardFlashTestClock clock = BeginRewardFlashTest();
    EXPECT(gFlashMemoryPresent);
    Save_ResetSaveCounters();
    ClearSaveData();
    ClearBag();
    for (u32 i = 0; i < BAG_ITEMS_COUNT; i++)
        EXPECT(AddBagItem(ITEM_POTION, MAX_BAG_ITEM_CAPACITY));
    FlagSet(FLAG_CE_TOURNAMENT_REWARD_PENDING);
    EXPECT(!CheckBagHasSpace(ITEM_GOLD_BOTTLE_CAP, 1));
    Script_CEClaimTournamentReward();
    EXPECT_EQ(gSpecialVar_Result, FALSE);
    EXPECT(FlagGet(FLAG_CE_TOURNAMENT_REWARD_PENDING));
    EXPECT_EQ(TrySavingData(SAVE_NORMAL), SAVE_STATUS_OK);

    // Destroy both RAM values so the assertions depend on actual flash loading.
    ClearBag();
    FlagClear(FLAG_CE_TOURNAMENT_REWARD_PENDING);
    EXPECT_EQ(LoadGameSave(SAVE_NORMAL), SAVE_STATUS_OK);
    EXPECT(FlagGet(FLAG_CE_TOURNAMENT_REWARD_PENDING));
    EXPECT_EQ(CountTotalItemQuantityInBag(ITEM_GOLD_BOTTLE_CAP), 0);
    EXPECT(!CheckBagHasSpace(ITEM_GOLD_BOTTLE_CAP, 1));
    Script_CEClaimTournamentReward();
    EXPECT_EQ(gSpecialVar_Result, FALSE);
    EXPECT(FlagGet(FLAG_CE_TOURNAMENT_REWARD_PENDING));

    EXPECT(RemoveBagItem(ITEM_POTION, MAX_BAG_ITEM_CAPACITY));
    EXPECT(CheckBagHasSpace(ITEM_GOLD_BOTTLE_CAP, 1));
    Script_CEClaimTournamentReward();
    EXPECT_EQ(gSpecialVar_Result, TRUE);
    EXPECT(!FlagGet(FLAG_CE_TOURNAMENT_REWARD_PENDING));
    EXPECT_EQ(CountTotalItemQuantityInBag(ITEM_GOLD_BOTTLE_CAP), 1);
    EXPECT_EQ(TrySavingData(SAVE_NORMAL), SAVE_STATUS_OK);

    // Set the wrong flag and remove the reward in RAM before the second load.
    FlagSet(FLAG_CE_TOURNAMENT_REWARD_PENDING);
    EXPECT(RemoveBagItem(ITEM_GOLD_BOTTLE_CAP, 1));
    EXPECT_EQ(LoadGameSave(SAVE_NORMAL), SAVE_STATUS_OK);
    EXPECT(!FlagGet(FLAG_CE_TOURNAMENT_REWARD_PENDING));
    EXPECT_EQ(CountTotalItemQuantityInBag(ITEM_GOLD_BOTTLE_CAP), 1);
    Script_CEClaimTournamentReward();
    EXPECT_EQ(gSpecialVar_Result, FALSE);
    EXPECT_EQ(CountTotalItemQuantityInBag(ITEM_GOLD_BOTTLE_CAP), 1);
    EndRewardFlashTest(&clock);
}
