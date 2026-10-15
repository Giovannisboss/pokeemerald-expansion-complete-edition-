#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Complete Edition: sound attacks respect Gen4 and Gen6 Substitute rules")
{
    u32 gen;
    PARAMETRIZE { gen = GEN_4; }
    PARAMETRIZE { gen = GEN_6; }
    GIVEN {
        WITH_CONFIG(B_UPDATED_MOVE_FLAGS, gen);
        PLAYER(SPECIES_WOBBUFFET) { Speed(10); }
        OPPONENT(SPECIES_WOBBUFFET) { MaxHP(400); HP(400); Speed(20); }
    } WHEN {
        TURN { MOVE(opponent, MOVE_SUBSTITUTE); MOVE(player, MOVE_CELEBRATE); }
        TURN { MOVE(player, MOVE_HYPER_VOICE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SUBSTITUTE, opponent);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_HYPER_VOICE, player);
        if (gen == GEN_4)
            MESSAGE("The substitute took damage for the opposing Wobbuffet!");
        else
            HP_BAR(opponent);
    } THEN {
        if (gen == GEN_4)
            EXPECT_EQ(opponent->hp, 300);
        else
            EXPECT_LT(opponent->hp, 300);
    }
}

SINGLE_BATTLE_TEST("Complete Edition: ability weather remains permanent in Gen4 and expires in Gen6")
{
    u32 gen;
    PARAMETRIZE { gen = GEN_4; }
    PARAMETRIZE { gen = GEN_6; }
    GIVEN {
        WITH_CONFIG(B_ABILITY_WEATHER, gen);
        PLAYER(SPECIES_POLITOED) { Ability(ABILITY_DRIZZLE); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN {}
        TURN {}
        TURN {}
        TURN {}
        TURN {}
        TURN {}
    } SCENE {
        ABILITY_POPUP(player, ABILITY_DRIZZLE);
        MESSAGE("It started to rain!");
        if (gen == GEN_4)
            NOT MESSAGE("The rain stopped.");
        else
            MESSAGE("The rain stopped.");
    } THEN {
        EXPECT_EQ(!!(gBattleWeather & B_WEATHER_RAIN), gen == GEN_4);
    }
}

SINGLE_BATTLE_TEST("Complete Edition: Zen Mode Skill Swap follows Gen4 and Gen7 rules")
{
    u32 gen;
    PARAMETRIZE { gen = GEN_4; }
    PARAMETRIZE { gen = GEN_7; }
    GIVEN {
        WITH_CONFIG(B_UPDATED_ABILITY_DATA, gen);
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_SHADOW_TAG); }
        OPPONENT(SPECIES_DARMANITAN) { Ability(ABILITY_ZEN_MODE); }
    } WHEN {
        TURN { MOVE(player, MOVE_SKILL_SWAP); }
    } SCENE {
        if (gen == GEN_4)
            ANIMATION(ANIM_TYPE_MOVE, MOVE_SKILL_SWAP, player);
        else
            NOT ANIMATION(ANIM_TYPE_MOVE, MOVE_SKILL_SWAP, player);
    } THEN {
        EXPECT_EQ(player->ability, gen == GEN_4 ? ABILITY_ZEN_MODE : ABILITY_SHADOW_TAG);
        EXPECT_EQ(opponent->ability, gen == GEN_4 ? ABILITY_SHADOW_TAG : ABILITY_ZEN_MODE);
    }
}
