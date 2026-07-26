/*
 * mangled: _ZN9cRSubGame8CompleteEb
 * demangled: cRSubGame::Complete(bool)
 * address: 0007a8ac
 * size: 532
 */

/* cRSubGame::Complete(bool) */

void __thiscall cRSubGame::Complete(cRSubGame *this,bool param_1)

{
  uint *puVar1;
  uint uVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  int iVar7;
  undefined4 *puVar8;

  cRSubGoldy::ScoreStatsDisplay((cRSubGoldy *)(this + 0xfac4));
  puVar8 = *(undefined4 **)(this + 0x30fcbc);
  iVar4 = *(int *)(this + 0x30fccc);
  puVar1 = *(uint **)(DAT_0007aac0 + 0x7a8ec + DAT_0007aac4);
  puVar8[0x1b] = puVar8[0x1b] + 1;
  *(int *)(this + 0x30fccc) = *(int *)(this + 0x30fccc) + 1;
  uVar2 = *puVar1;
  *(ushort *)((int)puVar8 + iVar4 * 6 + 0x74) = *(ushort *)((int)puVar8 + iVar4 * 6 + 0x74) | 8;
  if ((uVar2 & 1) == 0) {
    *puVar8 = 1;
    puVar8[1] = *(undefined4 *)(this + 0xfd90);
    uVar3 = *(undefined4 *)(this + 0xfd98);
    uVar5 = *(undefined4 *)(this + 0xfd9c);
    uVar6 = *(undefined4 *)(this + 0xfda0);
    puVar8[2] = *(undefined4 *)(this + 0xfd94);
    puVar8[3] = uVar3;
    puVar8[4] = uVar5;
    puVar8[5] = uVar6;
    uVar3 = *(undefined4 *)(this + 0xfda8);
    puVar8[6] = *(undefined4 *)(this + 0xfda4);
    puVar8[7] = uVar3;
    uVar3 = *(undefined4 *)(this + 0x44);
    puVar8[8] = *(undefined4 *)(this + 0xfdac);
    puVar8[0x12] = *(undefined4 *)(this + 0x4c);
    puVar8[0xd] = *(undefined4 *)(this + 0x50);
    puVar8[0x13] = uVar3;
    uVar3 = *(undefined4 *)(this + 0x48);
    puVar8[0x7eac] = *(undefined4 *)(this + 0x321070);
    puVar8[0x7ead] = *(undefined4 *)(this + 0x321074);
    puVar8[0x14] = uVar3;
    iVar7 = *(int *)(this + 0xfdb0);
    puVar8[9] = iVar7;
    puVar8[0xb] = *(undefined4 *)(this + 0x60);
    iVar4 = *(int *)(this + 0x60);
    if ((((iVar4 != 1) || (iVar7 != 0)) && (this[0x30fcc0] == (cRSubGame)0x0)) && (param_1)) {
      if (iVar4 == 1) {
        cRSubHighScore::AddSurvival((cRSubHighScore *)(this + 0x2cf49c));
        return;
      }
      if (iVar4 == 4) {
        cRSubHighScore::AddTimeTrial
                  ((cRSubHighScore *)(this + 0x2cf49c),*(int *)(this + 100),(bool)this[0xfefc]);
        return;
      }
      if (iVar4 == 0) {
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
