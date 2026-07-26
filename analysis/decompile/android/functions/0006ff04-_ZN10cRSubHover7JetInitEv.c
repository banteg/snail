/*
 * mangled: _ZN10cRSubHover7JetInitEv
 * demangled: cRSubHover::JetInit()
 * address: 0006ff04
 * size: 264
 */

/* cRSubHover::JetInit() */

void __thiscall cRSubHover::JetInit(cRSubHover *this)

{
  int iVar1;
  uint uVar2;
  cRSubHover *pcVar3;
  int iVar4;
  int iVar5;
  float extraout_s0;
  float extraout_s1;
  float extraout_s2;
  float extraout_s3;
  undefined4 local_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;

  iVar5 = 0;
  do {
    iVar4 = 0;
    pcVar3 = this + iVar5 * 0x20 + 0x28;
    do {
      iVar1 = cRSpriteManager::New((int)&gRSpriteManager,1,0x89,-1);
      iVar4 = iVar4 + 1;
      uVar2 = *(uint *)(iVar1 + 4);
      *(undefined4 *)(iVar1 + 0x68) = 0;
      *(int *)(pcVar3 + -8) = iVar1;
      *(undefined4 *)(iVar1 + 0x6c) = 0;
      *(undefined4 *)(iVar1 + 0x70) = 0;
      *(undefined4 *)(iVar1 + 0x74) = 0;
      *(undefined4 *)(iVar1 + 100) = 0;
      *(undefined4 *)(iVar1 + 0x60) = 0;
      *(undefined4 *)(iVar1 + 0x5c) = 0;
      *(undefined4 *)(iVar1 + 0x58) = 0;
      *(undefined4 *)(iVar1 + 0x54) = 0;
      *(undefined4 *)(iVar1 + 0x78) = 0;
      *(uint *)(iVar1 + 4) = uVar2 | 0x800;
      tColour::tColour((tColour *)&local_48,extraout_s0,extraout_s1,extraout_s2,extraout_s3);
      *(undefined4 *)(*(int *)(pcVar3 + -8) + 0x28) = 1;
      *(undefined4 *)(iVar1 + 0x2c) = local_48;
      *(undefined4 *)(iVar1 + 0x30) = uStack_44;
      *(undefined4 *)(iVar1 + 0x34) = uStack_40;
      *(undefined4 *)(iVar1 + 0x38) = uStack_3c;
      *(undefined4 *)pcVar3 = 0;
      *(undefined4 *)(pcVar3 + 4) = 0x3e2aaaab;
      *(undefined4 *)(pcVar3 + -4) = 0;
      pcVar3 = pcVar3 + 0x10;
    } while (iVar4 != 2);
    iVar5 = iVar5 + 1;
  } while (iVar5 != 0xf);
  return;
}
