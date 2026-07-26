/*
 * mangled: _ZN6cRNuke4InitEv
 * demangled: cRNuke::Init()
 * address: 0006dd58
 * size: 268
 */

/* cRNuke::Init() */

void __thiscall cRNuke::Init(cRNuke *this)

{
  int iVar1;
  int iVar2;
  cRNuke *pcVar3;
  float fVar4;

  iVar1 = Game;
  if (*(int *)this == 0) {
    iVar2 = *(int *)(this + 4);
    fVar4 = *(float *)(iVar2 + 100);
    *(undefined4 *)this = 1;
    *(float *)(this + 0xc) = fVar4 - 5.0;
    fVar4 = *(float *)(iVar1 + 0x718f4);
    *(undefined4 *)(this + 0x14) = 0x3dd67751;
    *(undefined4 *)(this + 0x10) = 0;
    *(float *)(this + 8) = fVar4 + fVar4;
    pcVar3 = this;
    while( true ) {
      iVar1 = cRSpriteManager::New((int)&gRSpriteManager,*(int *)(iVar2 + 0x370),0x77,-1);
      *(int *)(pcVar3 + 0x18) = iVar1;
      pcVar3 = pcVar3 + 4;
      *(undefined4 *)(iVar1 + 0x78) = 0;
      *(undefined4 *)(iVar1 + 0x68) = 0;
      *(undefined4 *)(iVar1 + 0x6c) = 0;
      *(uint *)(iVar1 + 4) = *(uint *)(iVar1 + 4) | 0x800;
      *(undefined4 *)(iVar1 + 0x60) = 0x40400000;
      *(undefined4 *)(iVar1 + 100) = 0x40400000;
      *(undefined4 *)(iVar1 + 0x5c) = 0;
      *(undefined4 *)(iVar1 + 0x58) = 0;
      *(undefined4 *)(iVar1 + 0x54) = 0;
      *(undefined4 *)(iVar1 + 0x50) = 0;
      *(undefined4 *)(iVar1 + 0x4c) = 0;
      *(undefined4 *)(iVar1 + 0x48) = 0;
      if (pcVar3 == this + 100) break;
      iVar2 = *(int *)(this + 4);
    }
  }
  AI();
  return;
}
