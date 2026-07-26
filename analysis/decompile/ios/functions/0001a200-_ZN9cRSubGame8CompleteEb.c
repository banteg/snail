/*
 * mangled: _ZN9cRSubGame8CompleteEb
 * demangled: cRSubGame::Complete(bool)
 * address: 0001a200
 * size: 524
 */

/* cRSubGame::Complete(bool) */

void __thiscall cRSubGame::Complete(cRSubGame *this,bool param_1)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;

  cRSubGoldy::ScoreStatsDisplay((cRSubGoldy *)(this + 0xf448));
  iVar2 = *(int *)(this + 0x2e09d8) * 6 + *(int *)(this + 0x2e09c8);
  *(ushort *)(iVar2 + 0x74) = *(ushort *)(iVar2 + 0x74) | 8;
  *(int *)(*(int *)(this + 0x2e09c8) + 0x6c) = *(int *)(*(int *)(this + 0x2e09c8) + 0x6c) + 1;
  *(int *)(this + 0x2e09d8) = *(int *)(this + 0x2e09d8) + 1;
  if ((*(uint *)PTR__gCheat_001b61dc & 1) != 0) {
    return;
  }
  **(undefined4 **)(this + 0x2e09c8) = 1;
  *(undefined4 *)(*(int *)(this + 0x2e09c8) + 4) = *(undefined4 *)(this + 0xf714);
  iVar2 = *(int *)(this + 0x2e09c8);
  uVar1 = *(undefined4 *)(this + 0xf71c);
  uVar3 = *(undefined4 *)(this + 0xf720);
  uVar4 = *(undefined4 *)(this + 0xf724);
  *(undefined4 *)(iVar2 + 8) = *(undefined4 *)(this + 0xf718);
  *(undefined4 *)(iVar2 + 0xc) = uVar1;
  *(undefined4 *)(iVar2 + 0x10) = uVar3;
  *(undefined4 *)(iVar2 + 0x14) = uVar4;
  uVar1 = *(undefined4 *)(this + 0xf72c);
  *(undefined4 *)(iVar2 + 0x18) = *(undefined4 *)(this + 0xf728);
  *(undefined4 *)(iVar2 + 0x1c) = uVar1;
  *(undefined4 *)(*(int *)(this + 0x2e09c8) + 0x20) = *(undefined4 *)(this + 0xf730);
  *(undefined4 *)(*(int *)(this + 0x2e09c8) + 0x4c) = *(undefined4 *)(this + 0x3c);
  *(undefined4 *)(*(int *)(this + 0x2e09c8) + 0x50) = *(undefined4 *)(this + 0x40);
  *(undefined4 *)(*(int *)(this + 0x2e09c8) + 0x24) = *(undefined4 *)(this + 0xf734);
  *(undefined4 *)(*(int *)(this + 0x2e09c8) + 0x48) = *(undefined4 *)(this + 0x44);
  *(undefined4 *)(*(int *)(this + 0x2e09c8) + 0x2c) = *(undefined4 *)(this + 0x58);
  *(undefined4 *)(*(int *)(this + 0x2e09c8) + 0x34) = *(undefined4 *)(this + 0x48);
  *(undefined4 *)(*(int *)(this + 0x2e09c8) + 0x1fab0) = *(undefined4 *)(this + 0x2f1d7c);
  *(undefined4 *)(*(int *)(this + 0x2e09c8) + 0x1fab4) = *(undefined4 *)(this + 0x2f1d80);
  iVar2 = *(int *)(this + 0x58);
  if (iVar2 == 1) {
    if (*(int *)(*(int *)(this + 0x2e09c8) + 0x24) == 0) {
      return;
    }
    if (this[0x2e09cc] != (cRSubGame)0x0) {
      return;
    }
  }
  else if (this[0x2e09cc] != (cRSubGame)0x0) {
    return;
  }
  if (!param_1) {
    return;
  }
  if (iVar2 == 1) {
    cRSubHighScore::AddSurvival((cRSubHighScore *)(this + 0x2a01a8));
    return;
  }
  if (iVar2 == 4) {
    cRSubHighScore::AddTimeTrial
              ((cRSubHighScore *)(this + 0x2a01a8),*(int *)(this + 0x5c),(bool)this[0xf878]);
    return;
  }
  if (iVar2 != 0) {
    return;
  }
  if (*(int *)(this + 0x2f1dcc) == 0) {
    cRSubHighScore::AddArcade((cRSubHighScore *)(this + 0x2a01a8),*(int *)(this + 0x5c));
    return;
  }
  if (*(int *)(this + 0x2f1dcc) != 1) {
    return;
  }
  cRSubHighScore::AddArcadePro((cRSubHighScore *)(this + 0x2a01a8),*(int *)(this + 0x5c));
  return;
}
