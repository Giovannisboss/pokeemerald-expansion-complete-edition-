#include "global.h"
#include "pokemon.h"
#include "complete_edition_research.h"
#include "event_data.h"
#include "malloc.h"
#include "pokedex.h"
#include "script_menu.h"
#include "script_pokemon_util.h"
#include "string_util.h"

static const u16 sStarters[] = {
    SPECIES_BULBASAUR, SPECIES_CHARMANDER, SPECIES_SQUIRTLE,
    SPECIES_CHIKORITA, SPECIES_CYNDAQUIL, SPECIES_TOTODILE,
    SPECIES_TREECKO, SPECIES_TORCHIC, SPECIES_MUDKIP,
    SPECIES_TURTWIG, SPECIES_CHIMCHAR, SPECIES_PIPLUP,
};

// Named aliases live in flags.h. This reserved range is never used by upstream scripts.
#define CE_STARTER_FLAG_FIRST FLAG_CE_STARTER_BULBASAUR

bool32 CompleteEditionCanResearch(u32 dex, bool32 champion)
{
    return champion && dex >= 1 && dex <= 493;
}

static void PushSpeciesChoice(u32 species, u32 id)
{
    struct ListMenuItem item;
    u8 *name = Alloc(POKEMON_NAME_LENGTH + 1);
    AGB_ASSERT(name != NULL);
    StringCopy(name, GetSpeciesName(species));
    item.name = name;
    item.id = id;
    MultichoiceDynamic_PushElement(item);
}

void Script_CEResearchMenu(void)
{
    static const u16 starts[] = {1, 152, 252, 387};
    static const u16 ends[] = {151, 251, 386, 493};
    u32 region = gSpecialVar_0x8005;
    if (region >= ARRAY_COUNT(starts))
        return;
    for (u32 dex = starts[region]; dex <= ends[region]; dex++)
        PushSpeciesChoice(NationalPokedexNumToSpecies(dex), dex + 1024);
}

void Script_CEPrepareEncounter(void)
{
    u32 dex = gSpecialVar_Result - 1024;
    gSpecialVar_Result = FALSE;
    if (!CompleteEditionCanResearch(dex, FlagGet(FLAG_SYS_GAME_CLEAR)))
        return;
    // Research encounters are real, catchable wild battles, not party injections.
    // Repeats are intentional: running away, losing or failing a capture never locks a species.
    CreateScriptedWildMon(NationalPokedexNumToSpecies(dex), 50, ITEM_NONE);
    gSpecialVar_Result = TRUE;
}

void Script_CEStarterMenu(void)
{
    for (u32 i = 0; i < ARRAY_COUNT(sStarters); i++)
        PushSpeciesChoice(sStarters[i], i);
}

void Script_CEGiveStarter(void)
{
    u32 index = gSpecialVar_Result;
    gSpecialVar_Result = 1;
    if (index >= ARRAY_COUNT(sStarters) || !FlagGet(FLAG_BADGE01_GET))
        return;
    if (FlagGet(CE_STARTER_FLAG_FIRST + index))
    {
        gSpecialVar_Result = 2;
        return;
    }
    if (ScriptGiveMon(sStarters[index], 5, ITEM_NONE) == MON_CANT_GIVE)
        return;
    FlagSet(CE_STARTER_FLAG_FIRST + index);
    gSpecialVar_Result = 0;
}
