/*
 * mangled: _ZN7cRSound4PlayEiR7tVector
 * demangled: cRSound::Play(int, tVector&)
 * address: 00030958
 * size: 248
 */

/* cRSound::Play(int, tVector&) */

void __thiscall cRSound::Play(cRSound *this,int param_1,tVector *param_2)

{
  float fVar1;
  int iVar2;
  float extraout_s0;
  float extraout_s1;
  float extraout_s2;
  float local_1c;
  float local_18;
  float local_14;

  iVar2 = **(int **)(DAT_00030a6c + 0x3097c + DAT_00030a70);
  local_14 = *(float *)(param_2 + 8) - *(float *)(iVar2 + 0x1cc);
  local_1c = *(float *)param_2 - *(float *)(iVar2 + 0x1c4);
  local_18 = *(float *)(param_2 + 4) - *(float *)(iVar2 + 0x1c8);
  fVar1 = (float)tVector::Magnitude((tVector *)&local_1c);
  if ((fVar1 < DAT_00030a50) && (fVar1 <= DAT_00030a54)) {
    RShellSoundPlay(*(int *)(*(int *)this + param_1 * 0xc + 4),extraout_s0,extraout_s1,extraout_s2);
  }
  return;
}
