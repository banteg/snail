/*
 * mangled: _ZN8cRParcel2AIEv
 * demangled: cRParcel::AI()
 * address: 0001badc
 * size: 1148
 */

/* cRParcel::AI() */

void __thiscall cRParcel::AI(cRParcel *this)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  uint in_fpscr;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float local_28;
  float local_24;
  float local_20;

  iVar2 = *(int *)(this + 0x30);
  if (*(char *)(iVar2 + 0x12) == '\0') {
    switch(*(undefined4 *)(this + 0x2c)) {
    case 1:
      if (*(float *)(this + 0x18) < *(float *)(iVar2 + 0x11c3c) - 10.0) {
        cRSprite::Kill(*(cRSprite **)(this + 0x48));
        *(undefined4 *)(this + 0x2c) = 0;
      }
      iVar2 = *(int *)(this + 0x48);
      uVar1 = *(undefined4 *)(this + 0x14);
      uVar3 = *(undefined4 *)(this + 0x18);
      fVar6 = *(float *)(this + 0x50) + *(float *)(this + 0x54);
      *(float *)(this + 0x50) = fVar6;
      if (1.0 < fVar6) {
        *(float *)(this + 0x50) = fVar6 - 1.0;
      }
      *(undefined4 *)(iVar2 + 0x48) = *(undefined4 *)(this + 0x10);
      *(undefined4 *)(iVar2 + 0x4c) = uVar1;
      *(undefined4 *)(iVar2 + 0x50) = uVar3;
      iVar2 = *(int *)(this + 0x48);
      fVar5 = *(float *)(iVar2 + 0x4c);
      fVar6 = (float)Sin((*(float *)(this + 0x50) + *(float *)(this + 0x50)) * 3.1415927);
      *(float *)(iVar2 + 0x4c) = fVar5 + fVar6 * 0.3;
      *(float *)(*(int *)(this + 0x48) + 0x7c) =
           *(float *)(*(int *)(this + 0x58) + 0x360) + *(float *)(*(int *)(this + 0x58) + 0x34c);
      iVar2 = *(int *)(this + 0x58);
      if (*(char *)(iVar2 + 0x374) != '\0') {
        *(float *)(*(int *)(this + 0x48) + 0x7c) =
             *(float *)(*(int *)(this + 0x48) + 0x7c) +
             *(float *)(iVar2 + 0x390) + *(float *)(iVar2 + 0x38c);
      }
      break;
    case 4:
      fVar5 = *(float *)(this + 0x14);
      fVar6 = (float)Sin((*(float *)(this + 0x50) + *(float *)(this + 0x50)) * 3.1415927);
      *(undefined4 *)(this + 0x5c) = 0;
      *(undefined4 *)(this + 0x60) = 0x3d2aaaab;
      iVar2 = *(int *)(this + 0x30);
      fVar5 = fVar5 + fVar6 * 0.3;
      local_28 = *(float *)(iVar2 + 0x132b8) - *(float *)(this + 0x10);
      *(float *)(this + 0x14) = fVar5;
      local_24 = *(float *)(iVar2 + 0x132bc) - fVar5;
      local_20 = *(float *)(iVar2 + 0x132c0) - *(float *)(this + 0x18);
      uVar1 = tVector::Magnitude((tVector *)&local_28);
      *(undefined4 *)(this + 0x2c) = 5;
      iVar2 = *(int *)(this + 0x30);
      *(undefined4 *)(this + 100) = uVar1;
      fVar6 = *(float *)(iVar2 + 0x132bc);
      fVar5 = *(float *)(iVar2 + 0x132c0);
      *(float *)(this + 0x68) = *(float *)(this + 0x10) - *(float *)(iVar2 + 0x132b8);
      *(float *)(this + 0x6c) = *(float *)(this + 0x14) - fVar6;
      *(float *)(this + 0x70) = *(float *)(this + 0x18) - fVar5;
      tVector::Normalize((tVector *)(this + 0x68));
      iVar2 = *(int *)(this + 0x30);
    case 5:
      fVar10 = 1.0;
      fVar5 = *(float *)(iVar2 + 0x132bc);
      fVar6 = (1.0 - *(float *)(this + 0x5c)) * *(float *)(this + 100);
      fVar7 = *(float *)(iVar2 + 0x132c0);
      iVar4 = *(int *)(this + 0x48);
      *(float *)(this + 0x10) = *(float *)(iVar2 + 0x132b8) + fVar6 * *(float *)(this + 0x68);
      *(float *)(this + 0x14) = fVar5 + fVar6 * *(float *)(this + 0x6c);
      *(float *)(this + 0x18) = fVar7 + fVar6 * *(float *)(this + 0x70);
      fVar6 = (1.0 - *(float *)(this + 0x5c)) * 0.6 + 0.4;
      *(float *)(iVar4 + 100) = fVar6;
      *(float *)(iVar4 + 0x60) = fVar6;
      iVar4 = *(int *)(this + 0x48);
      iVar2 = *(int *)(this + 0x30);
      fVar6 = (float)Sin(*(float *)(this + 0x5c) * 3.1415927);
      fVar7 = *(float *)(this + 0x14);
      fVar6 = fVar6 * 0.5;
      fVar8 = *(float *)(iVar2 + 0x11c80);
      fVar5 = *(float *)(iVar2 + 0x11c84);
      fVar9 = *(float *)(this + 0x18);
      *(float *)(iVar4 + 0x48) = *(float *)(this + 0x10) + fVar6 * *(float *)(iVar2 + 0x11c7c);
      *(float *)(iVar4 + 0x4c) = fVar7 + fVar6 * fVar8;
      *(float *)(iVar4 + 0x50) = fVar9 + fVar6 * fVar5;
      fVar6 = *(float *)(this + 0x5c);
      *(float *)(this + 0x5c) = fVar6 + *(float *)(this + 0x60);
      if (fVar10 < fVar6 + *(float *)(this + 0x60)) {
        *(undefined4 *)(this + 0x2c) = 0;
        cRSprite::Kill(*(cRSprite **)(this + 0x48));
      }
      break;
    case 6:
      *(undefined4 *)(this + 0x5c) = 0;
      *(undefined4 *)(this + 0x60) = 0x3c888889;
      *(undefined4 *)(this + 0x2c) = 7;
      uVar1 = gRMathRand2();
      fVar7 = 16384.0;
      fVar5 = 6.1035156e-05;
      fVar6 = (float)VectorSignedToFloat(uVar1,(byte)(in_fpscr >> 0x16) & 3);
      *(float *)(this + 0x74) = (fVar6 - 16384.0) * 6.1035156e-05;
      uVar1 = gRMathRand2();
      iVar2 = *(int *)(this + 0x30);
      *(undefined4 *)(this + 0x7c) = 0;
      fVar6 = (float)VectorSignedToFloat(uVar1,(byte)(in_fpscr >> 0x16) & 3);
      *(float *)(this + 0x78) = (fVar6 - fVar7) * fVar5 * 1.5 + 1.0;
    case 7:
      local_28 = *(float *)(&DAT_003052e8 + iVar2) - *(float *)(iVar2 + 0x132b8);
      local_24 = *(float *)(&DAT_003052ec + iVar2) - *(float *)(iVar2 + 0x132bc);
      iVar4 = *(int *)(this + 0x48);
      local_20 = *(float *)(&DAT_003052f0 + iVar2) - *(float *)(iVar2 + 0x132c0);
      fVar6 = *(float *)(this + 0x5c) * 0.6 + 0.4;
      *(float *)(iVar4 + 100) = fVar6;
      *(float *)(iVar4 + 0x60) = fVar6;
      iVar4 = *(int *)(this + 0x30);
      fVar6 = *(float *)(this + 0x5c);
      iVar2 = *(int *)(this + 0x48);
      fVar5 = *(float *)(iVar4 + 0x132bc);
      fVar7 = *(float *)(iVar4 + 0x132c0);
      *(float *)(iVar2 + 0x48) = *(float *)(iVar4 + 0x132b8) + fVar6 * local_28;
      *(float *)(iVar2 + 0x4c) = fVar5 + fVar6 * local_24;
      *(float *)(iVar2 + 0x50) = fVar7 + fVar6 * local_20;
      iVar2 = *(int *)(this + 0x48);
      fVar6 = (float)Sin(*(float *)(this + 0x5c) * 3.1415927);
      fVar7 = *(float *)(this + 0x78);
      fVar5 = *(float *)(this + 0x7c);
      *(float *)(iVar2 + 0x48) = *(float *)(iVar2 + 0x48) + fVar6 * *(float *)(this + 0x74);
      *(float *)(iVar2 + 0x4c) = *(float *)(iVar2 + 0x4c) + fVar6 * fVar7;
      *(float *)(iVar2 + 0x50) = *(float *)(iVar2 + 0x50) + fVar6 * fVar5;
      fVar6 = *(float *)(this + 0x5c);
      *(float *)(this + 0x5c) = fVar6 + *(float *)(this + 0x60);
      if (1.0 < fVar6 + *(float *)(this + 0x60)) {
        cRCompletion::RegisterParcel((cRCompletion *)(*(int *)(this + 0x30) + 0x3052b8));
        *(undefined4 *)(this + 0x2c) = 0;
        cRSprite::Kill(*(cRSprite **)(this + 0x48));
      }
    }
  }
  return;
}
