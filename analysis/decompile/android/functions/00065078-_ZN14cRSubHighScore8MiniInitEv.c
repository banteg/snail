/*
 * mangled: _ZN14cRSubHighScore8MiniInitEv
 * demangled: cRSubHighScore::MiniInit()
 * address: 00065078
 * size: 128
 */

/* cRSubHighScore::MiniInit() */

void __thiscall cRSubHighScore::MiniInit(cRSubHighScore *this)

{
  int iVar1;
  int iVar2;
  cRSubHighScore *pcVar3;

  iVar1 = 0;
  pcVar3 = this;
  do {
    *(undefined4 *)(pcVar3 + 0x28) = 0xffffffff;
    *(undefined4 *)(pcVar3 + 8) = 0;
    iVar2 = iVar1 + 1;
    cRTime::Zero((cRTime *)(this + iVar1 * 0x38 + 0xc));
    memcpy(this + iVar1 * 0x38 + 0x2d,&DAT_000934bc,5);
    *(undefined4 *)(pcVar3 + 0x24) = 0;
    pcVar3[0x2c] = (cRSubHighScore)0x0;
    pcVar3 = pcVar3 + 0x38;
    iVar1 = iVar2;
  } while (iVar2 != 0x55);
  LoadMiniData(this);
  return;
}
