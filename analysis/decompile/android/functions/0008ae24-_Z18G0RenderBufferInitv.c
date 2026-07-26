/*
 * mangled: _Z18G0RenderBufferInitv
 * demangled: G0RenderBufferInit()
 * address: 0008ae24
 * size: 168
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* G0RenderBufferInit() */

void G0RenderBufferInit(void)

{
  BufferCount = 0;
  BufferTexture = 0xffffffff;
  BufferColour = 0;
  BufferUVArray = RShellMemoryScratch();
  BufferBlendMode = 0xffffffff;
  BufferSPA = BufferUVArray;
  glVertexPointer(3,0x1406,0x14,BufferUVArray);
  glTexCoordPointer(2,0x1406,0x14,BufferUVArray + 0xc);
  glBindBuffer(0x8893,gSpriteIndexArrayVBO);
  return;
}
