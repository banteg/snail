/*
 * mangled: _ZN6cRSlug4KillEv
 * demangled: cRSlug::Kill()
 * address: 00077ed8
 * size: 128
 */

/* cRSlug::Kill() */

void __thiscall cRSlug::Kill(cRSlug *this)

{
  undefined4 uVar1;
  uint in_fpscr;

  if (*(int *)(this + 0x74) != 1) {
    return;
  }
  uVar1 = gRMathRand2();
  VectorSignedToFloat(uVar1,(byte)(in_fpscr >> 0x16) & 3);
  VoicePlay((int)this);
  *(undefined4 *)(this + 0x74) = 2;
  uVar1 = 1;
  if (*(float *)(this + 0x5c) <= 0.0) {
    uVar1 = 2;
  }
  *(undefined4 *)(this + 0x78) = uVar1;
  cRSubGoldy::ScoreAdd((cRSubGoldy *)(*(int *)(this + 0x7c) + 0xfac4),1,0);
  Explode(this);
  return;
}
