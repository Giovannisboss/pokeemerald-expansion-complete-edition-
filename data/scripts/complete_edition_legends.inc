// Generated from data/complete_edition_world.json.

CE_Legend_ARTICUNO::
	lock
	faceplayer
	setvar VAR_0x8005, 0
	callnative Script_CELegendIsReady
	goto_if_eq VAR_RESULT, FALSE, CE_Legend_ARTICUNO_NotReady
	msgbox CE_Legend_ARTICUNO_Text, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CE_Legend_End
	setvar VAR_0x8005, 0
	callnative Script_CEPrepareLegend
	goto_if_eq VAR_RESULT, FALSE, CE_Legend_End
	playmoncry SPECIES_ARTICUNO, CRY_MODE_ENCOUNTER
	waitmoncry
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, CE_Legend_End
	setflag FLAG_CE_LEGEND_ARTICUNO
	removeobject VAR_LAST_TALKED
	goto CE_Legend_End

CE_Legend_ARTICUNO_NotReady:
	msgbox CE_Legend_ARTICUNO_Locked, MSGBOX_DEFAULT
	goto CE_Legend_End

CE_Legend_ARTICUNO_Text:
	.string "An icy cry echoes through the\ncave.\pA shiny ARTICUNO waits. Challenge\nit?$"

CE_Legend_ARTICUNO_Locked:
	.string "It is waiting for a worthy\nvisitor.\pEarn the MIND BADGE.$"

CE_Legend_ARTICUNO_Hint:
	.string "Shoal Cave ice chamber.\pEarn the MIND BADGE.$"

CE_Legend_ZAPDOS::
	lock
	faceplayer
	setvar VAR_0x8005, 1
	callnative Script_CELegendIsReady
	goto_if_eq VAR_RESULT, FALSE, CE_Legend_ZAPDOS_NotReady
	msgbox CE_Legend_ZAPDOS_Text, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CE_Legend_End
	setvar VAR_0x8005, 1
	callnative Script_CEPrepareLegend
	goto_if_eq VAR_RESULT, FALSE, CE_Legend_End
	playmoncry SPECIES_ZAPDOS, CRY_MODE_ENCOUNTER
	waitmoncry
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, CE_Legend_End
	setflag FLAG_CE_LEGEND_ZAPDOS
	removeobject VAR_LAST_TALKED
	goto CE_Legend_End

CE_Legend_ZAPDOS_NotReady:
	msgbox CE_Legend_ZAPDOS_Locked, MSGBOX_DEFAULT
	goto CE_Legend_End

CE_Legend_ZAPDOS_Text:
	.string "The generators crackle with\nenergy.\pA shiny ZAPDOS waits. Challenge\nit?$"

CE_Legend_ZAPDOS_Locked:
	.string "It is waiting for a worthy\nvisitor.\pEarn the MIND BADGE.$"

CE_Legend_ZAPDOS_Hint:
	.string "New Mauville.\pEarn the MIND BADGE.$"

CE_Legend_MOLTRES::
	lock
	faceplayer
	setvar VAR_0x8005, 2
	callnative Script_CELegendIsReady
	goto_if_eq VAR_RESULT, FALSE, CE_Legend_MOLTRES_NotReady
	msgbox CE_Legend_MOLTRES_Text, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CE_Legend_End
	setvar VAR_0x8005, 2
	callnative Script_CEPrepareLegend
	goto_if_eq VAR_RESULT, FALSE, CE_Legend_End
	playmoncry SPECIES_MOLTRES, CRY_MODE_ENCOUNTER
	waitmoncry
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, CE_Legend_End
	setflag FLAG_CE_LEGEND_MOLTRES
	removeobject VAR_LAST_TALKED
	goto CE_Legend_End

CE_Legend_MOLTRES_NotReady:
	msgbox CE_Legend_MOLTRES_Locked, MSGBOX_DEFAULT
	goto CE_Legend_End

CE_Legend_MOLTRES_Text:
	.string "A brilliant flame circles the\ncrater.\pA shiny MOLTRES waits. Challenge\nit?$"

CE_Legend_MOLTRES_Locked:
	.string "It is waiting for a worthy\nvisitor.\pEarn the MIND BADGE.$"

CE_Legend_MOLTRES_Hint:
	.string "Mt. Chimney.\pEarn the MIND BADGE.$"

CE_Legend_MEWTWO::
	lock
	faceplayer
	setvar VAR_0x8005, 3
	callnative Script_CELegendIsReady
	goto_if_eq VAR_RESULT, FALSE, CE_Legend_MEWTWO_NotReady
	msgbox CE_Legend_MEWTWO_Text, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CE_Legend_End
	setvar VAR_0x8005, 3
	callnative Script_CEPrepareLegend
	goto_if_eq VAR_RESULT, FALSE, CE_Legend_End
	playmoncry SPECIES_MEWTWO, CRY_MODE_ENCOUNTER
	waitmoncry
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, CE_Legend_End
	setflag FLAG_CE_LEGEND_MEWTWO
	removeobject VAR_LAST_TALKED
	goto CE_Legend_End

CE_Legend_MEWTWO_NotReady:
	msgbox CE_Legend_MEWTWO_Locked, MSGBOX_DEFAULT
	goto CE_Legend_End

