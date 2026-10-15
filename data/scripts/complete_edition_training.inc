CE_Training_EventScript::
	lock
	faceplayer
	msgbox CE_Training_Text_Welcome, MSGBOX_DEFAULT
	dynmultipush CE_Training_Text_Nature, 0
	dynmultipush CE_Training_Text_Silver, 1
	dynmultipush CE_Training_Text_Gold, 2
	dynmultipush CE_Training_Text_EV, 3
	dynmultipush CE_Training_Text_Reset, 4
	dynmultipush CE_Training_Text_Shop, 5
	dynmultipush CE_Training_Text_Exit, 6
	dynmultistack 0, 0, FALSE, 7, FALSE, 0, NULL
	goto_if_ge VAR_RESULT, 6, CE_Training_End
	goto_if_eq VAR_RESULT, 5, CE_Training_Shop
	copyvar VAR_0x8005, VAR_RESULT
	special ChoosePartyMon
	goto_if_ge VAR_0x8004, PARTY_SIZE, CE_Training_End
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	goto_if_eq VAR_RESULT, SPECIES_EGG, CE_Training_Invalid
	goto_if_eq VAR_0x8005, 0, CE_Training_Nature
	goto_if_eq VAR_0x8005, 4, CE_Training_Reset
	goto_if_eq VAR_0x8005, 2, CE_Training_Confirm
	dynmultipush CE_Training_Text_HP, 0
	dynmultipush CE_Training_Text_Atk, 1
	dynmultipush CE_Training_Text_Def, 2
	dynmultipush CE_Training_Text_Spe, 3
	dynmultipush CE_Training_Text_SpA, 4
	dynmultipush CE_Training_Text_SpD, 5
	dynmultistack 0, 0, FALSE, 7, FALSE, 0, NULL
	goto_if_ge VAR_RESULT, 6, CE_Training_End
	copyvar VAR_0x8006, VAR_RESULT
	goto_if_ne VAR_0x8005, 3, CE_Training_Confirm
	callnative Script_CEEVAmountMenu
	dynmultistack 0, 0, FALSE, 7, FALSE, 0, NULL
	goto_if_eq VAR_RESULT, MULTI_B_PRESSED, CE_Training_End
	copyvar VAR_0x8007, VAR_RESULT
	subvar VAR_0x8007, 1024
	goto CE_Training_Confirm

CE_Training_Nature:
	msgbox CE_Training_Text_Mint, MSGBOX_DEFAULT
	dynmultipush CE_Training_Text_Hardy, 0
	dynmultipush CE_Training_Text_Lonely, 1
	dynmultipush CE_Training_Text_Brave, 2
	dynmultipush CE_Training_Text_Adamant, 3
	dynmultipush CE_Training_Text_Naughty, 4
	dynmultipush CE_Training_Text_Bold, 5
	dynmultipush CE_Training_Text_Docile, 6
	dynmultipush CE_Training_Text_Relaxed, 7
	dynmultipush CE_Training_Text_Impish, 8
	dynmultipush CE_Training_Text_Lax, 9
	dynmultipush CE_Training_Text_Timid, 10
	dynmultipush CE_Training_Text_Hasty, 11
	dynmultipush CE_Training_Text_Serious, 12
	dynmultipush CE_Training_Text_Jolly, 13
	dynmultipush CE_Training_Text_Naive, 14
	dynmultipush CE_Training_Text_Modest, 15
	dynmultipush CE_Training_Text_Mild, 16
	dynmultipush CE_Training_Text_Quiet, 17
	dynmultipush CE_Training_Text_Bashful, 18
	dynmultipush CE_Training_Text_Rash, 19
	dynmultipush CE_Training_Text_Calm, 20
	dynmultipush CE_Training_Text_Gentle, 21
	dynmultipush CE_Training_Text_Sassy, 22
	dynmultipush CE_Training_Text_Careful, 23
	dynmultipush CE_Training_Text_Quirky, 24
	dynmultistack 0, 0, FALSE, 7, FALSE, 0, NULL
	goto_if_ge VAR_RESULT, 25, CE_Training_End
	copyvar VAR_0x8006, VAR_RESULT
	checkmoney 3000
	goto_if_eq VAR_RESULT, FALSE, CE_Training_NoMoney
	goto CE_Training_Confirm

CE_Training_Reset:
	msgbox CE_Training_Text_ResetWarning, MSGBOX_DEFAULT
CE_Training_Confirm:
	msgbox CE_Training_Text_Confirm, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CE_Training_End
	callnative Script_CompleteEditionTraining
	goto_if_eq VAR_RESULT, 1, CE_Training_Invalid
	goto_if_eq VAR_RESULT, 2, CE_Training_NoCap
	goto_if_eq VAR_RESULT, 3, CE_Training_Limit
	goto_if_eq VAR_RESULT, 4, CE_Training_NoChange
	call_if_eq VAR_0x8005, 0, CE_Training_Pay
	msgbox CE_Training_Text_Done, MSGBOX_DEFAULT
	goto CE_Training_End
CE_Training_Pay:
	removemoney 3000
	return
