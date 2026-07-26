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
  int iVar3;
  int iVar4;
  int *piVar5;

  iVar1 = DAT_0006526c;
  iVar3 = DAT_00065268 + 0x651cc;
  piVar5 = *(int **)(iVar3 + DAT_0006526c);
  iVar2 = *piVar5;
  if (*(int *)(iVar2 + 0x71900) == 0) {
    cRSubHighScore::MiniDelete((cRSubHighScore *)(gGroup0 + iVar2 + 0xce694),10);
    iVar2 = *piVar5;
    *(undefined4 *)(iVar2 + 0x15c) = 2;
    iVar4 = *(int *)(iVar2 + 0x71900);
    *(undefined4 *)(&DAT_003a463c + iVar2) = 2;
    *(undefined1 *)(iVar2 + 0x2c0) = 1;
    if (iVar4 != 1) {
      return;
    }
  }
  else if (*(int *)(iVar2 + 0x71900) != 1) {
    return;
  }
  cRSubHighScore::MiniDelete((cRSubHighScore *)(gGroup0 + iVar2 + 0xce694),0x15);
  iVar1 = **(int **)(iVar3 + iVar1);
  *(undefined4 *)(iVar1 + 0x15c) = 10;
  *(undefined1 *)(iVar1 + 0x2c0) = 1;
  *(undefined4 *)(&DAT_003a463c + iVar1) = 2;
  return;
}