CE_Legend_MEWTWO_Text:
	.string "A powerful mind watches from the\ndark.\pA shiny MEWTWO waits. Challenge\nit?$"

CE_Legend_MEWTWO_Locked:
	.string "It is waiting for a worthy\nvisitor.\pEarn the MIND BADGE.\pEnter the HALL OF FAME.$"

CE_Legend_MEWTWO_Hint:
	.string "Desert Underpass.\pEarn the MIND BADGE.\pEnter the HALL OF FAME.$"

CE_Legend_MEW::
	lock
	faceplayer
	setvar VAR_0x8005, 4
	callnative Script_CELegendIsReady
	goto_if_eq VAR_RESULT, FALSE, CE_Legend_MEW_NotReady
	msgbox CE_Legend_MEW_Text, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CE_Legend_End
	setvar VAR_0x8005, 4
	callnative Script_CEPrepareLegend
	goto_if_eq VAR_RESULT, FALSE, CE_Legend_End
	playmoncry SPECIES_MEW, CRY_MODE_ENCOUNTER
	waitmoncry
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, CE_Legend_End
	setflag FLAG_CE_LEGEND_MEW
	removeobject VAR_LAST_TALKED
	goto CE_Legend_End

CE_Legend_MEW_NotReady:
	msgbox CE_Legend_MEW_Locked, MSGBOX_DEFAULT
	goto CE_Legend_End

CE_Legend_MEW_Text:
	.string "A playful presence follows the\ntrees.\pA shiny MEW waits. Challenge it?$"

CE_Legend_MEW_Locked:
	.string "It is waiting for a worthy\nvisitor.\pEarn the MIND BADGE.\pComplete the Hoenn trails of\nCELEBI.$"

CE_Legend_MEW_Hint:
	.string "Petalburg Woods; meet Celebi\nfirst.\pEarn the MIND BADGE.\pComplete the Hoenn trails of\nCELEBI.$"

CE_Legend_RAIKOU::
	lock
	faceplayer
	setvar VAR_0x8005, 5
	callnative Script_CELegendIsReady
	goto_if_eq VAR_RESULT, FALSE, CE_Legend_RAIKOU_NotReady
	msgbox CE_Legend_RAIKOU_Text, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CE_Legend_End
	setvar VAR_0x8005, 5
	callnative Script_CEPrepareLegend
	goto_if_eq VAR_RESULT, FALSE, CE_Legend_End
	playmoncry SPECIES_RAIKOU, CRY_MODE_ENCOUNTER
	waitmoncry
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, CE_Legend_End
	setflag FLAG_CE_LEGEND_RAIKOU
	removeobject VAR_LAST_TALKED
	goto CE_Legend_End

CE_Legend_RAIKOU_NotReady:
	msgbox CE_Legend_RAIKOU_Locked, MSGBOX_DEFAULT
	goto CE_Legend_End

CE_Legend_RAIKOU_Text:
	.string "Thunder rolls across the eastern\nbank.\pA shiny RAIKOU waits. Challenge\nit?$"

CE_Legend_RAIKOU_Locked:
	.string "It is waiting for a worthy\nvisitor.\pEarn the MIND BADGE.$"

CE_Legend_RAIKOU_Hint:
	.string "Route 118.\pEarn the MIND BADGE.$"

CE_Legend_ENTEI::
	lock
	faceplayer
	setvar VAR_0x8005, 6
	callnative Script_CELegendIsReady
	goto_if_eq VAR_RESULT, FALSE, CE_Legend_ENTEI_NotReady
	msgbox CE_Legend_ENTEI_Text, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CE_Legend_End
	setvar VAR_0x8005, 6
	callnative Script_CEPrepareLegend
	goto_if_eq VAR_RESULT, FALSE, CE_Legend_End
	playmoncry SPECIES_ENTEI, CRY_MODE_ENCOUNTER
	waitmoncry
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, CE_Legend_End
	setflag FLAG_CE_LEGEND_ENTEI
	removeobject VAR_LAST_TALKED
	goto CE_Legend_End

CE_Legend_ENTEI_NotReady:
	msgbox CE_Legend_ENTEI_Locked, MSGBOX_DEFAULT
	goto CE_Legend_End

CE_Legend_ENTEI_Text:
	.string "Warm pawprints lead into the\ncavern.\pA shiny ENTEI waits. Challenge it?$"

CE_Legend_ENTEI_Locked:
	.string "It is waiting for a worthy\nvisitor.\pEarn the MIND BADGE.$"

CE_Legend_ENTEI_Hint:
	.string "Fiery Path.\pEarn the MIND BADGE.$"

CE_Legend_SUICUNE::
	lock
	faceplayer
	setvar VAR_0x8005, 7
	callnative Script_CELegendIsReady
	goto_if_eq VAR_RESULT, FALSE, CE_Legend_SUICUNE_NotReady
	msgbox CE_Legend_SUICUNE_Text, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CE_Legend_End
	setvar VAR_0x8005, 7
	callnative Script_CEPrepareLegend
	goto_if_eq VAR_RESULT, FALSE, CE_Legend_End
	playmoncry SPECIES_SUICUNE, CRY_MODE_ENCOUNTER
	waitmoncry
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, CE_Legend_End
	setflag FLAG_CE_LEGEND_SUICUNE
	removeobject VAR_LAST_TALKED
	goto CE_Legend_End

