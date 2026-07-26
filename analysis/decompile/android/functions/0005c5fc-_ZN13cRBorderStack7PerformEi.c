/*
 * mangled: _ZN13cRBorderStack7PerformEi
 * demangled: cRBorderStack::Perform(int)
 * address: 0005c5fc
 * size: 616
 */

/* cRBorderStack::Perform(int) */

void __thiscall cRBorderStack::Perform(cRBorderStack *this,int param_1)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  uint *puVar4;
  int iVar5;
  int iVar6;

  switch(param_1) {
  case 0:
    iVar5 = *(int *)(this + 0x648);
    iVar3 = 0;
    puVar4 = (uint *)(iVar5 + 0x80c);
    do {
      uVar1 = *puVar4;
      if (((uVar1 != 0) && ((uVar1 & 0x400) == 0)) && ((uVar1 & 0x10000000) == 0)) {
        if ((uVar1 & 0x1000) == 0) {
          *puVar4 = uVar1 | 0x1000;
          iVar6 = *(int *)(this + 4);
          *(undefined4 *)(this + (iVar6 + 1) * 8) = *(undefined4 *)this;
          iVar2 = *(int *)(this + 4);
          *(int *)(this + (iVar6 + 1) * 8 + 4) = iVar5 + iVar3 * 0x71c + 0x678;
          *(int *)(this + 4) = iVar2 + 1;
        }
      }
      iVar3 = iVar3 + 1;
      puVar4 = puVar4 + 0x1c7;
    } while (iVar3 != 0x96);
    *(int *)this = *(int *)this + 1;
    break;
  case 1:
    if (*(int *)this < 1) {
      return;
    }
    iVar5 = *(int *)(this + 4);
    iVar3 = *(int *)this + -1;
    *(int *)this = iVar3;
    if (iVar5 < 1) {
      return;
    }
    iVar2 = iVar5 + -1;
    *(int *)(this + 4) = iVar2;
    if (iVar3 == *(int *)(this + iVar5 * 8)) {
      do {
        *(uint *)(*(int *)(this + iVar2 * 8 + 0xc) + 0x194) =
             *(uint *)(*(int *)(this + iVar2 * 8 + 0xc) + 0x194) & 0xffffefff;
        iVar5 = *(int *)(this + 4);
        iVar2 = iVar5 + -1;
        *(int *)(this + 4) = iVar2;
        iVar3 = *(int *)(this + iVar5 * 8 + 0xc);
        *(undefined4 *)(iVar3 + 0x204) = 0;
        *(undefined4 *)(iVar3 + 0x200) = 0;
        *(undefined4 *)(iVar3 + 0x214) = *(undefined4 *)(iVar3 + 0x208);
        *(undefined4 *)(iVar3 + 0x210) = *(undefined4 *)(iVar3 + 0x208);
        if (iVar2 < 0) break;
      } while (*(int *)(this + iVar5 * 8) == *(int *)this);
    }
    goto LAB_0005c650;
  case 2:
    if (*(int *)this < 1) {
      return;
    }
    iVar5 = *(int *)(this + 4);
    iVar3 = *(int *)this + -1;
    *(int *)this = iVar3;
    if (iVar5 < 1) {
      return;
    }
    iVar2 = iVar5 + -1;
    *(int *)(this + 4) = iVar2;
    if (iVar3 == *(int *)(this + iVar5 * 8)) {
      do {
        *(uint *)(*(int *)(this + iVar2 * 8 + 0xc) + 0x194) =
             *(uint *)(*(int *)(this + iVar2 * 8 + 0xc) + 0x194) & 0xffff7fff;
        iVar3 = *(int *)(this + 4);
        iVar2 = iVar3 + -1;
        *(int *)(this + 4) = iVar2;
        if (iVar2 < 0) break;
      } while (*(int *)(this + iVar3 * 8) == *(int *)this);
    }
LAB_0005c650:
    *(int *)(this + 4) = iVar2 + 1;
    break;
  case 3:
    iVar5 = *(int *)(this + 0x648);
    iVar3 = 0;
    puVar4 = (uint *)(iVar5 + 0x80c);
    do {
      uVar1 = *puVar4;
      if ((((uVar1 != 0) && ((uVar1 & 0x400) == 0)) && ((uVar1 & 0x10000000) == 0)) &&
         ((uVar1 & 0x1000) == 0)) {
        if ((uVar1 & 0x8000) == 0) {
          *puVar4 = uVar1 | 0x8000;
          iVar6 = *(int *)(this + 4);
          *(undefined4 *)(this + (iVar6 + 1) * 8) = *(undefined4 *)this;
          iVar2 = *(int *)(this + 4);
          *(int *)(this + (iVar6 + 1) * 8 + 4) = iVar5 + iVar3 * 0x71c + 0x678;
          *(int *)(this + 4) = iVar2 + 1;
        }
      }
      iVar3 = iVar3 + 1;
      puVar4 = puVar4 + 0x1c7;
    } while (iVar3 != 0x96);
    *(int *)this = *(int *)this + 1;
  }
  return;
}
