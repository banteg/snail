/*
 * mangled: _Z17G0FontRenderStartv
 * demangled: G0FontRenderStart()
 * address: 00070234
 * size: 496
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* G0FontRenderStart() */

void G0FontRenderStart(void)

{
  undefined *puVar1;
  float fVar2;
  float fVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  float fVar6;
  float fVar7;

  fVar2 = (float)RShellGetScreenWidth();
  fVar7 = 1.0;
  fVar3 = (float)RShellGetScreenHeight();
  _glMatrixMode(0x1701);
  _glPushMatrix();
  _glLoadIdentity();
  uVar4 = RShellGetScreenWidth();
  uVar5 = RShellGetScreenHeight();
  _glOrthof(0,uVar4,uVar5,0,0xbf800000,fVar7);
  _glMatrixMode(0x1702);
  _glLoadIdentity();
  _glMatrixMode(0x1700);
  _glPushMatrix();
  _glLoadIdentity();
  _glTranslatef(fVar2 * 0.5,fVar3 * 0.5,0);
  puVar1 = PTR__Game_001b60b8;
  _glRotatef(*(uint *)(*(int *)PTR__Game_001b60b8 + 0x3c) ^ 0x80000000,0,0,fVar7);
  fVar6 = (float)Sin(*(float *)(*(int *)puVar1 + 0x3c) * 0.01745);
  fVar6 = ABS(fVar6);
  _glScalef((fVar7 - fVar6) + fVar6 * (fVar3 / fVar2),(fVar7 - fVar6) + fVar6 * (fVar2 / fVar3),0);
  _glTranslatef(fVar2 * -0.5,fVar3 * -0.5,0);
  _glEnable(0xde1);
  _glDepthMask(0);
  _glDisable(0xb71);
  _glEnableClientState(&DAT_00008074);
  _glEnableClientState(&DAT_00008078);
  if (_GLCullFlag != '\0') {
    _GLCullFlag = '\0';
    _glDisable(0xb44);
  }
  _BufferCount = 0;
  _BufferTexture = 0xffffffff;
  _BufferColour = 0;
  _BufferUVArray = RShellMemoryScratch();
  _BufferBlendMode = 0xffffffff;
  _BufferSPA = _BufferUVArray;
  _glVertexPointer(3,0x1406,0x14,_BufferUVArray);
  _glTexCoordPointer(2,0x1406,0x14,_BufferUVArray + 0xc);
  _glBindBuffer(0x8893,_gSpriteIndexArrayVBO);
  return;
}