CE_Legend_SUICUNE_NotReady:
	msgbox CE_Legend_SUICUNE_Locked, MSGBOX_DEFAULT
	goto CE_Legend_End

CE_Legend_SUICUNE_Text:
	.string "A clear breeze carries a distant\ncry.\pA shiny SUICUNE waits. Challenge\nit?$"

CE_Legend_SUICUNE_Locked:
	.string "It is waiting for a worthy\nvisitor.\pEarn the MIND BADGE.$"

CE_Legend_SUICUNE_Hint:
	.string "Route 119.\pEarn the MIND BADGE.$"

CE_Legend_LUGIA::
	lock
	faceplayer
	setvar VAR_0x8005, 8
	callnative Script_CELegendIsReady
	goto_if_eq VAR_RESULT, FALSE, CE_Legend_LUGIA_NotReady
	msgbox CE_Legend_LUGIA_Text, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CE_Legend_End
	setvar VAR_0x8005, 8
	callnative Script_CEPrepareLegend
	goto_if_eq VAR_RESULT, FALSE, CE_Legend_End
	playmoncry SPECIES_LUGIA, CRY_MODE_ENCOUNTER
	waitmoncry
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, CE_Legend_End
	setflag FLAG_CE_LEGEND_LUGIA
	removeobject VAR_LAST_TALKED
	goto CE_Legend_End

CE_Legend_LUGIA_NotReady:
	msgbox CE_Legend_LUGIA_Locked, MSGBOX_DEFAULT
	goto CE_Legend_End

CE_Legend_LUGIA_Text:
	.string "A silver wing stirs the silent\nship.\pA shiny LUGIA waits. Challenge it?$"

CE_Legend_LUGIA_Locked:
	.string "It is waiting for a worthy\nvisitor.\pEarn the MIND BADGE.\pEnter the HALL OF FAME.\pComplete the Hoenn trails of\nARTICUNO, ZAPDOS, MOLTRES.$"

CE_Legend_LUGIA_Hint:
	.string "Abandoned Ship hidden rooms; three\nbirds.\pEarn the MIND BADGE.\pEnter the HALL OF FAME.\pComplete the Hoenn trails of\nARTICUNO, ZAPDOS, MOLTRES.$"

CE_Legend_HO_OH::
	lock
	faceplayer
	setvar VAR_0x8005, 9
	callnative Script_CELegendIsReady
	goto_if_eq VAR_RESULT, FALSE, CE_Legend_HO_OH_NotReady
	msgbox CE_Legend_HO_OH_Text, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CE_Legend_End
	setvar VAR_0x8005, 9
	callnative Script_CEPrepareLegend
	goto_if_eq VAR_RESULT, FALSE, CE_Legend_End
	playmoncry SPECIES_HO_OH, CRY_MODE_ENCOUNTER
	waitmoncry
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, CE_Legend_End
	setflag FLAG_CE_LEGEND_HO_OH
	removeobject VAR_LAST_TALKED
	goto CE_Legend_End

CE_Legend_HO_OH_NotReady:
	msgbox CE_Legend_HO_OH_Locked, MSGBOX_DEFAULT
	goto CE_Legend_End

CE_Legend_HO_OH_Text:
	.string "Rainbow light falls on the summit.\pA shiny HO-OH waits. Challenge it?$"

CE_Legend_HO_OH_Locked:
	.string "It is waiting for a worthy\nvisitor.\pEarn the MIND BADGE.\pEnter the HALL OF FAME.\pComplete the Hoenn trails of\nRAIKOU, ENTEI, SUICUNE.$"

CE_Legend_HO_OH_Hint:
	.string "Mt. Pyre summit; three legendary\nbeasts.\pEarn the MIND BADGE.\pEnter the HALL OF FAME.\pComplete the Hoenn trails of\nRAIKOU, ENTEI, SUICUNE.$"

CE_Legend_CELEBI::
	lock
	faceplayer
	setvar VAR_0x8005, 10
	callnative Script_CELegendIsReady
	goto_if_eq VAR_RESULT, FALSE, CE_Legend_CELEBI_NotReady
	msgbox CE_Legend_CELEBI_Text, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CE_Legend_End
	setvar VAR_0x8005, 10
	callnative Script_CEPrepareLegend
	goto_if_eq VAR_RESULT, FALSE, CE_Legend_End
	playmoncry SPECIES_CELEBI, CRY_MODE_ENCOUNTER
	waitmoncry
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, CE_Legend_End
	setflag FLAG_CE_LEGEND_CELEBI
	removeobject VAR_LAST_TALKED
	goto CE_Legend_End

CE_Legend_CELEBI_NotReady:
	msgbox CE_Legend_CELEBI_Locked, MSGBOX_DEFAULT
	goto CE_Legend_End

CE_Legend_CELEBI_Text:
	.string "The forest seems to remember you.\pA shiny CELEBI waits. Challenge\nit?$"

CE_Legend_CELEBI_Locked:
	.string "It is waiting for a worthy\nvisitor.\pEarn the MIND BADGE.$"

