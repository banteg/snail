/*
 * mangled: _ZN15cRSplashManager6RenderEf
 * demangled: cRSplashManager::Render(float)
 * address: 00089cf8
 * size: 620
 */

/* cRSplashManager::Render(float) */

void cRSplashManager::Render(float param_1)

{
  float fVar1;
  int iVar2;
  int in_r0;
  float fVar3;
  float fVar4;
  float *pfVar5;
  int iVar6;
  undefined4 uVar7;
  undefined4 *puVar8;
  float extraout_s0;
  float extraout_s1;
  float extraout_s2;
  float extraout_s3;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  tColourSmall atStack_34 [4];

  fVar10 = DAT_00089f64;
  RenderStart();
  glClearColor(fVar10,fVar10,fVar10,0x3f800000);
  glClear(0x4100);
  fVar3 = (float)RShellGetScreenWidth();
  iVar6 = DAT_00089f74 + 0x89d48;
  fVar4 = (float)RShellGetScreenHeight();
  tColourSmall::tColourSmall(atStack_34);
  tColourSmall::Set(atStack_34,extraout_s0,extraout_s1,extraout_s2,extraout_s3);
  G0SetColour(atStack_34);
  glEnable(0xde1);
  glBindTexture(0xde1,*(undefined4 *)(in_r0 + 0xa4));
  iVar2 = DAT_00089f7c;
  fVar9 = DAT_00089f6c;
  fVar1 = DAT_00089f68;
  puVar8 = *(undefined4 **)(iVar6 + DAT_00089f78);
  *puVar8 = 0xffffffff;
  pfVar5 = *(float **)(iVar6 + iVar2);
  pfVar5[0xd] = fVar1;
  pfVar5[0x13] = fVar9;
  pfVar5[8] = fVar1;
  pfVar5[0xe] = fVar9;
  *pfVar5 = fVar10;
  pfVar5[1] = fVar10;
  pfVar5[2] = fVar10;
  pfVar5[3] = fVar10;
  pfVar5[4] = 1.0;
  pfVar5[6] = fVar10;
  pfVar5[10] = fVar3 + fVar10;
  pfVar5[5] = fVar3 + fVar10;
  pfVar5[7] = fVar10;
  pfVar5[9] = 1.0;
  pfVar5[0xc] = fVar10;
  pfVar5[0xf] = fVar10;
  pfVar5[0x11] = fVar10;
  pfVar5[0x12] = fVar10;
  pfVar5[0x10] = fVar4 + fVar10;
  pfVar5[0xb] = fVar4 + fVar10;
  glBindBuffer(0x8892,0);
  glBindBuffer(0x8893,0);
  glVertexPointer(3,0x1406,0x14,pfVar5);
  glTexCoordPointer(2,0x1406,0x14,pfVar5 + 3);
  glDisableClientState(0x8076);
  uVar7 = *(undefined4 *)(iVar6 + DAT_00089f80);
  glDrawElements(5,4,0x1403,uVar7);
  fVar1 = DAT_00089f70;
  if (*(char *)(in_r0 + 0x45) != '\0') {
    fVar12 = *(float *)(in_r0 + 0x98) +
             ((*(float *)(in_r0 + 0x9c) - *(float *)(in_r0 + 0x98)) * *(float *)(in_r0 + 0xa0)) /
             DAT_00089f70;
    glBindTexture(0xde1,*(undefined4 *)(in_r0 + 0xa8));
    fVar3 = *(float *)(in_r0 + 0x90);
    fVar9 = *(float *)(in_r0 + 0x94);
    fVar11 = *(float *)(in_r0 + 0x88);
    fVar4 = *(float *)(in_r0 + 0x8c);
    pfVar5[0xf] = fVar11;
    *pfVar5 = fVar11;
    pfVar5[1] = fVar4;
    pfVar5[6] = fVar4;
    *puVar8 = 0xffffffff;
    pfVar5[0x13] = fVar10;
    pfVar5[9] = 1.0;
    pfVar5[2] = fVar10;
    pfVar5[3] = fVar10;
    pfVar5[4] = 1.0;
    pfVar5[7] = fVar10;
    pfVar5[0xc] = fVar10;
    pfVar5[0xe] = fVar10;
    pfVar5[0x11] = fVar10;
    pfVar5[0x12] = fVar10;
    fVar10 = fVar12 / fVar1;
    fVar4 = fVar4 - fVar9;
    pfVar5[0xd] = fVar10;
    pfVar5[8] = fVar10;
    fVar11 = (fVar3 * fVar12) / fVar1 + fVar11;
    pfVar5[0x10] = fVar4;
    pfVar5[0xb] = fVar4;
    pfVar5[10] = fVar11;
    pfVar5[5] = fVar11;
    glVertexPointer(3,0x1406,0x14,pfVar5);
    glTexCoordPointer(2,0x1406,0x14,pfVar5 + 3);
    glDrawElements(5,4,0x1403,uVar7);
  }
  return;
}
