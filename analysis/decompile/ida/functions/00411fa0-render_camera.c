/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: render_camera @ 0x411fa0 */
/* selector: render_camera */

// Configures one 3D scene viewport, projection, view transform, depth state, fog state, and the after-sprites lane before world objects render. Cross-port Android symbols match this helper to `G0RenderCamera`.
TransformMatrix *__cdecl render_camera(
        float viewport_x,
        float viewport_y,
        float viewport_width,
        float viewport_height,
        float fov_degrees,
        TransformMatrix *camera_matrix,
        TransformMatrix *view_matrix,
        char draw_world,
        char post_sprite_pass)
{
  double v9; // st7
  __int64 v10; // rax
  double v11; // st7
  double v12; // st7
  float y; // edx
  float z; // eax
  float x; // ecx
  double v16; // st7
  float v17; // edx
  float v18; // eax
  double v19; // st7
  float fog_end; // edx
  Direct3DDevice8Vtbl *vtbl; // ecx
  float self; // [esp+6Ch] [ebp-C8h] BYREF
  ColorBGRA8 out; // [esp+70h] [ebp-C4h]
  int32_t v25; // [esp+74h] [ebp-C0h]
  Vec3 target; // [esp+78h] [ebp-BCh] BYREF
  Vec3 up; // [esp+84h] [ebp-B0h] BYREF
  Vec3 eye; // [esp+90h] [ebp-A4h] BYREF
  _DWORD v29[6]; // [esp+9Ch] [ebp-98h] BYREF
  TransformMatrix matrix; // [esp+B4h] [ebp-80h] BYREF
  TransformMatrix v31; // [esp+F4h] [ebp-40h] BYREF

  v29[0] = (__int64)viewport_x;
  v9 = viewport_width * 640.0;
  v29[1] = (__int64)viewport_y;
  self = v9;
  v10 = (__int64)v9;
  v11 = viewport_height * 480.0;
  v29[2] = v10;
  *(float *)&out = v11;
  v29[3] = (__int64)v11;
  v29[4] = 0;
  v29[5] = 1065353216;
  g_direct3d_renderer.device->vtbl->SetViewport(g_direct3d_renderer.device, (D3DViewport8 *)v29);
  g_render_projection_near_z = 0.30000001;
  g_render_projection_far_z = 52.0;
  g_render_projection_param_a = fov_degrees * 0.017453292;
  g_render_projection_param_b = self / *(float *)&out;
  build_perspective_projection_matrix(
    &matrix,
    g_render_projection_param_a,
    g_render_projection_param_b,
    0.30000001,
    52.0);
  g_direct3d_renderer.device->vtbl->SetTransform(g_direct3d_renderer.device, 3, &matrix);
  g_object_render_pass_filter = post_sprite_pass;
  v12 = camera_matrix->basis_forward.x + camera_matrix->position.x;
  y = camera_matrix->position.y;
  z = camera_matrix->position.z;
  eye.x = camera_matrix->position.x;
  x = camera_matrix->basis_up.x;
  eye.y = y;
  target.x = v12;
  v16 = camera_matrix->basis_forward.y + camera_matrix->position.y;
  v17 = camera_matrix->basis_up.y;
  eye.z = z;
  v18 = camera_matrix->basis_up.z;
  up.x = x;
  up.y = v17;
  target.y = v16;
  v19 = camera_matrix->basis_forward.z + camera_matrix->position.z;
  up.z = v18;
  target.z = v19;
  build_camera_view_matrix(&v31, &eye, &target, &up);
  g_direct3d_renderer.device->vtbl->SetTransform(g_direct3d_renderer.device, 2, &v31);
  g_direct3d_renderer.device->vtbl->SetRenderState(g_direct3d_renderer.device, 7, 1);
  g_direct3d_renderer.device->vtbl->SetRenderState(g_direct3d_renderer.device, 14, 1);
  g_direct3d_renderer.device->vtbl->SetRenderState(g_direct3d_renderer.device, 23, 4);
  if ( draw_world && g_game_base->fog_enabled )
  {
    fog_end = g_game_base->fog_end;
    out = LODWORD(g_game_base->fog_start);
    vtbl = g_direct3d_renderer.device->vtbl;
    v25 = LODWORD(fog_end);
    vtbl->SetRenderState(g_direct3d_renderer.device, 28, 1);
    noop_this_constructor(&self);
    pack_color_rgba_u8((tColourSmall *)&self, (tColour *)&g_game_base->fog_color);
    HIBYTE(self) = 0;
    g_direct3d_renderer.device->vtbl->SetRenderState(g_direct3d_renderer.device, 34, LODWORD(self));
    g_direct3d_renderer.device->vtbl->SetRenderState(g_direct3d_renderer.device, 140, 3);
    g_direct3d_renderer.device->vtbl->SetRenderState(g_direct3d_renderer.device, 36, (int32_t)out);
    g_direct3d_renderer.device->vtbl->SetRenderState(g_direct3d_renderer.device, 37, v25);
    g_direct3d_renderer.device->vtbl->SetRenderState(g_direct3d_renderer.device, 38, LODWORD(g_game_base->fog_density));
  }
  else
  {
    g_direct3d_renderer.device->vtbl->SetRenderState(g_direct3d_renderer.device, 28, 0);
  }
  g_render_camera_source_matrix = camera_matrix;
  g_render_camera_view_matrix = view_matrix;
  g_current_texture_ref = nullptr;
  return view_matrix;
}