CE_Legend_CELEBI_Hint:
	.string "Route 120.\pEarn the MIND BADGE.$"

CE_Legend_LATIAS::
	lock
	faceplayer
	setvar VAR_0x8005, 11
	callnative Script_CELegendIsReady
	goto_if_eq VAR_RESULT, FALSE, CE_Legend_LATIAS_NotReady
	msgbox CE_Legend_LATIAS_Text, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CE_Legend_End
	setvar VAR_0x8005, 11
	callnative Script_CEPrepareLegend
	goto_if_eq VAR_RESULT, FALSE, CE_Legend_End
	playmoncry SPECIES_LATIAS, CRY_MODE_ENCOUNTER
	waitmoncry
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, CE_Legend_End
	setflag FLAG_CE_LEGEND_LATIAS
	removeobject VAR_LAST_TALKED
	goto CE_Legend_End

CE_Legend_LATIAS_NotReady:
	msgbox CE_Legend_LATIAS_Locked, MSGBOX_DEFAULT
	goto CE_Legend_End

CE_Legend_LATIAS_Text:
	.string "A red shape darts above the\ngarden.\pA shiny LATIAS waits. Challenge\nit?$"

CE_Legend_LATIAS_Locked:
	.string "It is waiting for a worthy\nvisitor.\pEarn the MIND BADGE.$"

CE_Legend_LATIAS_Hint:
	.string "Route 123.\pEarn the MIND BADGE.$"

CE_Legend_LATIOS::
	lock
	faceplayer
	setvar VAR_0x8005, 12
	callnative Script_CELegendIsReady
	goto_if_eq VAR_RESULT, FALSE, CE_Legend_LATIOS_NotReady
	msgbox CE_Legend_LATIOS_Text, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CE_Legend_End
	setvar VAR_0x8005, 12
	callnative Script_CEPrepareLegend
	goto_if_eq VAR_RESULT, FALSE, CE_Legend_End
	playmoncry SPECIES_LATIOS, CRY_MODE_ENCOUNTER
	waitmoncry
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, CE_Legend_End
	setflag FLAG_CE_LEGEND_LATIOS
	removeobject VAR_LAST_TALKED
	goto CE_Legend_End

CE_Legend_LATIOS_NotReady:
	msgbox CE_Legend_LATIOS_Locked, MSGBOX_DEFAULT
	goto CE_Legend_End

CE_Legend_LATIOS_Text:
	.string "A blue shape races along the\ncoast.\pA shiny LATIOS waits. Challenge\nit?$"

CE_Legend_LATIOS_Locked:
	.string "It is waiting for a worthy\nvisitor.\pEarn the MIND BADGE.$"

CE_Legend_LATIOS_Hint:
	.string "Route 115.\pEarn the MIND BADGE.$"

CE_Legend_JIRACHI::
	lock
	faceplayer
	setvar VAR_0x8005, 13
	callnative Script_CELegendIsReady
	goto_if_eq VAR_RESULT, FALSE, CE_Legend_JIRACHI_NotReady
	msgbox CE_Legend_JIRACHI_Text, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CE_Legend_End
	setvar VAR_0x8005, 13
	callnative Script_CEPrepareLegend
	goto_if_eq VAR_RESULT, FALSE, CE_Legend_End
	playmoncry SPECIES_JIRACHI, CRY_MODE_ENCOUNTER
	waitmoncry
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, CE_Legend_End
	setflag FLAG_CE_LEGEND_JIRACHI
	removeobject VAR_LAST_TALKED
	goto CE_Legend_End

CE_Legend_JIRACHI_NotReady:
	msgbox CE_Legend_JIRACHI_Locked, MSGBOX_DEFAULT
	goto CE_Legend_End

CE_Legend_JIRACHI_Text:
	.string "A fallen star answers a quiet\nwish.\pA shiny JIRACHI waits. Challenge\nit?$"

CE_Legend_JIRACHI_Locked:
	.string "It is waiting for a worthy\nvisitor.\pEarn the MIND BADGE.$"

CE_Legend_JIRACHI_Hint:
	.string "Meteor Falls entrance chamber.\pEarn the MIND BADGE.$"

CE_Legend_DEOXYS::
	lock
	faceplayer
	setvar VAR_0x8005, 14
	callnative Script_CELegendIsReady
	goto_if_eq VAR_RESULT, FALSE, CE_Legend_DEOXYS_NotReady
	msgbox CE_Legend_DEOXYS_Text, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CE_Legend_End
	setvar VAR_0x8005, 14
	callnative Script_CEPrepareLegend
	goto_if_eq VAR_RESULT, FALSE, CE_Legend_End
	playmoncry SPECIES_DEOXYS, CRY_MODE_ENCOUNTER
	waitmoncry
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, CE_Legend_End
	setflag FLAG_CE_LEGEND_DEOXYS
	removeobject VAR_LAST_TALKED
	goto CE_Legend_End

CE_Legend_DEOXYS_NotReady:
	msgbox CE_Legend_DEOXYS_Locked, MSGBOX_DEFAULT
	goto CE_Legend_End

CE_Legend_DEOXYS_Text:
	.string "A strange signal reaches the\nisland.\pA shiny DEOXYS waits. Challenge\nit?$"

