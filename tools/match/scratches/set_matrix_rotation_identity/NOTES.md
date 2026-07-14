# TransformMatrix::set_matrix_rotation_identity @ 0x44d250

Exact 16-instruction `tMatrix::RotIdentity()` body. It resets the rotational
basis and homogeneous lanes while deliberately preserving translation.
Windows passes the matrix in `ECX`, path/camera/player callers already use the
shared `TransformMatrix` method, and iOS and Android independently preserve the
authored method symbol.

2026-07-14 ownership metadata closure: the analysis header and both decompiler
replay scripts now describe the exact source owner as a void `__thiscall`
member rather than an ABI-equivalent `__fastcall` free function.
