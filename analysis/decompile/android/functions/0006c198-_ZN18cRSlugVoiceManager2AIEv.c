/*
 * mangled: _ZN18cRSlugVoiceManager2AIEv
 * demangled: cRSlugVoiceManager::AI()
 * address: 0006c198
 * size: 60
 */

/* cRSlugVoiceManager::AI() */

void __thiscall cRSlugVoiceManager::AI(cRSlugVoiceManager *this)

{
  float fVar1;
  float fVar2;

  fVar1 = DAT_0006c1d4;
  if (0.0 < *(float *)(this + 4)) {
    fVar2 = *(float *)(this + 4) + *(float *)(this + 8);
    *(float *)(this + 4) = fVar2;
    if (fVar1 < fVar2) {
      *(undefined4 *)(this + 4) = DAT_0006c1d8;
      *this = (cRSlugVoiceManager)0x0;
    }
    return;
  }
  return;
}
