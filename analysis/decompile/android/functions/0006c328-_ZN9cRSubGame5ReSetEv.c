/*
 * mangled: _ZN9cRSubGame5ReSetEv
 * demangled: cRSubGame::ReSet()
 * address: 0006c328
 * size: 456
 */

/* cRSubGame::ReSet() */

void __thiscall cRSubGame::ReSet(cRSubGame *this)

{
  undefined4 uVar1;
  undefined4 uVar2;
  cRSubGame *pcVar3;
  undefined4 uVar4;
  int iVar5;

  pcVar3 = this + 0x3094;
  do {
    *(undefined4 *)pcVar3 = 0;
    *(cRSubGame **)(pcVar3 + 0xc) = this;
    pcVar3 = pcVar3 + 0x68;
  } while (pcVar3 != this + 0x33d4);
  *(undefined4 *)(this + 0x2ebc) = 0;
  pcVar3 = this + 0x657c;
  *(cRSubGame **)(this + 0x2ec8) = this;
  *(undefined4 *)(this + 0x2f1c) = 0;
  *(cRSubGame **)(this + 0x2f28) = this;
  do {
    *(undefined4 *)pcVar3 = 0;
    *(cRSubGame **)(pcVar3 + 8) = this;
    *(undefined4 *)(pcVar3 + -4) = 0;
    pcVar3 = pcVar3 + 0xb8;
  } while (pcVar3 != this + 0x896c);
  pcVar3 = this + 0x341c;
  do {
    *(undefined4 *)pcVar3 = 0;
    *(cRSubGame **)(pcVar3 + 8) = this;
    pcVar3 = pcVar3 + 0xe0;
  } while (pcVar3 != this + 0x421c);
  *(undefined4 *)(this + 0x8b14) = 0;
  *(undefined4 *)(this + 0x8968) = 0;
  *(cRSubGame **)(this + 0x8a78) = this;
  *(cRSubGame **)(this + 0x8c24) = this;
  if ((this[0x30fcc0] == (cRSubGame)0x0) ||
     (iVar5 = *(int *)(this + 0x30fcbc), *(int *)(this + 0x60) != *(int *)(iVar5 + 0x2c))) {
    if (*(int *)(this + 0x332d9c) == 2) {
      *(undefined4 *)(this + 0xfd90) = 0;
      cRSubGoldy::ScoreStatsInit((cRSubGoldy *)(this + 0xfac4));
    }
    cRTime::Zero((cRTime *)(this + 0xfd94));
    *(undefined4 *)(this + 0xfdac) = DAT_0006c4f0;
    *(undefined4 *)(this + 0xfdb0) = 0;
  }
  else {
    *(undefined4 *)(this + 0xfd90) = *(undefined4 *)(iVar5 + 4);
    uVar1 = *(undefined4 *)(iVar5 + 0xc);
    uVar2 = *(undefined4 *)(iVar5 + 0x10);
    uVar4 = *(undefined4 *)(iVar5 + 0x14);
    *(undefined4 *)(this + 0xfd94) = *(undefined4 *)(iVar5 + 8);
    *(undefined4 *)(this + 0xfd98) = uVar1;
    *(undefined4 *)(this + 0xfd9c) = uVar2;
    *(undefined4 *)(this + 0xfda0) = uVar4;
    uVar1 = *(undefined4 *)(iVar5 + 0x1c);
    *(undefined4 *)(this + 0xfda4) = *(undefined4 *)(iVar5 + 0x18);
    *(undefined4 *)(this + 0xfda8) = uVar1;
    uVar1 = *(undefined4 *)(iVar5 + 0x24);
    *(undefined4 *)(this + 0xfdac) = *(undefined4 *)(iVar5 + 0x20);
    *(undefined4 *)(this + 0xfdb0) = uVar1;
  }
  this[1] = (cRSubGame)0x1;
  uVar1 = DAT_0006c4f0;
  *this = (cRSubGame)0x1;
  *(undefined4 *)(this + 0x6500) = 0;
  this[0x30fcc0] = (cRSubGame)0x0;
  *(undefined4 *)(this + 0xfe30) = uVar1;
  return;
}
