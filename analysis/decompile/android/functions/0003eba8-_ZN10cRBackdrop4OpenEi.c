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
  int iVar6;
  int iVar7;
  undefined2 *puVar8;
  undefined4 *puVar9;
  short sVar10;
  undefined4 *puVar11;
  short *psVar12;
  uint uVar13;
  uint uVar14;
  uint in_fpscr;
  float fVar15;
  float fVar16;
  float fVar17;

  *(int *)(this + 0x3c) = param_1;
  *(int *)(this + 0x40) = (param_1 + 2) * param_1 * 2;
  uVar3 = RShellMemoryMalloc((param_1 + 1) * (param_1 + 1) * 0x28,"NOT GIVEN");
  *(undefined4 *)(this + 0x7c) = uVar3;
  if (*(int *)(this + 0x44) == 0) {
    uVar3 = RShellMemoryMalloc((*(int *)(this + 0x3c) + 1) * (*(int *)(this + 0x3c) + 1) * 0x14,
                               "Back drop distortvertices");
    *(undefined4 *)(this + 0x44) = uVar3;
    uVar3 = RShellMemoryMalloc(*(int *)(this + 0x40) << 1,"Backdrop index list");
    *(undefined4 *)(this + 0x48) = uVar3;
    uVar3 = RShellMemoryMalloc(8,"Backdrop index list fast");
    *(undefined4 *)(this + 0x50) = uVar3;
  }
  uVar4 = *(uint *)(this + 0x3c);
  psVar12 = *(short **)(this + 0x48);
  sVar2 = (short)uVar4;
  if ((int)uVar4 < 1) {
    sVar10 = sVar2 + 1;
  }
  else {
    uVar14 = uVar4 + 1;
    uVar13 = 0;
    sVar10 = (short)uVar14;
    while( true ) {
      iVar6 = 0;
      *psVar12 = (short)uVar13;
      psVar5 = psVar12;
      uVar1 = uVar13;
      do {
        iVar6 = iVar6 + 1;
        psVar5[1] = (short)uVar1;
        psVar5 = psVar5 + 2;
        *psVar5 = (short)uVar1 + 1;
        uVar1 = (uVar1 & 0xffff) + (uVar14 & 0xffff);
      } while (iVar6 <= (int)uVar4);
      uVar13 = uVar13 + 1;
      psVar12[uVar14 * 2 + 1] = psVar12[uVar14 * 2];
      if (uVar13 == uVar4) break;
      psVar12 = psVar12 + uVar14 * 2 + 2;
    }
  }
  puVar8 = *(undefined2 **)(this + 0x50);
  puVar8[1] = sVar2;
  *puVar8 = 0;
  puVar8[2] = sVar2 * sVar10;
  puVar8[3] = sVar10 * sVar10 + -1;
  if (-1 < (int)uVar4) {
    fVar15 = (float)VectorSignedToFloat(uVar4,(byte)(in_fpscr >> 0x16) & 3);
    puVar11 = *(undefined4 **)(this + 0x44);
    iVar6 = 0;
    do {
      fVar16 = (float)VectorSignedToFloat(iVar6,(byte)(in_fpscr >> 0x16) & 3);
      iVar7 = 0;
      puVar9 = puVar11;
      do {
        fVar17 = (float)VectorSignedToFloat(iVar7,(byte)(in_fpscr >> 0x16) & 3);
        iVar7 = iVar7 + 1;
        *puVar9 = 0;
        puVar9[1] = 0;
        puVar9[2] = 0;
        puVar9[3] = fVar16 / fVar15;
        puVar9[4] = fVar17 / fVar15;
        puVar9 = puVar9 + (uVar4 + 1) * 5;
      } while (iVar7 <= (int)uVar4);
      iVar6 = iVar6 + 1;
      puVar11 = puVar11 + 5;
    } while (iVar6 <= (int)uVar4);
  }
  MakeVBO(this);
  return;
}
