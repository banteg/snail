/*
 * mangled: _ZN9cRWarning5StartEv
 * demangled: cRWarning::Start()
 * address: 0006ecb0
 * size: 32
 */

/* cRWarning::Start() */

void __thiscall cRWarning::Start(cRWarning *this)

{
  undefined4 uVar1;

  uVar1 = DAT_0006ecd0;
  *(undefined4 *)(this + 0xc) = DAT_0006ecd0;
  *(undefined4 *)(this + 4) = uVar1;
  *(undefined4 *)this = 2;
  cRBorder::UnHideInit(*(cRBorder **)(this + 0x14));
  return;
}
