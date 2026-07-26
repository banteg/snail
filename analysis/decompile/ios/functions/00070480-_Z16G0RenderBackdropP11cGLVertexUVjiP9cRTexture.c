/*
 * mangled: _Z16G0RenderBackdropP11cGLVertexUVjiP9cRTexture
 * demangled: G0RenderBackdrop(cGLVertexUV*, unsigned int, int, cRTexture*)
 * address: 00070480
 * size: 268
 */

/* G0RenderBackdrop(cGLVertexUV*, unsigned int, int, cRTexture*) */

void G0RenderBackdrop(cGLVertexUV *param_1,uint param_2,int param_3,cRTexture *param_4)

{
  undefined4 local_1c;

  G0FontRenderStart();
  _glDisable(0xb71);
  _glDisable(0xbe2);
  tColourSmall::tColourSmall((tColourSmall *)&local_1c);
  tColourSmall::Set((tColourSmall *)&local_1c,1.0,1.0,1.0,1.0);
  if (_GLColour != local_1c) {
    _GLColour = local_1c;
    _glColor4ub(local_1c._2_1_,local_1c._1_1_,local_1c & 0xff,local_1c._3_1_);
  }
  G0BindTexture(*(int *)(param_4 + 0x8c));
  _glEnableClientState(&DAT_00008074);
  _glEnableClientState(&DAT_00008078);
  _glVertexPointer(3,0x1406,0x14,param_1);
  _glTexCoordPointer(2,0x1406,0x14,param_1 + 0xc);
  _glBindBuffer(0x8893,param_2);
  _glDrawElements(5,param_3,0x1403,0);
  _glBindBuffer(0x8893,0);
  _glDisableClientState(&DAT_00008074);
  _glDisableClientState(&DAT_00008078);
  G0FontRenderEnd();
  return;
}
