/*
 * mangled: _ZN9cRToolTip5ReSetEv
 * demangled: cRToolTip::ReSet()
 * address: 0005c478
 * size: 84
 */

/* cRToolTip::ReSet() */

void __thiscall cRToolTip::ReSet(cRToolTip *this)

{
  if (*(int *)(this + 4) != 2) {
    if (*(int *)(this + 4) != 3) {
      return;
    }
    cRBorderManager::Kill
              ((cRBorderManager *)(**(int **)(DAT_0005c4cc + 0x5c490 + DAT_0005c4d0) + 0xd14),
               *(cRBorder **)(this + 0x18));
    *(undefined4 *)(this + 0x18) = 0;
  }
  *(undefined4 *)(this + 4) = 1;
  return;
}
