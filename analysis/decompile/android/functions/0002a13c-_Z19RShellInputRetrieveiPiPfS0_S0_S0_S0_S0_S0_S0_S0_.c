/*
 * mangled: _Z19RShellInputRetrieveiPiPfS0_S0_S0_S0_S0_S0_S0_S0_
 * demangled: RShellInputRetrieve(int, int*, float*, float*, float*, float*, float*, float*, float*, float*, float*)
 * address: 0002a13c
 * size: 220
 */

/* RShellInputRetrieve(int, int*, float*, float*, float*, float*, float*, float*, float*, float*,
   float*) */

void RShellInputRetrieve(int param_1,int *param_2,float *param_3,float *param_4,float *param_5,
                        float *param_6,float *param_7,float *param_8,float *param_9,float *param_10,
                        float *param_11)

{
  undefined4 uVar1;

  if (param_1 == 0) {
    *param_3 = (float)RShellInput._20_4_;
    *param_4 = (float)RShellInput._24_4_;
    uVar1 = RShellInput._28_4_;
    *param_5 = (float)RShellInput._40_4_;
    *param_6 = (float)RShellInput._44_4_;
    *param_7 = (float)RShellInput._48_4_;
    *param_2 = uVar1;
    *param_10 = (float)RShellInput._52_4_;
    *param_11 = (float)RShellInput._56_4_;
    *param_8 = (float)RShellInput._32_4_;
    *param_9 = (float)RShellInput._36_4_;
  }
  else {
    *param_3 = (float)RShellMusicCurrent._4_4_;
    *param_4 = (float)RShellMusicCurrent._8_4_;
    uVar1 = RShellMusicCurrent._12_4_;
    *param_5 = (float)RShellMusicCurrent._24_4_;
    *param_6 = (float)RShellMusicCurrent._28_4_;
    *param_7 = (float)RShellMusicCurrent._32_4_;
    *param_2 = uVar1;
    *param_8 = (float)RShellMusicCurrent._16_4_;
    *param_9 = (float)RShellMusicCurrent._20_4_;
  }
  return;
}
