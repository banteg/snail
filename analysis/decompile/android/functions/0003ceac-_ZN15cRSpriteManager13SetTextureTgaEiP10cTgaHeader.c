/*
 * mangled: _ZN15cRSpriteManager13SetTextureTgaEiP10cTgaHeader
 * demangled: cRSpriteManager::SetTextureTga(int, cTgaHeader*)
 * address: 0003ceac
 * size: 80
 */

/* cRSpriteManager::SetTextureTga(int, cTgaHeader*) */

void __thiscall
cRSpriteManager::SetTextureTga(cRSpriteManager *this,int param_1,cTgaHeader *param_2)

{
  int iVar1;

  iVar1 = *(int *)(DAT_0003cefc + 0x3cec4 + DAT_0003cf00) + param_1 * 0x20;
  memcpy(*(void **)(*(int *)(iVar1 + 4) + 0x98),param_2,
         (uint)*(ushort *)(param_2 + 0xe) * (uint)*(ushort *)(param_2 + 0xc) * 4 + 0x12);
  G0TextureLoad(*(int *)(*(int *)(iVar1 + 4) + 0x8c),1);
  return;
}
