# Complete Edition splash art

`complete_edition.png` is the production 240×160 indexed background for the new native GBA title screen. Its palette uses 240 colours; the final 16 BG colours are reserved for native text. `src/complete_edition_title.c` supplies the title and blinking Start prompt independently, so lettering remains readable and localisable.

Created with the built-in image-generation tool on 2026-10-15. The generated 3:2 artwork was resized and quantised for the GBA; the normal project graphics pipeline converts the indexed PNG to 600 8bpp tiles and its 15-bit palette at build time. No image-generation service is required to compile the game.

## Generation prompt

> Use case: stylized-concept. Asset type: production background artwork for a Pokémon Emerald: Complete Edition Game Boy Advance title screen, 3:2 landscape aspect ratio. Create a beautiful authentic early-2000s GBA pixel-art landscape. Shiny Rayquaza (black serpentine dragon, gold ring markings, red fins, no limbs beyond its small clawed arms) coils dynamically across the lower two thirds above emerald green Hoenn islands and turquoise ocean, with a distant volcanic silhouette. Dark teal and emerald atmosphere, luminous gold rim light, restrained 32-colour-looking pixel clusters, crisp clean silhouettes and expressive eyes. Compose for eventual 240x160 screen, very readable at tiny resolution, no fine noise or dithering. Leave upper third mostly calm dark teal sky as clear negative space for the game logo, leave a calm dark strip at bottom for PRESS START. Artwork only: absolutely no text, no letters, no logos, no borders, no UI. Wide 3:2 composition.
