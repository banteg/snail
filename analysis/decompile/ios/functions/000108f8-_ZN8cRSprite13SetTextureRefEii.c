/*
 * mangled: _ZN8cRSprite13SetTextureRefEii
 * demangled: cRSprite::SetTextureRef(int, int)
 * address: 000108f8
 * size: 60
 */

/* cRSprite::SetTextureRef(int, int) */

void __thiscall cRSprite::SetTextureRef(cRSprite *this,int param_1,int param_2)

{
  int iVar1;

  iVar1 = *(int *)(&DAT_002ac600 + param_1 * 0x20);
  *(int *)(this + 0x98) = param_1;
  *(int *)(this + 0x1c) = iVar1 + param_2 * 0xa4;
  return;
}
