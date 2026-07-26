/*
 * mangled: _ZN14cREnemyManager8RegisterER7tVectorfiP8cRBodPos
 * demangled: cREnemyManager::Register(tVector&, float, int, cRBodPos*)
 * address: 000629e8
 * size: 92
 */

/* cREnemyManager::Register(tVector&, float, int, cRBodPos*) */

void __thiscall
cREnemyManager::Register
          (cREnemyManager *this,tVector *param_1,float param_2,int param_3,cRBodPos *param_4)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  int in_stack_00000000;

  if ((*(uint *)(in_stack_00000000 + 4) & 0x1000) == 0) {
    uVar1 = *(undefined4 *)param_1;
    uVar2 = *(undefined4 *)(param_1 + 4);
    uVar3 = *(undefined4 *)(param_1 + 8);
    *(cRBodPos **)(this + *(int *)this * 0x18 + 4) = param_4;
    iVar4 = *(int *)this;
    *(int *)this = iVar4 + 1;
    *(int *)(this + iVar4 * 0x18 + 0x14) = param_3;
    *(int *)(this + iVar4 * 0x18 + 0x18) = in_stack_00000000;
    *(undefined4 *)(this + iVar4 * 0x18 + 8) = uVar1;
    *(undefined4 *)(this + iVar4 * 0x18 + 0xc) = uVar2;
    *(undefined4 *)(this + iVar4 * 0x18 + 0x10) = uVar3;
  }
  return;
}
