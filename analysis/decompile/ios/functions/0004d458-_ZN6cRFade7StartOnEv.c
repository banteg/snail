/*
 * mangled: _ZN6cRFade7StartOnEv
 * demangled: cRFade::StartOn()
 * address: 0004d458
 * size: 136
 */

/* WARNING: Removing unreachable block (ram,0x0004d47c) */
/* cRFade::StartOn() */

void __thiscall cRFade::StartOn(cRFade *this)

{
  undefined4 local_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined4 uStack_10;

  *(undefined4 *)this = 1;
  *(undefined4 *)(this + 4) = 0x3f800000;
  *(undefined4 *)(this + 4) = 0x3f71c71c;
  if (0 < *(int *)(*(int *)PTR__Game_001b60b8 + 0x328)) {
    *(undefined4 *)(this + 4) = 0x3f800000;
  }
  tColour::tColour((tColour *)&local_1c,0.0,0.0,0.0,*(float *)(this + 4));
  OSDPrint(3,0,0,0x44200000,0x43f00000,0x1000000,local_1c,uStack_18,uStack_14,uStack_10,9);
  return;
}
