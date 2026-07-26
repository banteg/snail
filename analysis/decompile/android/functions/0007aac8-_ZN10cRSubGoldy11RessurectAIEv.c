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
  float fVar2;
  int iVar3;
  undefined4 uVar4;
  cRSubGame *this_00;
  int iVar5;
  int iVar6;
  int *piVar7;
  float fVar8;

  iVar5 = DAT_0007ac50;
  iVar6 = DAT_0007ac4c + 0x7aae8;
  *(undefined4 *)(this + 0x410) = DAT_0007ac44;
  fVar2 = DAT_0007ac48;
  iVar3 = **(int **)(iVar6 + iVar5);
  if (*(int *)(iVar3 + 0x24) == 0) {
    fVar8 = *(float *)(this + 0x80);
    *(float *)(this + 0x80) = fVar8 + *(float *)(this + 0x84);
    if (fVar8 + *(float *)(this + 0x84) <= fVar2) {
      return;
    }
    cRFade::Start((cRFade *)(iVar3 + 0x24),(_func_void *)0x0);
    bVar1 = fVar2 < *(float *)(this + 0x80);
  }
  else if (*(float *)(this + 0x80) <= DAT_0007ac48) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  if (bVar1) {
    piVar7 = *(int **)(iVar6 + iVar5);
    iVar5 = *piVar7;
    if (*(int *)(iVar5 + 0x24) == 4) {
      if (*(int *)(this + 0x74) == 0) {
        if (*(int *)(*(int *)(this + 0x400) + 0x60) == 0) {
          *(int *)(this + 0x3ff4) = *(int *)(this + 0x3ff4) + -1;
        }
        uVar4 = *(undefined4 *)(iVar5 + 0x15c);
        *(undefined4 *)(iVar5 + 0x15c) = 0x1c;
        *(undefined4 *)(iVar5 + 0x160) = uVar4;
      }
      else {
        this_00 = *(cRSubGame **)(this + 0x400);
        *(undefined4 *)(this_00 + 0x332d9c) = 2;
        cRSubGame::Complete(this_00,true);
        iVar5 = *(int *)(this + 0x400);
        if (gGroup0[iVar5 + 0x9d619] == '\0') {
          iVar3 = *piVar7;
          *(undefined4 *)(iVar3 + 0x160) = *(undefined4 *)(iVar3 + 0x15c);
          if ((*(int *)(iVar5 + 0x60) == 0) && (*(char *)(iVar3 + 0x2c1) == '\0')) {
            *(undefined4 *)(iVar3 + 0x160) = 2;
            *(undefined4 *)(iVar3 + 0x15c) = 0x1a;
          }
          else {
            *(undefined4 *)(iVar3 + 0x15c) = 0x1b;
          }
        }
        else {
          iVar5 = *piVar7;
          uVar4 = *(undefined4 *)(iVar5 + 0x15c);
          *(undefined4 *)(iVar5 + 0x15c) = 0x1a;
          *(undefined4 *)(iVar5 + 0x160) = uVar4;
        }
      }
    }
  }
  return;
}
