/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* export: isolated copy with manifest symbols applied */
/* function: release_direct3d_device_interfaces @ 0x411960 */
/* selector: release_direct3d_device_interfaces */

// Releases the Direct3D device and Direct3D8 interface owned by one Direct3DRenderer and clears both pointers.
void __thiscall release_direct3d_device_interfaces(Direct3DRenderer *renderer)
{
  Direct3DDevice8 *device; // eax
  Direct3D8 *d3d; // eax

  device = renderer->device;
  if ( device != nullptr )
  {
    device->vtbl->Release(device);
    renderer->device = nullptr;
  }
  d3d = renderer->d3d;
  if ( d3d != nullptr )
  {
    d3d->vtbl->Release(renderer->d3d);
    renderer->d3d = nullptr;
  }
}
