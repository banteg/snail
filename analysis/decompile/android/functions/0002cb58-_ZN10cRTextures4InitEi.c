/*
 * mangled: _ZN10cRTextures4InitEi
 * demangled: cRTextures::Init(int)
 * address: 0002cb58
 * size: 44
 */

/* cRTextures::Init(int) */

void __thiscall cRTextures::Init(cRTextures *this,int param_1)

{
  *(int *)(this + 4) = param_1;
  *(undefined4 *)this = 0;
  cRHash::Init((cRHash *)(this + 0x39b0),param_1,TexturesFunctionGetName);
  return;
}
