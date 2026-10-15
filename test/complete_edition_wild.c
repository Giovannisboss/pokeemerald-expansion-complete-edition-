#include "global.h"
#include "pokemon.h"
#include "pokedex.h"
#include "wild_encounter.h"
#include "test/test.h"

static void AddWildSpecies(bool8 *available, const struct WildPokemonInfo *info, u32 count)
{
    if (info == NULL)
        return;
    for (u32 i = 0; i < count; i++)
    {
        enum Species species = info->wildPokemon[i].species;
        EXPECT_LE(SpeciesToNationalPokedexNum(species), 493);
        EXPECT_GT(info->wildPokemon[i].minLevel, 0);
        EXPECT_LE(info->wildPokemon[i].minLevel, info->wildPokemon[i].maxLevel);
        EXPECT_LE(info->wildPokemon[i].maxLevel, 100);
        if (species <= SPECIES_ARCEUS)
            available[species] = TRUE;
    }
}

TEST("Complete Edition: all ordinary Gen 1-4 species have a wild, starter or original gift evolution path")
{
    bool8 available[SPECIES_ARCEUS + 1] = {0};
    for (u32 i = 0; gWildMonHeaders[i].mapGroup != MAP_GROUP(MAP_UNDEFINED); i++)
    {
        const struct WildEncounterTypes *types = &gWildMonHeaders[i].encounterTypes[0];
        AddWildSpecies(available, types->landMonsInfo, 12);
        AddWildSpecies(available, types->waterMonsInfo, 5);
        AddWildSpecies(available, types->rockSmashMonsInfo, 5);
        AddWildSpecies(available, types->fishingMonsInfo, 10);
    }
    const u16 starters[] = {SPECIES_BULBASAUR, SPECIES_CHARMANDER, SPECIES_SQUIRTLE,
        SPECIES_CHIKORITA, SPECIES_CYNDAQUIL, SPECIES_TOTODILE, SPECIES_TREECKO,
        SPECIES_TORCHIC, SPECIES_MUDKIP, SPECIES_TURTWIG, SPECIES_CHIMCHAR, SPECIES_PIPLUP};
    for (u32 i = 0; i < ARRAY_COUNT(starters); i++)
        available[starters[i]] = TRUE;
    available[SPECIES_CASTFORM] = TRUE; // Original Weather Institute gift.
    for (u32 pass = 0; pass < 4; pass++)
        for (u32 species = 1; species <= SPECIES_ARCEUS; species++)
            if (available[species])
            {
                const struct Evolution *evos = GetSpeciesEvolutions(species);
                if (evos == NULL)
                    continue;
                for (u32 e = 0; evos[e].method != EVOLUTIONS_END; e++)
                    if (evos[e].targetSpecies <= SPECIES_ARCEUS)
                        available[evos[e].targetSpecies] = TRUE;
            }
    for (u32 dex = 1; dex <= 493; dex++)
    {
        enum Species species = NationalPokedexNumToSpecies(dex);
        const struct SpeciesInfo *info = &gSpeciesInfo[species];
        if (info->isRestrictedLegendary || info->isSubLegendary || info->isMythical)
            continue; // Original events and the postgame research fallback are separate.
        EXPECT_EQ(available[species], TRUE);
    }
}
