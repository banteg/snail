/*
 * mangled: _ZN9cRSubGame11SetFeaturesEv
 * demangled: cRSubGame::SetFeatures()
 * address: 00017a40
 * size: 108
 */

/* cRSubGame::SetFeatures() */

void __thiscall cRSubGame::SetFeatures(cRSubGame *this)

{
  if (this[0x2e09cc] != (cRSubGame)0x0) {
    *(undefined4 *)(this + 100) = *(undefined4 *)(*(int *)(this + 0x2e09d0) + 0x38);
    return;
  }
  *(undefined4 *)(this + 100) = 0x484;
  *(char **)(this + 100) =
       "brian/Desktop/Project_1_3_0_02/iSMu/OpenFeint.2.4.8/OpenFeint/api/internal/OpenFeint/OpenFeintSettings.mm"
  ;
  switch(*(undefined4 *)(this + 0x58)) {
  case 0:
  case 1:
    *(undefined4 *)(this + 100) = 0xf5cfff;
    return;
  case 4:
    *(undefined4 *)(this + 100) = 0x75cfff;
    return;
  case 7:
    *(undefined4 *)(this + 100) = 0xe4cfff;
  }
  return;
}
