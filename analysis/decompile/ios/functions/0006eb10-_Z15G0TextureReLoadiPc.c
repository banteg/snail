/*
 * mangled: _Z15G0TextureReLoadiPc
 * demangled: G0TextureReLoad(int, char*)
 * address: 0006eb10
 * size: 124
 */

/* G0TextureReLoad(int, char*) */

void G0TextureReLoad(int param_1,char *param_2)

{
  _glDeleteTextures(1,param_1 * 4 + texNameList);
  _glGenTextures(1,param_1 * 4 + texNameList);
  Rstrcpy(PTR__gTextureList_001b61d0 + param_1 * 0xa4 + 0x14,param_2);
  G0TextureLoad(param_1,1);
  return;
}
