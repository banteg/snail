/*
 * mangled: _Z19G0RenderSprite3DEndv
 * demangled: G0RenderSprite3DEnd()
 * address: 0008af28
 * size: 44
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* G0RenderSprite3DEnd() */

void G0RenderSprite3DEnd(void)

{
  G0RenderBufferRender();
  G0RenderBufferUnInit();
  glMatrixMode(0x1700);
  glPopMatrix();
  glDisableClientState(0x8074);
  glDisableClientState(0x8078);
  return;
}
