CE_Visitor_0::
	lock
	faceplayer
	goto_if_unset FLAG_BADGE01_GET, CE_Battles_NotReady
	msgbox CE_Battles_Text_Visitors, MSGBOX_DEFAULT
	dynmultipush CE_Battles_Text_BROCK, 0
	dynmultipush CE_Battles_Text_FALKNER, 1
	dynmultipush CE_Battles_Text_ROARK, 2
	dynmultistack 0, 0, FALSE, 7, FALSE, 0, NULL
	goto_if_eq VAR_RESULT, 0, CE_Visitor_Battle_0_0
	goto_if_eq VAR_RESULT, 1, CE_Visitor_Battle_0_1
	goto_if_eq VAR_RESULT, 2, CE_Visitor_Battle_0_2
	goto CE_Battles_End
CE_Visitor_Battle_0_0:
	trainerbattle_no_intro TRAINER_CE_VISITOR_BROCK, CE_Battles_Text_Defeat
	goto CE_Battles_End
CE_Visitor_Battle_0_1:
	trainerbattle_no_intro TRAINER_CE_VISITOR_FALKNER, CE_Battles_Text_Defeat
	goto CE_Battles_End
CE_Visitor_Battle_0_2:
	trainerbattle_no_intro TRAINER_CE_VISITOR_ROARK, CE_Battles_Text_Defeat
	goto CE_Battles_End
CE_Visitor_1::
	lock
	faceplayer
	goto_if_unset FLAG_BADGE02_GET, CE_Battles_NotReady
	msgbox CE_Battles_Text_Visitors, MSGBOX_DEFAULT
	dynmultipush CE_Battles_Text_MISTY, 0
	dynmultipush CE_Battles_Text_BUGSY, 1
	dynmultipush CE_Battles_Text_GARDENIA, 2
	dynmultistack 0, 0, FALSE, 7, FALSE, 0, NULL
	goto_if_eq VAR_RESULT, 0, CE_Visitor_Battle_1_0
	goto_if_eq VAR_RESULT, 1, CE_Visitor_Battle_1_1
	goto_if_eq VAR_RESULT, 2, CE_Visitor_Battle_1_2
	goto CE_Battles_End
CE_Visitor_Battle_1_0:
	trainerbattle_no_intro TRAINER_CE_VISITOR_MISTY, CE_Battles_Text_Defeat
	goto CE_Battles_End
CE_Visitor_Battle_1_1:
	trainerbattle_no_intro TRAINER_CE_VISITOR_BUGSY, CE_Battles_Text_Defeat
	goto CE_Battles_End
CE_Visitor_Battle_1_2:
	trainerbattle_no_intro TRAINER_CE_VISITOR_GARDENIA, CE_Battles_Text_Defeat
	goto CE_Battles_End
CE_Visitor_2::
	lock
	faceplayer
	goto_if_unset FLAG_BADGE03_GET, CE_Battles_NotReady
	msgbox CE_Battles_Text_Visitors, MSGBOX_DEFAULT
	dynmultipush CE_Battles_Text_LT__SURGE, 0
	dynmultipush CE_Battles_Text_WHITNEY, 1
	dynmultipush CE_Battles_Text_MAYLENE, 2
	dynmultistack 0, 0, FALSE, 7, FALSE, 0, NULL
	goto_if_eq VAR_RESULT, 0, CE_Visitor_Battle_2_0
	goto_if_eq VAR_RESULT, 1, CE_Visitor_Battle_2_1
	goto_if_eq VAR_RESULT, 2, CE_Visitor_Battle_2_2
	goto CE_Battles_End
CE_Visitor_Battle_2_0:
	trainerbattle_no_intro TRAINER_CE_VISITOR_LT__SURGE, CE_Battles_Text_Defeat
	goto CE_Battles_End
CE_Visitor_Battle_2_1:
	trainerbattle_no_intro TRAINER_CE_VISITOR_WHITNEY, CE_Battles_Text_Defeat
	goto CE_Battles_End
CE_Visitor_Battle_2_2:
	trainerbattle_no_intro TRAINER_CE_VISITOR_MAYLENE, CE_Battles_Text_Defeat
	goto CE_Battles_End
