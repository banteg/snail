# initialize_font3d_objects

Initial relationship scratch for the 3D font object builder at `0x44ae10`.

Recovered relationships:

- This is not a sprite path. It allocates one BOD/object record per registered
  glyph and loads `Objects/Font3D`.
- The scratch uses the promoted `BodBase` render-object fields: `set_bod_object`
  fills `object +0x24`, then the font setup clears render arguments `+0x1c` and
  `+0x20` before populating the object quad.
- `FontSheet::glyph_width[index] / line_marker_y` is cached in
  `g_font3d_scales[index]` and scales four x-coordinate lanes in the object
  vertex array.
- The facequad texture pointer is selected from `texture_ref_a/texture_ref_b`
  through `FontSheet::texture_page[index]`.
- The UV quad uses `u0[index]`, `v0[index]`, `1.0f - line_step`, and
  `1.0f - line_marker_fraction`.

Initial match: 40.00%, 94 candidate instructions versus 126 target
instructions. The residual is mostly cursor/register ownership: native walks
the object pointer field at `data_77550c`, the scale cache at
`g_font3d_scales`, and the atlas arrays as separate cursors. The current
scratch keeps those as narrow named globals; masked audit is `8 ok / 0
unresolved / 1 mismatch`.

2026-06-20 scale-cache curation: `0x7770e8` is now named `g_font3d_scales`.
The remaining named mismatch is the native `ebp` scale-cache cursor aligned
against the candidate's `g_font3d_bods+0x1c` cursor. A scale-only cursor source
rewrite was neutral at 40.00%, while a broader object/atlas/scale cursor
rewrite regressed to 32.00%, so the register-ownership residual is left visible.

2026-06-21 object-call reload pass:

- Reloading `bod->object` for the `load_object_definition("Objects/Font3D", ...)`
  call, while keeping the existing `object` local for the following quad,
  vertex, ready, and flag writes, improves the focused matcher from 40.00% to
  44.34%. The candidate grows from 94 to 95 instructions, keeps the 3/126
  prefix, and adds one clean masked operand.
- Reloading the object again for the final flag OR clears the old
  `g_font3d_scales` versus `g_font3d_bods` mask mismatch, but scores lower at
  43.24%, so the higher-scoring loader-call reload is retained and the cursor
  mismatch remains documented.
- Removing the cached facequad pointer, removing the cached vertices pointer,
  combining those removals, and removing the texture-ref local all regress or
  stay neutral. Those forms add instructions but lose the current register
  skeleton, so the scratch keeps the local `object`, `quad`, and `vertices`
  views after the loader call.
- Moving the `object` local until after the load/clear block collapses the
  prologue and drops below 30%, while scale-cursor variants around
  `g_font3d_scales` regress to roughly 36%. Keep the indexed scale store until
  a stronger object-field cursor lead appears.

2026-07-10 shared object owner closure:

- The glyph BODs now borrow slots from the typed global `ObjectList`; the
  loader and all subsequent field writes use the shared `Object` and
  `ObjectFaceQuad` layouts rather than private lookalikes.
- This corrects the old local name at `Object +0x14`: the value set to `1` is
  `blend_mode`, not a font-specific `ready` flag. The x scaling is likewise
  expressed as four `Vector3::x` lanes on the owned vertex array.
- The consolidation is codegen-neutral at 44.34%, 95/126, prefix 3/126, with
  9 clean masked operands and the one documented cursor-alignment mismatch.

2026-07-12 native cursor and contract recovery:

- The sole native caller discards `eax` and immediately initializes font-wave
  state. The empty-font path leaves the incoming font id in `eax`, while the
  populated path leaves the loop count, proving this routine is `void`; the
  old scratch return value was an invented contract and has been removed.
- `g_font3d_bods` is a fixed 128-entry `BodBase` array at `0x7754e8`, occupying
  exactly `0x1c00` bytes and ending at `g_font3d_scales`. The old
  `data_77550c` view is its first `BodBase::object` lane at `+0x24`, not a
  separate object-pointer array. Both arrays now have shared declarations.
- Native owns four independent loop cursors: `ebx` is the selected
  `FontSheet` byte offset, `ebp` walks `g_font3d_scales`, `esi` walks the
  `BodBase::object` lanes in `0x38`-byte steps, and `edi` walks the sheet's
  `v0` lane. Repeating the borrowed `bod->object` access, instead of caching
  private object/quad/vertex views, lets the compiler recover that ownership
  naturally.
- Correcting the void contract, keeping the scale cursor inside the non-empty
  path, and ordering the independent index/scale advances raises the focused
  result from 44.34% to 96.83% with identical 126-instruction streams, prefix
  37/126, and 19 clean masked operands with no unresolved or mismatched names.
- The remaining differences are two legal instruction-scheduling choices: an
  object reload and x87 constant load move across independent stores, and the
  `v0`/BOD cursor increments swap order. They are left visible rather than
  forced with volatile aliases or dummy dependencies.

2026-07-14 analysis ownership closure:

- Binary Ninja and IDA now share the exact `FontSheet` (`0x828`) and
  `cFontPrintBuffer` (`0x84`) layouts plus the fixed `g_font3d_bods[128]`,
  `g_font3d_scales[128]`, and one-sheet font bank extents.
- Both tracked decompiles recover the authored `void(int16_t)` contract and
  name all three fixed banks. The old `data_77550c` pointer-lane view is gone
  from the durable snapshots.
- This is analysis-only ownership recovery. The matcher source and honest
  96.83% result remain byte-identical; the two scheduler differences above
  remain deliberately visible.

## Shared tint policy closure (2026-07-16)

Each Font3D object is shared by many BOD draws whose colours can differ. Its
low `0x10` bit is therefore the persistent
`OBJECT_FLAG_REFRESH_TINT_EACH_DRAW`, paired with the renderer consumer that
rewrites grouped diffuse colours without clearing the bit. This distinguishes
the shared-font policy from the one-shot fringe `OBJECT_FLAG_TINT_DIRTY` bit
without changing the honest 96.83% scheduler residual.
