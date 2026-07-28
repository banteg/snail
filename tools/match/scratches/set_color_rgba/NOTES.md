# set_color_rgba @ 0x44db60

Exact 10/10-instruction Windows implementation of the authored
`tColour::Set(float, float, float, float)` role. Android preserves the same
16-byte class, RGBA field order, method name, and four stores. Windows moves
the receiver to `eax` before the stores and returns it; the pointer-returning
source reproduces that shape naturally and is used directly by many callers.

The adjacent exact helpers close the rest of this owner family:

- `set_color_alpha` is void `tColour::Alpha(float)`;
- `set_color_grayscale` is void `tColour::Grey(float)`;
- `store_color4f` has a cross-port constructor counterpart but not the exact
  Windows constructor source shape;
- `set_color_rgb` is the three-float `Set` overload; and
- `set_color_white` / `set_color_black` are `White()` / `Black()`.

The matcher retains stable descriptive `FUNCTION=` identifiers, while the
shared header, primary definitions, object symbols, and downstream callsites
now use the authored names. All six promoted methods and all 662 scratch scores
remain byte-identical. The four-argument Windows `Set` deliberately retains its
pointer return because that is what reproduces native's `mov eax, ecx`; mobile's
void contract supplies the name and behavior, not permission to discard
Windows codegen evidence.