CE_Visitor_3::
	lock
	faceplayer
	goto_if_unset FLAG_BADGE04_GET, CE_Battles_NotReady
	msgbox CE_Battles_Text_Visitors, MSGBOX_DEFAULT
	dynmultipush CE_Battles_Text_ERIKA, 0
	dynmultipush CE_Battles_Text_MORTY, 1
	dynmultipush CE_Battles_Text_WAKE, 2
	dynmultistack 0, 0, FALSE, 7, FALSE, 0, NULL
	goto_if_eq VAR_RESULT, 0, CE_Visitor_Battle_3_0
	goto_if_eq VAR_RESULT, 1, CE_Visitor_Battle_3_1
	goto_if_eq VAR_RESULT, 2, CE_Visitor_Battle_3_2
	goto CE_Battles_End
CE_Visitor_Battle_3_0:
	trainerbattle_no_intro TRAINER_CE_VISITOR_ERIKA, CE_Battles_Text_Defeat
	goto CE_Battles_End
CE_Visitor_Battle_3_1:
	trainerbattle_no_intro TRAINER_CE_VISITOR_MORTY, CE_Battles_Text_Defeat
	goto CE_Battles_End
CE_Visitor_Battle_3_2:
	trainerbattle_no_intro TRAINER_CE_VISITOR_WAKE, CE_Battles_Text_Defeat
	goto CE_Battles_End
CE_Visitor_4::
	lock
	faceplayer
	goto_if_unset FLAG_BADGE05_GET, CE_Battles_NotReady
	msgbox CE_Battles_Text_Visitors, MSGBOX_DEFAULT
	dynmultipush CE_Battles_Text_KOGA, 0
	dynmultipush CE_Battles_Text_CHUCK, 1
	dynmultipush CE_Battles_Text_FANTINA, 2
	dynmultistack 0, 0, FALSE, 7, FALSE, 0, NULL
	goto_if_eq VAR_RESULT, 0, CE_Visitor_Battle_4_0
	goto_if_eq VAR_RESULT, 1, CE_Visitor_Battle_4_1
	goto_if_eq VAR_RESULT, 2, CE_Visitor_Battle_4_2
	goto CE_Battles_End
CE_Visitor_Battle_4_0:
	trainerbattle_no_intro TRAINER_CE_VISITOR_KOGA, CE_Battles_Text_Defeat
	goto CE_Battles_End
CE_Visitor_Battle_4_1:
	trainerbattle_no_intro TRAINER_CE_VISITOR_CHUCK, CE_Battles_Text_Defeat
	goto CE_Battles_End
CE_Visitor_Battle_4_2:
	trainerbattle_no_intro TRAINER_CE_VISITOR_FANTINA, CE_Battles_Text_Defeat
	goto CE_Battles_End
CE_Visitor_5::
	lock
	faceplayer
	goto_if_unset FLAG_BADGE06_GET, CE_Battles_NotReady
	msgbox CE_Battles_Text_Visitors, MSGBOX_DEFAULT
	dynmultipush CE_Battles_Text_SABRINA, 0
	dynmultipush CE_Battles_Text_JASMINE, 1
	dynmultipush CE_Battles_Text_BYRON, 2
	dynmultistack 0, 0, FALSE, 7, FALSE, 0, NULL
	goto_if_eq VAR_RESULT, 0, CE_Visitor_Battle_5_0
	goto_if_eq VAR_RESULT, 1, CE_Visitor_Battle_5_1
	goto_if_eq VAR_RESULT, 2, CE_Visitor_Battle_5_2
	goto CE_Battles_End
CE_Visitor_Battle_5_0:
	trainerbattle_no_intro TRAINER_CE_VISITOR_SABRINA, CE_Battles_Text_Defeat
	goto CE_Battles_End
CE_Visitor_Battle_5_1:
	trainerbattle_no_intro TRAINER_CE_VISITOR_JASMINE, CE_Battles_Text_Defeat
	goto CE_Battles_End
CE_Visitor_Battle_5_2:
	trainerbattle_no_intro TRAINER_CE_VISITOR_BYRON, CE_Battles_Text_Defeat
	goto CE_Battles_End
