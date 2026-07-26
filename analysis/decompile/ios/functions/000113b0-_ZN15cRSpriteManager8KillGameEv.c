/*
 * mangled: _ZN15cRSpriteManager8KillGameEv
 * demangled: cRSpriteManager::KillGame()
 * address: 000113b0
 * size: 260
 */

/* cRSpriteManager::KillGame() */

void cRSpriteManager::KillGame(void)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  int iVar5;

  iVar5 = 0;
  do {
    puVar4 = *(undefined4 **)((int)&DAT_002ac5dc + iVar5);
    while (puVar1 = puVar4, puVar1 != (undefined4 *)0x0) {
      puVar4 = (undefined4 *)puVar1[3];
      if ((puVar1[1] & 0x800) != 0) {
        if ((puVar1[1] & 1) == 0) {
          RShellError("Sprite kill error, already dead (%s)",puVar1[7] + 0xc);
        }
        if (puVar1 != &_gSpriteDummy) {
          puVar1[1] = puVar1[1] & 0xfffffffe;
          iVar2 = puVar1[2];
          if (puVar1 == (undefined4 *)(&DAT_002ac5dc)[iVar2]) {
            iVar3 = puVar1[3];
            if (iVar3 != 0) {
              *(undefined4 *)(iVar3 + 0x10) = 0;
            }
            (&DAT_002ac5dc)[iVar2] = iVar3;
            puVar1[3] = DAT_002ac5e8;
            DAT_002ac5e8 = puVar1;
          }
          else {
            iVar2 = puVar1[4];
            if (iVar2 != 0) {
              *(undefined4 *)(iVar2 + 0xc) = puVar1[3];
            }
            if (puVar1[3] != 0) {
              *(int *)(puVar1[3] + 0x10) = iVar2;
            }
            puVar1[3] = DAT_002ac5e8;
            DAT_002ac5e8 = puVar1;
          }
        }
      }
    }
    iVar5 = iVar5 + 4;
  } while (iVar5 != 0xc);
  return;
}
