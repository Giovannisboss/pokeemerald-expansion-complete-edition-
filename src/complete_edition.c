#include "global.h"
#include "battle.h"
#include "pokemon.h"
#include "complete_edition.h"
#include "event_data.h"
#include "item.h"

static bool32 CanTrainMon(struct Pokemon *mon)
{
    return GetMonData(mon, MON_DATA_SPECIES) != SPECIES_NONE
        && !GetMonData(mon, MON_DATA_IS_EGG);
}

bool32 CompleteEditionSetNature(struct Pokemon *mon, u32 nature)
{
    if (!CanTrainMon(mon) || nature >= NUM_NATURES)
        return FALSE;
    // Mint-style nature: no PID change, preserving gender, forms and breeding nature.
    SetMonData(mon, MON_DATA_HIDDEN_NATURE, &nature);
    CalculateMonStats(mon);
    return TRUE;
}

u32 CompleteEditionTrainIV(struct Pokemon *mon, u32 stat, bool32 allStats)
{
    u32 i, value = MAX_PER_STAT_IVS;
    enum Item item = allStats ? ITEM_GOLD_BOTTLE_CAP : ITEM_BOTTLE_CAP;
    bool32 changed = FALSE;
    if (!CanTrainMon(mon) || (!allStats && stat >= NUM_STATS))
        return CE_SERVICE_INVALID;
    for (i = 0; i < NUM_STATS; i++)
        if ((allStats || i == stat) && GetMonData(mon, MON_DATA_HP_IV + i) != value)
            changed = TRUE;
    if (!changed)
        return CE_SERVICE_NO_CHANGE;
    // Remove the cap only after every validation, and before changing the mon.
    if (!RemoveBagItem(item, 1))
        return CE_SERVICE_NO_CAP;
    for (i = 0; i < NUM_STATS; i++)
        if (allStats || i == stat)
            SetMonData(mon, MON_DATA_HP_IV + i, &value);
    CalculateMonStats(mon);
    return CE_SERVICE_OK;
}

u32 CompleteEditionSetEV(struct Pokemon *mon, u32 stat, u32 value)
{
    u32 i, total = value;
    if (!CanTrainMon(mon) || stat >= NUM_STATS || value > MAX_PER_STAT_EVS)
        return CE_SERVICE_INVALID;
    for (i = 0; i < NUM_STATS; i++)
        if (i != stat)
            total += GetMonData(mon, MON_DATA_HP_EV + i);
    if (total > MAX_TOTAL_EVS)
        return CE_SERVICE_EV_LIMIT;
    SetMonData(mon, MON_DATA_HP_EV + stat, &value);
    CalculateMonStats(mon);
    return CE_SERVICE_OK;
}

void CompleteEditionResetEVs(struct Pokemon *mon)
{
    u32 i, value = 0;
    if (!CanTrainMon(mon))
        return;
    for (i = 0; i < NUM_STATS; i++)
        SetMonData(mon, MON_DATA_HP_EV + i, &value);
    CalculateMonStats(mon);
}

// 8004 = party slot, 8005 = operation, 8006 = stat/nature, 8007 = EV value.
void Script_CompleteEditionTraining(void)
{
    struct Pokemon *mon;
    gSpecialVar_Result = CE_SERVICE_INVALID;
    if (gSpecialVar_0x8004 >= CalculatePlayerPartyCount())
        return;
    mon = &gParties[B_TRAINER_PLAYER][gSpecialVar_0x8004];
    if (!CanTrainMon(mon))
        return;
    switch (gSpecialVar_0x8005)
    {
    case 0:
        gSpecialVar_Result = CompleteEditionSetNature(mon, gSpecialVar_0x8006) ? CE_SERVICE_OK : CE_SERVICE_INVALID;
        break;
    case 1:
    case 2:
        gSpecialVar_Result = CompleteEditionTrainIV(mon, gSpecialVar_0x8006, gSpecialVar_0x8005 == 2);
        break;
    case 3:
        gSpecialVar_Result = CompleteEditionSetEV(mon, gSpecialVar_0x8006, gSpecialVar_0x8007);
        break;
    case 4:
        CompleteEditionResetEVs(mon);
        gSpecialVar_Result = CE_SERVICE_OK;
        break;
    }
}
