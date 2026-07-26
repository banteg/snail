/*
 * mangled: _ZN8cRSprite13SetTextureRefEii
 * demangled: cRSprite::SetTextureRef(int, int)
 * address: 0003cdb0
 * size: 44
 */

/* cRSprite::SetTextureRef(int, int) */

void __thiscall cRSprite::SetTextureRef(cRSprite *this,int param_1,int param_2)

{
  *(int *)(this + 0x98) = param_1;
  *(int *)(this + 0x1c) = param_2 * 0xa4 + *(int *)(gSpriteReference + param_1 * 0x20 + 4);
  return;
}
