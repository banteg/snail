/*
 * mangled: _Z12G0RenderFontP9cRTextureffffffffffffffR7tColourif
 * demangled: G0RenderFont(cRTexture*, float, float, float, float, float, float, float, float, float, float, float, float, float, float, tColour&, int, float)
 * address: 0006fce8
 * size: 1292
 */

/* G0RenderFont(cRTexture*, float, float, float, float, float, float, float, float, float, float,
   float, float, float, float, tColour&, int, float) */

void G0RenderFont(cRTexture *param_1,float param_2,float param_3,float param_4,float param_5,
                 float param_6,float param_7,float param_8,float param_9,float param_10,
                 float param_11,float param_12,float param_13,float param_14,float param_15,
                 tColour *param_16,int param_17,float param_18)

{
  float *pfVar1;
  uint uVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  undefined8 uVar9;
  undefined4 local_5c;

  uVar9 = CONCAT44(param_15,param_13);
  tColourSmall::tColourSmall((tColourSmall *)&local_5c);
  tColourSmall::operator=((tColourSmall *)&local_5c,param_16);
  fVar3 = (float)RShellGetScreenWidth();
  fVar3 = fVar3 / 640.0;
  fVar4 = (float)RShellGetScreenHeight();
  fVar8 = fVar3 * param_2;
  fVar4 = fVar4 / 480.0;
  fVar7 = fVar4 * param_3;
  if (param_10 == 0.0) {
    param_4 = param_4 * fVar3;
    param_5 = param_5 * fVar4;
    param_6 = param_6 * fVar3;
    param_7 = param_7 * fVar4;
    param_8 = param_8 * fVar3;
    param_9 = param_9 * fVar4;
  }
  fVar3 = fVar3 * param_10;
  fVar4 = fVar4 * param_11;
  if (*(int *)(param_1 + 0x8c) == _BufferTexture) {
    uVar2 = local_5c;
    if (local_5c == _BufferColour) {
      uVar2 = _BufferBlendMode;
    }
    if ((local_5c == _BufferColour && param_17 == uVar2) && (_BufferCount < 0xfe))
    goto LAB_0006fea8;
  }
  if (0 < _BufferCount) {
    _glDrawElements(5,_BufferCount * 6,0x1403,0);
  }
  _BufferTexture = 0xffffffff;
  _BufferCount = 0;
  _BufferColour = 0;
  _BufferUVArray = (float *)RShellMemoryScratch();
  _BufferBlendMode = 0xffffffff;
  _BufferSPA = _BufferUVArray;
  _glVertexPointer(3,0x1406,0x14,_BufferUVArray);
  _glTexCoordPointer(2,0x1406,0x14,_BufferUVArray + 3);
  _glBindBuffer(0x8893,_gSpriteIndexArrayVBO);
  _BufferColour = local_5c;
  _BufferTexture = *(int *)(param_1 + 0x8c);
  _BufferBlendMode = param_17;
  G0SetBlend(param_17);
  G0BindTexture(*(int *)(param_1 + 0x8c));
  if (_GLColour != local_5c) {
    _GLColour = local_5c;
    _glColor4ub(local_5c._2_1_,local_5c._1_1_,local_5c & 0xff,local_5c._3_1_);
  }
LAB_0006fea8:
  _BufferCount = _BufferCount + 1;
  if (param_18 == 0.0) {
    fVar5 = (float)((ulonglong)uVar9 >> 0x20);
    if (fVar3 == 0.0) {
      *_BufferSPA = fVar8;
      fVar3 = 1.0 - (float)uVar9;
      _BufferSPA[1] = fVar7;
      _BufferSPA[2] = 0.0;
      _BufferSPA[3] = param_12;
      _BufferSPA[4] = fVar3;
      pfVar1 = _BufferSPA + 5;
      _BufferSPA = _BufferSPA + 5;
      *pfVar1 = param_4;
      _BufferSPA[1] = param_5;
      _BufferSPA[2] = 0.0;
      _BufferSPA[3] = param_14;
      _BufferSPA[4] = fVar3;
      pfVar1 = _BufferSPA + 5;
      _BufferSPA = _BufferSPA + 5;
      *pfVar1 = param_6;
      _BufferSPA[1] = param_7;
      _BufferSPA[2] = 0.0;
      _BufferSPA[3] = param_14;
      _BufferSPA[4] = 1.0 - fVar5;
      pfVar1 = _BufferSPA + 5;
      _BufferSPA = _BufferSPA + 5;
      *pfVar1 = param_8;
      _BufferSPA[1] = param_9;
    }
    else {
      *_BufferSPA = fVar8;
      fVar6 = 1.0 - (float)uVar9;
      _BufferSPA[1] = fVar7;
      _BufferSPA[2] = 0.0;
      _BufferSPA[3] = param_12;
      _BufferSPA[4] = fVar6;
      pfVar1 = _BufferSPA + 5;
      _BufferSPA = _BufferSPA + 5;
      *pfVar1 = fVar8 + fVar3;
      _BufferSPA[1] = fVar7;
      _BufferSPA[2] = 0.0;
      _BufferSPA[3] = param_14;
      _BufferSPA[4] = fVar6;
      pfVar1 = _BufferSPA + 5;
      _BufferSPA = _BufferSPA + 5;
      *pfVar1 = fVar8 + fVar3;
      _BufferSPA[1] = fVar7 + fVar4;
      _BufferSPA[2] = 0.0;
      _BufferSPA[3] = param_14;
      _BufferSPA[4] = 1.0 - fVar5;
      pfVar1 = _BufferSPA + 5;
      _BufferSPA = _BufferSPA + 5;
      *pfVar1 = fVar8;
      _BufferSPA[1] = fVar7 + fVar4;
    }
    _BufferSPA[2] = 0.0;
    _BufferSPA[3] = param_12;
    _BufferSPA[4] = 1.0 - fVar5;
  }
  else {
    fVar3 = fVar3 * 0.5;
    fVar4 = fVar4 * 0.5;
    fVar8 = fVar3 + fVar8;
    fVar7 = fVar4 + fVar7;
    fVar3 = (float)Sqrt(fVar4 * fVar4 + fVar3 * fVar3);
    fVar3 = fVar3 * 1.414;
    fVar4 = (float)Sin(param_18);
    fVar4 = fVar4 * fVar3;
    fVar5 = (float)Cos(param_18);
    fVar6 = 1.0 - (float)uVar9;
    fVar5 = fVar5 * fVar3;
    *_BufferSPA = fVar8 + fVar4;
    _BufferSPA[1] = fVar7 + fVar5;
    _BufferSPA[2] = 0.0;
    _BufferSPA[3] = param_12;
    _BufferSPA[4] = fVar6;
    pfVar1 = _BufferSPA + 5;
    _BufferSPA = _BufferSPA + 5;
    *pfVar1 = fVar8 - fVar5;
    _BufferSPA[1] = fVar7 + fVar4;
    _BufferSPA[2] = 0.0;
    _BufferSPA[3] = param_14;
    _BufferSPA[4] = fVar6;
    pfVar1 = _BufferSPA + 5;
    _BufferSPA = _BufferSPA + 5;
    *pfVar1 = fVar8 - fVar4;
    fVar3 = 1.0 - (float)((ulonglong)uVar9 >> 0x20);
    _BufferSPA[1] = fVar7 - fVar5;
    _BufferSPA[2] = 0.0;
    _BufferSPA[3] = param_14;
    _BufferSPA[4] = fVar3;
    pfVar1 = _BufferSPA + 5;
    _BufferSPA = _BufferSPA + 5;
    *pfVar1 = fVar8 + fVar5;
    _BufferSPA[1] = fVar7 - fVar4;
    _BufferSPA[2] = 0.0;
    _BufferSPA[3] = param_12;
    _BufferSPA[4] = fVar3;
  }
  _BufferSPA = _BufferSPA + 5;
  return;
}
