/*
 * mangled: _ZN10cRSubHover9JetUnInitEv
 * demangled: cRSubHover::JetUnInit()
 * address: 0006ec2c
 * size: 48
 */

/* cRSubHover::JetUnInit() */

void __thiscall cRSubHover::JetUnInit(cRSubHover *this)

{
  int iVar1;

  iVar1 = 0;
  do {
    iVar1 = iVar1 + 1;
    cRSprite::Kill(*(cRSprite **)(this + 0x20));
    cRSprite::Kill(*(cRSprite **)(this + 0x30));
    this = this + 0x20;
  } while (iVar1 != 0xf);
  return;
}
