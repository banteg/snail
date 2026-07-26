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
  float fVar2;

  fVar1 = DAT_0006c16c;
  if (this[0xcc] != (cRSlug)0x0) {
    fVar2 = *(float *)(this + 0xd0);
    *(float *)(this + 0xd0) = fVar2 + *(float *)(this + 0xd4);
    if (fVar1 < fVar2 + *(float *)(this + 0xd4)) {
      *(undefined4 *)(this + 0xd0) = DAT_0006c170;
      this[0xcc] = (cRSlug)0x0;
    }
    return;
  }
  return;
}
