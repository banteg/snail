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
  float fVar2;

  fVar1 = DAT_00086f20;
  if (0.0 < *(float *)(this + 0x10)) {
    fVar2 = *(float *)(this + 0x10) + *(float *)(this + 0x14);
    *(float *)(this + 0x10) = fVar2;
    if (fVar1 < fVar2) {
      *(undefined4 *)(this + 0x10) = DAT_00086f24;
    }
    return;
  }
  return;
}
