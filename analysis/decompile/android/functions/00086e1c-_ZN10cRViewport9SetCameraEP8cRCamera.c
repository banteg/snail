/*
 * mangled: _ZN10cRViewport9SetCameraEP8cRCamera
 * demangled: cRViewport::SetCamera(cRCamera*)
 * address: 00086e1c
 * size: 20
 */

/* cRViewport::SetCamera(cRCamera*) */

void __thiscall cRViewport::SetCamera(cRViewport *this,cRCamera *param_1)

{
  *(cRCamera **)(this + 0x20) = param_1;
  *(uint *)(this + 8) = *(uint *)(this + 8) | 1;
  return;
}