CE_Legend_DEOXYS_Locked:
	.string "It is waiting for a worthy\nvisitor.\pEarn the MIND BADGE.\pEnter the HALL OF FAME.$"

CE_Legend_DEOXYS_Hint:
	.string "Mossdeep City.\pEarn the MIND BADGE.\pEnter the HALL OF FAME.$"

CE_Legend_UXIE::
	lock
	faceplayer
	setvar VAR_0x8005, 15
	callnative Script_CELegendIsReady
	goto_if_eq VAR_RESULT, FALSE, CE_Legend_UXIE_NotReady
	msgbox CE_Legend_UXIE_Text, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CE_Legend_End
	setvar VAR_0x8005, 15
	callnative Script_CEPrepareLegend
	goto_if_eq VAR_RESULT, FALSE, CE_Legend_End
	playmoncry SPECIES_UXIE, CRY_MODE_ENCOUNTER
	waitmoncry
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, CE_Legend_End
	setflag FLAG_CE_LEGEND_UXIE
	removeobject VAR_LAST_TALKED
	goto CE_Legend_End

CE_Legend_UXIE_NotReady:
	msgbox CE_Legend_UXIE_Locked, MSGBOX_DEFAULT
	goto CE_Legend_End

CE_Legend_UXIE_Text:
	.string "Still eyes hold a forgotten\nmemory.\pA shiny UXIE waits. Challenge it?$"

CE_Legend_UXIE_Locked:
	.string "It is waiting for a worthy\nvisitor.\pEarn the MIND BADGE.$"

CE_Legend_UXIE_Hint:
	.string "Safari Zone northwest.\pEarn the MIND BADGE.$"

CE_Legend_MESPRIT::
	lock
	faceplayer
	setvar VAR_0x8005, 16
	callnative Script_CELegendIsReady
	goto_if_eq VAR_RESULT, FALSE, CE_Legend_MESPRIT_NotReady
	msgbox CE_Legend_MESPRIT_Text, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CE_Legend_End
	setvar VAR_0x8005, 16
	callnative Script_CEPrepareLegend
	goto_if_eq VAR_RESULT, FALSE, CE_Legend_End
	playmoncry SPECIES_MESPRIT, CRY_MODE_ENCOUNTER
	waitmoncry
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, CE_Legend_End
	setflag FLAG_CE_LEGEND_MESPRIT
	removeobject VAR_LAST_TALKED
	goto CE_Legend_End

CE_Legend_MESPRIT_NotReady:
	msgbox CE_Legend_MESPRIT_Locked, MSGBOX_DEFAULT
	goto CE_Legend_End

CE_Legend_MESPRIT_Text:
	.string "A gentle feeling settles over the\nlake.\pA shiny MESPRIT waits. Challenge\nit?$"

CE_Legend_MESPRIT_Locked:
	.string "It is waiting for a worthy\nvisitor.\pEarn the MIND BADGE.$"

CE_Legend_MESPRIT_Hint:
	.string "Route 114.\pEarn the MIND BADGE.$"

CE_Legend_AZELF::
	lock
	faceplayer
	setvar VAR_0x8005, 17
	callnative Script_CELegendIsReady
	goto_if_eq VAR_RESULT, FALSE, CE_Legend_AZELF_NotReady
	msgbox CE_Legend_AZELF_Text, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CE_Legend_End
	setvar VAR_0x8005, 17
	callnative Script_CEPrepareLegend
	goto_if_eq VAR_RESULT, FALSE, CE_Legend_End
	playmoncry SPECIES_AZELF, CRY_MODE_ENCOUNTER
	waitmoncry
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, CE_Legend_End
	setflag FLAG_CE_LEGEND_AZELF
	removeobject VAR_LAST_TALKED
	goto CE_Legend_End

CE_Legend_AZELF_NotReady:
	msgbox CE_Legend_AZELF_Locked, MSGBOX_DEFAULT
	goto CE_Legend_End

CE_Legend_AZELF_Text:
	.string "A small presence tests your\nresolve.\pA shiny AZELF waits. Challenge it?$"

CE_Legend_AZELF_Locked:
	.string "It is waiting for a worthy\nvisitor.\pEarn the MIND BADGE.$"

CE_Legend_AZELF_Hint:
	.string "Route 120.\pEarn the MIND BADGE.$"

CE_Legend_DIALGA::
	lock
	faceplayer
	setvar VAR_0x8005, 18
	callnative Script_CELegendIsReady
	goto_if_eq VAR_RESULT, FALSE, CE_Legend_DIALGA_NotReady
	msgbox CE_Legend_DIALGA_Text, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CE_Legend_End
	setvar VAR_0x8005, 18
	callnative Script_CEPrepareLegend
	goto_if_eq VAR_RESULT, FALSE, CE_Legend_End
	playmoncry SPECIES_DIALGA, CRY_MODE_ENCOUNTER
	waitmoncry
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, CE_Legend_End
	setflag FLAG_CE_LEGEND_DIALGA
	removeobject VAR_LAST_TALKED
	goto CE_Legend_End

CE_Legend_DIALGA_NotReady:
	msgbox CE_Legend_DIALGA_Locked, MSGBOX_DEFAULT
	goto CE_Legend_End

