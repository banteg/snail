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

  if (((*(uint *)(*(int *)(DAT_0006e4cc + 0x6e3fc + DAT_0006e4d0) + 0x1c) & 0x10) != 0) &&
     (this[0x438] == (cRSubGoldy)0x0)) {
    iVar1 = cRSpriteManager::New
                      (*(int *)(DAT_0006e4cc + 0x6e3fc + DAT_0006e4d4),*(int *)(this + 0x370),0x13,
                       -1);
    uVar3 = DAT_0006e4b8;
    uVar2 = DAT_0006e4b4;
    *(undefined4 *)(iVar1 + 0x68) = DAT_0006e4b4;
    *(undefined4 *)(iVar1 + 0x70) = uVar2;
    *(undefined4 *)(iVar1 + 0x6c) = uVar3;
    *(undefined4 *)(iVar1 + 0x54) = uVar2;
    uVar3 = DAT_0006e4bc;
    *(undefined4 *)(iVar1 + 0x58) = uVar2;
    *(undefined4 *)(iVar1 + 0x74) = uVar3;
    *(undefined4 *)(iVar1 + 0x60) = DAT_0006e4c0;
    *(undefined4 *)(iVar1 + 100) = DAT_0006e4c4;
    fVar4 = *(float *)(this + 0x410);
    *(undefined4 *)(iVar1 + 0x78) = uVar2;
    fVar4 = fVar4 * DAT_0006e4c8;
    *(uint *)(iVar1 + 4) = *(uint *)(iVar1 + 4) | 0x800;
    *(float *)(iVar1 + 0x5c) = fVar4;
    uVar2 = *(undefined4 *)(param_1 + 4);
    uVar3 = *(undefined4 *)(param_1 + 8);
    *(undefined4 *)(iVar1 + 0x48) = *(undefined4 *)param_1;
    *(undefined4 *)(iVar1 + 0x4c) = uVar2;
    *(undefined4 *)(iVar1 + 0x50) = uVar3;
  }
  return;
}
