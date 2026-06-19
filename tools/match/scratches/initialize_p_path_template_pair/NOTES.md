# initialize_p_path_template_pair

Honest starter scratch for `initialize_p_path_template_pair @ 0x425a40`.

The constructor callsite shows nine explicit stack arguments and the target tail
is `ret 0x24`. The first argument selects runtime kinds `0x21..0x23`; the body
uses the width, endpoint X positions, segment count, and two track textures.

The scratch builds the endpoint samples, fills the three P-family curve formulas
seen in the decompile, derives orientation and deltas, generates the strip mesh,
and finalizes the template. Residuals are expected.
