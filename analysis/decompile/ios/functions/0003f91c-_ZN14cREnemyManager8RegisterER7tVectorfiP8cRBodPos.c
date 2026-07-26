/*
 * mangled: _ZN14cREnemyManager8RegisterER7tVectorfiP8cRBodPos
 * demangled: cREnemyManager::Register(tVector&, float, int, cRBodPos*)
 * address: 0003f91c
 * size: 136
 */

/* cREnemyManager::Register(tVector&, float, int, cRBodPos*) */

void __thiscall
cREnemyManager::Register
          (cREnemyManager *this,tVector *param_1,float param_2,int param_3,cRBodPos *param_4)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;

  if ((*(uint *)(param_4 + 4) & 0x1000) != 0) {
    return;
  }
  *(int *)(this + *(int *)this * 0x18 + 4) = param_3;
  iVar2 = *(int *)this;
  uVar1 = *(undefined4 *)(param_1 + 4);
  uVar3 = *(undefined4 *)(param_1 + 8);
  *(undefined4 *)(this + iVar2 * 0x18 + 8) = *(undefined4 *)param_1;
  *(undefined4 *)(this + iVar2 * 0x18 + 0xc) = uVar1;
  *(undefined4 *)(this + iVar2 * 0x18 + 0x10) = uVar3;
  *(float *)(this + *(int *)this * 0x18 + 0x14) = param_2;
  *(cRBodPos **)(this + (*(int *)this + 1) * 0x18) = param_4;
  *(int *)this = *(int *)this + 1;
  return;
}
