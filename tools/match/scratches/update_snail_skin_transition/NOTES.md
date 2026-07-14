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
