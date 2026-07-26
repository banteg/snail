/*
 * mangled: _ZN14cRSubHighScore8MiniInitEv
 * demangled: cRSubHighScore::MiniInit()
 * address: 0003d410
 * size: 168
 */

/* cRSubHighScore::MiniInit() */

void __thiscall cRSubHighScore::MiniInit(cRSubHighScore *this)

{
  cRSubHighScore *pcVar1;
  int iVar2;
  int iVar3;

  *(undefined4 *)(this + 0x28) = 0xffffffff;
  *(undefined4 *)(this + 8) = 0;
  iVar3 = 1;
  cRTime::Zero((cRTime *)(this + 0xc));
  _memcpy(this + 0x2d,"Anon",5);
  *(undefined4 *)(this + 0x24) = 0;
  this[0x2c] = (cRSubHighScore)0x0;
  pcVar1 = this;
  do {
    iVar2 = iVar3 * 0x38;
    *(undefined4 *)(pcVar1 + 0x60) = 0xffffffff;
    *(undefined4 *)(pcVar1 + 0x40) = 0;
    cRTime::Zero((cRTime *)(this + iVar2 + 0xc));
    iVar3 = iVar3 + 1;
    _memcpy(this + iVar2 + 0x2d,"Anon",5);
    *(undefined4 *)(pcVar1 + 0x5c) = 0;
    pcVar1[100] = (cRSubHighScore)0x0;
    pcVar1 = pcVar1 + 0x38;
  } while (iVar3 != 0x55);
  LoadMiniData(this);
  return;
}
