# update_snail_skin_transition @ 0x445f80

Exact 100.00% match, 25/25 instructions, with one clean masked operand.

This is the Windows `SnailSkin::update_snail_skin_transition`, authored as
`cRSnailSkin::AI`. The exact owner follows its borrowed `Snail*` backlink to
the Snail's animated `Object`, raises `OBJECT_FLAG_USE_OVERRIDE_TEXTURE`, and
installs `material_overrides[selected_slot]` in
`Object::override_texture_ref`. If a
timed change is active, it advances
`progress` by `progress_step` and restores slot zero after progress exceeds
one.

Android independently exports `cRSnailSkin::AI()` and follows the same
Snail-to-object link for its flag/material write and timer state machine. The
Windows renderer independently consumes `Object::override_texture_ref`, so
the old synthetic visual-root/material-index view is retired.

## 2026-07-18 durable lifecycle replay

The focused Snail-presentation lane now replays this method through the exact
0x20-byte `SnailSkin` child. Paired tracked decompiles follow its borrowed
`Snail*` backlink into the owned render `Object`, then recover the object flag,
override texture, three borrowed `TextureRef*` slots, and timed reset fields.
Strict health checks reject the old `owner_render_state`, `slot_ids`, raw
object offsets, and synthetic transition owner. Focused matching remains exact
at 25/25 with its operand clean.
