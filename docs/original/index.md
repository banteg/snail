# Original

These pages track the shipped game as it exists today: archive layout, decoded asset families, and format constraints that the rewrite has to preserve.

The point of this section is to separate stable facts about the shipped files from deeper executable analysis. If a page is mainly about what is on disk, it belongs here. If it is mainly about how the runtime interprets or transforms those files, it belongs under [RE](../re/index.md).

## Pages

- [Asset formats overview](asset-formats.md): high-level map of the archive and format families
- [Archive container](archive-container.md): the verified `SnailMail.dat` layout and decode rule
- [Asset families](asset-families.md): top-level groups and extension counts from the decoded index
- [X2 format](x2-format.md): mesh and animation-fragment observations
- [OBJECT format](object-format.md): `_OBJECT.TXT` mesh structure
- [Segment format](segment-format.md): `SEGMENTS/*.TXT` structure and authored metadata
- [Level format](level-format.md): `LEVELS/*.TXT` structure and level-script fields

Use this section for stable facts about the original content. Put lower-level reversing workflows and function-by-function runtime notes under [RE](../re/index.md).
