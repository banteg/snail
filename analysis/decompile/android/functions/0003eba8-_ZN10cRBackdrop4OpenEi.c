/*
 * mangled: _ZN10cRBackdrop4OpenEi
 * demangled: cRBackdrop::Open(int)
 * address: 0003eba8
 * size: 448
 */

/* cRBackdrop::Open(int) */

void __thiscall cRBackdrop::Open(cRBackdrop *this,int param_1)

{
  uint uVar1;
  short sVar2;
  undefined4 uVar3;
  uint uVar4;
  short *psVar5;
  char *pcVar6;
  int iVar7;
  undefined2 *puVar8;
  undefined4 *puVar9;
  short sVar10;
  int iVar11;
  undefined4 *puVar12;
  short *psVar13;
  uint uVar14;
  uint uVar15;
  uint in_fpscr;
  float fVar16;
  float fVar17;
  float fVar18;

  *(int *)(this + 0x3c) = param_1;
  iVar7 = DAT_0003ed6c;
  iVar11 = DAT_0003ed70 + 0x3ebdc;
  *(int *)(this + 0x40) = (param_1 + 2) * param_1 * 2;
  uVar3 = RShellMemoryMalloc((param_1 + 1) * (param_1 + 1) * 0x28,(char *)(iVar11 + iVar7));
  *(undefined4 *)(this + 0x7c) = uVar3;
  if (*(int *)(this + 0x44) == 0) {
    uVar3 = RShellMemoryMalloc((*(int *)(this + 0x3c) + 1) * (*(int *)(this + 0x3c) + 1) * 0x14,
                               (char *)(iVar11 + DAT_0003ed74));
    pcVar6 = (char *)(iVar11 + DAT_0003ed78);
    *(undefined4 *)(this + 0x44) = uVar3;
    uVar3 = RShellMemoryMalloc(*(int *)(this + 0x40) << 1,pcVar6);
    pcVar6 = (char *)(iVar11 + DAT_0003ed7c);
    *(undefined4 *)(this + 0x48) = uVar3;
    uVar3 = RShellMemoryMalloc(8,pcVar6);
    *(undefined4 *)(this + 0x50) = uVar3;
  }
  uVar4 = *(uint *)(this + 0x3c);
  psVar13 = *(short **)(this + 0x48);
  sVar2 = (short)uVar4;
  if ((int)uVar4 < 1) {
    sVar10 = sVar2 + 1;
  }
  else {
    uVar15 = uVar4 + 1;
    uVar14 = 0;
    sVar10 = (short)uVar15;
    while( true ) {
      iVar7 = 0;
      *psVar13 = (short)uVar14;
      psVar5 = psVar13;
      uVar1 = uVar14;
      do {
        iVar7 = iVar7 + 1;
        psVar5[1] = (short)uVar1;
        psVar5 = psVar5 + 2;
        *psVar5 = (short)uVar1 + 1;
        uVar1 = (uVar1 & 0xffff) + (uVar15 & 0xffff);
      } while (iVar7 <= (int)uVar4);
      uVar14 = uVar14 + 1;
      psVar13[uVar15 * 2 + 1] = psVar13[uVar15 * 2];
      if (uVar14 == uVar4) break;
      psVar13 = psVar13 + uVar15 * 2 + 2;
    }
  }
  puVar8 = *(undefined2 **)(this + 0x50);
  puVar8[1] = sVar2;
  *puVar8 = 0;
  puVar8[2] = sVar2 * sVar10;
  puVar8[3] = sVar10 * sVar10 + -1;
  uVar3 = DAT_0003ed68;
  if (-1 < (int)uVar4) {
    fVar16 = (float)VectorSignedToFloat(uVar4,(byte)(in_fpscr >> 0x16) & 3);
    puVar12 = *(undefined4 **)(this + 0x44);
    iVar7 = 0;
    do {
      fVar17 = (float)VectorSignedToFloat(iVar7,(byte)(in_fpscr >> 0x16) & 3);
      iVar11 = 0;
      puVar9 = puVar12;
      do {
        fVar18 = (float)VectorSignedToFloat(iVar11,(byte)(in_fpscr >> 0x16) & 3);
        iVar11 = iVar11 + 1;
        *puVar9 = uVar3;
        puVar9[1] = uVar3;
        puVar9[2] = uVar3;
        puVar9[3] = fVar17 / fVar16;
        puVar9[4] = fVar18 / fVar16;
        puVar9 = puVar9 + (uVar4 + 1) * 5;
      } while (iVar11 <= (int)uVar4);
      iVar7 = iVar7 + 1;
      puVar12 = puVar12 + 5;
    } while (iVar7 <= (int)uVar4);
  }
  MakeVBO(this);
  return;
}
