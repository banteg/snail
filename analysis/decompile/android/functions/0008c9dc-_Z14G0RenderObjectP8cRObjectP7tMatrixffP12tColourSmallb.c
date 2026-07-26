/*
 * mangled: _Z14G0RenderObjectP8cRObjectP7tMatrixffP12tColourSmallb
 * demangled: G0RenderObject(cRObject*, tMatrix*, float, float, tColourSmall*, bool)
 * address: 0008c9dc
 * size: 1820
 */

/* G0RenderObject(cRObject*, tMatrix*, float, float, tColourSmall*, bool) */

void G0RenderObject(cRObject *param_1,tMatrix *param_2,float param_3,float param_4,
                   tColourSmall *param_5,bool param_6)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  tMatrix *ptVar4;
  uint in_fpscr;
  undefined8 uVar5;
  float fVar6;
  tColourSmall *in_stack_00000000;
  char in_stack_00000004;
  float local_60;
  float local_5c;
  float local_58;
  float fStack_54;
  float local_50;
  float local_4c;
  float local_48;
  float fStack_44;
  float local_40;
  float local_3c;
  float local_38;
  float fStack_34;
  float local_30;
  float fStack_2c;
  float fStack_28;
  float fStack_24;

  uVar5 = CONCAT44(param_4,param_3);
  uVar1 = *(uint *)param_1;
  if ((int)uVar1 < 0) {
    uVar5 = wprintf("DEBUG OBJECT\n");
    uVar1 = *(uint *)param_1;
  }
  if ((uVar1 & 0x40000) != 0) {
    return;
  }
  if (*(int *)(param_1 + 0xa0) == 0) {
    return;
  }
  if (G0AfterSprites == '\0') {
    if (in_stack_00000004 != '\0') {
      return;
    }
  }
  else if (in_stack_00000004 == '\0') {
    return;
  }
  if ((uVar1 & 0x200000) != 0) {
    iVar2 = *(int *)(param_1 + 0x104);
    fVar6 = (float)VectorSignedToFloat(*(undefined4 *)(iVar2 + 4),(byte)(in_fpscr >> 0x16) & 3);
    *(undefined4 *)(param_1 + 0xa4) =
         **(undefined4 **)(*(int *)(iVar2 + 0xc) + (int)(fVar6 * *(float *)(iVar2 + 0x10)) * 4);
    fVar6 = (float)VectorSignedToFloat(*(undefined4 *)(iVar2 + 4),(byte)(in_fpscr >> 0x16) & 3);
    iVar2 = *(int *)(*(int *)(iVar2 + 0xc) + (int)(fVar6 * *(float *)(iVar2 + 0x10)) * 4);
    uVar3 = *(undefined4 *)(iVar2 + 8);
    *(undefined4 *)(*(int *)(param_1 + 0x10c) + 0x50) = *(undefined4 *)(iVar2 + 4);
    uVar1 = *(uint *)param_1;
    *(undefined4 *)(param_1 + 0xcc) = uVar3;
  }
  ptVar4 = param_2;
  if ((uVar1 & 0x800000) != 0) {
    uVar5 = cRDistort::BuildMatrix((tMatrix *)(param_1 + 0xf0),param_2);
    ptVar4 = (tMatrix *)&local_60;
  }
  glMatrixMode((int)uVar5,(int)((ulonglong)uVar5 >> 0x20),0x1700);
  glPushMatrix();
  if ((*(uint *)param_1 & 0x80) == 0) {
    if ((*(uint *)param_1 & 0x1000) == 0) {
      glMatrixMode(0x1702);
      glLoadIdentity();
      goto LAB_0008ccfc;
    }
    glMatrixMode(0x1702);
    glLoadIdentity();
    glScalef(0x3c000000,0x3c000000,0x3c000000);
    glMatrixMode(0x1700);
  }
  else {
    glMatrixMode(0x1702);
    glLoadIdentity();
    if ((*(uint *)param_1 & 0x1000) == 0) {
      glTranslatef(param_5,(uint)param_6,0);
    }
    else {
      glScalef(0x3c000000,0x3c000000,0x3c000000);
      glTranslatef((float)param_5 * 128.0,(float)(uint)param_6 * 128.0,0);
    }
LAB_0008ccfc:
    glMatrixMode(0x1700);
  }
  G0SetCull(SUB41(((*(uint *)param_1 ^ 0x100000) << 0xb) >> 0x1f,0));
  if ((*(uint *)param_1 & 0x1000) != 0) {
    local_60 = *(float *)ptVar4;
    local_5c = *(float *)(ptVar4 + 4);
    local_58 = *(float *)(ptVar4 + 8);
    fStack_54 = *(float *)(ptVar4 + 0xc);
    local_60 = *(float *)ptVar4 * 0.0078125;
    local_50 = *(float *)(ptVar4 + 0x10);
    local_4c = *(float *)(ptVar4 + 0x14);
    local_48 = *(float *)(ptVar4 + 0x18);
    fStack_44 = *(float *)(ptVar4 + 0x1c);
    local_40 = *(float *)(ptVar4 + 0x20);
    local_3c = *(float *)(ptVar4 + 0x24);
    local_38 = *(float *)(ptVar4 + 0x28);
    fStack_34 = *(float *)(ptVar4 + 0x2c);
    local_30 = *(float *)(ptVar4 + 0x30);
    fStack_2c = *(float *)(ptVar4 + 0x34);
    fStack_28 = *(float *)(ptVar4 + 0x38);
    fStack_24 = *(float *)(ptVar4 + 0x3c);
    local_5c = *(float *)(ptVar4 + 4) * 0.0078125;
    local_38 = *(float *)(ptVar4 + 0x28) * 0.0078125;
    local_58 = *(float *)(ptVar4 + 8) * 0.0078125;
    local_50 = *(float *)(ptVar4 + 0x10) * 0.0078125;
    local_4c = *(float *)(ptVar4 + 0x14) * 0.0078125;
    local_48 = *(float *)(ptVar4 + 0x18) * 0.0078125;
    local_40 = *(float *)(ptVar4 + 0x20) * 0.0078125;
    local_3c = *(float *)(ptVar4 + 0x24) * 0.0078125;
    ptVar4 = (tMatrix *)&local_60;
  }
  glMultMatrixf(ptVar4);
  G0SetBlend(*(int *)(param_1 + 8));
  G0SetColour(in_stack_00000000);
  uVar1 = *(uint *)param_1;
  if ((uVar1 & 0x4000000) == 0) {
    wprintf("Non GLVertex Remenant Object Render\n");
  }
  else {
    if (**(int **)(param_1 + 0x10c) == 0) goto LAB_0008cc98;
    if ((uVar1 & 8) == 0) {
      G0BindTexture(*(int *)(**(int **)(param_1 + 0x10c) + 0x8c));
    }
    else {
      G0BindTexture(*(int *)(*(int *)(param_1 + 0xc) + 0x8c));
    }
    glEnableClientState(0x8074);
    glEnableClientState(0x8078);
    uVar1 = *(uint *)param_1;
    if ((uVar1 & 0x400000) == 0) {
      if ((uVar1 & 4) == 0) {
        if ((uVar1 & 0x10000000) == 0) {
          glVertexPointer(3,0x1406,0x14,*(undefined4 *)(*(int *)(param_1 + 0x10c) + 8));
          uVar3 = 0x14;
          iVar2 = *(int *)(*(int *)(param_1 + 0x10c) + 8) + 0xc;
          goto LAB_0008cf84;
        }
        if ((uVar1 & 0x200) == 0) {
          if ((uVar1 & 0x1000) == 0) {
            glVertexPointer(3,0x1406,0x14,*(undefined4 *)(*(int *)(param_1 + 0x10c) + 8));
            glTexCoordPointer(2,0x1406,0x14,*(int *)(*(int *)(param_1 + 0x10c) + 8) + 0xc);
          }
          else {
            glVertexPointer(3,0x1402,10,*(undefined4 *)(*(int *)(param_1 + 0x10c) + 8));
            glTexCoordPointer(2,0x1402,10,*(int *)(*(int *)(param_1 + 0x10c) + 8) + 6);
          }
          goto LAB_0008cea0;
        }
        glBindBuffer(0x8892,*(undefined4 *)(*(int *)(param_1 + 0x10c) + 0x4c));
        glBindBuffer(0x8893,*(undefined4 *)(*(int *)(param_1 + 0x10c) + 0x58));
        if ((*(uint *)param_1 & 0x1000) == 0) {
          glVertexPointer(3,0x1406,0x14);
          glTexCoordPointer(2,0x1406,0x14,0xc);
        }
        else {
          glVertexPointer(3,0x1402,10,0);
          glTexCoordPointer(2,0x1402,10,6);
        }
      }
      else {
        if ((uVar1 & 0x10000000) == 0) {
          glVertexPointer(3,0x1406,0,*(undefined4 *)(param_1 + 0xa4));
          iVar2 = *(int *)(*(int *)(param_1 + 0x10c) + 0x10);
          uVar3 = 0;
LAB_0008cf84:
          glTexCoordPointer(2,0x1406,uVar3,iVar2);
          glDrawElements(4,*(undefined4 *)(*(int *)(param_1 + 0x10c) + 0x14),0x1403,
                         *(undefined4 *)(*(int *)(param_1 + 0x10c) + 0x18));
          uVar1 = *(uint *)param_1;
          goto LAB_0008cc98;
        }
        if ((uVar1 & 0x200) == 0) {
          if ((uVar1 & 0x1000) == 0) {
            glVertexPointer(3,0x1406,0,*(undefined4 *)(param_1 + 0xa4));
            glTexCoordPointer(2,0x1406,0,*(undefined4 *)(*(int *)(param_1 + 0x10c) + 0x10));
          }
          else {
            glVertexPointer(3,0x1402,0,*(undefined4 *)(param_1 + 0xa4));
            glTexCoordPointer(2,0x1402,0,*(undefined4 *)(*(int *)(param_1 + 0x10c) + 0x10));
          }
LAB_0008cea0:
          glDrawElements(5,*(undefined4 *)(*(int *)(param_1 + 0x10c) + 0x44),0x1403,
                         *(undefined4 *)(*(int *)(param_1 + 0x10c) + 0x48));
          uVar1 = *(uint *)param_1;
          goto LAB_0008cc98;
        }
        if ((uVar1 & 0x1000) == 0) {
          glBindBuffer(0x8892,*(undefined4 *)(*(int *)(param_1 + 0x10c) + 0x50));
          glVertexPointer(3,0x1406,0,0);
          glBindBuffer(0x8892,*(undefined4 *)(*(int *)(param_1 + 0x10c) + 0x54));
          glTexCoordPointer(2,0x1406,0,0);
        }
        else {
          glBindBuffer(0x8892,*(undefined4 *)(*(int *)(param_1 + 0x10c) + 0x50));
          glVertexPointer(3,0x1402,0,0);
          glBindBuffer(0x8892,*(undefined4 *)(*(int *)(param_1 + 0x10c) + 0x54));
          glTexCoordPointer(2,0x1402,0,0);
        }
        glBindBuffer(0x8893,*(undefined4 *)(*(int *)(param_1 + 0x10c) + 0x58));
      }
      glDrawElements(5,*(undefined4 *)(*(int *)(param_1 + 0x10c) + 0x44),0x1403,0);
      glBindBuffer(0x8892,0);
      glBindBuffer(0x8893,0);
      uVar1 = *(uint *)param_1;
      goto LAB_0008cc98;
    }
    if ((uVar1 & 0x1000) == 0) {
      glVertexPointer(3,0x1406,0x14,*(undefined4 *)(*(int *)(param_1 + 0x10c) + 8));
      glTexCoordPointer(2,0x1406,0x14,*(int *)(*(int *)(param_1 + 0x10c) + 8) + 0xc);
    }
    else {
      glVertexPointer(3,0x1402,10,*(undefined4 *)(*(int *)(param_1 + 0x10c) + 8));
      glTexCoordPointer(2,0x1402,10,*(int *)(*(int *)(param_1 + 0x10c) + 8) + 6);
    }
    iVar2 = *(int *)(param_1 + 0x10c);
    if (0 < *(int *)(iVar2 + 0x30)) {
      glDrawElements(4,*(int *)(iVar2 + 0x30),0x1403,
                     *(int *)(iVar2 + 0x20) + *(int *)(iVar2 + 0x2c) * 2);
      iVar2 = *(int *)(param_1 + 0x10c);
    }
    if (0 < *(int *)(iVar2 + 0x38)) {
      glDrawElements(4,*(int *)(iVar2 + 0x38),0x1403,*(undefined4 *)(iVar2 + 0x20));
      uVar1 = *(uint *)param_1;
      goto LAB_0008cc98;
    }
  }
  uVar1 = *(uint *)param_1;
LAB_0008cc98:
  if ((uVar1 & 0x4000) != 0) {
    G0RenderToon(param_1,param_2);
    uVar1 = *(uint *)param_1;
  }
  if ((uVar1 & 0x80) == 0) {
    glPopMatrix();
  }
  else {
    glMatrixMode(0x1702);
    glLoadIdentity();
    glMatrixMode(0x1700);
    glPopMatrix();
  }
  return;
}