CE_Visitor_6::
	lock
	faceplayer
	goto_if_unset FLAG_BADGE07_GET, CE_Battles_NotReady
	msgbox CE_Battles_Text_Visitors, MSGBOX_DEFAULT
	dynmultipush CE_Battles_Text_BLAINE, 0
	dynmultipush CE_Battles_Text_PRYCE, 1
	dynmultipush CE_Battles_Text_CANDICE, 2
	dynmultistack 0, 0, FALSE, 7, FALSE, 0, NULL
	goto_if_eq VAR_RESULT, 0, CE_Visitor_Battle_6_0
	goto_if_eq VAR_RESULT, 1, CE_Visitor_Battle_6_1
	goto_if_eq VAR_RESULT, 2, CE_Visitor_Battle_6_2
	goto CE_Battles_End
CE_Visitor_Battle_6_0:
	trainerbattle_no_intro TRAINER_CE_VISITOR_BLAINE, CE_Battles_Text_Defeat
	goto CE_Battles_End
CE_Visitor_Battle_6_1:
	trainerbattle_no_intro TRAINER_CE_VISITOR_PRYCE, CE_Battles_Text_Defeat
	goto CE_Battles_End
CE_Visitor_Battle_6_2:
	trainerbattle_no_intro TRAINER_CE_VISITOR_CANDICE, CE_Battles_Text_Defeat
	goto CE_Battles_End
CE_Visitor_7::
	lock
	faceplayer
	goto_if_unset FLAG_BADGE08_GET, CE_Battles_NotReady
	msgbox CE_Battles_Text_Visitors, MSGBOX_DEFAULT
	dynmultipush CE_Battles_Text_GIOVANNI, 0
	dynmultipush CE_Battles_Text_CLAIR, 1
	dynmultipush CE_Battles_Text_VOLKNER, 2
	dynmultistack 0, 0, FALSE, 7, FALSE, 0, NULL
	goto_if_eq VAR_RESULT, 0, CE_Visitor_Battle_7_0
	goto_if_eq VAR_RESULT, 1, CE_Visitor_Battle_7_1
	goto_if_eq VAR_RESULT, 2, CE_Visitor_Battle_7_2
	goto CE_Battles_End
CE_Visitor_Battle_7_0:
	trainerbattle_no_intro TRAINER_CE_VISITOR_GIOVANNI, CE_Battles_Text_Defeat
	goto CE_Battles_End
CE_Visitor_Battle_7_1:
	trainerbattle_no_intro TRAINER_CE_VISITOR_CLAIR, CE_Battles_Text_Defeat
	goto CE_Battles_End
CE_Visitor_Battle_7_2:
	trainerbattle_no_intro TRAINER_CE_VISITOR_VOLKNER, CE_Battles_Text_Defeat
	goto CE_Battles_End
CE_Tournament_EventScript::
	lock
	faceplayer
	goto_if_unset FLAG_SYS_GAME_CLEAR, CE_Battles_NotChampion
	msgbox CE_Battles_Text_Tournament, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CE_Battles_End
	callnative Script_CEStartTournament
	setvar VAR_TEMP_2, 0
CE_Tournament_Round:
	special HealPlayerParty
	callnative Script_CENextTournament
	goto_if_eq VAR_RESULT, 0, CE_Tournament_Battle_0
	goto_if_eq VAR_RESULT, 1, CE_Tournament_Battle_1
	goto_if_eq VAR_RESULT, 2, CE_Tournament_Battle_2
	goto_if_eq VAR_RESULT, 3, CE_Tournament_Battle_3
	goto_if_eq VAR_RESULT, 4, CE_Tournament_Battle_4
	goto_if_eq VAR_RESULT, 5, CE_Tournament_Battle_5
	goto_if_eq VAR_RESULT, 6, CE_Tournament_Battle_6
	goto_if_eq VAR_RESULT, 7, CE_Tournament_Battle_7
	goto_if_eq VAR_RESULT, 8, CE_Tournament_Battle_8
	goto_if_eq VAR_RESULT, 9, CE_Tournament_Battle_9
	goto_if_eq VAR_RESULT, 10, CE_Tournament_Battle_10
	goto_if_eq VAR_RESULT, 11, CE_Tournament_Battle_11
	goto_if_eq VAR_RESULT, 12, CE_Tournament_Battle_12
	goto_if_eq VAR_RESULT, 13, CE_Tournament_Battle_13
	goto_if_eq VAR_RESULT, 14, CE_Tournament_Battle_14
	goto_if_eq VAR_RESULT, 15, CE_Tournament_Battle_15
	goto_if_eq VAR_RESULT, 16, CE_Tournament_Battle_16
	goto_if_eq VAR_RESULT, 17, CE_Tournament_Battle_17
	goto_if_eq VAR_RESULT, 18, CE_Tournament_Battle_18
	goto_if_eq VAR_RESULT, 19, CE_Tournament_Battle_19
	goto_if_eq VAR_RESULT, 20, CE_Tournament_Battle_20
	goto_if_eq VAR_RESULT, 21, CE_Tournament_Battle_21
	goto_if_eq VAR_RESULT, 22, CE_Tournament_Battle_22
	goto_if_eq VAR_RESULT, 23, CE_Tournament_Battle_23
	goto_if_eq VAR_RESULT, 24, CE_Tournament_Battle_24
	goto_if_eq VAR_RESULT, 25, CE_Tournament_Battle_25
	goto_if_eq VAR_RESULT, 26, CE_Tournament_Battle_26
	goto_if_eq VAR_RESULT, 27, CE_Tournament_Battle_27
	goto_if_eq VAR_RESULT, 28, CE_Tournament_Battle_28
	goto_if_eq VAR_RESULT, 29, CE_Tournament_Battle_29
	goto_if_eq VAR_RESULT, 30, CE_Tournament_Battle_30
	goto_if_eq VAR_RESULT, 31, CE_Tournament_Battle_31
