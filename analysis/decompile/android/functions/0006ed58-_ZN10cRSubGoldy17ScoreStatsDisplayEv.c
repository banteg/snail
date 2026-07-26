/*
 * mangled: _ZN10cRSubGoldy17ScoreStatsDisplayEv
 * demangled: cRSubGoldy::ScoreStatsDisplay()
 * address: 0006ed58
 * size: 276
 */

/* cRSubGoldy::ScoreStatsDisplay() */

void __thiscall cRSubGoldy::ScoreStatsDisplay(cRSubGoldy *this)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;

  iVar1 = DAT_0006ee74;
  iVar3 = DAT_0006ee6c + 0x6ed74;
  if (*(int *)(this + 0x2cc) == 0) {
    return;
  }
  wprintf((char *)(iVar3 + DAT_0006ee70));
  uVar2 = __divsi3(*(int *)(this + 0x2f8) * 100,*(undefined4 *)(this + 0x2cc));
  wprintf((char *)(iVar3 + iVar1),uVar2);
  iVar1 = DAT_0006ee78;
  uVar2 = __divsi3(*(int *)(this + 0x2fc) * 100,*(undefined4 *)(this + 0x2cc));
  wprintf((char *)(iVar3 + iVar1),uVar2);
  iVar1 = DAT_0006ee7c;
  uVar2 = __divsi3(*(int *)(this + 0x300) * 100,*(undefined4 *)(this + 0x2cc));
  wprintf((char *)(iVar3 + iVar1),uVar2);
  iVar1 = DAT_0006ee80;
  uVar2 = __divsi3(*(int *)(this + 0x304) * 100,*(undefined4 *)(this + 0x2cc));
  wprintf((char *)(iVar3 + iVar1),uVar2);
  iVar1 = DAT_0006ee84;
  uVar2 = __divsi3(*(int *)(this + 0x308) * 100,*(undefined4 *)(this + 0x2cc));
  wprintf((char *)(iVar3 + iVar1),uVar2);
  iVar1 = DAT_0006ee88;
  uVar2 = __divsi3(*(int *)(this + 0x30c) * 100,*(undefined4 *)(this + 0x2cc));
  wprintf((char *)(iVar3 + iVar1),uVar2);
  wprintf((char *)(iVar3 + DAT_0006ee8c));
  return;
}
