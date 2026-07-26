/*
 * mangled: _Z15G0FontRenderEndv
 * demangled: G0FontRenderEnd()
 * address: 0008bfd4
 * size: 64
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* G0FontRenderEnd() */

void G0FontRenderEnd(void)

{
  G0RenderBufferRender();
  glDepthMask(1);
  glEnable(0xb71);
  glPopMatrix();
  glMatrixMode(0x1701);
  glPopMatrix();
  glDisableClientState(0x8074);
  glDisableClientState(0x8078);
  G0ResetColour();
  return;
}
