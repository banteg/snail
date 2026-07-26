/*
 * mangled: _ZN12cRLoadingBar9TgaRenderEP10cTgaHeaderS1_iiii
 * demangled: cRLoadingBar::TgaRender(cTgaHeader*, cTgaHeader*, int, int, int, int)
 * address: 0008991c
 * size: 224
 */

/* cRLoadingBar::TgaRender(cTgaHeader*, cTgaHeader*, int, int, int, int) */

cRLoadingBar * __thiscall
cRLoadingBar::TgaRender
          (cRLoadingBar *this,cTgaHeader *param_1,cTgaHeader *param_2,int param_3,int param_4,
          int param_5,int param_6)

{
  cRLoadingBar *pcVar1;
  cRLoadingBar *pcVar2;
  int iVar3;
  cRLoadingBar *pcVar4;
  cRLoadingBar *pcVar5;
  cRLoadingBar *pcVar6;
  int iVar7;
  cRLoadingBar *pcVar8;

  if (param_4 < param_6) {
    iVar7 = 0;
    do {
      if (param_3 < param_5) {
        pcVar4 = (cRLoadingBar *)
                 (param_2 +
                 ((uint)*(ushort *)(param_2 + 0xc) * ((*(ushort *)(param_2 + 0xe) - 1) - param_4) +
                 param_3) * 3 + 0x12);
        this = (cRLoadingBar *)
               (param_1 +
               ((uint)*(ushort *)(param_1 + 0xc) * ((*(ushort *)(param_1 + 0xe) - 1) + iVar7) +
               param_3) * 3 + 0x12);
        pcVar2 = pcVar4;
        iVar3 = param_3;
        pcVar5 = pcVar4;
        pcVar6 = this;
        pcVar8 = this;
        do {
          iVar3 = iVar3 + 1;
          *pcVar5 = *pcVar6;
          pcVar1 = this + 1;
          this = this + 3;
          pcVar2[1] = *pcVar1;
          pcVar2 = pcVar2 + 3;
          pcVar1 = pcVar8 + 2;
          pcVar8 = pcVar8 + 3;
          pcVar4[2] = *pcVar1;
          pcVar4 = pcVar4 + 3;
          pcVar5 = pcVar5 + 3;
          pcVar6 = pcVar6 + 3;
        } while (iVar3 != param_5);
      }
      param_4 = param_4 + 1;
      iVar7 = iVar7 + -1;
    } while (param_4 < param_6);
  }
  return this;
}
