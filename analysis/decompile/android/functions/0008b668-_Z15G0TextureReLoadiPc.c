/*
 * mangled: _Z15G0TextureReLoadiPc
 * demangled: G0TextureReLoad(int, char*)
 * address: 0008b668
 * size: 120
 */

/* G0TextureReLoad(int, char*) */

void G0TextureReLoad(int param_1,char *param_2)

{
  cRResourceManager::RemoveTexture((cRResourceManager *)&gResourceManager,param_1);
  glDeleteTextures(1,texNameList + param_1 * 4);
  glGenTextures(1,texNameList + param_1 * 4);
  Rstrcpy(gTextureList + param_1 * 0xa4 + 0x14,param_2);
  G0TextureLoad(param_1,1);
  return;
}
