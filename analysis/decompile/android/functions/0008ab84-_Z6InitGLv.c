/*
 * mangled: _Z6InitGLv
 * demangled: InitGL()
 * address: 0008ab84
 * size: 368
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* InitGL() */

void InitGL(void)

{
  short *psVar1;
  short sVar2;
  short *psVar3;
  short sVar4;
  float extraout_s0;
  float extraout_s1;
  float extraout_s2;
  float extraout_s3;

  gBindTextureRefLast = 0xffffffff;
  gG0BlendMode = 0xffffffff;
  psVar1 = (short *)RShellMemoryScratch();
  psVar3 = psVar1;
  sVar2 = 0;
  do {
    sVar4 = sVar2 + 4;
    *psVar3 = sVar2;
    psVar3[1] = sVar2;
    psVar3[2] = sVar2 + 1;
    psVar3[3] = sVar2 + 3;
    psVar3[5] = sVar2 + 2;
    psVar3[4] = sVar2 + 2;
    psVar3 = psVar3 + 6;
    sVar2 = sVar4;
  } while (sVar4 != 0x400);
  glGenBuffers(1,&gSpriteIndexArrayVBO);
  glBindBuffer(0x8893,gSpriteIndexArrayVBO);
  glBufferData(0x8893,0xc00,psVar1,0x88e4);
  glBindBuffer(0x8893,0);
  glEnable(0xbd0);
  glEnable(0x809d);
  glShadeModel(0x1d00);
  glClearColor(0,0,0,0);
  glClearDepthf(0x3f800000);
  glEnable(0xb71);
  glDepthFunc(0x203);
  glDepthRangef(0,0x3f800000);
  glHint(0xc50,0x1101);
  glHint(0xc52,0x1101);
  glDisable(0xbc0);
  tColourSmall::Set((tColourSmall *)&GLColour,extraout_s0,extraout_s1,extraout_s2,extraout_s3);
  glColor4f(0x3f800000,0x3f800000,0x3f800000,0x3f800000);
  return;
}
