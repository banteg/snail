/*
 * mangled: _ZN12cRClickStart4InitEP10cRSubGoldy
 * demangled: cRClickStart::Init(cRSubGoldy*)
 * address: 00071bd0
 * size: 276
 */

/* cRClickStart::Init(cRSubGoldy*) */

void __thiscall cRClickStart::Init(cRClickStart *this,cRSubGoldy *param_1)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  int *piVar5;
  float extraout_s0;
  float extraout_s1;
  float extraout_s2;
  float extraout_s3;
  undefined4 local_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;

  uVar2 = DAT_00071ce4;
  iVar4 = DAT_00071cf0 + 0x71bf0;
  piVar5 = *(int **)(iVar4 + DAT_00071cf4);
  uVar3 = cRBorderManager::GetBorder((cRBorderManager *)(*piVar5 + 0xd14));
  *(undefined4 *)(this + 0x78) = uVar3;
  tColour::tColour((tColour *)&local_38,extraout_s0,extraout_s1,extraout_s2,extraout_s3);
  cRBorder::Init(uVar3,0x400002,iVar4 + DAT_00071cf8,0x14,uVar2,DAT_00071cec,local_38,uStack_34,
                 uStack_30,uStack_2c,2,uVar2);
  cRBorder::HideInit(*(cRBorder **)(this + 0x78));
  iVar4 = *piVar5;
  this[0x9c] = (cRClickStart)0x1;
  *(cRSubGoldy **)(this + 0x8c) = param_1;
  cLinkedList<cRBod>::Add((cLinkedList<cRBod> *)(iVar4 + 0x358),(cRBod *)this);
  iVar4 = *piVar5;
  *(undefined4 *)(this + 0x74) = 2;
  *(undefined4 *)(this + 0x20) = uVar2;
  *(undefined4 *)(this + 0x1c) = uVar2;
  cVar1 = gDirectory[iVar4 + 0x2544];
  *(undefined4 *)(*(int *)(this + 0x8c) + 0x2ec) = 0;
  if (cVar1 == '\0') {
    cRBorder::UnHideInit(*(cRBorder **)(this + 0x78));
  }
  else {
    cRBorder::HideInit(*(cRBorder **)(this + 0x78));
  }
  return;
}
