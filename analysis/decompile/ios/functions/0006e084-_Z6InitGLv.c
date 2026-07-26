/*
 * mangled: _Z6InitGLv
 * demangled: InitGL()
 * address: 0006e084
 * size: 252
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* InitGL() */

void InitGL(void)

{
  short *psVar1;
  short sVar2;
  short sVar3;
  short *psVar4;

  _gBindTextureRefLast = 0xffffffff;
  _gG0BlendMode = 0xffffffff;
  psVar1 = (short *)RShellMemoryScratch();
  psVar4 = psVar1;
  sVar2 = 0;
  do {
    psVar4[2] = sVar2 + 1;
    psVar4[3] = sVar2 + 3;
    psVar4[4] = sVar2 + 2;
    psVar4[5] = sVar2 + 2;
    sVar3 = sVar2 + 4;
    *psVar4 = sVar2;
    psVar4[1] = sVar2;
    psVar4 = psVar4 + 6;
    sVar2 = sVar3;
  } while (sVar3 != 0x400);
  _glGenBuffers(1,&_gSpriteIndexArrayVBO);
  _glBindBuffer(0x8893,_gSpriteIndexArrayVBO);
  _glBufferData(0x8893,0xc00,psVar1,&DAT_000088e4);
  _glBindBuffer(0x8893,0);
  _glShadeModel("");
  _glClearColor(0,0x3f800000,0,0);
  _glClearDepthf(0x3f800000);
  _glEnable(0xb71);
  _glDepthFunc(0x203);
  _glDepthRangef(0,0x3f800000);
  _glHint(0xc50,0x1101);
  _glHint(0xc52,0x1101);
  return;
}
