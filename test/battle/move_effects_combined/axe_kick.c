#include "global.h"
#include "test/battle.h"

ASSUMPTIONS
{
    ASSUME(GetMoveEffect(MOVE_AXE_KICK) == EFFECT_RECOIL_IF_MISS);
    ASSUME(MoveHasAdditionalEffect(MOVE_AXE_KICK, MOVE_EFFECT_CONFUSION) == TRUE);
}

SINGLE_BATTLE_TEST("Axe Kick confuses the target")
{
    GIVEN {
        WITH_CONFIG(B_RECOIL_IF_MISS_DMG, GEN_5);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_AXE_KICK); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_AXE_KICK, player);
        ANIMATION(ANIM_TYPE_STATUS, B_ANIM_STATUS_CONFUSION, opponent);
        MESSAGE("The opposing Wobbuffet became confused!");
    }
}

SINGLE_BATTLE_TEST("Axe Kick deals damage half the hp to user if def battler protected")
{
    GIVEN {
        WITH_CONFIG(B_RECOIL_IF_MISS_DMG, GEN_5);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponent, MOVE_PROTECT); MOVE(player, MOVE_AXE_KICK); }
    } SCENE {
        s32 maxHP = GetMonData(&PLAYER_PARTY[0], MON_DATA_MAX_HP);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_PROTECT, opponent);
        MESSAGE("The opposing Wobbuffet protected itself!");
        MESSAGE("The opposing Wobbuffet protected itself!");
        MESSAGE("Wobbuffet kept going and crashed!");
        HP_BAR(player, hp: maxHP / 2);
    }
}

SINGLE_BATTLE_TEST("Axe Kick deals damage half the hp to user if it fails")
{
    GIVEN {
        WITH_CONFIG(B_RECOIL_IF_MISS_DMG, GEN_5);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_AXE_KICK, hit: FALSE); }
    } SCENE {
        s32 maxHP = GetMonData(&PLAYER_PARTY[0], MON_DATA_MAX_HP);
        MESSAGE("Wobbuffet used Axe Kick!");
        MESSAGE("The opposing Wobbuffet avoided the attack!");
        MESSAGE("Wobbuffet kept going and crashed!");
        HP_BAR(player, hp: maxHP / 2);
    }
}

SINGLE_BATTLE_TEST("Axe Kick still deals crash damage when boosted by Sheer Force")
{
    enum Ability ability;

    PARAMETRIZE { ability = ABILITY_SHEER_FORCE; }
    PARAMETRIZE { ability = ABILITY_INTIMIDATE; }

    GIVEN {
        WITH_CONFIG(B_RECOIL_IF_MISS_DMG, GEN_5);
        ASSUME(MoveIsAffectedBySheerForce(MOVE_AXE_KICK));
        PLAYER(SPECIES_TAUROS) { Ability(ability); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_AXE_KICK, hit: FALSE); }
    } SCENE {
        s32 maxHP = GetMonData(&PLAYER_PARTY[0], MON_DATA_MAX_HP);
        MESSAGE("Tauros used Axe Kick!");
        MESSAGE("The opposing Wobbuffet avoided the attack!");
        MESSAGE("Tauros kept going and crashed!");
        HP_BAR(player, hp: maxHP / 2);
    }
}
