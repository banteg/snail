/*
 * mangled: _ZN10cRSubHover2OnEv
 * demangled: cRSubHover::On()
 * address: 00070bf0
 * size: 100
 */

/* cRSubHover::On() */

void __thiscall cRSubHover::On(cRSubHover *this)

{
  if (*(int *)(this + 0xc) != 0) {
    return;
  }
  *(undefined4 *)(this + 0xc) = 1;
  *(undefined4 *)(this + 0x14) = 0;
  *(undefined4 *)this = 0;
  *(undefined4 *)(this + 0x1c) = 0;
  *(undefined4 *)(this + 0x18) = 0;
  cRSnail::SetJetPack((cRSnail *)(Game + 0x83b64),1);
  JetInit(this);
  return;
}
