/*
 * mangled: _ZN10cRBackdrop4OpenEv
 * demangled: cRBackdrop::Open()
 * address: 00041b70
 * size: 1104
 */

/* cRBackdrop::Open() */

void __thiscall cRBackdrop::Open(cRBackdrop *this)

{
  short sVar1;
  undefined4 uVar2;
  short *psVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  uint in_fpscr;
  float fVar7;

  *(undefined4 *)(this + 0x3c) = 0xf0;
  uVar2 = RShellMemoryMalloc(0x974,"Back drop distortvertices");
  *(undefined4 *)(this + 0x40) = uVar2;
  psVar3 = (short *)RShellMemoryMalloc(*(int *)(this + 0x3c) << 1,"Backdrop index list");
  iVar4 = 0;
  *(undefined4 *)(this + 0x13c8) = 0;
  *(undefined4 *)(this + 0x13cc) = 0;
  *(short **)(this + 0x44) = psVar3;
  while( true ) {
    sVar1 = (short)iVar4;
    psVar3[2] = sVar1 + 1;
    psVar3[3] = sVar1 + 0xb;
    psVar3[4] = sVar1 + 0xc;
    psVar3[5] = sVar1 + 0x16;
    psVar3[6] = sVar1 + 0x17;
    psVar3[7] = sVar1 + 0x21;
    psVar3[8] = sVar1 + 0x22;
    psVar3[9] = sVar1 + 0x2c;
    psVar3[10] = sVar1 + 0x2d;
    psVar3[0xb] = sVar1 + 0x37;
    psVar3[0xc] = sVar1 + 0x38;
    psVar3[0xd] = sVar1 + 0x42;
    psVar3[0xe] = sVar1 + 0x43;
    psVar3[0xf] = sVar1 + 0x4d;
    psVar3[0x10] = sVar1 + 0x4e;
    psVar3[0x11] = sVar1 + 0x58;
    psVar3[0x12] = sVar1 + 0x59;
    *psVar3 = sVar1;
    psVar3[1] = sVar1;
    psVar3[0x13] = sVar1 + 99;
    iVar4 = iVar4 + 1;
    psVar3[0x14] = sVar1 + 100;
    psVar3[0x15] = sVar1 + 0x6e;
    psVar3[0x16] = sVar1 + 0x6f;
    psVar3[0x17] = sVar1 + 0x6f;
    if (iVar4 == 10) break;
    psVar3 = psVar3 + 0x18;
  }
  iVar6 = 0;
  iVar4 = 0;
  do {
    iVar5 = iVar4 + 0xdc;
    fVar7 = (float)VectorSignedToFloat(iVar6,(byte)(in_fpscr >> 0x16) & 3);
    iVar6 = iVar6 + 1;
    *(undefined4 *)(*(int *)(this + 0x40) + iVar4) = 0;
    fVar7 = fVar7 / 10.0;
    *(undefined4 *)(*(int *)(this + 0x40) + iVar4 + 4) = 0;
    *(undefined4 *)(*(int *)(this + 0x40) + iVar4 + 8) = 0;
    *(float *)(*(int *)(this + 0x40) + iVar4 + 0xc) = fVar7;
    *(undefined4 *)(*(int *)(this + 0x40) + iVar4 + 0x10) = 0;
    *(undefined4 *)(*(int *)(this + 0x40) + iVar5) = 0;
    *(undefined4 *)(*(int *)(this + 0x40) + iVar5 + 4) = 0;
    *(undefined4 *)(*(int *)(this + 0x40) + iVar5 + 8) = 0;
    *(float *)(*(int *)(this + 0x40) + iVar5 + 0xc) = fVar7;
    *(undefined4 *)(*(int *)(this + 0x40) + iVar5 + 0x10) = 0x3dcccccd;
    iVar5 = iVar4 + 0x1b8;
    *(undefined4 *)(*(int *)(this + 0x40) + iVar5) = 0;
    *(undefined4 *)(*(int *)(this + 0x40) + iVar5 + 4) = 0;
    *(undefined4 *)(*(int *)(this + 0x40) + iVar5 + 8) = 0;
    *(float *)(*(int *)(this + 0x40) + iVar5 + 0xc) = fVar7;
    *(undefined4 *)(*(int *)(this + 0x40) + iVar5 + 0x10) = 0x3e4ccccd;
    iVar5 = iVar4 + 0x294;
    *(undefined4 *)(*(int *)(this + 0x40) + iVar5) = 0;
    *(undefined4 *)(*(int *)(this + 0x40) + iVar5 + 4) = 0;
    *(undefined4 *)(*(int *)(this + 0x40) + iVar5 + 8) = 0;
    *(float *)(*(int *)(this + 0x40) + iVar5 + 0xc) = fVar7;
    *(undefined4 *)(*(int *)(this + 0x40) + iVar5 + 0x10) = 0x3e99999a;
    iVar5 = iVar4 + 0x370;
    *(undefined4 *)(*(int *)(this + 0x40) + iVar5) = 0;
    *(undefined4 *)(*(int *)(this + 0x40) + iVar5 + 4) = 0;
    *(undefined4 *)(*(int *)(this + 0x40) + iVar5 + 8) = 0;
    *(float *)(*(int *)(this + 0x40) + iVar5 + 0xc) = fVar7;
    *(undefined4 *)(*(int *)(this + 0x40) + iVar5 + 0x10) = 0x3ecccccd;
    iVar5 = iVar4 + 0x44c;
    *(undefined4 *)(*(int *)(this + 0x40) + iVar5) = 0;
    *(undefined4 *)(*(int *)(this + 0x40) + iVar5 + 4) = 0;
    *(undefined4 *)(*(int *)(this + 0x40) + iVar5 + 8) = 0;
    *(float *)(*(int *)(this + 0x40) + iVar5 + 0xc) = fVar7;
    *(undefined4 *)(*(int *)(this + 0x40) + iVar5 + 0x10) = 0x3f000000;
    iVar5 = iVar4 + 0x528;
    *(undefined4 *)(*(int *)(this + 0x40) + iVar5) = 0;
    *(undefined4 *)(*(int *)(this + 0x40) + iVar5 + 4) = 0;
    *(undefined4 *)(*(int *)(this + 0x40) + iVar5 + 8) = 0;
    *(float *)(*(int *)(this + 0x40) + iVar5 + 0xc) = fVar7;
    *(undefined4 *)(*(int *)(this + 0x40) + iVar5 + 0x10) = 0x3f19999a;
    iVar5 = iVar4 + 0x604;
    *(undefined4 *)(*(int *)(this + 0x40) + iVar5) = 0;
    *(undefined4 *)(*(int *)(this + 0x40) + iVar5 + 4) = 0;
    *(undefined4 *)(*(int *)(this + 0x40) + iVar5 + 8) = 0;
    *(float *)(*(int *)(this + 0x40) + iVar5 + 0xc) = fVar7;
    *(undefined4 *)(*(int *)(this + 0x40) + iVar5 + 0x10) = 0x3f333333;
    iVar5 = iVar4 + 0x6e0;
    *(undefined4 *)(*(int *)(this + 0x40) + iVar5) = 0;
    *(undefined4 *)(*(int *)(this + 0x40) + iVar5 + 4) = 0;
    *(undefined4 *)(*(int *)(this + 0x40) + iVar5 + 8) = 0;
    *(float *)(*(int *)(this + 0x40) + iVar5 + 0xc) = fVar7;
    *(undefined4 *)(*(int *)(this + 0x40) + iVar5 + 0x10) = 0x3f4ccccd;
    iVar5 = iVar4 + 0x7bc;
    *(undefined4 *)(*(int *)(this + 0x40) + iVar5) = 0;
    *(undefined4 *)(*(int *)(this + 0x40) + iVar5 + 4) = 0;
    *(undefined4 *)(*(int *)(this + 0x40) + iVar5 + 8) = 0;
    *(float *)(*(int *)(this + 0x40) + iVar5 + 0xc) = fVar7;
    *(undefined4 *)(*(int *)(this + 0x40) + iVar5 + 0x10) = 0x3f666666;
    iVar5 = iVar4 + 0x898;
    iVar4 = iVar4 + 0x14;
    *(undefined4 *)(*(int *)(this + 0x40) + iVar5) = 0;
    *(undefined4 *)(*(int *)(this + 0x40) + iVar5 + 4) = 0;
    *(undefined4 *)(*(int *)(this + 0x40) + iVar5 + 8) = 0;
    *(float *)(*(int *)(this + 0x40) + iVar5 + 0xc) = fVar7;
    *(undefined4 *)(*(int *)(this + 0x40) + iVar5 + 0x10) = 0x3f800000;
  } while (iVar6 != 0xb);
  G0BackdropVBO((uint *)(this + 0x48),*(int *)(this + 0x3c),*(ushort **)(this + 0x44));
  return;
}
