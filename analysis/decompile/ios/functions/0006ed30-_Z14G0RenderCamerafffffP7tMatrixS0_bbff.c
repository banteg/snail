/*
 * mangled: _Z14G0RenderCamerafffffP7tMatrixS0_bbff
 * demangled: G0RenderCamera(float, float, float, float, float, tMatrix*, tMatrix*, bool, bool, float, float)
 * address: 0006ed30
 * size: 808
 */

/* G0RenderCamera(float, float, float, float, float, tMatrix*, tMatrix*, bool, bool, float, float)
    */

void G0RenderCamera(float param_1,float param_2,float param_3,float param_4,float param_5,
                   tMatrix *param_6,tMatrix *param_7,bool param_8,bool param_9,float param_10,
                   float param_11)

{
  undefined *puVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  int iVar6;
  float fVar7;
  undefined4 local_38;

  fVar2 = (float)RShellGetScreenWidth();
  fVar7 = 1.0;
  fVar3 = (float)RShellGetScreenHeight();
  fVar4 = (float)RShellGetScreenWidth();
  fVar5 = (float)RShellGetScreenHeight();
  _glViewport((int)(fVar2 * (param_1 + (fVar7 - param_3) * 0.5)),
              (int)(fVar3 * (param_2 + (fVar7 - param_4) * 0.5)),(int)(param_3 * fVar4),
              (int)(param_4 * fVar5));
  fVar2 = (float)RShellGetScreenWidth();
  fVar3 = (float)RShellGetScreenHeight();
  _glScissor(0,0,(int)fVar2,(int)fVar3);
  _glEnable(0xc11);
  _G0AfterSprites = param_9;
  _glMatrixMode(0x1701);
  _glLoadIdentity();
  tColourSmall::tColourSmall((tColourSmall *)&local_38);
  tColourSmall::White((tColourSmall *)&local_38);
  if (_GLColour != local_38) {
    _GLColour = local_38;
    _glColor4ub(local_38._2_1_,local_38._1_1_,local_38 & 0xff,local_38._3_1_);
  }
  fVar3 = (param_3 * *(float *)PTR__gG0ScreenWidth_001b610c) /
          (param_4 * *(float *)PTR__gG0ScreenHeight_001b6114);
  fVar2 = (float)_tanf((param_5 * 3.1415927) / 360.0);
  fVar2 = fVar2 * 0.3;
  _glFrustumf(param_11 * 0.05 - fVar2 * fVar3,param_11 * 0.05 + fVar3 * fVar2,-fVar2,fVar2,
              0x3e99999a,0x42500000);
  _glRotatef(param_10,0,0,fVar7);
  _glMatrixMode(0x1700);
  _glLoadIdentity();
  gluLookAt(*(float *)(param_6 + 0x30),*(float *)(param_6 + 0x34),*(float *)(param_6 + 0x38),
            *(float *)(param_6 + 0x30) + *(float *)(param_6 + 0x20),
            *(float *)(param_6 + 0x34) + *(float *)(param_6 + 0x24),
            *(float *)(param_6 + 0x38) + *(float *)(param_6 + 0x28),*(float *)(param_6 + 0x10),
            *(float *)(param_6 + 0x14),*(float *)(param_6 + 0x18));
  _glEnable(0xb71);
  _glDepthFunc(0x203);
  _glDepthMask(1);
  _glDepthRangef(0xbf800000,fVar7);
  puVar1 = PTR__Game_001b60b8;
  if (param_8) {
    if (*(char *)(*(int *)PTR__Game_001b60b8 + 4) != '\0') {
      _glEnable(0xb60);
      _glFogfv(0xb66,*(int *)puVar1 + 0x14);
      _glFogf(0xb62,0x3ca3d70a);
      _glHint(0xc54,0x1100);
      iVar6 = *(int *)puVar1;
      _glClearColor(*(undefined4 *)(iVar6 + 0x14),*(undefined4 *)(iVar6 + 0x18),
                    *(undefined4 *)(iVar6 + 0x1c),*(undefined4 *)(iVar6 + 0x20));
      goto LAB_0006efac;
    }
  }
  _glDisable(0xb60);
  _glClearColor(0,0,0,0);
LAB_0006efac:
  _G0Camera = param_6;
  _G0CameraInv = param_7;
  _gBindTextureRefLast = 0xffffffff;
  _gG0BlendMode = 0xffffffff;
  _glTexEnvf(&DAT_00002300,&DAT_00002200,0x46040000);
  _glEnable(0xde1);
  _glEnableClientState(&DAT_00008074);
  _glEnableClientState(&DAT_00008078);
  return;
}
