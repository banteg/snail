/*
 * mangled: _ZN6cRQuit6UnInitEv
 * demangled: cRQuit::UnInit()
 * address: 0006f65c
 * size: 88
 */

/* cRQuit::UnInit() */

void __thiscall cRQuit::UnInit(cRQuit *this)

{
  if (*(int *)this != 1) {
    *(undefined4 *)this = 0;
    return;
  }
  cRBorderManager::Kill
            ((cRBorderManager *)(**(int **)(DAT_0006f6b4 + 0x6f674 + DAT_0006f6b8) + 0xd14),
             *(cRBorder **)(this + 4));
  *(undefined4 *)(this + 4) = 0;
  *(undefined4 *)this = 0;
  return;
}
