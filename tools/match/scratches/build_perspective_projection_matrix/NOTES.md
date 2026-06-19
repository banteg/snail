# `build_perspective_projection_matrix`

Projection helper at `0x450314`.

Recovered behavior:

- stdcall helper returning the destination matrix pointer;
- computes `half_fov = vertical_fov_radians * 0.5f`;
- computes `y_scale = cos(half_fov) / sin(half_fov)`;
- writes a Direct3D-style perspective projection matrix:
  - `m00 = y_scale / aspect_ratio`;
  - `m11 = y_scale`;
  - `m22 = far_z / (near_z - far_z)`;
  - `m23 = -1.0f`;
  - `m32 = near_z * far_z / (near_z - far_z)`;
  - all other slots are zero.

Native code uses x87 `fsincos` after multiplying by `0.5f`, stores the cosine
back into the FOV argument slot, and stores the sine through a local pointer
before dividing. The retained scratch models that argument/local aliasing in
source and uses a raw 16-float matrix view. VC6 still emits separate
`fcos`/`fsin` plus integer zero stores for this source. That is documented as
source-shape debt rather than closed with inline assembly.
