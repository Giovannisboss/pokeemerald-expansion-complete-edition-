#include "global.h"
#include "pokemon.h"
#include "complete_edition_legends.h"
#include "event_data.h"
#include "malloc.h"
#include "script_menu.h"
#include "script_pokemon_util.h"
#include "string_util.h"
#include "data/complete_edition_legends.h"

static bool32 HasRegiInParty(enum Species species)
{
    for (u32 i = 0; i < PARTY_SIZE; i++)
    {
        struct Pokemon *mon = &gParties[B_TRAINER_PLAYER][i];
        if (GetMonData(mon, MON_DATA_SPECIES) == species && !GetMonData(mon, MON_DATA_IS_EGG))
            return TRUE;
    }
    return FALSE;
}

bool32 CompleteEditionLegendIsReady(u32 index)
{
    if (index >= CE_LEGEND_COUNT || !FlagGet(FLAG_BADGE07_GET))
        return FALSE;
    const struct CELegend *legend = &gCELegends[index];
    if (FlagGet(legend->caughtFlag) || (legend->needsChampion && !FlagGet(FLAG_SYS_GAME_CLEAR)))
        return FALSE;
    for (u32 i = 0; i < CE_LEGEND_COUNT; i++)
        if ((legend->prerequisites & (1u << i)) && !FlagGet(gCELegends[i].caughtFlag))
            return FALSE;
    if (legend->needsRegis
     && (!HasRegiInParty(SPECIES_REGIROCK) || !HasRegiInParty(SPECIES_REGICE) || !HasRegiInParty(SPECIES_REGISTEEL)))
        return FALSE;
    return TRUE;
}

void Script_CELegendIsReady(void)
{
    gSpecialVar_Result = CompleteEditionLegendIsReady(gSpecialVar_0x8005);
}

void Script_CEPrepareLegend(void)
{
    u32 index = gSpecialVar_0x8005;
    gSpecialVar_Result = FALSE;
    if (!CompleteEditionLegendIsReady(index))
        return;
    CreateScriptedWildMon(gCELegends[index].species, gCELegends[index].level, ITEM_NONE);
    gSpecialVar_Result = TRUE;
}

void Script_CELegendHintsMenu(void)
{
    for (u32 i = 0; i < CE_LEGEND_COUNT; i++)
    {
        struct ListMenuItem item;
        u8 *name = Alloc(POKEMON_NAME_LENGTH + 1);
        AGB_ASSERT(name != NULL);
        StringCopy(name, GetSpeciesName(gCELegends[i].species));
        item.name = name;
        item.id = 1024 + i;
        MultichoiceDynamic_PushElement(item);
    }
}
