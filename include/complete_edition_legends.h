#ifndef GUARD_COMPLETE_EDITION_LEGENDS_H
#define GUARD_COMPLETE_EDITION_LEGENDS_H

#define CE_LEGEND_COUNT 29

struct CELegend
{
    u16 species;
    u16 caughtFlag;
    u8 level;
    bool8 needsChampion;
    bool8 needsRegis;
    u32 prerequisites;
};

extern const struct CELegend gCELegends[CE_LEGEND_COUNT];
bool32 CompleteEditionLegendIsReady(u32 index);
void Script_CELegendIsReady(void);
void Script_CEPrepareLegend(void);
void Script_CELegendHintsMenu(void);

#endif
