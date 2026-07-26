/*
 * mangled: _ZN10cRSubGoldy17ScoreStatsDisplayEv
 * demangled: cRSubGoldy::ScoreStatsDisplay()
 * address: 00017f00
 * size: 308
 */

/* cRSubGoldy::ScoreStatsDisplay() */

void __thiscall cRSubGoldy::ScoreStatsDisplay(cRSubGoldy *this)

{
  undefined4 uVar1;

  if (*(int *)(this + 0x2cc) == 0) {
    return;
  }
  wprintf("\n Score Stats: %i\n");
  uVar1 = ___divsi3(*(int *)(this + 0x2f8) * 100,*(undefined4 *)(this + 0x2cc));
  wprintf("Garbage       :%i%%\n",uVar1);
  uVar1 = ___divsi3(*(int *)(this + 0x2fc) * 100,*(undefined4 *)(this + 0x2cc));
  wprintf("Slug          :%i%%\n",uVar1);
  uVar1 = ___divsi3(*(int *)(this + 0x300) * 100,*(undefined4 *)(this + 0x2cc));
  wprintf("Ring          :%i%%\n",uVar1);
  uVar1 = ___divsi3(*(int *)(this + 0x304) * 100,*(undefined4 *)(this + 0x2cc));
  wprintf("Parcel Collect:%i%%\n",uVar1);
  uVar1 = ___divsi3(*(int *)(this + 0x308) * 100,*(undefined4 *)(this + 0x2cc));
  wprintf("Parcel Deliver:%i%%\n",uVar1);
  uVar1 = ___divsi3(*(int *)(this + 0x30c) * 100,*(undefined4 *)(this + 0x2cc));
  wprintf("Bonus         :%i%%\n",uVar1);
  wprintf("\n");
  return;
}
