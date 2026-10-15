#include "global.h"
#include "event_data.h"
#include "random.h"
#include "complete_edition_tournament.h"

static EWRAM_DATA u32 sTournamentUsed = 0;

void Script_CEStartTournament(void)
{
    sTournamentUsed = 0;
}

void Script_CENextTournament(void)
{
    u32 opponent;
    if (sTournamentUsed == 0xFFFFFFFF)
    {
        gSpecialVar_Result = 0xFFFF;
        return;
    }
    do {
        opponent = Random() % 32;
    } while (sTournamentUsed & (1u << opponent));
    sTournamentUsed |= 1u << opponent;
    gSpecialVar_Result = opponent;
}