CE_Legend_DIALGA_Text:
	.string "For a moment, every sound stands\nstill.\pA shiny DIALGA waits. Challenge\nit?$"

CE_Legend_DIALGA_Locked:
	.string "It is waiting for a worthy\nvisitor.\pEarn the MIND BADGE.\pEnter the HALL OF FAME.\pComplete the Hoenn trails of UXIE,\nMESPRIT, AZELF.$"

CE_Legend_DIALGA_Hint:
	.string "Sky Pillar ground floor; three\nlake spirits.\pEarn the MIND BADGE.\pEnter the HALL OF FAME.\pComplete the Hoenn trails of UXIE,\nMESPRIT, AZELF.$"

CE_Legend_PALKIA::
	lock
	faceplayer
	setvar VAR_0x8005, 19
	callnative Script_CELegendIsReady
	goto_if_eq VAR_RESULT, FALSE, CE_Legend_PALKIA_NotReady
	msgbox CE_Legend_PALKIA_Text, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CE_Legend_End
	setvar VAR_0x8005, 19
	callnative Script_CEPrepareLegend
	goto_if_eq VAR_RESULT, FALSE, CE_Legend_End
	playmoncry SPECIES_PALKIA, CRY_MODE_ENCOUNTER
	waitmoncry
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, CE_Legend_End
	setflag FLAG_CE_LEGEND_PALKIA
	removeobject VAR_LAST_TALKED
	goto CE_Legend_End

CE_Legend_PALKIA_NotReady:
	msgbox CE_Legend_PALKIA_Locked, MSGBOX_DEFAULT
	goto CE_Legend_End

CE_Legend_PALKIA_Text:
	.string "The cavern opens onto an endless\nsky.\pA shiny PALKIA waits. Challenge\nit?$"

CE_Legend_PALKIA_Locked:
	.string "It is waiting for a worthy\nvisitor.\pEarn the MIND BADGE.\pEnter the HALL OF FAME.\pComplete the Hoenn trails of UXIE,\nMESPRIT, AZELF.$"

CE_Legend_PALKIA_Hint:
	.string "Seafloor Cavern deepest room; lake\nspirits.\pEarn the MIND BADGE.\pEnter the HALL OF FAME.\pComplete the Hoenn trails of UXIE,\nMESPRIT, AZELF.$"

CE_Legend_HEATRAN::
	lock
	faceplayer
	setvar VAR_0x8005, 20
	callnative Script_CELegendIsReady
	goto_if_eq VAR_RESULT, FALSE, CE_Legend_HEATRAN_NotReady
	msgbox CE_Legend_HEATRAN_Text, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CE_Legend_End
	setvar VAR_0x8005, 20
	callnative Script_CEPrepareLegend
	goto_if_eq VAR_RESULT, FALSE, CE_Legend_End
	playmoncry SPECIES_HEATRAN, CRY_MODE_ENCOUNTER
	waitmoncry
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, CE_Legend_End
	setflag FLAG_CE_LEGEND_HEATRAN
	removeobject VAR_LAST_TALKED
	goto CE_Legend_End

CE_Legend_HEATRAN_NotReady:
	msgbox CE_Legend_HEATRAN_Locked, MSGBOX_DEFAULT
	goto CE_Legend_End

CE_Legend_HEATRAN_Text:
	.string "Heavy footsteps echo below the\nlava.\pA shiny HEATRAN waits. Challenge\nit?$"

CE_Legend_HEATRAN_Locked:
	.string "It is waiting for a worthy\nvisitor.\pEarn the MIND BADGE.\pEnter the HALL OF FAME.$"

CE_Legend_HEATRAN_Hint:
	.string "Fiery Path.\pEarn the MIND BADGE.\pEnter the HALL OF FAME.$"

CE_Legend_REGIGIGAS::
	lock
	faceplayer
	setvar VAR_0x8005, 21
	callnative Script_CELegendIsReady
	goto_if_eq VAR_RESULT, FALSE, CE_Legend_REGIGIGAS_NotReady
	msgbox CE_Legend_REGIGIGAS_Text, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CE_Legend_End
	setvar VAR_0x8005, 21
	callnative Script_CEPrepareLegend
	goto_if_eq VAR_RESULT, FALSE, CE_Legend_End
	playmoncry SPECIES_REGIGIGAS, CRY_MODE_ENCOUNTER
	waitmoncry
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, CE_Legend_End
	setflag FLAG_CE_LEGEND_REGIGIGAS
	removeobject VAR_LAST_TALKED
	goto CE_Legend_End

CE_Legend_REGIGIGAS_NotReady:
	msgbox CE_Legend_REGIGIGAS_Locked, MSGBOX_DEFAULT
	goto CE_Legend_End

CE_Legend_REGIGIGAS_Text:
	.string "An ancient giant waits for its\nkin.\pA shiny REGIGIGAS waits. Challenge\nit?$"

CE_Legend_REGIGIGAS_Locked:
	.string "It is waiting for a worthy\nvisitor.\pEarn the MIND BADGE.\pEnter the HALL OF FAME.\pBring REGIROCK, REGICE and\nREGISTEEL together in your party.$"

CE_Legend_REGIGIGAS_Hint:
	.string "Ancient Tomb; bring all three\nRegis.\pEarn the MIND BADGE.\pEnter the HALL OF FAME.\pBring REGIROCK, REGICE and\nREGISTEEL together in your party.$"

