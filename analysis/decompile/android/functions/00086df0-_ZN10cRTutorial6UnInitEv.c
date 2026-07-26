/*
 * mangled: _ZN10cRTutorial6UnInitEv
 * demangled: cRTutorial::UnInit()
 * address: 00086df0
 * size: 36
 */

/* cRTutorial::UnInit() */

void cRTutorial::UnInit(void)

{
  cRTipManager::UnInitTips
            ((cRTipManager *)(&DAT_003a63d8 + **(int **)(DAT_00086e14 + 0x86e08 + DAT_00086e18)));
  return;
}
