/*
 * mangled: _ZN7cKeyPad7KeyTestEiiPi
 * demangled: cKeyPad::KeyTest(int, int, int*)
 * address: 0004b4dc
 * size: 136
 */

/* cKeyPad::KeyTest(int, int, int*) */

undefined1 __thiscall cKeyPad::KeyTest(cKeyPad *this,int param_1,int param_2,int *param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;

  if (0 < *(int *)(this + 8)) {
    iVar3 = *(int *)(this + 4);
    iVar1 = 0;
    iVar4 = 0;
    iVar2 = iVar3;
    do {
      if ((((*(int *)(iVar3 + iVar1) < param_1) && (param_1 < *(int *)(iVar2 + 8))) &&
          (*(int *)(iVar3 + iVar1 + 4) < param_2)) && (param_2 < *(int *)(iVar2 + 0xc))) {
        *param_3 = iVar4;
        return *(undefined1 *)(iVar3 + iVar1 + 0x10);
      }
      iVar4 = iVar4 + 1;
      iVar1 = iVar1 + 0x14;
      iVar2 = iVar2 + 0x14;
    } while (iVar4 < *(int *)(this + 8));
  }
  *param_3 = -1;
  return 0;
}
