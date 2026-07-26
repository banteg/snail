/*
 * mangled: _ZN10cRVoiceSet2AIEv
 * demangled: cRVoiceSet::AI()
 * address: 00086eec
 * size: 52
 */

/* cRVoiceSet::AI() */

void __thiscall cRVoiceSet::AI(cRVoiceSet *this)

{
  float fVar1;

  if (0.0 < *(float *)(this + 0x10)) {
    fVar1 = *(float *)(this + 0x10) + *(float *)(this + 0x14);
    *(float *)(this + 0x10) = fVar1;
    if (1.0 < fVar1) {
      *(undefined4 *)(this + 0x10) = 0;
    }
    return;
  }
  return;
}