CE_Tournament_AfterBattle:
	addvar VAR_TEMP_2, 1
	goto_if_lt VAR_TEMP_2, 8, CE_Tournament_Round
	msgbox CE_Battles_Text_Winner, MSGBOX_DEFAULT
	giveitem ITEM_GOLD_BOTTLE_CAP, 1
	goto CE_Battles_End
CE_Tournament_Battle_0:
	trainerbattle_no_intro TRAINER_CE_PWT_BROCK, CE_Battles_Text_Defeat
	goto CE_Tournament_AfterBattle
CE_Tournament_Battle_1:
	trainerbattle_no_intro TRAINER_CE_PWT_MISTY, CE_Battles_Text_Defeat
	goto CE_Tournament_AfterBattle
CE_Tournament_Battle_2:
	trainerbattle_no_intro TRAINER_CE_PWT_LT__SURGE, CE_Battles_Text_Defeat
	goto CE_Tournament_AfterBattle
CE_Tournament_Battle_3:
	trainerbattle_no_intro TRAINER_CE_PWT_ERIKA, CE_Battles_Text_Defeat
	goto CE_Tournament_AfterBattle
CE_Tournament_Battle_4:
	trainerbattle_no_intro TRAINER_CE_PWT_KOGA, CE_Battles_Text_Defeat
	goto CE_Tournament_AfterBattle
CE_Tournament_Battle_5:
	trainerbattle_no_intro TRAINER_CE_PWT_SABRINA, CE_Battles_Text_Defeat
	goto CE_Tournament_AfterBattle
CE_Tournament_Battle_6:
	trainerbattle_no_intro TRAINER_CE_PWT_BLAINE, CE_Battles_Text_Defeat
	goto CE_Tournament_AfterBattle
CE_Tournament_Battle_7:
	trainerbattle_no_intro TRAINER_CE_PWT_GIOVANNI, CE_Battles_Text_Defeat
	goto CE_Tournament_AfterBattle
CE_Tournament_Battle_8:
	trainerbattle_no_intro TRAINER_CE_PWT_FALKNER, CE_Battles_Text_Defeat
	goto CE_Tournament_AfterBattle
CE_Tournament_Battle_9:
	trainerbattle_no_intro TRAINER_CE_PWT_BUGSY, CE_Battles_Text_Defeat
	goto CE_Tournament_AfterBattle
CE_Tournament_Battle_10:
	trainerbattle_no_intro TRAINER_CE_PWT_WHITNEY, CE_Battles_Text_Defeat
	goto CE_Tournament_AfterBattle
CE_Tournament_Battle_11:
	trainerbattle_no_intro TRAINER_CE_PWT_MORTY, CE_Battles_Text_Defeat
	goto CE_Tournament_AfterBattle
CE_Tournament_Battle_12:
	trainerbattle_no_intro TRAINER_CE_PWT_CHUCK, CE_Battles_Text_Defeat
	goto CE_Tournament_AfterBattle
CE_Tournament_Battle_13:
	trainerbattle_no_intro TRAINER_CE_PWT_JASMINE, CE_Battles_Text_Defeat
	goto CE_Tournament_AfterBattle
