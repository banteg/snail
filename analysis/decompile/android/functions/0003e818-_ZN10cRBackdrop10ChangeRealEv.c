/*
 * mangled: _ZN10cRBackdrop10ChangeRealEv
 * demangled: cRBackdrop::ChangeReal()
 * address: 0003e818
 * size: 352
 */

/* cRBackdrop::ChangeReal() */

void cRBackdrop::ChangeReal(void)

{
  cRBackdrop *in_r0;
  int iVar1;
  float in_s0;
  undefined8 uVar2;

  iVar1 = *(int *)(in_r0 + 0x60);
  if (iVar1 == *(int *)(in_r0 + 0x5c)) goto LAB_0003e8ac;
  if (*(float *)(Game + 0x3c) == 0.0) {
    if (gSegmentText[iVar1 * 0x1ac + Game + 0x4e4] != '\0') goto LAB_0003e93c;
LAB_0003e874:
    iVar1 = cRSpriteManager::GetTextureRef((cRSpriteManager *)&gRSpriteManager,7);
    in_s0 = (float)G0TextureReLoad(iVar1,gSegmentText +
                                         *(int *)(in_r0 + 0x60) * 0x1ac + Game + 0x464);
  }
  else {
    if ((*(float *)(Game + 0x3c) != 180.0) || (gSegmentText[iVar1 * 0x1ac + Game + 0x4e4] == '\0'))
    goto LAB_0003e874;
LAB_0003e93c:
    iVar1 = cRSpriteManager::GetTextureRef((cRSpriteManager *)&gRSpriteManager,7);
    in_s0 = (float)G0TextureReLoad(iVar1,gSegmentText +
                                         *(int *)(in_r0 + 0x60) * 0x1ac + Game + 0x4e5);
  }
  *(undefined4 *)(in_r0 + 0x5c) = *(undefined4 *)(in_r0 + 0x60);
LAB_0003e8ac:
  uVar2 = SetDistort(in_r0,in_s0);
  SetTextureDimensions(in_r0,(float)uVar2,(float)((ulonglong)uVar2 >> 0x20));
  iVar1 = Game;
  in_r0[0x75] = in_r0[0x74];
  in_r0[0x58] = in_r0[0x59];
  *(undefined4 *)(in_r0 + 0x80) = 1;
  in_r0[0x34] = *(cRBackdrop *)(gSegmentText + *(int *)(in_r0 + 0x60) * 0x1ac + iVar1 + 0x584);
  return;
}
