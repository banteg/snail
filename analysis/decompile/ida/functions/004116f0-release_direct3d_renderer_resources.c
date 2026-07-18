/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: release_direct3d_renderer_resources @ 0x4116f0 */
/* selector: release_direct3d_renderer_resources */

// Direct3DRenderer member teardown entry point that tail-calls the device/interface release body with the existing renderer receiver.
// attributes: thunk
void __thiscall release_direct3d_renderer_resources(Direct3DRenderer *renderer)
{
  release_direct3d_device_interfaces(renderer);
}
