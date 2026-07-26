/*
 * mangled: _ZN15cRSplashManager6RenderEf
 * demangled: cRSplashManager::Render(float)
 * address: 00089cf8
 * size: 620
 */

/* cRSplashManager::Render(float) */

void cRSplashManager::Render(float param_1)

{
  int in_r0;
  float fVar1;
  float fVar2;
  float extraout_s0;
  float extraout_s1;
  float extraout_s2;
  float extraout_s3;
  tColourSmall atStack_34 [4];

  RenderStart();
  glClearColor(0,0,0,0x3f800000);
  glClear(0x4100);
  fVar1 = (float)RShellGetScreenWidth();
  fVar2 = (float)RShellGetScreenHeight();
  tColourSmall::tColourSmall(atStack_34);
  tColourSmall::Set(atStack_34,extraout_s0,extraout_s1,extraout_s2,extraout_s3);
  G0SetColour(atStack_34);
  glEnable(0xde1);
  glBindTexture(0xde1,*(undefined4 *)(in_r0 + 0xa4));
  gBindTextureRefLast = 0xffffffff;
  gSplashSpriteVertexUVArray._52_4_ = 0x3f700000;
  gSplashSpriteVertexUVArray._76_4_ = 0x3ec00000;
  gSplashSpriteVertexUVArray._32_4_ = 0x3f700000;
  gSplashSpriteVertexUVArray._56_4_ = 0x3ec00000;
  gSplashSpriteVertexUVArray._0_4_ = 0;
  gSplashSpriteVertexUVArray._4_4_ = 0;
  gSplashSpriteVertexUVArray._8_4_ = 0;
  gSplashSpriteVertexUVArray._12_4_ = 0;
  gSplashSpriteVertexUVArray._16_4_ = 0x3f800000;
  gSplashSpriteVertexUVArray._24_4_ = 0;
  gSplashSpriteVertexUVArray._28_4_ = 0;
  gSplashSpriteVertexUVArray._36_4_ = 0x3f800000;
  gSplashSpriteVertexUVArray._48_4_ = 0;
  gSplashSpriteVertexUVArray._60_4_ = 0;
  gSplashSpriteVertexUVArray._68_4_ = 0;
  gSplashSpriteVertexUVArray._72_4_ = 0;
  gSplashSpriteVertexUVArray._20_4_ = fVar1 + 0.0;
  gSplashSpriteVertexUVArray._40_4_ = fVar1 + 0.0;
  gSplashSpriteVertexUVArray._44_4_ = fVar2 + 0.0;
  gSplashSpriteVertexUVArray._64_4_ = fVar2 + 0.0;
  glBindBuffer(0x8892,0);
  glBindBuffer(0x8893,0);
  glVertexPointer(3,0x1406,0x14,gSplashSpriteVertexUVArray);
  glTexCoordPointer(2,0x1406,0x14,0x38ca7c);
  glDisableClientState(0x8076);
  glDrawElements(5,4,0x1403,&gSplashSpriteIndexArray);
  if (*(char *)(in_r0 + 0x45) != '\0') {
    fVar1 = *(float *)(in_r0 + 0x98) +
            ((*(float *)(in_r0 + 0x9c) - *(float *)(in_r0 + 0x98)) * *(float *)(in_r0 + 0xa0)) /
            100.0;
    glBindTexture(0xde1,*(undefined4 *)(in_r0 + 0xa8));
    gSplashSpriteVertexUVArray._0_4_ = *(float *)(in_r0 + 0x88);
    gSplashSpriteVertexUVArray._4_4_ = *(float *)(in_r0 + 0x8c);
    gBindTextureRefLast = 0xffffffff;
    gSplashSpriteVertexUVArray._76_4_ = 0;
    gSplashSpriteVertexUVArray._36_4_ = 0x3f800000;
    gSplashSpriteVertexUVArray._8_4_ = 0;
    gSplashSpriteVertexUVArray._12_4_ = 0;
    gSplashSpriteVertexUVArray._16_4_ = 0x3f800000;
    gSplashSpriteVertexUVArray._28_4_ = 0;
    gSplashSpriteVertexUVArray._48_4_ = 0;
    gSplashSpriteVertexUVArray._56_4_ = 0;
    gSplashSpriteVertexUVArray._68_4_ = 0;
    gSplashSpriteVertexUVArray._72_4_ = 0;
    gSplashSpriteVertexUVArray._32_4_ = fVar1 / 100.0;
    gSplashSpriteVertexUVArray._44_4_ =
         (float)gSplashSpriteVertexUVArray._4_4_ - *(float *)(in_r0 + 0x94);
    gSplashSpriteVertexUVArray._20_4_ =
         (*(float *)(in_r0 + 0x90) * fVar1) / 100.0 + (float)gSplashSpriteVertexUVArray._0_4_;
    gSplashSpriteVertexUVArray._24_4_ = gSplashSpriteVertexUVArray._4_4_;
    gSplashSpriteVertexUVArray._40_4_ = gSplashSpriteVertexUVArray._20_4_;
    gSplashSpriteVertexUVArray._52_4_ = gSplashSpriteVertexUVArray._32_4_;
    gSplashSpriteVertexUVArray._60_4_ = gSplashSpriteVertexUVArray._0_4_;
    gSplashSpriteVertexUVArray._64_4_ = gSplashSpriteVertexUVArray._44_4_;
    glVertexPointer(3,0x1406,0x14,gSplashSpriteVertexUVArray);
    glTexCoordPointer(2,0x1406,0x14,0x38ca7c);
    glDrawElements(5,4,0x1403,&gSplashSpriteIndexArray);
  }
  return;
}
