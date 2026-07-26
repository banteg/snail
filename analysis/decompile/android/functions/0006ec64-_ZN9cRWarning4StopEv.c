/*
 * mangled: _ZN9cRWarning4StopEv
 * demangled: cRWarning::Stop()
 * address: 0006ec64
 * size: 16
 */

/* cRWarning::Stop() */

void __thiscall cRWarning::Stop(cRWarning *this)

{
  *(undefined4 *)this = 0;
  cRBorder::HideInit(*(cRBorder **)(this + 0x14));
  return;
}
