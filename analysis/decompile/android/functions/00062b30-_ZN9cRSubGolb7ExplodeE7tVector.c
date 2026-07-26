/*
 * mangled: _ZN9cRSubGolb7ExplodeE7tVector
 * demangled: cRSubGolb::Explode(tVector)
 * address: 00062b30
 * size: 180
 */

/* cRSubGolb::Explode(tVector) */

void cRSubGolb::Explode(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  int iVar2;

  if ((*(uint *)(*(int *)(DAT_00062bfc + 0x62b50 + DAT_00062c00) + 0x1c) & 0x10) != 0) {
    iVar2 = cRSpriteManager::New
                      (*(int *)(DAT_00062bfc + 0x62b50 + DAT_00062c04),
                       *(int *)(*(int *)(param_1 + 600) + 0x370),0x13,-1);
    uVar1 = DAT_00062be4;
    *(undefined4 *)(iVar2 + 0x78) = DAT_00062be4;
    *(undefined4 *)(iVar2 + 0x68) = uVar1;
    *(undefined4 *)(iVar2 + 0x70) = uVar1;
    *(undefined4 *)(iVar2 + 0x5c) = uVar1;
    *(undefined4 *)(iVar2 + 0x54) = uVar1;
    *(undefined4 *)(iVar2 + 0x6c) = DAT_00062be8;
    *(undefined4 *)(iVar2 + 0x74) = DAT_00062bec;
    *(undefined4 *)(iVar2 + 0x60) = DAT_00062bf0;
    *(undefined4 *)(iVar2 + 100) = DAT_00062bf4;
    *(undefined4 *)(iVar2 + 0x58) = DAT_00062bf8;
    *(uint *)(iVar2 + 4) = *(uint *)(iVar2 + 4) | 0x800;
    *(undefined4 *)(iVar2 + 0x48) = param_2;
    *(undefined4 *)(iVar2 + 0x4c) = param_3;
    *(undefined4 *)(iVar2 + 0x50) = param_4;
  }
  return;
}
