/*
 * mangled: _Z9G0SetCullb
 * demangled: G0SetCull(bool)
 * address: 0008c668
 * size: 88
 */

/* G0SetCull(bool) */

void G0SetCull(bool param_1)

{
  if ((bool)GLCullFlag == param_1) {
    return;
  }
  if (!param_1) {
    GLCullFlag = param_1;
    glDisable(0xb44);
    return;
  }
  GLCullFlag = 1;
  glEnable(0xb44);
  glCullFace(0x404);
  return;
}
