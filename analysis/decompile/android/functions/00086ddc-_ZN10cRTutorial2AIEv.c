/*
 * mangled: _ZN10cRTutorial2AIEv
 * demangled: cRTutorial::AI()
 * address: 00086ddc
 * size: 20
 */

/* cRTutorial::AI() */

void __thiscall cRTutorial::AI(cRTutorial *this)

{
  int iVar1;

  iVar1 = *(int *)(this + 0xc);
  cRSubGame::LocFromPos
            (iVar1,*(undefined4 *)(iVar1 + 0xfb20),*(undefined4 *)(iVar1 + 0xfb24),
             *(undefined4 *)(iVar1 + 0xfb28));
  return;
}
