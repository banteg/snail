/*
 * mangled: _ZN7cRSound4PlayEiR7tVector
 * demangled: cRSound::Play(int, tVector&)
 * address: 000631fc
 * size: 224
 */

/* cRSound::Play(int, tVector&) */

void __thiscall cRSound::Play(cRSound *this,int param_1,tVector *param_2)

{
  float fVar1;
  int iVar2;
  float fVar3;
  float fVar4;
  float local_1c;
  float local_18;
  float local_14;

  iVar2 = *(int *)PTR__Game_001b60b8;
  local_1c = *(float *)param_2 - *(float *)(iVar2 + 0x1c4);
  local_18 = *(float *)(param_2 + 4) - *(float *)(iVar2 + 0x1c8);
  local_14 = *(float *)(param_2 + 8) - *(float *)(iVar2 + 0x1cc);
  fVar1 = (float)tVector::Magnitude((tVector *)&local_1c);
  if ((fVar1 < 1e+10) && (fVar1 <= 25.0)) {
    fVar3 = *(float *)param_2 * -0.25 * 100.0;
    fVar4 = -100.0;
    if ((-100.0 <= fVar3) && (fVar4 = fVar3, 100.0 < fVar3)) {
      fVar4 = 100.0;
    }
    RShellSoundPlay(param_1,fVar1 / -25.0 + 1.0,-1.0,fVar4);
  }
  return;
}
