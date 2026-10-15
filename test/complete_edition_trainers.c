#include "global.h"
#include "battle.h"
#include "battle_setup.h"
#include "data.h"
#include "trainer_pools.h"
#include "pokemon.h"
#include "pokedex.h"
#include "test/test.h"
#include "constants/abilities.h"
#include "constants/battle_ai.h"
#include "constants/songs.h"
#include "complete_edition_tournament.h"
#include "event_data.h"

// The upstream test build substitutes dummy trainers. Include the actual
// production roster here so custom parties really are exercised by mGBA.
static const struct Trainer sProductionTrainers[DIFFICULTY_COUNT][TRAINERS_COUNT] = {
#include "../src/data/trainers.h"
};

TEST("Complete Edition: every custom trainer produces a valid shiny Gen 1-4 party")
{
    u32 id = TRAINER_CE_CHAMPION_STEVEN;
    for (u32 i = TRAINER_CE_CHAMPION_STEVEN; i < TRAINERS_COUNT_EMERALD; i++)
        PARAMETRIZE_LABEL("trainer %u", i) { id = i; }
    struct Pokemon party[PARTY_SIZE];
    const struct Trainer *trainer = &sProductionTrainers[DIFFICULTY_NORMAL][id];
    EXPECT(trainer->partySize >= 3 && trainer->partySize <= PARTY_SIZE);
    CreateNPCTrainerPartyFromTrainer(party, trainer);
    for (u32 slot = 0; slot < trainer->partySize; slot++)
    {
        enum Species species = GetMonData(&party[slot], MON_DATA_SPECIES);
        u32 dex = SpeciesToNationalPokedexNum(species);
        EXPECT(dex >= 1 && dex <= 493);
        EXPECT(IsMonShiny(&party[slot]));
        EXPECT_NE(GetSpeciesType(species, 0), TYPE_FAIRY);
        EXPECT_NE(GetSpeciesType(species, 1), TYPE_FAIRY);
        u32 total = 0;
        for (u32 stat = 0; stat < NUM_STATS; stat++)
        {
            u32 ev = GetMonData(&party[slot], MON_DATA_HP_EV + stat);
            EXPECT(ev <= 252);
            total += ev;
        }
        EXPECT(total <= 510);
        for (u32 move = 0; move < MAX_MON_MOVES; move++)
            EXPECT(GetMonData(&party[slot], MON_DATA_MOVE1 + move) <= MOVE_SHADOW_FORCE);
    }
}

TEST("Complete Edition: tournament draw never repeats an opponent and exhausts safely")
{
    u32 used = 0;
    Script_CEStartTournament();
    for (u32 i = 0; i < 32; i++)
    {
        Script_CENextTournament();
        EXPECT(gSpecialVar_Result < 32);
        EXPECT_EQ(used & (1u << gSpecialVar_Result), 0);
        used |= 1u << gSpecialVar_Result;
    }
    EXPECT_EQ(used, 0xFFFFFFFF);
    Script_CENextTournament();
    EXPECT_EQ(gSpecialVar_Result, 0xFFFF);
    Script_CEStartTournament();
    Script_CENextTournament();
    EXPECT(gSpecialVar_Result < 32);
}
