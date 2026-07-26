/*
 * mangled: _ZN6cRLogo4OpenEv
 * demangled: cRLogo::Open()
 * address: 00068b6c
 * size: 52
 */

/* cRLogo::Open() */

void __thiscall cRLogo::Open(cRLogo *this)

{
  int iVar1;
  int iVar2;

  iVar1 = 0;
  do {
    iVar2 = iVar1 + 1;
    cRLogoRow::Init((cRLogoRow *)
                    (this + (int)("Java_com_sandlotgames_snailmail_MyOpenFeintDelegate_JNIOFOInit" +
                                 iVar1 * 0x84 + 0x3b)));
    iVar1 = iVar2;
  } while (iVar2 != 100);
  return;
}
