/*
 * mangled: _ZN13cRProgressBar2AIEv
 * demangled: cRProgressBar::AI()
 * address: 00019788
 * size: 604
 */

/* cRProgressBar::AI() */

void cRProgressBar::AI(void)

{
  undefined *puVar1;
  int iVar2;
  uint in_fpscr;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  undefined4 local_68;
  undefined4 uStack_64;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined4 local_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined4 local_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;

  iVar2 = *(int *)PTR__Game_001b60b8;
  fVar3 = (float)VectorSignedToFloat(*(undefined4 *)(iVar2 + 0x72be0),(byte)(in_fpscr >> 0x16) & 3);
  fVar4 = (float)VectorSignedToFloat(*(undefined4 *)(iVar2 + 0x72be8),(byte)(in_fpscr >> 0x16) & 3);
  fVar3 = (*(float *)(iVar2 + 0x82024) - fVar3) / (fVar4 - fVar3);
  if (fVar3 < 0.0) {
    fVar3 = 244.0;
    fVar8 = 394.0;
    fVar4 = 355.0;
    fVar7 = 0.046875;
    fVar9 = 12.0;
  }
  else {
    if (1.0 < fVar3) {
      fVar3 = 1.0;
    }
    fVar3 = (1.0 - fVar3) * 232.0 + 12.0;
    fVar8 = fVar3 + 150.0;
    fVar4 = fVar8 - 39.0;
    fVar7 = fVar3 * -0.00390625 + 1.0;
    fVar9 = 256.0 - fVar3;
  }
  fVar5 = 1.0;
  tColour::tColour((tColour *)&local_48,1.0,1.0,1.0,1.0);
  puVar1 = PTR__gSpriteReference_001b61c8;
  fVar6 = 0.00390625;
  OSDPrintUV(0x88,0x41400000,fVar4,0x42800000,0x42800000,0x1000000,local_48,uStack_44,uStack_40,
             uStack_3c,*(undefined4 *)(PTR__gSpriteReference_001b61c8 + 0x1110),
             fVar5 - *(float *)(PTR__gSpriteReference_001b61c8 + 0x111c),
             *(undefined4 *)(PTR__gSpriteReference_001b61c8 + 0x1118),
             fVar5 - *(float *)(PTR__gSpriteReference_001b61c8 + 0x1114),1,0);
  tColour::tColour((tColour *)&local_58,fVar5,fVar5,fVar5,fVar5);
  OSDPrintUV(0x86,0x41500000,0x43160000,0x42800000,fVar3,0x1000000,local_58,uStack_54,uStack_50,
             uStack_4c,*(undefined4 *)(puVar1 + 0x10d0),fVar5 - *(float *)(puVar1 + 0x10dc),
             *(undefined4 *)(puVar1 + 0x10d8),
             (fVar5 - *(float *)(puVar1 + 0x10dc)) * fVar7 +
             (fVar5 - *(float *)(puVar1 + 0x10d4)) * fVar3 * fVar6,1,0);
  tColour::tColour((tColour *)&local_68,fVar5,fVar5,fVar5,fVar5);
  OSDPrintUV(0x87,0x41500000,fVar8,0x42800000,fVar9,0x1000000,local_68,uStack_64,uStack_60,uStack_5c
             ,*(undefined4 *)(puVar1 + 0x10f0),
             (fVar5 - *(float *)(puVar1 + 0x10fc)) * fVar7 +
             (fVar5 - *(float *)(puVar1 + 0x10f4)) * fVar3 * fVar6,*(undefined4 *)(puVar1 + 0x10f8),
             fVar5 - *(float *)(puVar1 + 0x10f4),1,0);
  return;
}
