/*
 * mangled: _ZN13cRBorderStack7PerformEi
 * demangled: cRBorderStack::Perform(int)
 * address: 0005c5fc
 * size: 616
 */

/* cRBorderStack::Perform(int) */

void __thiscall cRBorderStack::Perform(cRBorderStack *this,int param_1)

{
  undefined4 uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  uint *puVar5;
  int iVar6;
  int iVar7;

  switch(param_1) {
  case 0:
    iVar6 = *(int *)(this + 0x648);
    iVar4 = 0;
    puVar5 = (uint *)(iVar6 + 0x80c);
    do {
      uVar2 = *puVar5;
      if (((uVar2 != 0) && ((uVar2 & 0x400) == 0)) && ((uVar2 & 0x10000000) == 0)) {
        if ((uVar2 & 0x1000) == 0) {
          *puVar5 = uVar2 | 0x1000;
          iVar7 = *(int *)(this + 4);
          *(undefined4 *)(this + (iVar7 + 1) * 8) = *(undefined4 *)this;
          iVar3 = *(int *)(this + 4);
          *(int *)(this + (iVar7 + 1) * 8 + 4) = iVar6 + iVar4 * 0x71c + 0x678;
          *(int *)(this + 4) = iVar3 + 1;
        }
      }
      iVar4 = iVar4 + 1;
      puVar5 = puVar5 + 0x1c7;
    } while (iVar4 != 0x96);
    *(int *)this = *(int *)this + 1;
    break;
  case 1:
    if (*(int *)this < 1) {
      return;
    }
    iVar6 = *(int *)(this + 4);
    iVar4 = *(int *)this + -1;
    *(int *)this = iVar4;
    if (iVar6 < 1) {
      return;
    }
    iVar3 = iVar6 + -1;
    *(int *)(this + 4) = iVar3;
    uVar1 = DAT_0005c864;
    if (iVar4 == *(int *)(this + iVar6 * 8)) {
      do {
        *(uint *)(*(int *)(this + iVar3 * 8 + 0xc) + 0x194) =
             *(uint *)(*(int *)(this + iVar3 * 8 + 0xc) + 0x194) & 0xffffefff;
        iVar6 = *(int *)(this + 4);
        iVar3 = iVar6 + -1;
        *(int *)(this + 4) = iVar3;
        iVar4 = *(int *)(this + iVar6 * 8 + 0xc);
        *(undefined4 *)(iVar4 + 0x204) = uVar1;
        *(undefined4 *)(iVar4 + 0x200) = uVar1;
        *(undefined4 *)(iVar4 + 0x214) = *(undefined4 *)(iVar4 + 0x208);
        *(undefined4 *)(iVar4 + 0x210) = *(undefined4 *)(iVar4 + 0x208);
        if (iVar3 < 0) break;
      } while (*(int *)(this + iVar6 * 8) == *(int *)this);
    }
    goto LAB_0005c650;
  case 2:
    if (*(int *)this < 1) {
      return;
    }
    iVar6 = *(int *)(this + 4);
    iVar4 = *(int *)this + -1;
    *(int *)this = iVar4;
    if (iVar6 < 1) {
      return;
    }
    iVar3 = iVar6 + -1;
    *(int *)(this + 4) = iVar3;
    if (iVar4 == *(int *)(this + iVar6 * 8)) {
      do {
        *(uint *)(*(int *)(this + iVar3 * 8 + 0xc) + 0x194) =
             *(uint *)(*(int *)(this + iVar3 * 8 + 0xc) + 0x194) & 0xffff7fff;
        iVar4 = *(int *)(this + 4);
        iVar3 = iVar4 + -1;
        *(int *)(this + 4) = iVar3;
        if (iVar3 < 0) break;
      } while (*(int *)(this + iVar4 * 8) == *(int *)this);
    }
LAB_0005c650:
    *(int *)(this + 4) = iVar3 + 1;
    break;
  case 3:
    iVar6 = *(int *)(this + 0x648);
    iVar4 = 0;
    puVar5 = (uint *)(iVar6 + 0x80c);
    do {
      uVar2 = *puVar5;
      if ((((uVar2 != 0) && ((uVar2 & 0x400) == 0)) && ((uVar2 & 0x10000000) == 0)) &&
         ((uVar2 & 0x1000) == 0)) {
        if ((uVar2 & 0x8000) == 0) {
          *puVar5 = uVar2 | 0x8000;
          iVar7 = *(int *)(this + 4);
          *(undefined4 *)(this + (iVar7 + 1) * 8) = *(undefined4 *)this;
          iVar3 = *(int *)(this + 4);
          *(int *)(this + (iVar7 + 1) * 8 + 4) = iVar6 + iVar4 * 0x71c + 0x678;
          *(int *)(this + 4) = iVar3 + 1;
        }
      }
      iVar4 = iVar4 + 1;
      puVar5 = puVar5 + 0x1c7;
    } while (iVar4 != 0x96);
    *(int *)this = *(int *)this + 1;
  }
  return;
}
