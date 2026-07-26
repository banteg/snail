/*
 * mangled: _ZN6cRNuke4InitEv
 * demangled: cRNuke::Init()
 * address: 0006dd58
 * size: 268
 */

/* cRNuke::Init() */

void __thiscall cRNuke::Init(cRNuke *this)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  cRNuke *pcVar6;
  int iVar7;
  float fVar8;

  uVar3 = DAT_0006de70;
  uVar2 = DAT_0006de6c;
  uVar1 = DAT_0006de68;
  if (*(int *)this == 0) {
    iVar4 = *(int *)(this + 4);
    fVar8 = *(float *)(iVar4 + 100) - DAT_0006de64;
    iVar7 = *(int *)(DAT_0006de74 + 0x6dd74 + DAT_0006de7c);
    iVar5 = **(int **)(DAT_0006de74 + 0x6dd74 + DAT_0006de78);
    *(undefined4 *)this = 1;
    *(float *)(this + 0xc) = fVar8;
    fVar8 = *(float *)(iVar5 + 0x718f4);
    *(undefined4 *)(this + 0x14) = uVar2;
    *(undefined4 *)(this + 0x10) = uVar1;
    *(float *)(this + 8) = fVar8 + fVar8;
    pcVar6 = this;
    while( true ) {
      iVar4 = cRSpriteManager::New(iVar7,*(int *)(iVar4 + 0x370),0x77,-1);
      *(int *)(pcVar6 + 0x18) = iVar4;
      pcVar6 = pcVar6 + 4;
      *(undefined4 *)(iVar4 + 0x78) = uVar1;
      *(undefined4 *)(iVar4 + 0x68) = uVar1;
      *(undefined4 *)(iVar4 + 0x6c) = uVar1;
      *(uint *)(iVar4 + 4) = *(uint *)(iVar4 + 4) | 0x800;
      *(undefined4 *)(iVar4 + 0x60) = uVar3;
      *(undefined4 *)(iVar4 + 100) = uVar3;
      *(undefined4 *)(iVar4 + 0x5c) = uVar1;
      *(undefined4 *)(iVar4 + 0x58) = uVar1;
      *(undefined4 *)(iVar4 + 0x54) = uVar1;
      *(undefined4 *)(iVar4 + 0x50) = uVar1;
      *(undefined4 *)(iVar4 + 0x4c) = uVar1;
      *(undefined4 *)(iVar4 + 0x48) = uVar1;
      if (pcVar6 == this + 100) break;
      iVar4 = *(int *)(this + 4);
    }
  }
  AI();
  return;
}
