# Pokémon Emerald: Complete Edition — field guide

**Current development builds retain the Alpha 2 battery-save format. Alpha 1 saves remain incompatible. Back up your save before switching ROM versions.**

## Other generations in the wild

Alpha 1 used Emerald's original wild tables; the extra species were behind Birch's postgame research menu. Alpha 2 changes 105 encounter tables across Hoenn. Local Hoenn Pokémon remain common, with Kanto, Johto and Sinnoh species added to appropriate habitats at the area's existing levels.

You can immediately find **Pidgey, Sentret, Starly and Bidoof on Route 101**: their encounter slots are 10%, 10%, 5% and 4%. Route 102 adds Caterpie, Hoothoot, Shinx and Budew; Route 103 adds Rattata, Spearow, Aipom and Kricketot; Route 104 adds Weedle, Ledyba, Buneary and Combee. There is no Champion or National Dex gate on these encounters.

Other examples: Riolu in Steven's Granite Cave room, Gible and Larvitar in Meteor Falls' deeper chambers, Rotom and Porygon inside New Mauville, Spiritomb on Mt. Pyre 6F, fossil Pokémon in Mirage Tower and Desert Underpass, and Eevee in the Safari Zone's southern area. Surfing and fishing tables now include additional Water families too. The original Safari Zone expansion and late-game area requirements still apply.

A native emulator test verifies an encounter/evolution path for all 458 ordinary Gen 1–4 species, including the special starter sites and original Weather Institute Castform gift. Evolution supplies are sold by Birch's researcher; trade evolutions need no trading. This is a data-and-engine check, not a completed travel playthrough.

## Starter encounters

Birch's extra starter-adoption menu has been replaced with habitat advice. The original story's opening starter choice is retained. Each of the following starters appears as a shiny Pokémon on the map: speak to it, accept the encounter, and catch it using your own Poké Balls. Defeating it, fleeing or losing does **not** set its capture flag; you can retry. Each special encounter disappears only after a successful capture. Breed the captured starter if you want more of its family.

Badge counts below are minimums; normal story and HM access requirements also apply. Shoal Cave sites require low tide.

| Starter | Special location | Level | Badges |
| --- | --- | ---: | ---: |
| Bulbasaur | Petalburg Woods | 10 | 1 |
| Charmander | Fiery Path | 20 | 3 |
| Squirtle | Route 109 | 15 | 2 |
| Chikorita | Route 117 | 18 | 3 |
| Cyndaquil | Jagged Pass | 22 | 4 |
| Totodile | Route 114 | 20 | 3 |
| Treecko | Route 119 | 25 | 5 |
| Torchic | Route 112 | 18 | 3 |
| Mudkip | Route 120 | 25 | 5 |
| Turtwig | Route 123 | 30 | 6 |
| Chimchar | Meteor Falls 1F, entrance chamber | 25 | 4 |
| Piplup | Shoal Cave entrance room, low tide | 30 | 7 |

## Visiting Gym Leaders

All 24 visiting leaders now stand individually around Hoenn; the Pokémon Centre visitor desks have been removed. Talk to a leader and accept their challenge. The battles are optional and repeatable, and retain the alpha's three-Pokémon teams. Nature, IV and EV services remain in Pokémon Centres.

| Leader | Location | Minimum badges |
| --- | --- | ---: |
| Brock | Rusturf Tunnel | 1 |
| Misty | Route 109 | 2 |
| Lt. Surge | New Mauville Inside | 3 |
| Erika | Route 104 | 4 |
| Koga | Route 119 | 5 |
| Sabrina | Mt. Pyre 4F | 6 |
| Blaine | Fiery Path | 7 |
| Giovanni | Route 111 | 8 |
| Falkner | Route 104 | 1 |
| Bugsy | Petalburg Woods | 2 |
| Whitney | Route 117 | 3 |
| Morty | Mt. Pyre Exterior | 4 |
| Chuck | Granite Cave 1F | 5 |
| Jasmine | Route 118 | 6 |
| Pryce | Shoal Cave ice room, low tide | 7 |
| Clair | Meteor Falls 1F, entrance chamber | 8 |
| Roark | Granite Cave B1F | 1 |
| Gardenia | Route 116 | 2 |
| Maylene | Jagged Pass | 3 |
| Crasher Wake | Dewford Town | 4 |
| Fantina | Mt. Pyre 3F | 5 |
| Byron | Abandoned Ship Deck | 6 |
| Candice | Shoal Cave inner room, low tide | 7 |
| Volkner | Route 110 | 8 |

## Postgame and limits

The Battle Frontier World Tournament and repeatable Red, Blue, Silver and Gold battles retain their Alpha 1 locations. Every legendary and mythical remains catchable through the original events or Birch's repeatable research encounters, unlocked by the MIND BADGE from Tate and Liza in Mossdeep; 29 new world trails and linked quests now supplement the original six Hoenn legendary events. See [the legendary trails guide](COMPLETE_EDITION_LEGEND_TRAILS.md). Full travel and interaction QA remains unfinished.

The new Press Start screen shows shiny Rayquaza over Hoenn, with the Complete Edition title, a blinking prompt and looping Emerald title music. Press A or Start to enter the normal menu. The original intro and title button combinations are retained.

Storage is now **17 boxes / 510 Pokémon**, allowing all 493 to be kept simultaneously. The save still uses standard 128 KiB flash and two alternating save slots. The format reclaims old Mystery Gift/e-Reader/distribution, chat and multiplayer-record buffers; it preserves story, Match Call, Trainer Hill, Hall of Fame and Battle Frontier data. These removed legacy wireless/event record services are not supported by this build.

This remains an alpha. Native focused checks and title/menu smoke checks pass; complete story/Frontier travel testing, real-hardware testing, and the outstanding upstream full-suite failures have not been resolved. Several Johto/Sinnoh portraits remain temporary.

## Research catalogue unlock in Alpha 2.1

After defeating Tate and Liza and receiving the seventh Gym Badge (MIND BADGE), return to the researcher in Professor Birch's lab in Littleroot Town. Choose **Research encounters**, then a region and species. Champion status is no longer required. The species list, level-50 battles, Poké Ball requirement and repeat attempts are unchanged. The World Tournament and superbosses still require the postgame.

If you already earned the Mind Badge in an Alpha 2 save, the catalogue becomes available immediately when that save is loaded in Alpha 2.1. Load a normal battery save rather than an emulator save state from the earlier ROM. If the emulator associates saves with the ROM filename, copy your backed-up Alpha 2 `.sav` alongside the new ROM using the new ROM's basename.

## Legendary trails

The new **Legendary trails** option at Birch's researcher provides hints for 29 additional world encounters. See [the trail guide](COMPLETE_EDITION_LEGEND_TRAILS.md) for locations and linked unlocks. The Mind Badge remains the minimum; stronger encounters also require the Hall of Fame. These encounters are included in current builds. Complete travel, capture and save/reload verification remains open; see the status report for the tested scope.

## Battle mechanics

The game uses Generation 4 defaults and the physical/special split. Dynamax and Gigantamax are disabled for both players and trainers.

Winning all eight World Tournament rounds earns one Gold Bottle Cap. If the Items pocket is full, the desk retains the prize; make room and speak to the attendant again before entering another tournament.
