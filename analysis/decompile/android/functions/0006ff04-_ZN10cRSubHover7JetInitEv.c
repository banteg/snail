/*
 * mangled: _ZN10cRSubHover7JetInitEv
 * demangled: cRSubHover::JetInit()
 * address: 0006ff04
 * size: 264
 */

/* cRSubHover::JetInit() */

void __thiscall cRSubHover::JetInit(cRSubHover *this)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  cRSubHover *pcVar6;
  int iVar7;
  int iVar8;
  float extraout_s0;
  float extraout_s1;
  float extraout_s2;
  float extraout_s3;
  undefined4 local_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;

  uVar2 = DAT_00070010;
  uVar1 = DAT_0007000c;
  iVar4 = *(int *)(DAT_00070018 + 0x6ff14 + DAT_0007001c);
  iVar8 = 0;
  do {
    iVar7 = 0;
    pcVar6 = this + iVar8 * 0x20 + 0x28;
    do {
      iVar3 = cRSpriteManager::New(iVar4,1,0x89,-1);
      iVar7 = iVar7 + 1;
      uVar5 = *(uint *)(iVar3 + 4);
      *(undefined4 *)(iVar3 + 0x68) = uVar1;
      *(int *)(pcVar6 + -8) = iVar3;
      *(undefined4 *)(iVar3 + 0x6c) = uVar1;
      *(undefined4 *)(iVar3 + 0x70) = uVar1;
      *(undefined4 *)(iVar3 + 0x74) = uVar1;
      *(undefined4 *)(iVar3 + 100) = uVar1;
      *(undefined4 *)(iVar3 + 0x60) = uVar1;
      *(undefined4 *)(iVar3 + 0x5c) = uVar1;
      *(undefined4 *)(iVar3 + 0x58) = uVar1;
      *(undefined4 *)(iVar3 + 0x54) = uVar1;
      *(undefined4 *)(iVar3 + 0x78) = uVar1;
      *(uint *)(iVar3 + 4) = uVar5 | 0x800;
      tColour::tColour((tColour *)&local_48,extraout_s0,extraout_s1,extraout_s2,extraout_s3);
      *(undefined4 *)(*(int *)(pcVar6 + -8) + 0x28) = 1;
      *(undefined4 *)(iVar3 + 0x2c) = local_48;
      *(undefined4 *)(iVar3 + 0x30) = uStack_44;
      *(undefined4 *)(iVar3 + 0x34) = uStack_40;
      *(undefined4 *)(iVar3 + 0x38) = uStack_3c;
      *(undefined4 *)pcVar6 = uVar1;
      *(undefined4 *)(pcVar6 + 4) = uVar2;
      *(undefined4 *)(pcVar6 + -4) = 0;
      pcVar6 = pcVar6 + 0x10;
    } while (iVar7 != 2);
    iVar8 = iVar8 + 1;
  } while (iVar8 != 0xf);
  return;
}
