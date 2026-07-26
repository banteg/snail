/*
 * mangled: _Z21G0RenderSprite3DStartv
 * demangled: G0RenderSprite3DStart()
 * address: 0008c99c
 * size: 64
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* G0RenderSprite3DStart() */

void G0RenderSprite3DStart(void)

{
  glMatrixMode(0x1702);
  glLoadIdentity();
  glMatrixMode(0x1700);
  glPushMatrix();
  glLoadIdentity();
  G0RenderBufferInit();
  glEnableClientState(0x8074);
  glEnableClientState(0x8078);
  G0SetCull(false);
  return;
}
