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
  int iVar2;
  int iVar3;
  float fVar4;
  float fVar5;

  fVar4 = *(float *)(param_2 + 8);
  fVar5 = *(float *)(param_1 + 0x18);
  *(cRSubGoldy **)(this + 0x38) = param_3;
  iVar3 = *(int *)(param_1 + 0x2c);
  *this = (cRPathFollowGoldy)0x1;
  *(int *)(this + 4) = iVar3;
  *(undefined4 *)(this + 0xc) = 0;
  *(float *)(this + 0x10) = fVar4 - fVar5;
  fVar4 = *(float *)(param_2 + 4);
  *(cRSubLoc **)(this + 8) = param_1;
  iVar1 = Game;
  *(float *)(this + 0x14) = fVar4 - 0.49;
  iVar2 = cRSubLoc::Yi(param_1);
  *(undefined4 *)(iVar3 + 0x80) = *(undefined4 *)(gGroup0 + iVar2 * 0xdc + iVar1 + 0xd174);
  return;
}
