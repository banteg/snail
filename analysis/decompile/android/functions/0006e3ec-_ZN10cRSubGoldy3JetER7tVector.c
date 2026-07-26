/*
 * mangled: _ZN10cRSubGoldy3JetER7tVector
 * demangled: cRSubGoldy::Jet(tVector&)
 * address: 0006e3ec
 * size: 200
 */

/* cRSubGoldy::Jet(tVector&) */

void __thiscall cRSubGoldy::Jet(cRSubGoldy *this,tVector *param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  float fVar4;

  if (((gConfig._28_4_ & 0x10) != 0) && (this[0x438] == (cRSubGoldy)0x0)) {
    iVar1 = cRSpriteManager::New((int)&gRSpriteManager,*(int *)(this + 0x370),0x13,-1);
    *(undefined4 *)(iVar1 + 0x68) = 0;
    *(undefined4 *)(iVar1 + 0x70) = 0;
    *(undefined4 *)(iVar1 + 0x6c) = 0x3daaaaab;
    *(undefined4 *)(iVar1 + 0x54) = 0;
    *(undefined4 *)(iVar1 + 0x58) = 0;
    *(undefined4 *)(iVar1 + 0x74) = 0x3f555556;
    *(undefined4 *)(iVar1 + 0x60) = 0x3f000000;
    *(undefined4 *)(iVar1 + 100) = 0x3dcccccd;
    fVar4 = *(float *)(this + 0x410);
    *(undefined4 *)(iVar1 + 0x78) = 0;
    *(uint *)(iVar1 + 4) = *(uint *)(iVar1 + 4) | 0x800;
    *(float *)(iVar1 + 0x5c) = fVar4 * 0.7;
    uVar2 = *(undefined4 *)(param_1 + 4);
    uVar3 = *(undefined4 *)(param_1 + 8);
    *(undefined4 *)(iVar1 + 0x48) = *(undefined4 *)param_1;
    *(undefined4 *)(iVar1 + 0x4c) = uVar2;
    *(undefined4 *)(iVar1 + 0x50) = uVar3;
  }
  return;
}
