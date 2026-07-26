/*
 * mangled: _ZN10cRSubGoldy9DeathInitEv
 * demangled: cRSubGoldy::DeathInit()
 * address: 00070ffc
 * size: 176
 */

/* cRSubGoldy::DeathInit() */

void __thiscall cRSubGoldy::DeathInit(cRSubGoldy *this)

{
  switch(*(undefined4 *)(*(int *)(this + 0x400) + 0x60)) {
  case 0:
    if (*(int *)(this + 0x3ff4) < 1) {
      SetGameState(0,0,0,0);
      RessurectInit(this,1);
      return;
    }
    SetGameState(1,*(int *)(this + 0x2cc),*(int *)(*(int *)(this + 0x400) + 100),
                 *(int *)(this + 0x3ff4) + -1);
    RessurectInit(this,0);
    return;
  case 1:
    goto LAB_00071038;
  case 2:
    break;
  case 3:
    break;
  case 4:
LAB_00071038:
    RessurectInit(this,1);
    return;
  case 5:
    break;
  case 6:
    break;
  case 7:
    RessurectInit(this,0);
    return;
  }
  return;
}