CE_Legend_GIRATINA::
	lock
	faceplayer
	setvar VAR_0x8005, 22
	callnative Script_CELegendIsReady
	goto_if_eq VAR_RESULT, FALSE, CE_Legend_GIRATINA_NotReady
	msgbox CE_Legend_GIRATINA_Text, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CE_Legend_End
	setvar VAR_0x8005, 22
	callnative Script_CEPrepareLegend
	goto_if_eq VAR_RESULT, FALSE, CE_Legend_End
	playmoncry SPECIES_GIRATINA, CRY_MODE_ENCOUNTER
	waitmoncry
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, CE_Legend_End
	setflag FLAG_CE_LEGEND_GIRATINA
	removeobject VAR_LAST_TALKED
	goto CE_Legend_End

CE_Legend_GIRATINA_NotReady:
	msgbox CE_Legend_GIRATINA_Locked, MSGBOX_DEFAULT
	goto CE_Legend_End

CE_Legend_GIRATINA_Text:
	.string "A shadow moves against the light.\pA shiny GIRATINA waits. Challenge\nit?$"

CE_Legend_GIRATINA_Locked:
	.string "It is waiting for a worthy\nvisitor.\pEarn the MIND BADGE.\pEnter the HALL OF FAME.\pComplete the Hoenn trails of\nDIALGA, PALKIA.$"

CE_Legend_GIRATINA_Hint:
	.string "Mt. Pyre sixth floor; time and\nspace.\pEarn the MIND BADGE.\pEnter the HALL OF FAME.\pComplete the Hoenn trails of\nDIALGA, PALKIA.$"

CE_Legend_CRESSELIA::
	lock
	faceplayer
	setvar VAR_0x8005, 23
	callnative Script_CELegendIsReady
	goto_if_eq VAR_RESULT, FALSE, CE_Legend_CRESSELIA_NotReady
	msgbox CE_Legend_CRESSELIA_Text, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CE_Legend_End
	setvar VAR_0x8005, 23
	callnative Script_CEPrepareLegend
	goto_if_eq VAR_RESULT, FALSE, CE_Legend_End
	playmoncry SPECIES_CRESSELIA, CRY_MODE_ENCOUNTER
	waitmoncry
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, CE_Legend_End
	setflag FLAG_CE_LEGEND_CRESSELIA
	removeobject VAR_LAST_TALKED
	goto CE_Legend_End

CE_Legend_CRESSELIA_NotReady:
	msgbox CE_Legend_CRESSELIA_Locked, MSGBOX_DEFAULT
	goto CE_Legend_End

CE_Legend_CRESSELIA_Text:
	.string "A crescent glow calms the waves.\pA shiny CRESSELIA waits. Challenge\nit?$"

CE_Legend_CRESSELIA_Locked:
	.string "It is waiting for a worthy\nvisitor.\pEarn the MIND BADGE.\pEnter the HALL OF FAME.$"

CE_Legend_CRESSELIA_Hint:
	.string "Route 125.\pEarn the MIND BADGE.\pEnter the HALL OF FAME.$"

CE_Legend_PHIONE::
	lock
	faceplayer
	setvar VAR_0x8005, 24
	callnative Script_CELegendIsReady
	goto_if_eq VAR_RESULT, FALSE, CE_Legend_PHIONE_NotReady
	msgbox CE_Legend_PHIONE_Text, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CE_Legend_End
	setvar VAR_0x8005, 24
	callnative Script_CEPrepareLegend
	goto_if_eq VAR_RESULT, FALSE, CE_Legend_End
	playmoncry SPECIES_PHIONE, CRY_MODE_ENCOUNTER
	waitmoncry
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, CE_Legend_End
	setflag FLAG_CE_LEGEND_PHIONE
	removeobject VAR_LAST_TALKED
	goto CE_Legend_End

CE_Legend_PHIONE_NotReady:
	msgbox CE_Legend_PHIONE_Locked, MSGBOX_DEFAULT
	goto CE_Legend_End

CE_Legend_PHIONE_Text:
	.string "A tiny ripple follows the\nshoreline.\pA shiny PHIONE waits. Challenge\nit?$"

CE_Legend_PHIONE_Locked:
	.string "It is waiting for a worthy\nvisitor.\pEarn the MIND BADGE.$"

CE_Legend_PHIONE_Hint:
	.string "Route 109.\pEarn the MIND BADGE.$"

CE_Legend_MANAPHY::
	lock
	faceplayer
	setvar VAR_0x8005, 25
	callnative Script_CELegendIsReady
	goto_if_eq VAR_RESULT, FALSE, CE_Legend_MANAPHY_NotReady
	msgbox CE_Legend_MANAPHY_Text, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CE_Legend_End
	setvar VAR_0x8005, 25
	callnative Script_CEPrepareLegend
	goto_if_eq VAR_RESULT, FALSE, CE_Legend_End
	playmoncry SPECIES_MANAPHY, CRY_MODE_ENCOUNTER
	waitmoncry
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, CE_Legend_End
	setflag FLAG_CE_LEGEND_MANAPHY
	removeobject VAR_LAST_TALKED
	goto CE_Legend_End

