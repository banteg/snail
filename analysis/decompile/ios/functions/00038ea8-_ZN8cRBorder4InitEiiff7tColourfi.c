/*
 * mangled: _ZN8cRBorder4InitEiiff7tColourfi
 * demangled: cRBorder::Init(int, int, float, float, tColour, float, int)
 * address: 00038ea8
 * size: 724
 */

/* cRBorder::Init(int, int, float, float, tColour, float, int) */

void cRBorder::Init(cRBorder *param_1,uint param_2,int param_3,undefined4 param_4,undefined4 param_5
                   ,undefined4 param_6,undefined4 param_7,undefined4 param_8,undefined4 param_9,
                   float param_10,undefined4 param_11)

{
  undefined *puVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  uint in_fpscr;
  float fVar5;
  undefined4 local_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 local_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;

  uVar2 = *(uint *)(param_1 + 4);
  iVar3 = *(int *)PTR__Game_001b60b8;
  if ((uVar2 & 0x200) == 0) {
    *(int *)(param_1 + 8) = iVar3 + 0xd14;
    *(undefined4 *)(param_1 + 0xc) = *(undefined4 *)(iVar3 + 0xd20);
    *(cRBorder **)(iVar3 + 0xd20) = param_1;
    if (*(int *)(param_1 + 0xc) != 0) {
      *(cRBorder **)(*(int *)(param_1 + 0xc) + 8) = param_1;
    }
    *(uint *)(param_1 + 4) = uVar2 | 0x200;
  }
  else {
    RShellError("List ADDafter");
  }
  *(undefined4 *)(param_1 + 0x3c) = 6;
  *(undefined1 **)(param_1 + 0x16c) = &DAT_40800000;
  param_1[0x50] = (cRBorder)0x0;
  *(undefined4 *)(param_1 + 0x6e8) = 0x3f800000;
  *(undefined4 *)(param_1 + 0x288) = 0;
  *(undefined4 *)(param_1 + 0x29c) = 0;
  *(undefined4 *)(param_1 + 0x208) = 0x41200000;
  param_1[0x228] = (cRBorder)0x0;
  *(undefined4 *)(param_1 + 0x6e4) = 0;
  param_1[0x2c4] = (cRBorder)0x0;
  *(undefined4 *)(param_1 + 0x20c) = 0x41700000;
  *(undefined4 *)(param_1 + 0x2c) = 1;
  *(undefined4 *)(param_1 + 0x6ec) = param_4;
  *(undefined4 *)(param_1 + 0x224) = 0x41a00000;
  *(undefined4 *)(param_1 + 0x264) = 0x41a00000;
  *(undefined4 *)(param_1 + 0x244) = 0;
  *(cRBorder **)(param_1 + 0x290) = param_1;
  *(cRBorder **)(param_1 + 700) = param_1;
  *(undefined4 *)(param_1 + 0x220) = 0;
  *(undefined4 *)(param_1 + 0x250) = 0;
  *(undefined4 *)(param_1 + 0x38) = 0x3f800000;
  *(uint *)(param_1 + 0x194) = param_2 | 0x40801;
  *(uint *)(param_1 + 0x198) = param_2 | 0x40801;
  *(undefined4 *)(param_1 + 0x6f0) = param_5;
  *(undefined4 *)(param_1 + 0x1b0) = param_6;
  *(undefined4 *)(param_1 + 0x1b4) = param_7;
  *(undefined4 *)(param_1 + 0x1b8) = param_8;
  *(undefined4 *)(param_1 + 0x1bc) = param_9;
  *(undefined4 *)(param_1 + 0x1c0) = param_6;
  *(undefined4 *)(param_1 + 0x1c4) = param_7;
  *(undefined4 *)(param_1 + 0x1c8) = param_8;
  *(undefined4 *)(param_1 + 0x1cc) = param_9;
  tColour::tColour((tColour *)&local_38,1.0,1.0,1.0,1.0);
  *(undefined4 *)(param_1 + 0x1e0) = local_38;
  *(undefined4 *)(param_1 + 0x1e4) = uStack_34;
  *(undefined4 *)(param_1 + 0x1e8) = uStack_30;
  *(undefined4 *)(param_1 + 0x1ec) = uStack_2c;
  tColour::tColour((tColour *)&local_48,1.0,1.0,1.0,1.0);
  *(float *)(param_1 + 600) = param_10;
  *(undefined4 *)(param_1 + 0x1f0) = local_48;
  *(undefined4 *)(param_1 + 500) = uStack_44;
  *(undefined4 *)(param_1 + 0x1f8) = uStack_40;
  *(undefined4 *)(param_1 + 0x1fc) = uStack_3c;
  if ((*(uint *)(param_1 + 0x194) & 2) == 0) {
    *(undefined4 *)(param_1 + 0x200) = 0;
    *(undefined4 *)(param_1 + 0x210) = *(undefined4 *)(param_1 + 0x208);
    uVar4 = 0;
  }
  else {
    *(undefined4 *)(param_1 + 0x200) = 0x3f800000;
    *(undefined4 *)(param_1 + 0x210) = *(undefined4 *)(param_1 + 0x20c);
    uVar4 = 0x3f800000;
  }
  *(undefined4 *)(param_1 + 0x204) = uVar4;
  *(undefined4 *)(param_1 + 0x214) = *(undefined4 *)(param_1 + 0x210);
  *(undefined4 *)(param_1 + 0x218) = 0;
  *(undefined4 *)(param_1 + 0x21c) = 0;
  *(undefined4 *)(param_1 + 0x254) = 0;
  fVar5 = *(float *)(*(int *)PTR__Game_001b60b8 + 0x43e08);
  *(undefined4 *)(param_1 + 0x230) = param_5;
  *(undefined4 *)(param_1 + 0x22c) = param_4;
  puVar1 = PTR__gSpriteReference_001b61c8;
  *(float *)(param_1 + 600) = param_10 + fVar5;
  if (puVar1[param_3 * 0x20] == '\0') {
    uVar4 = VectorSignedToFloat(*(undefined4 *)(*(int *)(puVar1 + param_3 * 0x20 + 4) + 4),
                                (byte)(in_fpscr >> 0x16) & 3);
    *(undefined4 *)(param_1 + 0x23c) = uVar4;
    uVar4 = VectorSignedToFloat(*(undefined4 *)(*(int *)(puVar1 + param_3 * 0x20 + 4) + 8),
                                (byte)(in_fpscr >> 0x16) & 3);
    *(undefined4 *)(param_1 + 0x240) = uVar4;
  }
  else {
    uVar4 = VectorSignedToFloat(*(undefined4 *)(puVar1 + param_3 * 0x20 + 8),
                                (byte)(in_fpscr >> 0x16) & 3);
    *(undefined4 *)(param_1 + 0x23c) = uVar4;
    uVar4 = VectorSignedToFloat(*(undefined4 *)(puVar1 + param_3 * 0x20 + 0xc),
                                (byte)(in_fpscr >> 0x16) & 3);
    *(undefined4 *)(param_1 + 0x240) = uVar4;
  }
  *(int *)(param_1 + 0x268) = param_3;
  *(undefined4 *)(param_1 + 0x248) = *(undefined4 *)(param_1 + 0x23c);
  *(undefined4 *)(param_1 + 0x24c) = *(undefined4 *)(param_1 + 0x240);
  *(undefined4 *)(param_1 + 0x6ec) = *(undefined4 *)(param_1 + 0x22c);
  *(undefined4 *)(param_1 + 0x6f0) = *(undefined4 *)(param_1 + 0x230);
  *(undefined4 *)(param_1 + 0x26c) = param_11;
  *(undefined4 *)(param_1 + 0x25c) = 0;
  *(undefined4 *)(param_1 + 0x260) = 0;
  RePosition(param_1);
  return;
}