CE_Training_EV4:
	setvar VAR_0x8007, 4
	return
CE_Training_EV64:
	setvar VAR_0x8007, 64
	return
CE_Training_EV128:
	setvar VAR_0x8007, 128
	return
CE_Training_EV252:
	setvar VAR_0x8007, 252
	return
CE_Training_Shop:
	pokemart CE_Training_Items
	goto CE_Training_End
	.align 2
CE_Training_Items:
	.2byte ITEM_BOTTLE_CAP
	.2byte ITEM_GOLD_BOTTLE_CAP
	.2byte ITEM_NONE
CE_Training_Invalid:
	msgbox CE_Training_Text_Invalid, MSGBOX_DEFAULT
	goto CE_Training_End
CE_Training_NoCap:
	msgbox CE_Training_Text_NoCap, MSGBOX_DEFAULT
	goto CE_Training_End
CE_Training_Limit:
	msgbox CE_Training_Text_Limit, MSGBOX_DEFAULT
	goto CE_Training_End
CE_Training_NoChange:
	msgbox CE_Training_Text_NoChange, MSGBOX_DEFAULT
	goto CE_Training_End
CE_Training_NoMoney:
	msgbox CE_Training_Text_NoMoney, MSGBOX_DEFAULT
	goto CE_Training_End
CE_Training_End:
	release
	end

CE_Training_Text_Nature:
	.string "Battle nature - 3000$"

CE_Training_Text_Silver:
	.string "Silver Cap - one IV$"

CE_Training_Text_Gold:
	.string "Gold Cap - all IVs$"

CE_Training_Text_EV:
	.string "Set EVs - free$"

CE_Training_Text_Reset:
	.string "Reset EVs - free$"

CE_Training_Text_Shop:
	.string "Buy Bottle Caps$"

CE_Training_Text_Exit:
	.string "Cancel$"

CE_Training_Text_HP:
	.string "HP$"

CE_Training_Text_Atk:
	.string "Attack$"

CE_Training_Text_Def:
	.string "Defense$"

CE_Training_Text_Spe:
	.string "Speed$"

CE_Training_Text_SpA:
	.string "Sp. Atk$"

CE_Training_Text_SpD:
	.string "Sp. Def$"

CE_Training_Text_0:
	.string "0 EVs$"

CE_Training_Text_4:
	.string "4 EVs$"

CE_Training_Text_64:
	.string "64 EVs$"

CE_Training_Text_128:
	.string "128 EVs$"

CE_Training_Text_252:
	.string "252 EVs$"

CE_Training_Text_Hardy:
	.string "Hardy$"

CE_Training_Text_Lonely:
	.string "Lonely$"

CE_Training_Text_Brave:
	.string "Brave$"

CE_Training_Text_Adamant:
	.string "Adamant$"

CE_Training_Text_Naughty:
	.string "Naughty$"

CE_Training_Text_Bold:
	.string "Bold$"

CE_Training_Text_Docile:
	.string "Docile$"

CE_Training_Text_Relaxed:
	.string "Relaxed$"

CE_Training_Text_Impish:
	.string "Impish$"

CE_Training_Text_Lax:
	.string "Lax$"

CE_Training_Text_Timid:
	.string "Timid$"

CE_Training_Text_Hasty:
	.string "Hasty$"

CE_Training_Text_Serious:
	.string "Serious$"

CE_Training_Text_Jolly:
	.string "Jolly$"

CE_Training_Text_Naive:
	.string "Naive$"

CE_Training_Text_Modest:
	.string "Modest$"

CE_Training_Text_Mild:
	.string "Mild$"

CE_Training_Text_Quiet:
	.string "Quiet$"

CE_Training_Text_Bashful:
	.string "Bashful$"

CE_Training_Text_Rash:
	.string "Rash$"

CE_Training_Text_Calm:
	.string "Calm$"

CE_Training_Text_Gentle:
	.string "Gentle$"

CE_Training_Text_Sassy:
	.string "Sassy$"

CE_Training_Text_Careful:
	.string "Careful$"

CE_Training_Text_Quirky:
	.string "Quirky$"

CE_Training_Text_Invalid:
	.string "Choose a POKéMON, not an Egg.$"

CE_Training_Text_NoCap:
	.string "You need the matching Bottle Cap.$"

CE_Training_Text_Limit:
	.string "That exceeds the total of 510 EVs.\nReset some EVs first.$"

CE_Training_Text_NoChange:
	.string "Those IVs are already at maximum.\nYour Bottle Cap was not used.$"

CE_Training_Text_NoMoney:
	.string "You need 3000 for a battle nature.$"

CE_Training_Text_Welcome:
	.string "I am the training adviser!\nI help POKéMON reach their potential.$"

CE_Training_Text_Mint:
	.string "This changes the nature used for stats.\nOriginal breeding nature is preserved.$"

CE_Training_Text_ResetWarning:
	.string "This removes all EVs from this POKéMON.$"

CE_Training_Text_Confirm:
	.string "Apply this training?\nIV training uses one matching Cap.$"

CE_Training_Text_Done:
	.string "Training complete!\nYou can inspect IVs and EVs in SUMMARY.$"