CE_Tournament_Battle_14:
	trainerbattle_no_intro TRAINER_CE_PWT_PRYCE, CE_Battles_Text_Defeat
	goto CE_Tournament_AfterBattle
CE_Tournament_Battle_15:
	trainerbattle_no_intro TRAINER_CE_PWT_CLAIR, CE_Battles_Text_Defeat
	goto CE_Tournament_AfterBattle
CE_Tournament_Battle_16:
	trainerbattle_no_intro TRAINER_CE_PWT_ROARK, CE_Battles_Text_Defeat
	goto CE_Tournament_AfterBattle
CE_Tournament_Battle_17:
	trainerbattle_no_intro TRAINER_CE_PWT_GARDENIA, CE_Battles_Text_Defeat
	goto CE_Tournament_AfterBattle
CE_Tournament_Battle_18:
	trainerbattle_no_intro TRAINER_CE_PWT_MAYLENE, CE_Battles_Text_Defeat
	goto CE_Tournament_AfterBattle
CE_Tournament_Battle_19:
	trainerbattle_no_intro TRAINER_CE_PWT_WAKE, CE_Battles_Text_Defeat
	goto CE_Tournament_AfterBattle
CE_Tournament_Battle_20:
	trainerbattle_no_intro TRAINER_CE_PWT_FANTINA, CE_Battles_Text_Defeat
	goto CE_Tournament_AfterBattle
CE_Tournament_Battle_21:
	trainerbattle_no_intro TRAINER_CE_PWT_BYRON, CE_Battles_Text_Defeat
	goto CE_Tournament_AfterBattle
CE_Tournament_Battle_22:
	trainerbattle_no_intro TRAINER_CE_PWT_CANDICE, CE_Battles_Text_Defeat
	goto CE_Tournament_AfterBattle
CE_Tournament_Battle_23:
	trainerbattle_no_intro TRAINER_CE_PWT_VOLKNER, CE_Battles_Text_Defeat
	goto CE_Tournament_AfterBattle
CE_Tournament_Battle_24:
	trainerbattle_no_intro TRAINER_CE_PWT_ROXANNE, CE_Battles_Text_Defeat
	goto CE_Tournament_AfterBattle
CE_Tournament_Battle_25:
	trainerbattle_no_intro TRAINER_CE_PWT_BRAWLY, CE_Battles_Text_Defeat
	goto CE_Tournament_AfterBattle
CE_Tournament_Battle_26:
	trainerbattle_no_intro TRAINER_CE_PWT_WATTSON, CE_Battles_Text_Defeat
	goto CE_Tournament_AfterBattle
CE_Tournament_Battle_27:
	trainerbattle_no_intro TRAINER_CE_PWT_FLANNERY, CE_Battles_Text_Defeat
	goto CE_Tournament_AfterBattle
CE_Tournament_Battle_28:
	trainerbattle_no_intro TRAINER_CE_PWT_NORMAN, CE_Battles_Text_Defeat
	goto CE_Tournament_AfterBattle
CE_Tournament_Battle_29:
	trainerbattle_no_intro TRAINER_CE_PWT_WINONA, CE_Battles_Text_Defeat
	goto CE_Tournament_AfterBattle
CE_Tournament_Battle_30:
	trainerbattle_no_intro TRAINER_CE_PWT_TATE_LIZA, CE_Battles_Text_Defeat
	goto CE_Tournament_AfterBattle
CE_Tournament_Battle_31:
	trainerbattle_no_intro TRAINER_CE_PWT_JUAN, CE_Battles_Text_Defeat
	goto CE_Tournament_AfterBattle
CE_Superboss_EventScript::
	lock
	faceplayer
	goto_if_unset FLAG_SYS_GAME_CLEAR, CE_Battles_NotChampion
	msgbox CE_Battles_Text_Superboss, MSGBOX_DEFAULT
	dynmultipush CE_Battles_Text_RED, 0
	dynmultipush CE_Battles_Text_BLUE, 1
	dynmultipush CE_Battles_Text_SILVER, 2
	dynmultipush CE_Battles_Text_GOLD, 3
	dynmultistack 0, 0, FALSE, 7, FALSE, 0, NULL
	goto_if_eq VAR_RESULT, 0, CE_Superboss_Battle_0
	goto_if_eq VAR_RESULT, 1, CE_Superboss_Battle_1
	goto_if_eq VAR_RESULT, 2, CE_Superboss_Battle_2
	goto_if_eq VAR_RESULT, 3, CE_Superboss_Battle_3
	goto CE_Battles_End
