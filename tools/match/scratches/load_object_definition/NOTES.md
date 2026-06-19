# load_object_definition

`load_object_definition @ 0x44c420` parses an authored object directory's
`_Object.txt` file. It uses the shared archive data buffer, loads
`%s/_Object.txt`, terminates the text two bytes before the loaded size, then
walks line-by-line through the supported sections.

Recovered structure:

- `[VERTEX START]` is counted first, then `request_object_vertices` allocates
  the object vertex array and indexed `x/y/z` lines populate
  `Object::vertices`.
- `[FACEQUAD START]` is counted first, then `request_object_facequads`
  allocates indexed facequad records.
- Each facequad line has the face index, four vertex indices, eight UV floats,
  and a texture token. The loader appends `.tga`, builds `path/token.tga`,
  resolves it through `g_texture_refs.get_or_create_texture_ref`, and clears
  the facequad's first 16-bit flags/unknown word before writing indices and UVs.
- Lines starting with `*` are comments skipped by a hand-written newline scan,
  matching the native special case rather than the general line skipper helper.

Focused matcher result: 44.80%, 300 candidate instructions versus 325 target
instructions. The masked audit reports 36 ok and 5 mismatches; those mismatches
are alignment fallout between the current vertex and facequad block layout, not
unresolved symbols.

Known residuals:

- Candidate frame is `0x240` versus native `0x23c`, shifting every stack local
  by four bytes and leaving a zero-instruction prefix.
- Native keeps the object receiver in `edi` across the main parser. The current
  source still reloads the object argument in object-allocation and facequad
  store regions.
- Native stores vertex and facequad floats through x87 load/store scheduling;
  the current source often emits compact integer moves from stack locals.

Measured probes:

- Inverting the outer comment-line branch to keep the non-comment path inline
  improved the scratch from 44.44% to 44.80%.
- A `register` object pointer alias and then removing the alias were both
  score-neutral at 44.80%, so the simpler direct parameter use was retained.
