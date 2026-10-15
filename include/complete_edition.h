#ifndef GUARD_COMPLETE_EDITION_H
#define GUARD_COMPLETE_EDITION_H

// Results shared by the training-service script and its native operations.
#define CE_SERVICE_OK 0
#define CE_SERVICE_INVALID 1
#define CE_SERVICE_NO_CAP 2
#define CE_SERVICE_EV_LIMIT 3
#define CE_SERVICE_NO_CHANGE 4

bool32 CompleteEditionSetNature(struct Pokemon *mon, u32 nature);
u32 CompleteEditionTrainIV(struct Pokemon *mon, u32 stat, bool32 allStats);
u32 CompleteEditionSetEV(struct Pokemon *mon, u32 stat, u32 value);
void CompleteEditionResetEVs(struct Pokemon *mon);
void Script_CompleteEditionTraining(void);

#endif
