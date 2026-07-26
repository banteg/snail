/*
 * mangled: _ZN7cKeyPad4OpenEv
 * demangled: cKeyPad::Open()
 * address: 00076624
 * size: 536
 */

/* cKeyPad::Open() */

void __thiscall cKeyPad::Open(cKeyPad *this)

{
  undefined *this_00;
  char *pcVar1;
  char *pcVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  uint in_fpscr;
  float fVar8;
  int local_24;

  this_00 = PTR__gRSpriteManager_001b61e4;
  iVar7 = 0;
  cRSpriteManager::GetTexture((cRSpriteManager *)PTR__gRSpriteManager_001b61e4,0x8b);
  cRSpriteManager::GetTexture((cRSpriteManager *)this_00,0x8b);
  pcVar1 = (char *)RShellLoadFile("KeyPad/KeyPadMask.txt",&local_24);
  pcVar1[local_24 + -1] = '\0';
  pcVar2 = (char *)Rstrfind("KeyCount:",pcVar1);
  pcVar2 = (char *)Rstrscan(pcVar2,':');
  iVar3 = _atoi(pcVar2);
  *(int *)(this + 8) = iVar3;
  uVar4 = RShellMemoryMalloc(iVar3 * 0x14,"KeyPad Keys");
  *(undefined4 *)(this + 4) = uVar4;
  if (0 < *(int *)(this + 8)) {
    iVar3 = 0;
    do {
      pcVar2 = (char *)Rstrnewline(pcVar2);
      iVar7 = iVar7 + 1;
      *(char *)(*(int *)(this + 4) + iVar3 + 0x10) = *pcVar2;
      pcVar2 = (char *)Rstrscan(pcVar2,'-');
      pcVar2 = (char *)Rstrscan(pcVar2,' ');
      iVar6 = *(int *)(this + 4);
      iVar5 = _atoi(pcVar2);
      *(int *)(iVar3 + iVar6) = iVar5;
      pcVar2 = (char *)Rstrscan(pcVar2,' ');
      iVar6 = *(int *)(this + 4);
      iVar5 = _atoi(pcVar2);
      *(int *)(iVar3 + iVar6 + 4) = iVar5;
      pcVar2 = (char *)Rstrscan(pcVar2,' ');
      iVar6 = *(int *)(this + 4);
      iVar5 = _atoi(pcVar2);
      *(int *)(iVar3 + iVar6 + 8) = iVar5;
      pcVar2 = (char *)Rstrscan(pcVar2,' ');
      iVar6 = *(int *)(this + 4);
      iVar5 = _atoi(pcVar2);
      *(int *)(iVar3 + iVar6 + 0xc) = iVar5;
      *(undefined4 *)(this + 0x14) = 0x42c00000;
      fVar8 = (float)VectorSignedToFloat(*(undefined4 *)(iVar3 + *(int *)(this + 4)),
                                         (byte)(in_fpscr >> 0x16) & 3);
      *(int *)(iVar3 + *(int *)(this + 4)) = (int)((fVar8 / 480.0) * 640.0);
      fVar8 = (float)VectorSignedToFloat(*(undefined4 *)(iVar3 + *(int *)(this + 4) + 8),
                                         (byte)(in_fpscr >> 0x16) & 3);
      *(int *)(iVar3 + *(int *)(this + 4) + 8) = (int)((fVar8 / 480.0) * 640.0);
      fVar8 = (float)VectorSignedToFloat(*(undefined4 *)(iVar3 + *(int *)(this + 4) + 4),
                                         (byte)(in_fpscr >> 0x16) & 3);
      *(int *)(iVar3 + *(int *)(this + 4) + 4) =
           (int)(*(float *)(this + 0x14) + fVar8 * 0.00390625 * (480.0 - *(float *)(this + 0x14)));
      iVar5 = iVar3 + *(int *)(this + 4);
      iVar3 = iVar3 + 0x14;
      fVar8 = (float)VectorSignedToFloat(*(undefined4 *)(iVar5 + 0xc),(byte)(in_fpscr >> 0x16) & 3);
      *(int *)(iVar5 + 0xc) =
           (int)(*(float *)(this + 0x14) + fVar8 * 0.00390625 * (480.0 - *(float *)(this + 0x14)));
    } while (iVar7 < *(int *)(this + 8));
  }
  *(undefined4 *)this = 0;
  RShellMemoryFree(pcVar1);
  return;
}
