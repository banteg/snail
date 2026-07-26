/*
 * mangled: _ZN9cRLogoRow4InitEv
 * demangled: cRLogoRow::Init()
 * address: 00065830
 * size: 388
 */

/* cRLogoRow::Init() */

void __thiscall cRLogoRow::Init(cRLogoRow *this)

{
  cRObject *pcVar1;
  uint uVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  uint *puVar6;
  short sVar7;

  pcVar1 = (cRObject *)cRObjects::Add((cRObjects *)PTR__gObjectList_001b61cc);
  cRBod::SetObject((cRBod *)this,pcVar1);
  puVar6 = *(uint **)(this + 0x24);
  uVar2 = RShellMemoryMalloc(0x5c,"Logo Row");
  *puVar6 = *puVar6 | 0x16100000;
  puVar6[2] = 1;
  puVar6[0x28] = 1;
  puVar6[0x43] = uVar2;
  *(undefined4 *)(uVar2 + 0x44) = 0x78;
  uVar2 = puVar6[0x43];
  uVar3 = RShellMemoryMalloc(*(int *)(uVar2 + 0x44) << 1,"Logo Row Strip");
  *(undefined4 *)(uVar2 + 0x48) = uVar3;
  *(undefined4 *)(puVar6[0x43] + 4) = 0x50;
  uVar2 = puVar6[0x43];
  uVar3 = RShellMemoryMalloc(*(int *)(uVar2 + 4) * 0x14,"Logo Row VertexUV");
  *(undefined4 *)(uVar2 + 8) = uVar3;
  iVar4 = 0;
  sVar7 = 0;
  do {
    *(short *)(*(int *)(puVar6[0x43] + 0x48) + iVar4) = sVar7;
    *(short *)(iVar4 + *(int *)(puVar6[0x43] + 0x48) + 2) = sVar7;
    *(short *)(iVar4 + *(int *)(puVar6[0x43] + 0x48) + 4) = sVar7 + 1;
    *(short *)(iVar4 + *(int *)(puVar6[0x43] + 0x48) + 6) = sVar7 + 3;
    *(short *)(iVar4 + *(int *)(puVar6[0x43] + 0x48) + 8) = sVar7 + 2;
    *(short *)(iVar4 + *(int *)(puVar6[0x43] + 0x48) + 10) = sVar7 + 2;
    iVar5 = iVar4 * 0x1555555c;
    iVar4 = iVar4 + 0xc;
    *(undefined4 *)(*(int *)(puVar6[0x43] + 8) + iVar5) = 0;
    *(undefined4 *)(*(int *)(puVar6[0x43] + 8) + iVar5 + 4) = 0;
    *(undefined4 *)(*(int *)(puVar6[0x43] + 8) + iVar5 + 8) = 0;
    *(undefined4 *)(*(int *)(puVar6[0x43] + 8) + iVar5 + 0xc) = 0;
    *(undefined4 *)(*(int *)(puVar6[0x43] + 8) + iVar5 + 0x10) = 0;
    sVar7 = sVar7 + 4;
  } while (iVar4 != 0xf0);
  return;
}