CE_Legend_MANAPHY_NotReady:
	msgbox CE_Legend_MANAPHY_Locked, MSGBOX_DEFAULT
	goto CE_Legend_End

CE_Legend_MANAPHY_Text:
	.string "A song rises softly from the sea.\pA shiny MANAPHY waits. Challenge\nit?$"

CE_Legend_MANAPHY_Locked:
	.string "It is waiting for a worthy\nvisitor.\pEarn the MIND BADGE.$"

CE_Legend_MANAPHY_Hint:
	.string "Route 105.\pEarn the MIND BADGE.$"

CE_Legend_DARKRAI::
	lock
	faceplayer
	setvar VAR_0x8005, 26
	callnative Script_CELegendIsReady
	goto_if_eq VAR_RESULT, FALSE, CE_Legend_DARKRAI_NotReady
	msgbox CE_Legend_DARKRAI_Text, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CE_Legend_End
	setvar VAR_0x8005, 26
	callnative Script_CEPrepareLegend
	goto_if_eq VAR_RESULT, FALSE, CE_Legend_End
	playmoncry SPECIES_DARKRAI, CRY_MODE_ENCOUNTER
	waitmoncry
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, CE_Legend_End
	setflag FLAG_CE_LEGEND_DARKRAI
	removeobject VAR_LAST_TALKED
	goto CE_Legend_End

CE_Legend_DARKRAI_NotReady:
	msgbox CE_Legend_DARKRAI_Locked, MSGBOX_DEFAULT
	goto CE_Legend_End

CE_Legend_DARKRAI_Text:
	.string "A restless dream fills the empty\nroom.\pA shiny DARKRAI waits. Challenge\nit?$"

CE_Legend_DARKRAI_Locked:
	.string "It is waiting for a worthy\nvisitor.\pEarn the MIND BADGE.\pEnter the HALL OF FAME.$"

CE_Legend_DARKRAI_Hint:
	.string "Mt. Pyre fourth floor.\pEarn the MIND BADGE.\pEnter the HALL OF FAME.$"

CE_Legend_SHAYMIN::
	lock
	faceplayer
	setvar VAR_0x8005, 27
	callnative Script_CELegendIsReady
	goto_if_eq VAR_RESULT, FALSE, CE_Legend_SHAYMIN_NotReady
	msgbox CE_Legend_SHAYMIN_Text, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CE_Legend_End
	setvar VAR_0x8005, 27
	callnative Script_CEPrepareLegend
	goto_if_eq VAR_RESULT, FALSE, CE_Legend_End
	playmoncry SPECIES_SHAYMIN, CRY_MODE_ENCOUNTER
	waitmoncry
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, CE_Legend_End
	setflag FLAG_CE_LEGEND_SHAYMIN
	removeobject VAR_LAST_TALKED
	goto CE_Legend_End

CE_Legend_SHAYMIN_NotReady:
	msgbox CE_Legend_SHAYMIN_Locked, MSGBOX_DEFAULT
	goto CE_Legend_End

CE_Legend_SHAYMIN_Text:
	.string "The flowers bloom around a quiet\nguest.\pA shiny SHAYMIN waits. Challenge\nit?$"

CE_Legend_SHAYMIN_Locked:
	.string "It is waiting for a worthy\nvisitor.\pEarn the MIND BADGE.$"

CE_Legend_SHAYMIN_Hint:
	.string "Route 117.\pEarn the MIND BADGE.$"

CE_Legend_ARCEUS::
	lock
	faceplayer
	setvar VAR_0x8005, 28
	callnative Script_CELegendIsReady
	goto_if_eq VAR_RESULT, FALSE, CE_Legend_ARCEUS_NotReady
	msgbox CE_Legend_ARCEUS_Text, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CE_Legend_End
	setvar VAR_0x8005, 28
	callnative Script_CEPrepareLegend
	goto_if_eq VAR_RESULT, FALSE, CE_Legend_End
	playmoncry SPECIES_ARCEUS, CRY_MODE_ENCOUNTER
	waitmoncry
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, CE_Legend_End
	setflag FLAG_CE_LEGEND_ARCEUS
	removeobject VAR_LAST_TALKED
	goto CE_Legend_End

CE_Legend_ARCEUS_NotReady:
	msgbox CE_Legend_ARCEUS_Locked, MSGBOX_DEFAULT
	goto CE_Legend_End

CE_Legend_ARCEUS_Text:
	.string "The sky becomes completely silent.\pA shiny ARCEUS waits. Challenge\nit?$"

CE_Legend_ARCEUS_Locked:
	.string "It is waiting for a worthy\nvisitor.\pEarn the MIND BADGE.\pEnter the HALL OF FAME.\pComplete the Hoenn trails of\nGIRATINA, MEW, CELEBI, JIRACHI,\nMANAPHY, DARKRAI, SHAYMIN.$"

CE_Legend_ARCEUS_Hint:
	.string "Sky Pillar summit; seven mythic\ntrails.\pEarn the MIND BADGE.\pEnter the HALL OF FAME.\pComplete the Hoenn trails of\nGIRATINA, MEW, CELEBI, JIRACHI,\nMANAPHY, DARKRAI, SHAYMIN.$"

CE_Legend_End:
	release
	end
