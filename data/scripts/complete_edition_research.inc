CE_Research_EventScript::
	lock
	faceplayer
	msgbox CE_Research_Text_Welcome, MSGBOX_DEFAULT
	dynmultipush CE_Research_Text_Starters, 0
	dynmultipush CE_Research_Text_Expeditions, 1
	dynmultipush CE_Research_Text_EvolutionShop, 2
	dynmultipush CE_Research_Text_LegendTrails, 3
	dynmultistack 0, 0, FALSE, 7, FALSE, 0, NULL
	goto_if_eq VAR_RESULT, 0, CE_Research_Starters
	goto_if_eq VAR_RESULT, 1, CE_Research_Expeditions
	goto_if_eq VAR_RESULT, 2, CE_Research_EvolutionShop
	goto_if_eq VAR_RESULT, 3, CE_Legend_Hints
	goto CE_Research_End
CE_Research_Starters:
	msgbox CE_Research_Text_Habitats, MSGBOX_DEFAULT
	goto CE_Research_End
CE_Research_Expeditions:
	goto_if_unset FLAG_BADGE07_GET, CE_Research_NeedMindBadge
	msgbox CE_Research_Text_Explanation, MSGBOX_DEFAULT
	dynmultipush CE_Research_Text_Kanto, 0
	dynmultipush CE_Research_Text_Johto, 1
	dynmultipush CE_Research_Text_Hoenn, 2
	dynmultipush CE_Research_Text_Sinnoh, 3
	dynmultistack 0, 0, FALSE, 7, FALSE, 0, NULL
	goto_if_ge VAR_RESULT, 4, CE_Research_End
	copyvar VAR_0x8005, VAR_RESULT
	callnative Script_CEResearchMenu
	dynmultistack 0, 0, FALSE, 7, FALSE, 0, NULL
	goto_if_eq VAR_RESULT, MULTI_B_PRESSED, CE_Research_End
	callnative Script_CEPrepareEncounter
	goto_if_eq VAR_RESULT, FALSE, CE_Research_End
	dowildbattle
	goto CE_Research_End
CE_Research_NeedMindBadge:
	msgbox CE_Research_Text_NeedMindBadge, MSGBOX_DEFAULT
CE_Research_End:
	release
	end
CE_Research_Text_Welcome:
	.string "I coordinate BIRCH's research!\nWe study POKéMON from four regions.$"
CE_Research_Text_Starters:
	.string "Starter habitats$"
CE_Research_Text_Expeditions:
	.string "Research encounters$"
CE_Research_Text_LegendTrails:
	.string "Legendary trails$"
CE_Research_Text_Kanto:
	.string "KANTO$"
CE_Research_Text_Johto:
	.string "JOHTO$"
CE_Research_Text_Hoenn:
	.string "HOENN$"
CE_Research_Text_Sinnoh:
	.string "SINNOH$"
CE_Research_Text_Explanation:
	.string "Choose a species for a research battle.\nBring your own POKé BALLS!\pAll 493 species can be researched,\nincluding rare legends. Level: 50.\pYou may try again if a capture fails.$"
CE_Research_Text_NeedMindBadge:
	.string "Earn the MIND BADGE in MOSSDEEP\nto unlock research encounters.$"

CE_Research_EvolutionShop:
	pokemart CE_Research_EvolutionItems
	goto CE_Research_End
	.align 2
CE_Research_EvolutionItems:
	.2byte ITEM_FIRE_STONE
	.2byte ITEM_WATER_STONE
	.2byte ITEM_THUNDER_STONE
	.2byte ITEM_LEAF_STONE
	.2byte ITEM_MOON_STONE
	.2byte ITEM_SUN_STONE
	.2byte ITEM_SHINY_STONE
	.2byte ITEM_DUSK_STONE
	.2byte ITEM_DAWN_STONE
	.2byte ITEM_ICE_STONE
	.2byte ITEM_OVAL_STONE
	.2byte ITEM_KINGS_ROCK
	.2byte ITEM_METAL_COAT
	.2byte ITEM_DRAGON_SCALE
	.2byte ITEM_UPGRADE
	.2byte ITEM_DUBIOUS_DISC
	.2byte ITEM_REAPER_CLOTH
	.2byte ITEM_ELECTIRIZER
	.2byte ITEM_MAGMARIZER
	.2byte ITEM_PROTECTOR
	.2byte ITEM_DEEP_SEA_TOOTH
	.2byte ITEM_DEEP_SEA_SCALE
	.2byte ITEM_RAZOR_CLAW
	.2byte ITEM_RAZOR_FANG
	.2byte ITEM_NONE
CE_Research_Text_EvolutionShop:
	.string "Evolution supplies$"

CE_Research_Text_Habitats:
	.string "Starters live at special sites across\nHOENN. Approach one to battle it!\pLook in forests, volcanic paths,\ncoastal areas and SHOAL CAVE.\pSome require more GYM BADGES.\nBring POKé BALLS and explore!\pA failed capture does not make\nthem disappear. You can try again.$"
