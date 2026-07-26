/*
 * mangled: _ZN12cRCompletion14RegisterParcelEv
 * demangled: cRCompletion::RegisterParcel()
 * address: 000624d4
 * size: 176
 */

/* cRCompletion::RegisterParcel() */

void __thiscall cRCompletion::RegisterParcel(cRCompletion *this)

{
  undefined *puVar1;
  undefined *this_00;

  puVar1 = PTR__Game_001b60b8;
  if (*(int *)(this + 0x24) == *(int *)(this + 0x18)) {
    return;
  }
  cRSubGoldy::ScoreAdd((cRSubGoldy *)(*(int *)PTR__Game_001b60b8 + 0x81fc0),4,0);
  MacOFAddParcelDelivered();
  this_00 = PTR__gRSound_001b61e0;
  *(int *)(this + 0x24) = *(int *)(this + 0x24) + 1;
  cRSound::Play((cRSound *)this_00,0x2e);
  if (*(int *)(this + 0x24) != *(int *)(this + 0x18)) {
    return;
  }
  if (*(int *)(this + 0x1c) != 0) {
    cRSubGoldy::ScoreAdd((cRSubGoldy *)(*(int *)puVar1 + 0x81fc0),5,*(int *)(this + 0x44));
    cRSound::Play((cRSound *)this_00,0x32);
  }
  *(undefined4 *)(this + 0x10) = 3;
  return;
}
