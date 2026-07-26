/*
 * mangled: _Z20G0RenderBufferRenderv
 * demangled: G0RenderBufferRender()
 * address: 0008aeec
 * size: 52
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* G0RenderBufferRender() */

void G0RenderBufferRender(void)

{
  if (BufferCount < 1) {
    return;
  }
  glDrawElements(5,BufferCount * 6,0x1403,0);
  return;
}
