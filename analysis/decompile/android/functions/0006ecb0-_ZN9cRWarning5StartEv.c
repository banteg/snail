/*
 * mangled: _ZN9cRWarning5StartEv
 * demangled: cRWarning::Start()
 * address: 0006ecb0
 * size: 32
 */

/* cRWarning::Start() */

void __thiscall cRWarning::Start(cRWarning *this)

{
  *(undefined4 *)(this + 0xc) = 0x3f800000;
  *(undefined4 *)(this + 4) = 0x3f800000;
  *(undefined4 *)this = 2;
  cRBorder::UnHideInit(*(cRBorder **)(this + 0x14));
  return;
}
