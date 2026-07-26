/*
 * mangled: _Z19G0RenderSprite3DEndv
 * demangled: G0RenderSprite3DEnd()
 * address: 0006ecc0
 * size: 92
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* G0RenderSprite3DEnd() */

void G0RenderSprite3DEnd(void)

{
  if (0 < _BufferCount) {
    _glDrawElements(5,_BufferCount * 6,0x1403,0);
  }
  _glBindBuffer(0x8893,0);
  _glMatrixMode(0x1700);
  _glPopMatrix();
  _glDisableClientState(&DAT_00008074);
  _glDisableClientState(&DAT_00008078);
  return;
}
