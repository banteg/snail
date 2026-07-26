/*
 * mangled: _ZN12cRLoadingBar4InitEv
 * demangled: cRLoadingBar::Init()
 * address: 0008a660
 * size: 168
 */

/* cRLoadingBar::Init() */

void __thiscall cRLoadingBar::Init(cRLoadingBar *this)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  cRSplashManager *this_00;
  undefined4 uVar5;

  iVar3 = DAT_0008a718;
  iVar2 = DAT_0008a714;
  uVar1 = DAT_0008a708;
  *(undefined4 *)(this + 200) = DAT_0008a708;
  iVar4 = DAT_0008a71c;
  uVar5 = *(undefined4 *)(iVar2 + 0x8a678 + iVar3);
  *(undefined4 *)(this + 0xcc) = uVar1;
  this[0x24] = (cRLoadingBar)0x0;
  *(undefined4 *)(this + 0xb8) = uVar5;
  this_00 = *(cRSplashManager **)(iVar2 + 0x8a678 + iVar4);
  this[0xbd] = (cRLoadingBar)0x0;
  *(undefined4 *)(this + 0xc0) = 0;
  *(undefined4 *)(this + 0xc4) = 0;
  this[0xd1] = (cRLoadingBar)0x0;
  this[0xd3] = (cRLoadingBar)0x0;
  this[0x36] = (cRLoadingBar)0x0;
  this[0x77] = (cRLoadingBar)0x0;
  this[0x35] = (cRLoadingBar)0x0;
  cRSplashManager::Init(this_00);
  this[0xbc] = (cRLoadingBar)0x0;
  do {
    ScriptAI(this);
    uVar1 = DAT_0008a70c;
  } while (this[0xbc] == (cRLoadingBar)0x0);
  *(undefined4 *)this = 0;
  *(undefined4 *)(this + 0x28) = uVar1;
  *(undefined4 *)(this + 4) = 0;
  *(undefined4 *)(this + 0x2c) = DAT_0008a708;
  this[0x34] = (cRLoadingBar)0x1;
  *(undefined4 *)(this + 0x30) = DAT_0008a710;
  return;
}
