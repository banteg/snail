/*
 * mangled: _ZN9cRTimesUp6UnInitEv
 * demangled: cRTimesUp::UnInit()
 * address: 0006f6e8
 * size: 48
 */

/* cRTimesUp::UnInit() */

void __thiscall cRTimesUp::UnInit(cRTimesUp *this)

{
  if (*(int *)this == 0) {
    return;
  }
  cRBorderManager::Kill
            ((cRBorderManager *)(**(int **)(DAT_0006f718 + 0x6f6fc + DAT_0006f71c) + 0xd14),
             *(cRBorder **)(this + 4));
  return;
}
