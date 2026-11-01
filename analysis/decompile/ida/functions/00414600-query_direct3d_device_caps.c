/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* export: isolated copy with manifest symbols applied */
/* function: query_direct3d_device_caps @ 0x414600 */
/* selector: query_direct3d_device_caps */

// Direct3DRenderer member that queries adapter device capabilities into its owned D3DDeviceCaps8 block and reports the maximum texture dimensions.
void __thiscall query_direct3d_device_caps(Direct3DRenderer *renderer)
{
  renderer->d3d->vtbl->GetDeviceCaps(renderer->d3d, 0, 1, &renderer->device_caps);
  debug_report_stub("Max Texture Width %i\n", renderer->device_caps.max_texture_width);
  debug_report_stub("Max Texture Height %i\n", renderer->device_caps.max_texture_height);
}
