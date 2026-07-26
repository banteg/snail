/*
 * mangled: _ZN8cRBorder4InitEiiff7tColourfi
 * demangled: cRBorder::Init(int, int, float, float, tColour, float, int)
 * address: 0005e578
 * size: 704
 */

/* WARNING: Restarted to delay deadcode elimination for space: stack */
/* cRBorder::Init(int, int, float, float, tColour, float, int) */

void cRBorder::Init(cRBorder *param_1,uint param_2,int param_3,undefined4 param_4,undefined4 param_5
                   ,undefined4 param_6,undefined4 param_7,undefined4 param_8,undefined4 param_9,
                   float param_10,undefined4 param_11)

{
  char cVar1;
  undefined4 uVar2;
  uint uVar3;
  int iVar4;
  bool bVar5;
  uint in_fpscr;
  float extraout_s0;
  float extraout_s0_00;
  float extraout_s1;
  float extraout_s1_00;
  float extraout_s2;
  float extraout_s2_00;
  float extraout_s3;
  float extraout_s3_00;
  undefined4 extraout_s15;
  undefined4 uVar6;
  float fVar7;
  undefined4 local_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined4 local_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;

  iVar4 = Game;
  uVar3 = *(uint *)(param_1 + 4);
  if ((uVar3 & 0x200) == 0) {
    uVar2 = *(undefined4 *)(Game + 0xd20);
    *(int *)(param_1 + 8) = Game + 0xd14;
    *(undefined4 *)(param_1 + 0xc) = uVar2;
    *(cRBorder **)(iVar4 + 0xd20) = param_1;
    *(uint *)(param_1 + 4) = uVar3 | 0x200;
    if (*(int *)(param_1 + 0xc) != 0) {
      *(cRBorder **)(*(int *)(param_1 + 0xc) + 8) = param_1;
    }
  }
  else {
    RShellError("List ADDafter");
  }
  uVar2 = 0;
  param_1[0x50] = (cRBorder)0x0;
  *(undefined4 *)(param_1 + 0x244) = 0;
  *(undefined4 *)(param_1 + 0x288) = 0;
  *(undefined4 *)(param_1 + 0x220) = 0;
  *(undefined4 *)(param_1 + 0x29c) = 0;
  *(undefined4 *)(param_1 + 0x250) = 0;
  param_1[0x228] = (cRBorder)0x0;
  *(undefined4 *)(param_1 + 0x264) = 0x41a00000;
  *(undefined4 *)(param_1 + 0x224) = 0x41a00000;
  *(undefined4 *)(param_1 + 0x6e4) = 0;
  *(undefined4 *)(param_1 + 0x3c) = 6;
  *(undefined4 *)(param_1 + 0x16c) = 0x40800000;
  *(undefined4 *)(param_1 + 0x2c) = 1;
  *(undefined4 *)(param_1 + 0x208) = 0x41200000;
  *(cRBorder **)(param_1 + 0x290) = param_1;
  *(cRBorder **)(param_1 + 700) = param_1;
  *(undefined4 *)(param_1 + 0x20c) = 0x41700000;
  *(undefined4 *)(param_1 + 0x6e8) = 0x3f800000;
  UnHideInit(param_1);
  param_1[0x2c4] = (cRBorder)0x0;
  *(uint *)(param_1 + 0x198) = param_2 | 0x40801;
  *(uint *)(param_1 + 0x194) = param_2 | 0x40801;
  *(undefined4 *)(param_1 + 0x1b0) = param_6;
  *(undefined4 *)(param_1 + 0x1b4) = param_7;
  *(undefined4 *)(param_1 + 0x1b8) = param_8;
  *(undefined4 *)(param_1 + 0x1bc) = param_9;
  *(undefined4 *)(param_1 + 0x6f0) = param_5;
  *(undefined4 *)(param_1 + 0x6ec) = param_4;
  *(undefined4 *)(param_1 + 0x1c0) = param_6;
  *(undefined4 *)(param_1 + 0x1c4) = param_7;
  *(undefined4 *)(param_1 + 0x1c8) = param_8;
  *(undefined4 *)(param_1 + 0x1cc) = param_9;
  tColour::tColour((tColour *)&local_48,extraout_s0,extraout_s1,extraout_s2,extraout_s3);
  *(undefined4 *)(param_1 + 0x1e0) = local_48;
  *(undefined4 *)(param_1 + 0x1e4) = uStack_44;
  *(undefined4 *)(param_1 + 0x1e8) = uStack_40;
  *(undefined4 *)(param_1 + 0x1ec) = uStack_3c;
  tColour::tColour((tColour *)&local_58,extraout_s0_00,extraout_s1_00,extraout_s2_00,extraout_s3_00)
  ;
  *(float *)(param_1 + 600) = param_10;
  bVar5 = (*(uint *)(param_1 + 0x194) & 2) == 0;
  uVar6 = extraout_s15;
  if (!bVar5) {
    uVar6 = *(undefined4 *)(param_1 + 0x20c);
  }
  *(undefined4 *)(param_1 + 0x1f0) = local_58;
  *(undefined4 *)(param_1 + 500) = uStack_54;
  *(undefined4 *)(param_1 + 0x1f8) = uStack_50;
  *(undefined4 *)(param_1 + 0x1fc) = uStack_4c;
  if (bVar5) {
    uVar6 = *(undefined4 *)(param_1 + 0x208);
    *(undefined4 *)(param_1 + 0x200) = 0;
  }
  else {
    uVar2 = 0x3f800000;
    *(undefined4 *)(param_1 + 0x200) = 0x3f800000;
  }
  iVar4 = Game;
  *(undefined4 *)(param_1 + 0x204) = uVar2;
  *(undefined4 *)(param_1 + 0x254) = 0;
  if (bVar5) {
    *(undefined4 *)(param_1 + 0x210) = uVar6;
  }
  else {
    *(undefined4 *)(param_1 + 0x210) = uVar6;
  }
  *(undefined4 *)(param_1 + 0x21c) = 0;
  *(undefined4 *)(param_1 + 0x218) = 0;
  *(undefined4 *)(param_1 + 0x214) = *(undefined4 *)(param_1 + 0x210);
  fVar7 = *(float *)(iVar4 + 0x43e08);
  *(undefined4 *)(param_1 + 0x22c) = param_4;
  *(undefined4 *)(param_1 + 0x230) = param_5;
  cVar1 = gSpriteReference[param_3 * 0x20];
  *(float *)(param_1 + 600) = param_10 + fVar7;
  if (cVar1 == '\0') {
    uVar2 = VectorSignedToFloat(*(undefined4 *)(*(int *)(gSpriteReference + param_3 * 0x20 + 4) + 8)
                                ,(byte)(in_fpscr >> 0x16) & 3);
    uVar6 = VectorSignedToFloat(*(undefined4 *)(*(int *)(gSpriteReference + param_3 * 0x20 + 4) + 4)
                                ,(byte)(in_fpscr >> 0x16) & 3);
    *(undefined4 *)(param_1 + 0x240) = uVar2;
    *(undefined4 *)(param_1 + 0x23c) = uVar6;
  }
  else {
    iVar4 = param_3 * 4 + 1;
    uVar2 = VectorSignedToFloat(*(undefined4 *)(gSpriteReference + iVar4 * 8 + 4),
                                (byte)(in_fpscr >> 0x16) & 3);
    uVar6 = VectorSignedToFloat(*(undefined4 *)(gSpriteReference + iVar4 * 8),
                                (byte)(in_fpscr >> 0x16) & 3);
    *(undefined4 *)(param_1 + 0x240) = uVar2;
    *(undefined4 *)(param_1 + 0x23c) = uVar6;
  }
  *(int *)(param_1 + 0x268) = param_3;
  *(undefined4 *)(param_1 + 0x248) = uVar6;
  *(undefined4 *)(param_1 + 0x260) = 0;
  *(undefined4 *)(param_1 + 0x25c) = 0;
  *(undefined4 *)(param_1 + 0x26c) = param_11;
  *(undefined4 *)(param_1 + 0x24c) = *(undefined4 *)(param_1 + 0x240);
  *(undefined4 *)(param_1 + 0x6ec) = *(undefined4 *)(param_1 + 0x22c);
  *(undefined4 *)(param_1 + 0x6f0) = *(undefined4 *)(param_1 + 0x230);
  RePosition(param_1);
  return;
}
