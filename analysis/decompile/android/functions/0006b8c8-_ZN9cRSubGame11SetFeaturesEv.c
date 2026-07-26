/*
 * mangled: _ZN9cRSubGame11SetFeaturesEv
 * demangled: cRSubGame::SetFeatures()
 * address: 0006b8c8
 * size: 184
 */

/* cRSubGame::SetFeatures() */

void __thiscall cRSubGame::SetFeatures(cRSubGame *this)

{
  if (this[0x30fcc0] != (cRSubGame)0x0) {
    *(undefined4 *)(this + 0x6c) = *(undefined4 *)(*(int *)(this + 0x30fcc4) + 0x38);
    return;
  }
  *(undefined4 *)(this + 0x6c) = 0x484;
  *(undefined4 *)(this + 0x6c) = 0x600484;
  switch(*(undefined4 *)(this + 0x60)) {
  case 0:
    goto LAB_0006b938;
  case 1:
LAB_0006b938:
    *(uint *)(this + 0x6c) = *(uint *)(this + 0x6c) | 0x95cbff;
    return;
  case 2:
    break;
  case 3:
    break;
  case 4:
    *(uint *)(this + 0x6c) = *(uint *)(this + 0x6c) | 0x15cbff;
    return;
  case 5:
    break;
  case 6:
    break;
  case 7:
    *(uint *)(this + 0x6c) = *(uint *)(this + 0x6c) | 0x84cbff;
  }
  return;
}
