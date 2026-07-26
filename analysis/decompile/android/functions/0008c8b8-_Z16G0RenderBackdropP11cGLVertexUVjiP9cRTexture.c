/*
 * mangled: _Z16G0RenderBackdropP11cGLVertexUVjiP9cRTexture
 * demangled: G0RenderBackdrop(cGLVertexUV*, unsigned int, int, cRTexture*)
 * address: 0008c8b8
 * size: 228
 */

/* G0RenderBackdrop(cGLVertexUV*, unsigned int, int, cRTexture*) */

void G0RenderBackdrop(cGLVertexUV *param_1,uint param_2,int param_3,cRTexture *param_4)

{
  float extraout_s0;
  float extraout_s1;
  float extraout_s2;
  float extraout_s3;
  tColourSmall atStack_1c [4];

  G0FontRenderStart();
  glDisable(0xb71);
  glDisable(0xbe2);
  tColourSmall::tColourSmall(atStack_1c);
  tColourSmall::Set(atStack_1c,extraout_s0,extraout_s1,extraout_s2,extraout_s3);
  G0SetColour(atStack_1c);
  G0BindTexture(*(int *)(param_4 + 0x8c));
  glEnableClientState(0x8074);
  glEnableClientState(0x8078);
  glVertexPointer(3,0x1406,0x14,param_1);
  glTexCoordPointer(2,0x1406,0x14,param_1 + 0xc);
  glBindBuffer(0x8893,param_2);
  glDrawElements(5,param_3,0x1403,0);
  glBindBuffer(0x8893,0);
  glDisableClientState(0x8074);
  glDisableClientState(0x8078);
  G0FontRenderEnd();
  return;
}
