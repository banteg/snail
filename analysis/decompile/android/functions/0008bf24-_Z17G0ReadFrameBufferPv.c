/*
 * mangled: _Z17G0ReadFrameBufferPv
 * demangled: G0ReadFrameBuffer(void*)
 * address: 0008bf24
 * size: 120
 */

/* G0ReadFrameBuffer(void*) */

void G0ReadFrameBuffer(void *param_1)

{
  glReadPixels(0,0,(int)gG0ScreenWidth % 8 + (int)gG0ScreenWidth,(int)gG0ScreenHeight,0x1907,0x1401,
               param_1);
  return;
}
