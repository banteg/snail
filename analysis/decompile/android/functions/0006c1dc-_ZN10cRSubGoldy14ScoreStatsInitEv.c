/*
 * mangled: _ZN10cRSubGoldy14ScoreStatsInitEv
 * demangled: cRSubGoldy::ScoreStatsInit()
 * address: 0006c1dc
 * size: 32
 */

/* cRSubGoldy::ScoreStatsInit() */

void __thiscall cRSubGoldy::ScoreStatsInit(cRSubGoldy *this)

{
  int iVar1;

  iVar1 = 0;
  do {
    iVar1 = iVar1 + 1;
    *(undefined4 *)(this + 0x2f8) = 0;
    this = this + 4;
  } while (iVar1 != 7);
  return;
}
