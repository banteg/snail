/*
 * mangled: _ZN9cRSubGame8CompleteEb
 * demangled: cRSubGame::Complete(bool)
 * address: 0007a8ac
 * size: 532
 */

/* cRSubGame::Complete(bool) */

void __thiscall cRSubGame::Complete(cRSubGame *this,bool param_1)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  int iVar6;
  undefined4 *puVar7;

  cRSubGoldy::ScoreStatsDisplay((cRSubGoldy *)(this + 0xfac4));
  puVar7 = *(undefined4 **)(this + 0x30fcbc);
  iVar3 = *(int *)(this + 0x30fccc);
  puVar7[0x1b] = puVar7[0x1b] + 1;
  *(int *)(this + 0x30fccc) = *(int *)(this + 0x30fccc) + 1;
  uVar1 = gCheat & 1;
  *(ushort *)((int)puVar7 + iVar3 * 6 + 0x74) = *(ushort *)((int)puVar7 + iVar3 * 6 + 0x74) | 8;
  if (uVar1 == 0) {
    *puVar7 = 1;
    puVar7[1] = *(undefined4 *)(this + 0xfd90);
    uVar2 = *(undefined4 *)(this + 0xfd98);
    uVar4 = *(undefined4 *)(this + 0xfd9c);
    uVar5 = *(undefined4 *)(this + 0xfda0);
    puVar7[2] = *(undefined4 *)(this + 0xfd94);
    puVar7[3] = uVar2;
    puVar7[4] = uVar4;
    puVar7[5] = uVar5;
    uVar2 = *(undefined4 *)(this + 0xfda8);
    puVar7[6] = *(undefined4 *)(this + 0xfda4);
    puVar7[7] = uVar2;
    uVar2 = *(undefined4 *)(this + 0x44);
    puVar7[8] = *(undefined4 *)(this + 0xfdac);
    puVar7[0x12] = *(undefined4 *)(this + 0x4c);
    puVar7[0xd] = *(undefined4 *)(this + 0x50);
    puVar7[0x13] = uVar2;
    uVar2 = *(undefined4 *)(this + 0x48);
    puVar7[0x7eac] = *(undefined4 *)(this + 0x321070);
    puVar7[0x7ead] = *(undefined4 *)(this + 0x321074);
    puVar7[0x14] = uVar2;
    iVar6 = *(int *)(this + 0xfdb0);
    puVar7[9] = iVar6;
    puVar7[0xb] = *(undefined4 *)(this + 0x60);
    iVar3 = *(int *)(this + 0x60);
    if ((((iVar3 != 1) || (iVar6 != 0)) && (this[0x30fcc0] == (cRSubGame)0x0)) && (param_1)) {
      if (iVar3 == 1) {
        cRSubHighScore::AddSurvival((cRSubHighScore *)(this + 0x2cf49c));
        return;
      }
      if (iVar3 == 4) {
        cRSubHighScore::AddTimeTrial
                  ((cRSubHighScore *)(this + 0x2cf49c),*(int *)(this + 100),(bool)this[0xfefc]);
        return;
      }
      if (iVar3 == 0) {
        if (*(int *)(this + 0x3210c0) == 0) {
          cRSubHighScore::AddArcade((cRSubHighScore *)(this + 0x2cf49c),*(int *)(this + 100));
          return;
        }
        if (*(int *)(this + 0x3210c0) == 1) {
          cRSubHighScore::AddArcadePro((cRSubHighScore *)(this + 0x2cf49c),*(int *)(this + 100));
          return;
        }
      }
    }
  }
  return;
}
