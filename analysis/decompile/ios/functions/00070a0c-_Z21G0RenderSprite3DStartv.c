/*
 * mangled: _Z21G0RenderSprite3DStartv
 * demangled: G0RenderSprite3DStart()
 * address: 00070a0c
 * size: 204
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* G0RenderSprite3DStart() */

void G0RenderSprite3DStart(void)

{
  _glMatrixMode(0x1702);
  _glLoadIdentity();
  _glMatrixMode(0x1700);
  _glPushMatrix();
  _glLoadIdentity();
  _BufferCount = 0;
  _BufferTexture = 0xffffffff;
  _BufferColour = 0;
  _BufferUVArray = RShellMemoryScratch();
  _BufferBlendMode = 0xffffffff;
  _BufferSPA = _BufferUVArray;
  _glVertexPointer(3,0x1406,0x14,_BufferUVArray);
  _glTexCoordPointer(2,0x1406,0x14,_BufferUVArray + 0xc);
  _glBindBuffer(0x8893,_gSpriteIndexArrayVBO);
  _glEnableClientState(&DAT_00008074);
  _glEnableClientState(&DAT_00008078);
  if (_GLCullFlag == '\0') {
    return;
  }
  _GLCullFlag = 0;
  _glDisable(0xb44);
  return;
}
