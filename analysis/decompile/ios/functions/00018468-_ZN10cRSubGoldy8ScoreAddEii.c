/*
 * mangled: _ZN10cRSubGoldy8ScoreAddEii
 * demangled: cRSubGoldy::ScoreAdd(int, int)
 * address: 00018468
 * size: 224
 */

/* cRSubGoldy::ScoreAdd(int, int) */

void __thiscall cRSubGoldy::ScoreAdd(cRSubGoldy *this,int param_1,int param_2)

{
  int iVar1;
  int iVar2;

  switch(param_1) {
  case 0:
    param_2 = 10;
    break;
  case 1:
    param_2 = 500;
    break;
  case 2:
  case 3:
  case 4:
    param_2 = 100;
    break;
  case 5:
    break;
  case 6:
    param_2 = 0xfa;
    break;
  default:
    RShellError("Unknown Score Type");
    param_2 = 0;
  }
  *(int *)(this + param_1 * 4 + 0x2f8) = param_2 + *(int *)(this + param_1 * 4 + 0x2f8);
  iVar2 = *(int *)(this + 0x2cc);
  iVar1 = param_2 + iVar2;
  *(int *)(this + 0x2cc) = iVar1;
  if (iVar2 / 50000 == iVar1 / 50000) {
    return;
  }
  if (8 < *(int *)(this + 0x3fec)) {
    return;
  }
  *(int *)(this + 0x3fec) = *(int *)(this + 0x3fec) + 1;
  if (*(int *)(*(int *)PTR__Game_001b60b8 + 0x72bd0) == 0) {
    if (*(int *)(*(int *)PTR__Game_001b60b8 + 0x24) == 0) {
      cRSound::Play((cRSound *)PTR__gRSound_001b61e0,0x2d);
      return;
    }
    return;
  }
  return;
}
