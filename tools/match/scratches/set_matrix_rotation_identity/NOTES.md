# TransformMatrix::set_matrix_rotation_identity @ 0x44d250

Exact 16-instruction `tMatrix::RotIdentity()` body. It resets the rotational
basis and homogeneous lanes while deliberately preserving translation.
Windows passes the matrix in `ECX`, path/camera/player callers already use the
shared `TransformMatrix` method, and Android independently preserves the
authored method symbol.
