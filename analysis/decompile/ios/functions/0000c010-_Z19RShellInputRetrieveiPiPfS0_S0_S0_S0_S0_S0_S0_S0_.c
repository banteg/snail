/*
 * mangled: _Z19RShellInputRetrieveiPiPfS0_S0_S0_S0_S0_S0_S0_S0_
 * demangled: RShellInputRetrieve(int, int*, float*, float*, float*, float*, float*, float*, float*, float*, float*)
 * address: 0000c010
 * size: 200
 */

/* RShellInputRetrieve(int, int*, float*, float*, float*, float*, float*, float*, float*, float*,
   float*) */

void RShellInputRetrieve(int param_1,int *param_2,float *param_3,float *param_4,float *param_5,
                        float *param_6,float *param_7,float *param_8,float *param_9,float *param_10,
                        float *param_11)

{
  if (param_1 == 0) {
    *param_2 = DAT_0026657c;
    *param_3 = DAT_00266574;
    *param_4 = DAT_00266578;
    *param_5 = DAT_00266588;
    *param_6 = DAT_0026658c;
    *param_7 = DAT_00266590;
    *param_10 = DAT_00266594;
    *param_11 = DAT_00266598;
    *param_8 = DAT_00266580;
    *param_9 = DAT_00266584;
    return;
  }
  *param_2 = _gMouseWX1;
  *param_3 = _gMouseWY0;
  *param_4 = DAT_002665b8;
  *param_5 = DAT_002665c8;
  *param_6 = _RShellSoundCount;
  *param_7 = _RShellSoundName;
  *param_8 = DAT_002665c0;
  *param_9 = _gMouseWY1;
  return;
}
