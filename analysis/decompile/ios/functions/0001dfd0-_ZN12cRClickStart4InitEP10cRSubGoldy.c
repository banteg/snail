/*
 * mangled: _ZN12cRClickStart4InitEP10cRSubGoldy
 * demangled: cRClickStart::Init(cRSubGoldy*)
 * address: 0001dfd0
 * size: 368
 */

/* cRClickStart::Init(cRSubGoldy*) */

void __thiscall cRClickStart::Init(cRClickStart *this,cRSubGoldy *param_1)

{
  undefined *puVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  undefined4 local_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;

  puVar1 = PTR__Game_001b60b8;
  uVar2 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)PTR__Game_001b60b8 + 0xd14));
  *(undefined4 *)(this + 0x78) = uVar2;
  tColour::tColour((tColour *)&local_2c,1.0,1.0,1.0,0.03);
  cRBorder::Init(uVar2,&DAT_00400002,"Touch Screen to Start",0x14,0,0x43480000,local_2c,uStack_28,
                 uStack_24,uStack_20,2,0);
  cRBorder::HideInit(*(cRBorder **)(this + 0x78));
  this[0x9c] = (cRClickStart)0x1;
  *(cRSubGoldy **)(this + 0x8c) = param_1;
  iVar3 = *(int *)puVar1;
  if ((*(uint *)(this + 4) & 0x200) == 0) {
    if (*(int *)(iVar3 + 0x35c) == 0) {
      *(cRClickStart **)(iVar3 + 0x35c) = this;
      *(undefined4 *)(this + 8) = 0;
      *(undefined4 *)(*(int *)(iVar3 + 0x35c) + 0xc) = 0;
    }
    else {
      *(cRClickStart **)(*(int *)(iVar3 + 0x35c) + 8) = this;
      *(int *)(*(int *)(*(int *)(iVar3 + 0x35c) + 8) + 0xc) = *(int *)(iVar3 + 0x35c);
      iVar4 = *(int *)(*(int *)(iVar3 + 0x35c) + 8);
      *(int *)(iVar3 + 0x35c) = iVar4;
      *(undefined4 *)(iVar4 + 8) = 0;
    }
    *(uint *)(this + 4) = *(uint *)(this + 4) | 0x200;
  }
  else {
    RShellError("List ADD");
  }
  *(undefined4 *)(this + 0x74) = 2;
  *(undefined4 *)(*(int *)(this + 0x8c) + 0x2ec) = 0;
  *(undefined4 *)(this + 0x1c) = 0;
  *(undefined4 *)(this + 0x20) = 0;
  if ((&DAT_00353544)[*(int *)PTR__Game_001b60b8] == '\0') {
    cRBorder::UnHideInit(*(cRBorder **)(this + 0x78));
  }
  else {
    cRBorder::HideInit(*(cRBorder **)(this + 0x78));
  }
  return;
}
