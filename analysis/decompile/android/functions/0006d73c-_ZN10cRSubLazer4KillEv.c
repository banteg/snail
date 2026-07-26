/*
 * mangled: _ZN10cRSubLazer4KillEv
 * demangled: cRSubLazer::Kill()
 * address: 0006d73c
 * size: 52
 */

/* cRSubLazer::Kill() */

void __thiscall cRSubLazer::Kill(cRSubLazer *this)

{
  cLinkedList<cRBod>::Remove((cLinkedList<cRBod> *)(Game + 0x358),(cRBod *)this);
  *(undefined4 *)(this + 0x74) = 0;
  return;
}
