/*
 * mangled: _ZN8cRBorder13InputTextInitEiPci
 * demangled: cRBorder::InputTextInit(int, char*, int)
 * address: 0003ad1c
 * size: 572
 */

/* cRBorder::InputTextInit(int, char*, int) */

void __thiscall cRBorder::InputTextInit(cRBorder *this,int param_1,char *param_2,int param_3)

{
  cRBorder *pcVar1;
  int iVar2;
  int iVar3;
  char *pcVar4;
  int iVar5;
  float fVar6;
  float fVar7;
  float fVar8;

  *(int *)(this + 0x704) = param_3;
  Rstrcpy((char *)(this + 0x6c4),param_2);
  iVar2 = 0;
  *(undefined4 *)(this + 0x6f4) = 0;
  *(undefined4 *)(this + 0x708) = 0;
  if (this[0x2c4] != (cRBorder)0x0) {
    pcVar1 = this + 0x2c4;
    iVar3 = 0;
    do {
      iVar2 = iVar2 + 1;
      *(int *)(this + 0x708) = iVar3 + 1;
      *(int *)(this + 0x6f4) = iVar2;
      pcVar1 = pcVar1 + 1;
      iVar3 = iVar3 + 1;
    } while (*pcVar1 != (cRBorder)0x0);
  }
  this[iVar2 + 0x2c4] = (cRBorder)0x7c;
  this[iVar2 + 0x2c5] = (cRBorder)0x0;
  *(undefined4 *)(this + 0x6f8) = 1;
  *(undefined4 *)(this + 0x6fc) = 0;
  *(int *)(this + 0x70c) = param_1;
  *(undefined4 *)(this + 0x700) = 0x3daaaaab;
  RePosition(this);
  if ((param_3 & 0xcU) != 0) {
    iVar2 = 0;
    iVar3 = *(int *)PTR__Game_001b60b8;
    pcVar4 = section_00001504.segname + iVar3 + 0xc;
    do {
      if (*(int *)pcVar4 == 0) {
        iVar5 = iVar3 + iVar2 * 0x71c + 0x138c;
        *(undefined4 *)((int)&section_00001504 + iVar2 * 0x71c + iVar3 + 0x18) =
             *(undefined4 *)(iVar3 + 0x2d8);
        goto LAB_0003ae44;
      }
      iVar2 = iVar2 + 1;
      pcVar4 = pcVar4 + 0x71c;
    } while (iVar2 != 0x96);
    RShellError("Run out of Borders - Increase RGAME_BORDER_NUMBER");
    iVar5 = 0;
LAB_0003ae44:
    iVar2 = *(int *)(this + 700);
    *(int *)(this + 0x2c0) = iVar5;
    Init(iVar5,0x14,"OK",*(undefined4 *)(iVar2 + 0x70),0,0,*(undefined4 *)(iVar2 + 0x1b0),
         *(undefined4 *)(iVar2 + 0x1b4),*(undefined4 *)(iVar2 + 0x1b8),
         *(undefined4 *)(iVar2 + 0x1bc),0,0);
    iVar2 = *(int *)(this + 700);
    if ((*(uint *)(iVar2 + 0x704) & 4) == 0) {
      if ((*(uint *)(iVar2 + 0x704) & 8) != 0) {
        iVar3 = *(int *)(this + 0x2c0);
        fVar6 = *(float *)(iVar2 + 0x22c);
        *(undefined4 *)(iVar3 + 0x230) = *(undefined4 *)(iVar2 + 0x230);
        fVar6 = ((fVar6 - *(float *)(iVar3 + 0x23c)) - *(float *)(iVar2 + 0x20c)) +
                *(float *)(iVar3 + 0x20c) * -2.0;
        *(float *)(iVar3 + 0x6ec) = fVar6;
        *(float *)(iVar3 + 0x22c) = fVar6;
        *(undefined4 *)(iVar3 + 0x6f0) = *(undefined4 *)(iVar2 + 0x6f0);
      }
    }
    else {
      fVar6 = *(float *)(iVar2 + 0x22c);
      fVar8 = *(float *)(iVar2 + 0x23c);
      iVar3 = *(int *)(this + 0x2c0);
      fVar7 = *(float *)(iVar2 + 0x20c);
      *(undefined4 *)(iVar3 + 0x230) = *(undefined4 *)(iVar2 + 0x230);
      fVar6 = fVar6 + fVar8 + fVar7 + *(float *)(iVar3 + 0x20c);
      *(float *)(iVar3 + 0x6ec) = fVar6;
      *(float *)(iVar3 + 0x22c) = fVar6;
      *(undefined4 *)(iVar3 + 0x6f0) = *(undefined4 *)(iVar2 + 0x6f0);
    }
  }
  return;
}
