#include "global.h"
#include "test/battle.h"
#include "battle_stat_change.h"
#include "battle_dynamax.h"
#include "battle_gimmick.h"

SINGLE_BATTLE_TEST("Complete Edition: Dynamax and Gigantamax cannot activate on either side")
{
    GIVEN {
        WITH_CONFIG(B_DYNAMAX_ENABLED, FALSE);
        PLAYER(SPECIES_PIKACHU) { DynamaxLevel(10); GigantamaxFactor(TRUE); }
        OPPONENT(SPECIES_PIKACHU) { DynamaxLevel(10); GigantamaxFactor(TRUE); }
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE); MOVE(opponent, MOVE_CELEBRATE); }
    } THEN {
        u32 playerHP = player->hp, opponentHP = opponent->hp;
        EXPECT_EQ(GetConfig(B_DYNAMAX_ENABLED), FALSE);
        AssignUsableGimmicks();
        for (u32 battler = 0; battler < gBattlersCount; battler++)
        {
            EXPECT_EQ(CanDynamax(battler), FALSE);
            EXPECT_EQ(CanActivateGimmick(battler, GIMMICK_DYNAMAX), FALSE);
            EXPECT_NE(gBattleStruct->gimmick.usableGimmick[battler], GIMMICK_DYNAMAX);
            ActivateDynamax(battler); // Direct activation must also be harmless.
            EXPECT_EQ(GetActiveGimmick(battler), GIMMICK_NONE);
            EXPECT_EQ(gBattleStruct->dynamax.dynamaxTurns[battler], 0);
        }
        EXPECT_EQ(player->species, SPECIES_PIKACHU);
        EXPECT_EQ(opponent->species, SPECIES_PIKACHU);
        EXPECT_EQ(player->hp, playerHP);
        EXPECT_EQ(opponent->hp, opponentHP);
    }
}

SINGLE_BATTLE_TEST("Complete Edition: Gen4 Mental Herb retains its original limited effect")
{
    enum Move move;
    PARAMETRIZE { move = MOVE_TORMENT; }
    PARAMETRIZE { move = MOVE_TAUNT; }
    PARAMETRIZE { move = MOVE_HEAL_BLOCK; }
    GIVEN {
        WITH_CONFIG(B_MENTAL_HERB, GEN_4);
        PLAYER(SPECIES_WOBBUFFET) { Item(ITEM_MENTAL_HERB); Speed(2); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); }
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE); MOVE(opponent, move); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, move, opponent);
        NOT ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_HELD_ITEM_EFFECT, player);
    } THEN {
        EXPECT_EQ(player->item, ITEM_MENTAL_HERB);
        if (move == MOVE_TORMENT)
            EXPECT(player->volatiles.torment);
        else if (move == MOVE_TAUNT)
            EXPECT(player->volatiles.tauntTimer);
        else
            EXPECT(player->volatiles.healBlockTimer);
    }
}

SINGLE_BATTLE_TEST("Complete Edition: Gen4 Illuminate does not block accuracy reductions")
{
    GIVEN {
        WITH_CONFIG(B_ILLUMINATE_EFFECT, GEN_4);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_STARYU) { Ability(ABILITY_ILLUMINATE); }
    } WHEN {
        TURN { MOVE(player, MOVE_SAND_ATTACK); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SAND_ATTACK, player);
        MESSAGE("The opposing Staryu's accuracy fell!");
    } THEN {
        EXPECT_EQ(opponent->statStages[STAT_ACC], DEFAULT_STAT_STAGE - 1);
    }
}

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

SINGLE_BATTLE_TEST("Complete Edition: Gen4 Growth raises only Special Attack even in sunlight")
{
    enum Move weatherMove;
    PARAMETRIZE { weatherMove = MOVE_CELEBRATE; }
    PARAMETRIZE { weatherMove = MOVE_SUNNY_DAY; }
    GIVEN {
        PLAYER(SPECIES_BULBASAUR);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, weatherMove); }
        TURN { MOVE(player, MOVE_GROWTH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_GROWTH, player);
        MESSAGE("Bulbasaur's Sp. Atk rose!");
    } THEN {
        EXPECT_EQ(player->statStages[STAT_ATK], DEFAULT_STAT_STAGE);
        EXPECT_EQ(player->statStages[STAT_SPATK], DEFAULT_STAT_STAGE + 1);
    }
}

SINGLE_BATTLE_TEST("Complete Edition: Gen4 Embargo is not reflected by Magic Coat")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_MAGIC_COAT); MOVE(opponent, MOVE_EMBARGO); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_MAGIC_COAT, player);
        MESSAGE("Wobbuffet can't use items anymore!");
    } THEN {
        EXPECT_GT((u32)player->volatiles.embargoTimer, 0);
        EXPECT_EQ((u32)opponent->volatiles.embargoTimer, 0);
    }
}

SINGLE_BATTLE_TEST("Complete Edition: Gen4 Sheer Cold retains 30 percent accuracy for non Ice users")
{
    PASSES_RANDOMLY(30, 100, RNG_ACCURACY);
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_SHEER_COLD); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SHEER_COLD, player);
        HP_BAR(opponent, hp: 0);
    }
}

SINGLE_BATTLE_TEST("Complete Edition: Gen4 Transform preserves Ditto identity after fainting")
{
    GIVEN {
        PLAYER(SPECIES_DITTO) { HP(1); }
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_PIDGEOT);
    } WHEN {
        TURN { MOVE(opponent, MOVE_CELEBRATE); MOVE(player, MOVE_TRANSFORM); }
        TURN { MOVE(opponent, MOVE_SCRATCH); SEND_OUT(player, 1); }
    } THEN {
        EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_SPECIES), SPECIES_DITTO);
    }
}
