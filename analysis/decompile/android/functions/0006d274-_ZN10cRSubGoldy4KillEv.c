/*
 * mangled: _ZN10cRSubGoldy4KillEv
 * demangled: cRSubGoldy::Kill()
 * address: 0006d274
 * size: 24
 */

/* cRSubGoldy::Kill() */

void __thiscall cRSubGoldy::Kill(cRSubGoldy *this)

{
  FallingInit(this);
  *(undefined4 *)(this + 0x60) = 0xc1000000;
  return;
}
