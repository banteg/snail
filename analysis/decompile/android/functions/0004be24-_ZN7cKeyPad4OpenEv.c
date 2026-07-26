/*
 * mangled: _ZN7cKeyPad4OpenEv
 * demangled: cKeyPad::Open()
 * address: 0004be24
 * size: 516
 */

/* cKeyPad::Open() */

void __thiscall cKeyPad::Open(cKeyPad *this)

{
  char *pcVar1;
  char *pcVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  uint in_fpscr;
  float fVar10;
  undefined4 uVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  int local_34 [2];

  iVar7 = 0;
  cRSpriteManager::GetTexture((cRSpriteManager *)&gRSpriteManager,0x8b);
  cRSpriteManager::GetTexture((cRSpriteManager *)&gRSpriteManager,0x8b);
  pcVar1 = (char *)RShellLoadFile("KeyPad/KeyPadMask.txt",local_34);
  pcVar1[local_34[0] + -1] = '\0';
  pcVar2 = (char *)Rstrfind("KeyCount:",pcVar1);
  pcVar2 = (char *)Rstrscan(pcVar2,':');
  iVar3 = atoi(pcVar2);
  *(int *)(this + 8) = iVar3;
  uVar4 = RShellMemoryMalloc(iVar3 * 0x14,"KeyPad Keys");
  *(undefined4 *)(this + 4) = uVar4;
  if (0 < *(int *)(this + 8)) {
    iVar3 = 0;
    do {
      iVar3 = iVar3 + 1;
      pcVar2 = (char *)Rstrnewline(pcVar2);
      *(char *)(*(int *)(this + 4) + iVar7 + 0x10) = *pcVar2;
      pcVar2 = (char *)Rstrscan(pcVar2,'-');
      pcVar2 = (char *)Rstrscan(pcVar2,' ');
      iVar8 = *(int *)(this + 4);
      iVar5 = atoi(pcVar2);
      *(int *)(iVar8 + iVar7) = iVar5;
      pcVar2 = (char *)Rstrscan(pcVar2,' ');
      iVar8 = *(int *)(this + 4);
      iVar5 = atoi(pcVar2);
      *(int *)(iVar8 + iVar7 + 4) = iVar5;
      pcVar2 = (char *)Rstrscan(pcVar2,' ');
      iVar8 = *(int *)(this + 4);
      iVar5 = atoi(pcVar2);
      *(int *)(iVar8 + iVar7 + 8) = iVar5;
      pcVar2 = (char *)Rstrscan(pcVar2,' ');
      iVar9 = *(int *)(this + 4);
      iVar5 = atoi(pcVar2);
      iVar8 = *(int *)(this + 4);
      *(undefined4 *)(this + 0x14) = 0x42c00000;
      iVar6 = iVar8 + iVar7;
      uVar11 = *(undefined4 *)(iVar6 + 8);
      uVar4 = *(undefined4 *)(iVar6 + 4);
      fVar13 = (float)VectorSignedToFloat(*(undefined4 *)(iVar8 + iVar7),
                                          (byte)(in_fpscr >> 0x16) & 3);
      *(int *)(iVar9 + iVar7 + 0xc) = iVar5;
      fVar14 = (float)VectorSignedToFloat(*(undefined4 *)(iVar6 + 0xc),(byte)(in_fpscr >> 0x16) & 3)
      ;
      fVar12 = (float)VectorSignedToFloat(uVar11,(byte)(in_fpscr >> 0x16) & 3);
      fVar10 = (float)VectorSignedToFloat(uVar4,(byte)(in_fpscr >> 0x16) & 3);
      *(int *)(iVar8 + iVar7) = (int)((fVar13 / 480.0) * 640.0);
      iVar7 = iVar7 + 0x14;
      *(int *)(iVar6 + 8) = (int)((fVar12 / 480.0) * 640.0);
      *(int *)(iVar6 + 4) = (int)(fVar10 * 0.00390625 * 384.0 + 96.0);
      *(int *)(iVar6 + 0xc) = (int)(fVar14 * 0.00390625 * 384.0 + 96.0);
    } while (iVar3 < *(int *)(this + 8));
  }
  *(undefined4 *)this = 0;
  RShellMemoryFree(pcVar1);
  return;
}
