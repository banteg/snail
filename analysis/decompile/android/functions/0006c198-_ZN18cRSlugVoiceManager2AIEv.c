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

  if (0.0 < *(float *)(this + 4)) {
    fVar1 = *(float *)(this + 4) + *(float *)(this + 8);
    *(float *)(this + 4) = fVar1;
    if (1.0 < fVar1) {
      *(undefined4 *)(this + 4) = 0;
      *this = (cRSlugVoiceManager)0x0;
    }
    return;
  }
  return;
}
