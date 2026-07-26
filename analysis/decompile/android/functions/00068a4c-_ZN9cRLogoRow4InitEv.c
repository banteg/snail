/*
 * mangled: _ZN9cRLogoRow4InitEv
 * demangled: cRLogoRow::Init()
 * address: 00068a4c
 * size: 264
 */

/* cRLogoRow::Init() */

void __thiscall cRLogoRow::Init(cRLogoRow *this)

{
  cRObject *pcVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  char *pcVar5;
  undefined4 *puVar6;
  short *psVar7;
  short sVar8;
  uint *puVar9;
  short sVar10;
  int iVar11;
  uint uVar12;

  iVar11 = DAT_00068b58 + 0x68a64;
  pcVar1 = (cRObject *)cRObjects::Add(*(cRObjects **)(iVar11 + DAT_00068b5c));
  cRBod::SetObject((cRBod *)this,pcVar1);
  puVar9 = *(uint **)(this + 0x24);
  uVar2 = RShellMemoryMalloc(0x5c,(char *)(iVar11 + DAT_00068b60));
  pcVar5 = (char *)(iVar11 + DAT_00068b64);
  puVar9[0x28] = 1;
  puVar9[2] = 1;
  *puVar9 = *puVar9 | 0x16100000;
  *(undefined4 *)(uVar2 + 0x44) = 0x78;
  puVar9[0x43] = uVar2;
  uVar3 = RShellMemoryMalloc(0xf0,pcVar5);
  uVar12 = puVar9[0x43];
  pcVar5 = (char *)(iVar11 + DAT_00068b68);
  *(undefined4 *)(uVar12 + 4) = 0x50;
  *(undefined4 *)(uVar2 + 0x48) = uVar3;
  uVar4 = RShellMemoryMalloc(0x640,pcVar5);
  uVar3 = DAT_00068b54;
  *(undefined4 *)(uVar12 + 8) = uVar4;
  puVar6 = *(undefined4 **)(puVar9[0x43] + 8);
  psVar7 = *(short **)(puVar9[0x43] + 0x48);
  sVar8 = 0;
  do {
    sVar10 = sVar8 + 4;
    *psVar7 = sVar8;
    psVar7[1] = sVar8;
    psVar7[2] = sVar8 + 1;
    psVar7[3] = sVar8 + 3;
    *puVar6 = uVar3;
    psVar7[5] = sVar8 + 2;
    puVar6[1] = uVar3;
    psVar7[4] = sVar8 + 2;
    puVar6[2] = uVar3;
    puVar6[3] = uVar3;
    puVar6[4] = uVar3;
    psVar7 = psVar7 + 6;
    puVar6 = puVar6 + 0x14;
    sVar8 = sVar10;
  } while (sVar10 != 0x50);
  return;
}
