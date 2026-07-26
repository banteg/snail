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
  undefined4 *puVar4;
  short *psVar5;
  short sVar6;
  uint *puVar7;
  short sVar8;
  uint uVar9;

  pcVar1 = (cRObject *)cRObjects::Add((cRObjects *)gObjectList);
  cRBod::SetObject((cRBod *)this,pcVar1);
  puVar7 = *(uint **)(this + 0x24);
  uVar2 = RShellMemoryMalloc(0x5c,"Logo Row");
  puVar7[0x28] = 1;
  puVar7[2] = 1;
  *puVar7 = *puVar7 | 0x16100000;
  *(undefined4 *)(uVar2 + 0x44) = 0x78;
  puVar7[0x43] = uVar2;
  uVar3 = RShellMemoryMalloc(0xf0,"Logo Row Strip");
  uVar9 = puVar7[0x43];
  *(undefined4 *)(uVar9 + 4) = 0x50;
  *(undefined4 *)(uVar2 + 0x48) = uVar3;
  uVar3 = RShellMemoryMalloc(0x640,"Logo Row VertexUV");
  *(undefined4 *)(uVar9 + 8) = uVar3;
  puVar4 = *(undefined4 **)(puVar7[0x43] + 8);
  psVar5 = *(short **)(puVar7[0x43] + 0x48);
  sVar6 = 0;
  do {
    sVar8 = sVar6 + 4;
    *psVar5 = sVar6;
    psVar5[1] = sVar6;
    psVar5[2] = sVar6 + 1;
    psVar5[3] = sVar6 + 3;
    *puVar4 = 0;
    psVar5[5] = sVar6 + 2;
    puVar4[1] = 0;
    psVar5[4] = sVar6 + 2;
    puVar4[2] = 0;
    puVar4[3] = 0;
    puVar4[4] = 0;
    psVar5 = psVar5 + 6;
    puVar4 = puVar4 + 0x14;
    sVar6 = sVar8;
  } while (sVar8 != 0x50);
  return;
}
