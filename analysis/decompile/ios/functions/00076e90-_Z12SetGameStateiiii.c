/*
 * mangled: _Z12SetGameStateiiii
 * demangled: SetGameState(int, int, int, int)
 * address: 00076e90
 * size: 220
 */

/* SetGameState(int, int, int, int) */

void SetGameState(int param_1,int param_2,int param_3,int param_4)

{
  undefined *puVar1;

  puVar1 = PTR__gConfig_001b60d4;
  *(int *)(PTR__gConfig_001b60d4 + 0xcc) = param_1;
  if (param_1 == 2) {
    if (*(int *)(&DAT_00364944 + *(int *)PTR__Game_001b60b8) == 0) goto LAB_00076f0c;
    if (*(int *)(&DAT_00364944 + *(int *)PTR__Game_001b60b8) != 1) {
      gRegisterSaveFile("ism.cfg",PTR__gConfig_001b60d4,0xf0);
      return;
    }
  }
  else {
    if (*(int *)(&DAT_00364944 + *(int *)PTR__Game_001b60b8) == 0) {
      *(int *)(puVar1 + 0xd0) = param_2;
      *(int *)(puVar1 + 0xd8) = param_3;
LAB_00076f0c:
      *(int *)(puVar1 + 0xd4) = param_4;
      gRegisterSaveFile("ism.cfg",PTR__gConfig_001b60d4,0xf0);
      return;
    }
    if (*(int *)(&DAT_00364944 + *(int *)PTR__Game_001b60b8) != 1) {
      gRegisterSaveFile("ism.cfg",PTR__gConfig_001b60d4,0xf0);
      return;
    }
    *(int *)(puVar1 + 0xe0) = param_2;
    *(int *)(puVar1 + 0xdc) = param_3;
  }
  *(int *)(puVar1 + 0xe4) = param_4;
  gRegisterSaveFile("ism.cfg",PTR__gConfig_001b60d4,0xf0);
  return;
}
