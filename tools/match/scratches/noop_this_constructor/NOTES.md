# noop_this_constructor @ 0x44db50

Exact three-byte identity body (`eax = ecx; ret`) shared by compiler-folded
trivial default constructors. The scratch uses the already proven `Color4f`
surface because most recovered callers construct color temporaries or fields,
but the native range has no single owning class.

The reference manifest retains the independently observed AxisAngle,
Quaternion, callback, and decorated-constructor aliases. Fifty-one Windows
xrefs also cover render temporaries and startup-owned globals, so splitting
this body out of `linear_interpolate_matrix` restores a real shared function
boundary without inventing per-owner copies.

The old coarse extent charged the constructor and the preceding three-byte
alignment gap to `linear_interpolate_matrix`. The promoted ranges retain all
three constructor bytes and exclude only that non-function padding, explaining
the equal three-byte drop in generated proof and total byte accounting.
