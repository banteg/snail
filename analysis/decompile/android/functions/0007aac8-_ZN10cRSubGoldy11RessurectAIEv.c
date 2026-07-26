/*
 * mangled: _ZN10cRSubGoldy11RessurectAIEv
 * demangled: cRSubGoldy::RessurectAI()
 * address: 0007aac8
 * size: 380
 */

/* cRSubGoldy::RessurectAI() */

void __thiscall cRSubGoldy::RessurectAI(cRSubGoldy *this)

{
  bool bVar1;
  int iVar2;
  undefined4 uVar3;
  cRSubGame *this_00;
  int iVar4;
  float fVar5;

  *(undefined4 *)(this + 0x410) = 0;
  iVar2 = Game;
  if (*(int *)(Game + 0x24) == 0) {
    fVar5 = *(float *)(this + 0x80);
    *(float *)(this + 0x80) = fVar5 + *(float *)(this + 0x84);
    if (fVar5 + *(float *)(this + 0x84) <= 1.0) {
      return;
    }
    cRFade::Start((cRFade *)(iVar2 + 0x24),(_func_void *)0x0);
    bVar1 = 1.0 < *(float *)(this + 0x80);
  }
  else if (*(float *)(this + 0x80) <= 1.0) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  iVar2 = Game;
  if ((bVar1) && (*(int *)(Game + 0x24) == 4)) {
    if (*(int *)(this + 0x74) == 0) {
      if (*(int *)(*(int *)(this + 0x400) + 0x60) == 0) {
        *(int *)(this + 0x3ff4) = *(int *)(this + 0x3ff4) + -1;
      }
      uVar3 = *(undefined4 *)(iVar2 + 0x15c);
      *(undefined4 *)(iVar2 + 0x15c) = 0x1c;
      *(undefined4 *)(iVar2 + 0x160) = uVar3;
    }
    else {
      this_00 = *(cRSubGame **)(this + 0x400);
      *(undefined4 *)(this_00 + 0x332d9c) = 2;
      cRSubGame::Complete(this_00,true);
      iVar2 = Game;
      iVar4 = *(int *)(this + 0x400);
      if (gGroup0[iVar4 + 0x9d619] == '\0') {
        *(undefined4 *)(Game + 0x160) = *(undefined4 *)(Game + 0x15c);
        if ((*(int *)(iVar4 + 0x60) == 0) && (*(char *)(iVar2 + 0x2c1) == '\0')) {
          *(undefined4 *)(iVar2 + 0x160) = 2;
          *(undefined4 *)(iVar2 + 0x15c) = 0x1a;
        }
        else {
          *(undefined4 *)(iVar2 + 0x15c) = 0x1b;
        }
      }
      else {
        uVar3 = *(undefined4 *)(Game + 0x15c);
        *(undefined4 *)(Game + 0x15c) = 0x1a;
        *(undefined4 *)(iVar2 + 0x160) = uVar3;
      }
    }
  }
  return;
}
