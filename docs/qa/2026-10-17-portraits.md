# Dedicated portrait integration

18 user-supplied generated portraits converted to indexed 64x64 PNGs, transparent index zero and at most 15 visible colors. Source atlas SHA-256: 21fa9779481b0ebb4850c4e520df0242093e81e8b1d5297176e73a9816318a20.

Local validation passed: 18 distinct assets, 18 graphics mappings, 34 CE trainer assignments, all 158 existing picture IDs preserved. No save format change. Native resource tests check exact decompression, palette selection and buffer guards for every portrait. Build and native results are recorded by the accompanying workflow; ordinary battle presentation and story/postgame verification remain manual.

Patch packaging rebuilds pinned pret/pokeemerald and pret/agbcc references on the CI runner and requires the exact clean US/EU revision-0 SHA-1 before producing a BPS patch. Neither clean nor compiled ROM is uploaded.
