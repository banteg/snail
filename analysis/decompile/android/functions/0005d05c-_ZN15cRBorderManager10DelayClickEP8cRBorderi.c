/*
 * mangled: _ZN15cRBorderManager10DelayClickEP8cRBorderi
 * demangled: cRBorderManager::DelayClick(cRBorder*, int)
 * address: 0005d05c
 * size: 176
 */

/* cRBorderManager::DelayClick(cRBorder*, int) */

void __thiscall cRBorderManager::DelayClick(cRBorderManager *this,cRBorder *param_1,int param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;

  if (this[0x430e4] == (cRBorderManager)0x0) {
    if ((*(uint *)(param_1 + 0x194) & 0x40000000) != 0) {
      cRFade::Start((cRFade *)(**(int **)(DAT_0005d114 + 0x5d084 + DAT_0005d118) + 0x24),
                    (_func_void *)0x0);
    }
    uVar1 = DAT_0005d10c;
    *(int *)(this + 0x430e0) = param_2;
    this[0x430e4] = (cRBorderManager)0x1;
    uVar2 = DAT_0005d110;
    *(undefined4 *)(this + 0x430e8) = uVar1;
    *(cRBorder **)(this + 0x430f0) = param_1;
    *(undefined4 *)(this + 0x430ec) = uVar2;
  }
  return;
}
