/*
 * mangled: _Z15G0FontRenderEndv
 * demangled: G0FontRenderEnd()
 * address: 0006f0cc
 * size: 168
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* G0FontRenderEnd() */

void G0FontRenderEnd(void)

{
  undefined4 local_c;

  if (0 < _BufferCount) {
    _glDrawElements(5,_BufferCount * 6,0x1403,0);
  }
  _glDepthMask(1);
  _glEnable(0xb71);
  _glPopMatrix();
  _glMatrixMode(0x1701);
  _glPopMatrix();
  _glDisableClientState(&DAT_00008074);
  _glDisableClientState(&DAT_00008078);
  tColourSmall::tColourSmall((tColourSmall *)&local_c);
  tColourSmall::White((tColourSmall *)&local_c);
  if (_GLColour != local_c) {
    _GLColour = local_c;
    _glColor4ub(local_c._2_1_,local_c._1_1_,local_c & 0xff,local_c._3_1_);
  }
  return;
}
