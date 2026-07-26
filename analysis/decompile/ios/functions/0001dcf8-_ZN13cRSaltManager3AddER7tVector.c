/*
 * mangled: _ZN13cRSaltManager3AddER7tVector
 * demangled: cRSaltManager::Add(tVector&)
 * address: 0001dcf8
 * size: 296
 */

/* cRSaltManager::Add(tVector&) */

void __thiscall cRSaltManager::Add(cRSaltManager *this,tVector *param_1)

{
  undefined *puVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined4 uVar4;
  cRSaltManager *pcVar5;
  int iVar6;
  uint in_fpscr;
  float fVar7;

  iVar6 = 0;
  pcVar5 = this;
  do {
    if (*(int *)(pcVar5 + 0x74) == 0) {
      pcVar5 = this + iVar6 * 0x8c;
      *(undefined4 *)(pcVar5 + 0x80) = 0;
      *(undefined4 *)(pcVar5 + 0x74) = 1;
      puVar1 = PTR__Game_001b60b8;
      *(float *)(pcVar5 + 0x84) = *(float *)(*(int *)PTR__Game_001b60b8 + 0x72bc4) * 0.033333335;
      uVar2 = *(undefined4 *)(param_1 + 4);
      uVar4 = *(undefined4 *)(param_1 + 8);
      *(undefined4 *)(pcVar5 + 0x5c) = *(undefined4 *)param_1;
      *(undefined4 *)(pcVar5 + 0x60) = uVar2;
      *(undefined4 *)(pcVar5 + 100) = uVar4;
      iVar6 = iVar6 * 0x8c + 0x2c;
      tMatrix::RotIdentity((tMatrix *)(this + iVar6));
      uVar2 = gRMathRand2();
      fVar7 = (float)VectorSignedToFloat(uVar2,(byte)(in_fpscr >> 0x16) & 3);
      tMatrix::RotLocalY((tMatrix *)(this + iVar6),(fVar7 - 16384.0) * 6.1035156e-05 * 3.1415927);
      uVar3 = *(uint *)(pcVar5 + 4);
      pcVar5[0x88] = (cRSaltManager)0x1;
      iVar6 = *(int *)puVar1;
      if ((uVar3 & 0x200) == 0) {
        *(code **)(pcVar5 + 8) = MacAudioStartMusic + iVar6;
        *(undefined4 *)(pcVar5 + 0xc) = *(undefined4 *)(iVar6 + 0x75204);
        *(cRSaltManager **)(iVar6 + 0x75204) = pcVar5;
        if (*(int *)(pcVar5 + 0xc) != 0) {
          *(cRSaltManager **)(*(int *)(pcVar5 + 0xc) + 8) = pcVar5;
        }
        *(uint *)(pcVar5 + 4) = uVar3 | 0x200;
        return;
      }
      RShellError("List ADDafter");
      return;
    }
    iVar6 = iVar6 + 1;
    pcVar5 = pcVar5 + 0x8c;
  } while (iVar6 != 0x28);
  return;
}
