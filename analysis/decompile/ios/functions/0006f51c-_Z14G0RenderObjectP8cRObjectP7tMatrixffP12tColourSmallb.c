/*
 * mangled: _Z14G0RenderObjectP8cRObjectP7tMatrixffP12tColourSmallb
 * demangled: G0RenderObject(cRObject*, tMatrix*, float, float, tColourSmall*, bool)
 * address: 0006f51c
 * size: 1928
 */

/* G0RenderObject(cRObject*, tMatrix*, float, float, tColourSmall*, bool) */

void G0RenderObject(cRObject *param_1,tMatrix *param_2,float param_3,float param_4,
                   tColourSmall *param_5,bool param_6)

{
  uint uVar1;
  uint uVar2;
  undefined4 uVar3;
  tMatrix *ptVar4;
  int iVar5;
  uint in_fpscr;
  float fVar6;
  float local_5c;
  float local_58;
  float local_54;
  float fStack_50;
  float local_4c;
  float local_48;
  float local_44;
  float fStack_40;
  float local_3c;
  float local_38;
  float local_34;
  float fStack_30;
  float local_2c;
  float fStack_28;
  float fStack_24;
  float fStack_20;

  uVar1 = *(uint *)param_1;
  if ((int)uVar1 < 0) {
    wprintf("DEBUG OBJECT\n");
    uVar1 = *(uint *)param_1;
  }
  if ((uVar1 & 0x40000) != 0) {
    return;
  }
  if (*(int *)(param_1 + 0xa0) == 0) {
    return;
  }
  if (_G0AfterSprites == '\0') {
    if (param_6) {
      return;
    }
  }
  else if (!param_6) {
    return;
  }
  if ((uVar1 & 0x200000) != 0) {
    iVar5 = *(int *)(param_1 + 0x104);
    fVar6 = (float)VectorSignedToFloat(*(undefined4 *)(iVar5 + 4),(byte)(in_fpscr >> 0x16) & 3);
    *(undefined4 *)(param_1 + 0xa4) =
         **(undefined4 **)(*(int *)(iVar5 + 0xc) + (int)(fVar6 * *(float *)(iVar5 + 0x10)) * 4);
    fVar6 = (float)VectorSignedToFloat(*(undefined4 *)(iVar5 + 4),(byte)(in_fpscr >> 0x16) & 3);
    *(undefined4 *)(param_1 + 0xcc) =
         *(undefined4 *)
          (*(int *)(*(int *)(iVar5 + 0xc) + (int)(fVar6 * *(float *)(iVar5 + 0x10)) * 4) + 8);
    fVar6 = (float)VectorSignedToFloat(*(undefined4 *)(iVar5 + 4),(byte)(in_fpscr >> 0x16) & 3);
    *(undefined4 *)(*(int *)(param_1 + 0x10c) + 0x50) =
         *(undefined4 *)
          (*(int *)(*(int *)(iVar5 + 0xc) + (int)(fVar6 * *(float *)(iVar5 + 0x10)) * 4) + 4);
    uVar1 = *(uint *)param_1;
  }
  ptVar4 = param_2;
  if ((uVar1 & 0x800000) != 0) {
    cRDistort::BuildMatrix((cRDistort *)(param_1 + 0xf0),param_2,(tMatrix *)&local_5c);
    ptVar4 = (tMatrix *)&local_5c;
  }
  _glMatrixMode(0x1700);
  _glPushMatrix();
  if ((*(uint *)param_1 & 0x80) == 0) {
    if ((*(uint *)param_1 & 0x1000) == 0) {
      _glMatrixMode(0x1702);
      _glLoadIdentity();
      goto LAB_0006f5b8;
    }
    _glMatrixMode(0x1702);
    _glLoadIdentity();
    _glScalef(0x3c000000,0x3c000000,0x3c000000);
    _glMatrixMode(0x1700);
  }
  else {
    _glMatrixMode(0x1702);
    _glLoadIdentity();
    if ((*(uint *)param_1 & 0x1000) == 0) {
      _glTranslatef(param_3,param_4,0);
    }
    else {
      _glScalef(0x3c000000,0x3c000000,0x3c000000);
      _glTranslatef(param_3 * 128.0,param_4 * 128.0,0);
    }
LAB_0006f5b8:
    _glMatrixMode(0x1700);
  }
  uVar1 = *(uint *)param_1;
  uVar2 = (uVar1 >> 0x14 ^ 1) & 1;
  if (uVar2 != _GLCullFlag) {
    if (uVar2 == 0) {
      _GLCullFlag = 0;
      _glDisable(0xb44);
      uVar1 = *(uint *)param_1;
    }
    else {
      _GLCullFlag = 1;
      _glEnable(0xb44);
      _glCullFace(0x404);
      uVar1 = *(uint *)param_1;
    }
  }
  if ((uVar1 & 0x1000) != 0) {
    local_5c = *(float *)ptVar4;
    local_58 = *(float *)(ptVar4 + 4);
    local_54 = *(float *)(ptVar4 + 8);
    fStack_50 = *(float *)(ptVar4 + 0xc);
    local_5c = *(float *)ptVar4 * 0.0078125;
    local_4c = *(float *)(ptVar4 + 0x10);
    local_48 = *(float *)(ptVar4 + 0x14);
    local_44 = *(float *)(ptVar4 + 0x18);
    fStack_40 = *(float *)(ptVar4 + 0x1c);
    local_3c = *(float *)(ptVar4 + 0x20);
    local_38 = *(float *)(ptVar4 + 0x24);
    local_34 = *(float *)(ptVar4 + 0x28);
    fStack_30 = *(float *)(ptVar4 + 0x2c);
    local_2c = *(float *)(ptVar4 + 0x30);
    fStack_28 = *(float *)(ptVar4 + 0x34);
    fStack_24 = *(float *)(ptVar4 + 0x38);
    fStack_20 = *(float *)(ptVar4 + 0x3c);
    local_58 = *(float *)(ptVar4 + 4) * 0.0078125;
    local_54 = *(float *)(ptVar4 + 8) * 0.0078125;
    local_4c = *(float *)(ptVar4 + 0x10) * 0.0078125;
    local_48 = *(float *)(ptVar4 + 0x14) * 0.0078125;
    local_44 = *(float *)(ptVar4 + 0x18) * 0.0078125;
    local_3c = *(float *)(ptVar4 + 0x20) * 0.0078125;
    local_38 = *(float *)(ptVar4 + 0x24) * 0.0078125;
    local_34 = *(float *)(ptVar4 + 0x28) * 0.0078125;
    ptVar4 = (tMatrix *)&local_5c;
  }
  _glMultMatrixf(ptVar4);
  G0SetBlend(*(int *)(param_1 + 8));
  if (_GLColour != *(int *)param_5) {
    _GLColour = *(int *)param_5;
    _glColor4ub(param_5[2],param_5[1],*param_5,param_5[3]);
  }
  uVar1 = *(uint *)param_1;
  if ((uVar1 & 0x4000000) == 0) {
    wprintf("Non GLVertex Remenant Object Render\n");
  }
  else {
    if (**(int **)(param_1 + 0x10c) == 0) goto LAB_0006f7c4;
    if ((uVar1 & 8) == 0) {
      G0BindTexture(*(int *)(**(int **)(param_1 + 0x10c) + 0x8c));
    }
    else {
      G0BindTexture(*(int *)(*(int *)(param_1 + 0xc) + 0x8c));
    }
    _glEnableClientState(&DAT_00008074);
    _glEnableClientState(&DAT_00008078);
    uVar1 = *(uint *)param_1;
    if ((uVar1 & 0x400000) == 0) {
      if ((uVar1 & 4) == 0) {
        if ((uVar1 & 0x10000000) == 0) {
          _glVertexPointer(3,0x1406,0x14,*(undefined4 *)(*(int *)(param_1 + 0x10c) + 8));
          uVar3 = 0x14;
          iVar5 = *(int *)(*(int *)(param_1 + 0x10c) + 8) + 0xc;
          goto LAB_0006fb64;
        }
        if ((uVar1 & 0x200) == 0) {
          if ((uVar1 & 0x1000) == 0) {
            _glVertexPointer(3,0x1406,0x14,*(undefined4 *)(*(int *)(param_1 + 0x10c) + 8));
            _glTexCoordPointer(2,0x1406,0x14,*(int *)(*(int *)(param_1 + 0x10c) + 8) + 0xc);
          }
          else {
            _glVertexPointer(3,0x1402,10,*(undefined4 *)(*(int *)(param_1 + 0x10c) + 8));
            _glTexCoordPointer(2,0x1402,10,*(int *)(*(int *)(param_1 + 0x10c) + 8) + 6);
          }
          goto LAB_0006fb14;
        }
        _glBindBuffer(0x8892,*(undefined4 *)(*(int *)(param_1 + 0x10c) + 0x4c));
        _glBindBuffer(0x8893,*(undefined4 *)(*(int *)(param_1 + 0x10c) + 0x58));
        if ((*(uint *)param_1 & 0x1000) == 0) {
          _glVertexPointer(3,0x1406,0x14);
          _glTexCoordPointer(2,0x1406,0x14,0xc);
        }
        else {
          _glVertexPointer(3,0x1402,10,0);
          _glTexCoordPointer(2,0x1402,10,6);
        }
      }
      else {
        if ((uVar1 & 0x10000000) == 0) {
          _glVertexPointer(3,0x1406,0,*(undefined4 *)(param_1 + 0xa4));
          iVar5 = *(int *)(*(int *)(param_1 + 0x10c) + 0x10);
          uVar3 = 0;
LAB_0006fb64:
          _glTexCoordPointer(2,0x1406,uVar3,iVar5);
          _glDrawElements(4,*(undefined4 *)(*(int *)(param_1 + 0x10c) + 0x14),0x1403,
                          *(undefined4 *)(*(int *)(param_1 + 0x10c) + 0x18));
          uVar1 = *(uint *)param_1;
          goto LAB_0006f7c4;
        }
        if ((uVar1 & 0x200) == 0) {
          _glVertexPointer(3,0x1406,0,*(undefined4 *)(param_1 + 0xa4));
          _glTexCoordPointer(2,0x1406,0,*(undefined4 *)(*(int *)(param_1 + 0x10c) + 0x10));
LAB_0006fb14:
          _glDrawElements(5,*(undefined4 *)(*(int *)(param_1 + 0x10c) + 0x44),0x1403,
                          *(undefined4 *)(*(int *)(param_1 + 0x10c) + 0x48));
          uVar1 = *(uint *)param_1;
          goto LAB_0006f7c4;
        }
        if ((uVar1 & 0x1000) == 0) {
          _glBindBuffer(0x8892,*(undefined4 *)(*(int *)(param_1 + 0x10c) + 0x50));
          _glVertexPointer(3,0x1406,0,0);
          _glBindBuffer(0x8892,*(undefined4 *)(*(int *)(param_1 + 0x10c) + 0x54));
          _glTexCoordPointer(2,0x1406,0,0);
        }
        else {
          _glBindBuffer(0x8892,*(undefined4 *)(*(int *)(param_1 + 0x10c) + 0x50));
          _glVertexPointer(3,0x1402,0,0);
          _glBindBuffer(0x8892,*(undefined4 *)(*(int *)(param_1 + 0x10c) + 0x54));
          _glTexCoordPointer(2,0x1402,0,0);
        }
        _glBindBuffer(0x8893,*(undefined4 *)(*(int *)(param_1 + 0x10c) + 0x58));
      }
      _glDrawElements(5,*(undefined4 *)(*(int *)(param_1 + 0x10c) + 0x44),0x1403,0);
      _glBindBuffer(0x8892,0);
      _glBindBuffer(0x8893,0);
      uVar1 = *(uint *)param_1;
      goto LAB_0006f7c4;
    }
    if ((uVar1 & 0x1000) == 0) {
      _glVertexPointer(3,0x1406,0x14,*(undefined4 *)(*(int *)(param_1 + 0x10c) + 8));
      _glTexCoordPointer(2,0x1406,0x14,*(int *)(*(int *)(param_1 + 0x10c) + 8) + 0xc);
    }
    else {
      _glVertexPointer(3,0x1402,10,*(undefined4 *)(*(int *)(param_1 + 0x10c) + 8));
      _glTexCoordPointer(2,0x1402,10,*(int *)(*(int *)(param_1 + 0x10c) + 8) + 6);
    }
    iVar5 = *(int *)(param_1 + 0x10c);
    if (0 < *(int *)(iVar5 + 0x30)) {
      _glDrawElements(4,*(int *)(iVar5 + 0x30),0x1403,
                      *(int *)(iVar5 + 0x2c) * 2 + *(int *)(iVar5 + 0x20));
      iVar5 = *(int *)(param_1 + 0x10c);
    }
    if (0 < *(int *)(iVar5 + 0x38)) {
      _glDrawElements(4,*(int *)(iVar5 + 0x38),0x1403,*(undefined4 *)(iVar5 + 0x20));
      uVar1 = *(uint *)param_1;
      goto LAB_0006f7c4;
    }
  }
  uVar1 = *(uint *)param_1;
LAB_0006f7c4:
  if ((uVar1 & 0x4000) != 0) {
    G0RenderToon(param_1,param_2);
    uVar1 = *(uint *)param_1;
  }
  if ((uVar1 & 0x80) == 0) {
    _glPopMatrix();
  }
  else {
    _glMatrixMode(0x1702);
    _glLoadIdentity();
    _glMatrixMode(0x1700);
    _glPopMatrix();
  }
  return;
}
