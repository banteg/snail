/*
 * mangled: _ZN16cRPathFollowGolb4InitEP8cRSubLocR7tVectorP9cRSubGolb
 * demangled: cRPathFollowGolb::Init(cRSubLoc*, tVector&, cRSubGolb*)
 * address: 0004c04c
 * size: 68
 */

/* cRPathFollowGolb::Init(cRSubLoc*, tVector&, cRSubGolb*) */

void __thiscall
cRPathFollowGolb::Init(cRPathFollowGolb *this,cRSubLoc *param_1,tVector *param_2,cRSubGolb *param_3)

{
  undefined4 uVar1;
  float fVar2;
  float fVar3;

  fVar2 = *(float *)(param_2 + 8);
  fVar3 = *(float *)(param_1 + 0x18);
  uVar1 = *(undefined4 *)(param_1 + 0x2c);
  *(cRSubGolb **)(this + 0x24) = param_3;
  *(cRSubLoc **)(this + 8) = param_1;
  *this = (cRPathFollowGolb)0x1;
  *(undefined4 *)(this + 4) = uVar1;
  *(undefined4 *)(this + 0xc) = 0;
  *(float *)(this + 0x10) = fVar2 - fVar3;
  *(float *)(this + 0x14) = *(float *)(param_2 + 4) - 0.49;
  return;
}
