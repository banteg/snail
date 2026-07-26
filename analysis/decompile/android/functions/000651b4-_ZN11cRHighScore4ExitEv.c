/*
 * mangled: _ZN11cRHighScore4ExitEv
 * demangled: cRHighScore::Exit()
 * address: 000651b4
 * size: 180
 */

/* cRHighScore::Exit() */

void cRHighScore::Exit(void)

{
  int iVar1;
  int iVar2;

  if (*(int *)(Game + 0x71900) == 0) {
    cRSubHighScore::MiniDelete((cRSubHighScore *)(gGroup0 + Game + 0xce694),10);
    iVar1 = Game;
    *(undefined4 *)(Game + 0x15c) = 2;
    iVar2 = *(int *)(iVar1 + 0x71900);
    *(undefined4 *)(&DAT_003a463c + iVar1) = 2;
    *(undefined1 *)(iVar1 + 0x2c0) = 1;
    if (iVar2 != 1) {
      return;
    }
  }
  else {
    iVar1 = Game;
    if (*(int *)(Game + 0x71900) != 1) {
      return;
    }
  }
  cRSubHighScore::MiniDelete((cRSubHighScore *)(gGroup0 + iVar1 + 0xce694),0x15);
  iVar1 = Game;
  *(undefined4 *)(Game + 0x15c) = 10;
  *(undefined1 *)(iVar1 + 0x2c0) = 1;
  *(undefined4 *)(&DAT_003a463c + iVar1) = 2;
  return;
}
