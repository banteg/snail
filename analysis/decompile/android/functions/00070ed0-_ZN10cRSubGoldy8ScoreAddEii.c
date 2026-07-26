/*
 * mangled: _ZN10cRSubGoldy8ScoreAddEii
 * demangled: cRSubGoldy::ScoreAdd(int, int)
 * address: 00070ed0
 * size: 284
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
    goto LAB_00070f0c;
  case 3:
    goto LAB_00070f0c;
  case 4:
LAB_00070f0c:
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
  iVar2 = *(int *)(this + 0x2cc);
  iVar1 = param_2 + iVar2;
  *(int *)(this + 0x2cc) = iVar1;
  *(int *)(this + (param_1 + 0xbe) * 4) = param_2 + *(int *)(this + (param_1 + 0xbe) * 4);
  if ((((iVar2 / 50000 != iVar1 / 50000) && (*(int *)(this + 0x3ff4) < 9)) &&
      (*(int *)(this + 0x3ff4) = *(int *)(this + 0x3ff4) + 1, *(int *)(Game + 0x71900) == 0)) &&
     (*(int *)(Game + 0x24) == 0)) {
    cRSound::Play((int)&gRSound);
    return;
  }
  return;
}