CE_Superboss_Battle_0:
	trainerbattle_no_intro TRAINER_CE_SUPER_RED, CE_Battles_Text_Defeat
	goto CE_Battles_End
CE_Superboss_Battle_1:
	trainerbattle_no_intro TRAINER_CE_SUPER_BLUE, CE_Battles_Text_Defeat
	goto CE_Battles_End
CE_Superboss_Battle_2:
	trainerbattle_no_intro TRAINER_CE_SUPER_SILVER, CE_Battles_Text_Defeat
	goto CE_Battles_End
CE_Superboss_Battle_3:
	trainerbattle_no_intro TRAINER_CE_SUPER_GOLD, CE_Battles_Text_Defeat
	goto CE_Battles_End
CE_Battles_NotReady:
	msgbox CE_Battles_Text_NotReady, MSGBOX_DEFAULT
	goto CE_Battles_End
CE_Battles_NotChampion:
	msgbox CE_Battles_Text_NotChampion, MSGBOX_DEFAULT
CE_Battles_End:
	release
	end

CE_Battles_Text_Visitors:
	.string "Visiting GYM LEADERS are here!\nWould you like an optional battle?$"

CE_Battles_Text_BROCK:
	.string "BROCK$"

CE_Battles_Text_FALKNER:
	.string "FALKNER$"

CE_Battles_Text_ROARK:
	.string "ROARK$"

CE_Battles_Text_MISTY:
	.string "MISTY$"

CE_Battles_Text_BUGSY:
	.string "BUGSY$"

CE_Battles_Text_GARDENIA:
	.string "GARDENIA$"

CE_Battles_Text_LT__SURGE:
	.string "LT. SURGE$"

CE_Battles_Text_WHITNEY:
	.string "WHITNEY$"

CE_Battles_Text_MAYLENE:
	.string "MAYLENE$"

CE_Battles_Text_ERIKA:
	.string "ERIKA$"

CE_Battles_Text_MORTY:
	.string "MORTY$"

CE_Battles_Text_WAKE:
	.string "WAKE$"

CE_Battles_Text_KOGA:
	.string "KOGA$"

CE_Battles_Text_CHUCK:
	.string "CHUCK$"

CE_Battles_Text_FANTINA:
	.string "FANTINA$"

CE_Battles_Text_SABRINA:
	.string "SABRINA$"

CE_Battles_Text_JASMINE:
	.string "JASMINE$"

CE_Battles_Text_BYRON:
	.string "BYRON$"

CE_Battles_Text_BLAINE:
	.string "BLAINE$"

CE_Battles_Text_PRYCE:
	.string "PRYCE$"

CE_Battles_Text_CANDICE:
	.string "CANDICE$"

CE_Battles_Text_GIOVANNI:
	.string "GIOVANNI$"

CE_Battles_Text_CLAIR:
	.string "CLAIR$"

CE_Battles_Text_VOLKNER:
	.string "VOLKNER$"

CE_Battles_Text_RED:
	.string "RED$"

CE_Battles_Text_BLUE:
	.string "BLUE$"

CE_Battles_Text_SILVER:
	.string "SILVER$"

CE_Battles_Text_GOLD:
	.string "GOLD$"

CE_Battles_Text_Defeat:
	.string "A remarkable battle! You earned that win.$"

CE_Battles_Text_NotReady:
	.string "Earn the matching GYM BADGE first.\nOur visitors will wait for you.$"

CE_Battles_Text_NotChampion:
	.string "This challenge is for the CHAMPION.$"

CE_Battles_Text_Tournament:
	.string "WORLD TOURNAMENT: eight rounds!\n32 regional GYM LEADERS may enter.\pOpen level. Opponents are level 75-77.\nYour party is healed between rounds.\pWin all eight to earn a Gold Bottle Cap.\nEnter now?$"

CE_Battles_Text_Winner:
	.string "You are the tournament winner!$"

CE_Battles_Text_Superboss:
	.string "RED, BLUE, SILVER and GOLD await!\nTheir teams are level 95-97.\pThese challenges can be repeated.\nChoose your opponent!$"
