/*
 * mangled: _ZN14cAccelerometer4InitEv
 * demangled: cAccelerometer::Init()
 * address: 00075ae0
 * size: 92
 */

/* cAccelerometer::Init() */

void __thiscall cAccelerometer::Init(cAccelerometer *this)

{
  undefined *puVar1;

  *(undefined4 *)(this + 4) = 0x3f800000;
  *(undefined4 *)(this + 0x18) = 0;
  *(undefined4 *)(this + 8) = 0;
  puVar1 = PTR__Game_001b60b8;
  *(undefined4 *)this = 0;
  *(undefined4 *)(this + 0xc) = 0;
  *(undefined4 *)(this + 0x10) = 0;
  *(undefined4 *)(this + 0x14) = 0;
  *(undefined4 *)(*(int *)puVar1 + 0x3c) = 0x43870000;
  *(undefined4 *)(*(int *)puVar1 + 0x40) = 0x43870000;
  *(undefined4 *)(*(int *)puVar1 + 0x48) = 0;
  *(undefined4 *)(*(int *)puVar1 + 0x4c) = 0;
  *(undefined4 *)(this + 0x18) = 0x42c80000;
  return;
}
