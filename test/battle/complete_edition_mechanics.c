#include "global.h"
#include "test/battle.h"
#include "battle_stat_change.h"

SINGLE_BATTLE_TEST("Complete Edition: Gen4 sleep supports one to four immobile turns")
{
    u32 turns;
    PARAMETRIZE { turns = 1; }
    PARAMETRIZE { turns = 2; }
    PARAMETRIZE { turns = 3; }
    PARAMETRIZE { turns = 4; }
    GIVEN {
        WITH_CONFIG(B_SLEEP_TURNS, GEN_4);
        PLAYER(SPECIES_WOBBUFFET) { Speed(2); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); }
    } WHEN {
        TURN { MOVE(player, MOVE_HYPNOSIS, WITH_RNG(RNG_SLEEP_TURNS, turns + 1)); MOVE(opponent, MOVE_CELEBRATE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_HYPNOSIS, player);
        MESSAGE("The opposing Wobbuffet fell asleep!");
        STATUS_ICON(opponent, sleep: TRUE);
        NOT ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, opponent);
    } THEN {
        EXPECT_EQ(opponent->status1 & STATUS1_SLEEP, STATUS1_SLEEP_TURN(turns));
    }
}

SINGLE_BATTLE_TEST("Complete Edition: empty stat-change queues advance to the next battler")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } THEN {
        struct BattleCalcValues cv = {
            .battlerAtk = 0,
            .battlerDef = 0,
            .move = MOVE_CHARGE,
            .moveEffect = EFFECT_CHARGE,
        };
        struct StatChange st = {0};
        EXPECT_EQ(TryStatChange(&cv, &st), STAT_CHANGE_DIDNT_WORK);
        EXPECT(st.nextBattler);
    }
}

SINGLE_BATTLE_TEST("Complete Edition: Charge raises Special Defense and battle continues")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_CHARGE); }
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CHARGE, player);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, player);
        MESSAGE("Wobbuffet's Sp. Def rose!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, player);
        HP_BAR(opponent);
    } THEN {
        EXPECT_EQ(player->statStages[STAT_SPDEF], DEFAULT_STAT_STAGE + 1);
    }
}

SINGLE_BATTLE_TEST("Complete Edition: Charge still completes at maximum Special Defense")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_AMNESIA); }
        TURN { MOVE(player, MOVE_AMNESIA); }
        TURN { MOVE(player, MOVE_AMNESIA); }
        TURN { MOVE(player, MOVE_CHARGE); }
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CHARGE, player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, player);
        HP_BAR(opponent);
    } THEN {
        EXPECT_EQ(player->statStages[STAT_SPDEF], MAX_STAT_STAGE);
    }
}

SINGLE_BATTLE_TEST("Complete Edition: Technician boosts weak moves only", s16 damage)
{
    enum Ability ability;
    enum Move move;
    PARAMETRIZE { ability = ABILITY_SWARM; move = MOVE_SCRATCH; }
    PARAMETRIZE { ability = ABILITY_TECHNICIAN; move = MOVE_SCRATCH; }
    PARAMETRIZE { ability = ABILITY_SWARM; move = MOVE_SLASH; }
    PARAMETRIZE { ability = ABILITY_TECHNICIAN; move = MOVE_SLASH; }
    GIVEN {
        ASSUME(GetMovePower(MOVE_SCRATCH) == 40);
        ASSUME(GetMovePower(MOVE_SLASH) == 70);
        PLAYER(SPECIES_SCYTHER) { Ability(ability); }
        OPPONENT(SPECIES_WOBBUFFET) { MaxHP(999); HP(999); }
    } WHEN {
        TURN { MOVE(player, move); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(1.5), results[1].damage);
        EXPECT_EQ(results[2].damage, results[3].damage);
    }
}

// These run under the production generation defaults. Do not override the
// split or move-data configuration: that would stop testing the release rules.
SINGLE_BATTLE_TEST("Complete Edition: physical Water moves use Attack", s16 damage)
{
    u32 attack;
    PARAMETRIZE { attack = 100; }
    PARAMETRIZE { attack = 200; }
    GIVEN {
        ASSUME(GetMoveCategory(MOVE_AQUA_TAIL) == DAMAGE_CATEGORY_PHYSICAL);
        PLAYER(SPECIES_WOBBUFFET) { Attack(attack); SpAttack(100); }
        OPPONENT(SPECIES_WOBBUFFET) { MaxHP(999); HP(999); }
    } WHEN {
        TURN { MOVE(player, MOVE_AQUA_TAIL); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_AQUA_TAIL, player);
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_GT(results[1].damage, results[0].damage * 3 / 2);
    }
}

SINGLE_BATTLE_TEST("Complete Edition: special Ghost moves use Special Attack", s16 damage)
{
    u32 specialAttack;
    PARAMETRIZE { specialAttack = 100; }
    PARAMETRIZE { specialAttack = 200; }
    GIVEN {
        ASSUME(GetMoveCategory(MOVE_SHADOW_BALL) == DAMAGE_CATEGORY_SPECIAL);
        PLAYER(SPECIES_WOBBUFFET) { Attack(100); SpAttack(specialAttack); }
        OPPONENT(SPECIES_WOBBUFFET) { MaxHP(999); HP(999); }
    } WHEN {
        TURN { MOVE(player, MOVE_SHADOW_BALL); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SHADOW_BALL, player);
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_GT(results[1].damage, results[0].damage * 3 / 2);
    }
}
