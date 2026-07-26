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
  int iVar2;
  int iVar3;
  int iVar4;
  float in_s0;
  undefined8 uVar5;

  iVar1 = DAT_0003e980;
  iVar3 = *(int *)(in_r0 + 0x60);
  iVar4 = DAT_0003e97c + 0x3e838;
  if (iVar3 == *(int *)(in_r0 + 0x5c)) goto LAB_0003e8ac;
  iVar2 = **(int **)(iVar4 + DAT_0003e980);
  if (*(float *)(iVar2 + 0x3c) == 0.0) {
    if (gSegmentText[iVar3 * 0x1ac + iVar2 + 0x4e4] != '\0') goto LAB_0003e93c;
LAB_0003e874:
    iVar3 = cRSpriteManager::GetTextureRef(*(cRSpriteManager **)(iVar4 + DAT_0003e984),7);
    in_s0 = (float)G0TextureReLoad(iVar3,gSegmentText +
                                         *(int *)(in_r0 + 0x60) * 0x1ac + **(int **)(iVar4 + iVar1)
                                         + 0x464);
  }
  else {
    if ((*(float *)(iVar2 + 0x3c) != DAT_0003e978) ||
       (gSegmentText[iVar3 * 0x1ac + iVar2 + 0x4e4] == '\0')) goto LAB_0003e874;
LAB_0003e93c:
    iVar3 = cRSpriteManager::GetTextureRef(*(cRSpriteManager **)(iVar4 + DAT_0003e984),7);
    in_s0 = (float)G0TextureReLoad(iVar3,gSegmentText +
                                         *(int *)(in_r0 + 0x60) * 0x1ac + **(int **)(iVar4 + iVar1)
                                         + 0x4e5);
  }
  *(undefined4 *)(in_r0 + 0x5c) = *(undefined4 *)(in_r0 + 0x60);
LAB_0003e8ac:
  uVar5 = SetDistort(in_r0,in_s0);
  SetTextureDimensions(in_r0,(float)uVar5,(float)((ulonglong)uVar5 >> 0x20));
  iVar1 = **(int **)(iVar4 + iVar1);
  in_r0[0x75] = in_r0[0x74];
  in_r0[0x58] = in_r0[0x59];
  *(undefined4 *)(in_r0 + 0x80) = 1;
  in_r0[0x34] = *(cRBackdrop *)(gSegmentText + *(int *)(in_r0 + 0x60) * 0x1ac + iVar1 + 0x584);
  return;
}
