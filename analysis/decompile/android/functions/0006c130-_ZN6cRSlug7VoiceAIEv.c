/*
 * mangled: _ZN6cRSlug7VoiceAIEv
 * demangled: cRSlug::VoiceAI()
 * address: 0006c130
 * size: 60
 */

/* cRSlug::VoiceAI() */

void __thiscall cRSlug::VoiceAI(cRSlug *this)

{
  float fVar1;

  if (this[0xcc] != (cRSlug)0x0) {
    fVar1 = *(float *)(this + 0xd0);
    *(float *)(this + 0xd0) = fVar1 + *(float *)(this + 0xd4);
    if (1.0 < fVar1 + *(float *)(this + 0xd4)) {
      *(undefined4 *)(this + 0xd0) = 0;
      this[0xcc] = (cRSlug)0x0;
    }
    return;
  }
  return;
}
