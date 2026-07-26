/*
 * mangled: _Z15G0RemoveTextureP9cRTexture
 * demangled: G0RemoveTexture(cRTexture*)
 * address: 0008b158
 * size: 32
 */

/* G0RemoveTexture(cRTexture*) */

void G0RemoveTexture(cRTexture *param_1)

{
  glDeleteTextures(1,texNameList + *(int *)(param_1 + 0x8c) * 4);
  return;
}
