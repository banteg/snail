/*
 * mangled: _ZN10cRTutorial2AIEv
 * demangled: cRTutorial::AI()
 * address: 00066910
 * size: 32
 */

/* cRTutorial::AI() */

void __thiscall cRTutorial::AI(cRTutorial *this)

{
  int iVar1;

  iVar1 = *(int *)(this + 0xc);
  cRSubGame::LocFromPos
            (iVar1,*(undefined4 *)(iVar1 + 0xf4a4),*(undefined4 *)(iVar1 + 0xf4a8),
             *(undefined4 *)(iVar1 + 0xf4ac));
  return;
}
