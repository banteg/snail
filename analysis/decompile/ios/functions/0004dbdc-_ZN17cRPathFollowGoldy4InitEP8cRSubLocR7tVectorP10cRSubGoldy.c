/*
 * mangled: _ZN17cRPathFollowGoldy4InitEP8cRSubLocR7tVectorP10cRSubGoldy
 * demangled: cRPathFollowGoldy::Init(cRSubLoc*, tVector&, cRSubGoldy*)
 * address: 0004dbdc
 * size: 132
 */

/* cRPathFollowGoldy::Init(cRSubLoc*, tVector&, cRSubGoldy*) */

void __thiscall
cRPathFollowGoldy::Init
          (cRPathFollowGoldy *this,cRSubLoc *param_1,tVector *param_2,cRSubGoldy *param_3)

{
  undefined *puVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  float fVar5;

  *this = (cRPathFollowGoldy)0x1;
  iVar4 = *(int *)(param_1 + 0x2c);
  *(cRSubLoc **)(this + 8) = param_1;
  *(int *)(this + 4) = iVar4;
  *(undefined4 *)(this + 0xc) = 0;
  *(float *)(this + 0x10) = *(float *)(param_2 + 8) - *(float *)(param_1 + 0x18);
  fVar5 = *(float *)(param_2 + 4);
  *(cRSubGoldy **)(this + 0x38) = param_3;
  puVar1 = PTR__Game_001b60b8;
  *(float *)(this + 0x14) = fVar5 - 0.49;
  iVar3 = *(int *)puVar1;
  iVar2 = cRSubLoc::Yi(param_1);
  *(undefined4 *)(iVar4 + 0x80) = *(undefined4 *)(&DAT_00256df0 + iVar2 * 0xdc + iVar3);
  return;
}
