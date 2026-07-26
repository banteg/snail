/*
 * mangled: _ZN17cRPathFollowGoldy4InitEP8cRSubLocR7tVectorP10cRSubGoldy
 * demangled: cRPathFollowGoldy::Init(cRSubLoc*, tVector&, cRSubGoldy*)
 * address: 0004c3c4
 * size: 132
 */

/* cRPathFollowGoldy::Init(cRSubLoc*, tVector&, cRSubGoldy*) */

void __thiscall
cRPathFollowGoldy::Init
          (cRPathFollowGoldy *this,cRSubLoc *param_1,tVector *param_2,cRSubGoldy *param_3)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  float fVar5;
  float fVar6;

  iVar1 = DAT_0004c44c;
  fVar5 = *(float *)(param_2 + 8);
  fVar6 = *(float *)(param_1 + 0x18);
  *(cRSubGoldy **)(this + 0x38) = param_3;
  iVar4 = DAT_0004c450;
  iVar3 = *(int *)(param_1 + 0x2c);
  *this = (cRPathFollowGoldy)0x1;
  piVar2 = *(int **)(iVar1 + 0x4c3f0 + iVar4);
  *(int *)(this + 4) = iVar3;
  *(undefined4 *)(this + 0xc) = 0;
  *(float *)(this + 0x10) = fVar5 - fVar6;
  fVar5 = *(float *)(param_2 + 4) - DAT_0004c448;
  *(cRSubLoc **)(this + 8) = param_1;
  iVar4 = *piVar2;
  *(float *)(this + 0x14) = fVar5;
  iVar1 = cRSubLoc::Yi(param_1);
  *(undefined4 *)(iVar3 + 0x80) = *(undefined4 *)(gGroup0 + iVar1 * 0xdc + iVar4 + 0xd174);
  return;
}
