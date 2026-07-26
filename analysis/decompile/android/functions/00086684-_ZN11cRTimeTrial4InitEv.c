/*
 * mangled: _ZN11cRTimeTrial4InitEv
 * demangled: cRTimeTrial::Init()
 * address: 00086684
 * size: 44
 */

/* cRTimeTrial::Init() */

void __thiscall cRTimeTrial::Init(cRTimeTrial *this)

{
  int iVar1;

  iVar1 = 0;
  do {
    *(undefined4 *)(this + iVar1 * 4) = *(undefined4 *)((int)&gTimeTrialCourseNames + iVar1);
    iVar1 = iVar1 + 4;
  } while (iVar1 != 0xcc);
  return;
}
