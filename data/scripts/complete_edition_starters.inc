CE_Starter_BULBASAUR::
	lock
	faceplayer
	goto_if_unset FLAG_BADGE01_GET, CE_Starter_NotReady
	msgbox CE_Starter_Text_Challenge, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CE_Starter_End
	playmoncry SPECIES_BULBASAUR, CRY_MODE_ENCOUNTER
	waitmoncry
	setwildbattle SPECIES_BULBASAUR, 10
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, CE_Starter_End
	setflag FLAG_CE_STARTER_BULBASAUR
	removeobject VAR_LAST_TALKED
	goto CE_Starter_End

CE_Starter_CHARMANDER::
	lock
	faceplayer
	goto_if_unset FLAG_BADGE03_GET, CE_Starter_NotReady
	msgbox CE_Starter_Text_Challenge, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CE_Starter_End
	playmoncry SPECIES_CHARMANDER, CRY_MODE_ENCOUNTER
	waitmoncry
	setwildbattle SPECIES_CHARMANDER, 20
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, CE_Starter_End
	setflag FLAG_CE_STARTER_CHARMANDER
	removeobject VAR_LAST_TALKED
	goto CE_Starter_End

CE_Starter_SQUIRTLE::
	lock
	faceplayer
	goto_if_unset FLAG_BADGE02_GET, CE_Starter_NotReady
	msgbox CE_Starter_Text_Challenge, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CE_Starter_End
	playmoncry SPECIES_SQUIRTLE, CRY_MODE_ENCOUNTER
	waitmoncry
	setwildbattle SPECIES_SQUIRTLE, 15
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, CE_Starter_End
	setflag FLAG_CE_STARTER_SQUIRTLE
	removeobject VAR_LAST_TALKED
	goto CE_Starter_End

CE_Starter_CHIKORITA::
	lock
	faceplayer
	goto_if_unset FLAG_BADGE03_GET, CE_Starter_NotReady
	msgbox CE_Starter_Text_Challenge, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CE_Starter_End
	playmoncry SPECIES_CHIKORITA, CRY_MODE_ENCOUNTER
	waitmoncry
	setwildbattle SPECIES_CHIKORITA, 18
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, CE_Starter_End
	setflag FLAG_CE_STARTER_CHIKORITA
	removeobject VAR_LAST_TALKED
	goto CE_Starter_End

CE_Starter_CYNDAQUIL::
	lock
	faceplayer
	goto_if_unset FLAG_BADGE04_GET, CE_Starter_NotReady
	msgbox CE_Starter_Text_Challenge, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CE_Starter_End
	playmoncry SPECIES_CYNDAQUIL, CRY_MODE_ENCOUNTER
	waitmoncry
	setwildbattle SPECIES_CYNDAQUIL, 22
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, CE_Starter_End
	setflag FLAG_CE_STARTER_CYNDAQUIL
	removeobject VAR_LAST_TALKED
	goto CE_Starter_End

CE_Starter_TOTODILE::
	lock
	faceplayer
	goto_if_unset FLAG_BADGE03_GET, CE_Starter_NotReady
	msgbox CE_Starter_Text_Challenge, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CE_Starter_End
	playmoncry SPECIES_TOTODILE, CRY_MODE_ENCOUNTER
	waitmoncry
	setwildbattle SPECIES_TOTODILE, 20
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, CE_Starter_End
	setflag FLAG_CE_STARTER_TOTODILE
	removeobject VAR_LAST_TALKED
	goto CE_Starter_End

CE_Starter_TREECKO::
	lock
	faceplayer
	goto_if_unset FLAG_BADGE05_GET, CE_Starter_NotReady
	msgbox CE_Starter_Text_Challenge, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CE_Starter_End
	playmoncry SPECIES_TREECKO, CRY_MODE_ENCOUNTER
	waitmoncry
	setwildbattle SPECIES_TREECKO, 25
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, CE_Starter_End
	setflag FLAG_CE_STARTER_TREECKO
	removeobject VAR_LAST_TALKED
	goto CE_Starter_End

CE_Starter_TORCHIC::
	lock
	faceplayer
	goto_if_unset FLAG_BADGE03_GET, CE_Starter_NotReady
	msgbox CE_Starter_Text_Challenge, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CE_Starter_End
	playmoncry SPECIES_TORCHIC, CRY_MODE_ENCOUNTER
	waitmoncry
	setwildbattle SPECIES_TORCHIC, 18
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, CE_Starter_End
	setflag FLAG_CE_STARTER_TORCHIC
	removeobject VAR_LAST_TALKED
	goto CE_Starter_End

CE_Starter_MUDKIP::
	lock
	faceplayer
	goto_if_unset FLAG_BADGE05_GET, CE_Starter_NotReady
	msgbox CE_Starter_Text_Challenge, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CE_Starter_End
	playmoncry SPECIES_MUDKIP, CRY_MODE_ENCOUNTER
	waitmoncry
	setwildbattle SPECIES_MUDKIP, 25
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, CE_Starter_End
	setflag FLAG_CE_STARTER_MUDKIP
	removeobject VAR_LAST_TALKED
	goto CE_Starter_End

CE_Starter_TURTWIG::
	lock
	faceplayer
	goto_if_unset FLAG_BADGE06_GET, CE_Starter_NotReady
	msgbox CE_Starter_Text_Challenge, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CE_Starter_End
	playmoncry SPECIES_TURTWIG, CRY_MODE_ENCOUNTER
	waitmoncry
	setwildbattle SPECIES_TURTWIG, 30
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, CE_Starter_End
	setflag FLAG_CE_STARTER_TURTWIG
	removeobject VAR_LAST_TALKED
	goto CE_Starter_End

CE_Starter_CHIMCHAR::
	lock
	faceplayer
	goto_if_unset FLAG_BADGE04_GET, CE_Starter_NotReady
	msgbox CE_Starter_Text_Challenge, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CE_Starter_End
	playmoncry SPECIES_CHIMCHAR, CRY_MODE_ENCOUNTER
	waitmoncry
	setwildbattle SPECIES_CHIMCHAR, 25
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, CE_Starter_End
	setflag FLAG_CE_STARTER_CHIMCHAR
	removeobject VAR_LAST_TALKED
	goto CE_Starter_End

CE_Starter_PIPLUP::
	lock
	faceplayer
	goto_if_unset FLAG_BADGE07_GET, CE_Starter_NotReady
	msgbox CE_Starter_Text_Challenge, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CE_Starter_End
	playmoncry SPECIES_PIPLUP, CRY_MODE_ENCOUNTER
	waitmoncry
	setwildbattle SPECIES_PIPLUP, 30
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, CE_Starter_End
	setflag FLAG_CE_STARTER_PIPLUP
	removeobject VAR_LAST_TALKED
	goto CE_Starter_End

CE_Starter_NotReady:
	msgbox CE_Starter_Text_NotReady, MSGBOX_DEFAULT
CE_Starter_End:
	release
	end
CE_Starter_Text_Challenge:
	.string "A rare POKéMON is watching you!\nWould you like to approach it?$"
CE_Starter_Text_NotReady:
	.string "It seems wary of your approach.\nReturn with more GYM BADGES.$"
