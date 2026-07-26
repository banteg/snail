/*
 * mangled: _ZN15cRSpriteManager7SetLastEP8cRSprite
 * demangled: cRSpriteManager::SetLast(cRSprite*)
 * address: 0003ccc4
 * size: 112
 */

/* cRSpriteManager::SetLast(cRSprite*) */

void __thiscall cRSpriteManager::SetLast(cRSpriteManager *this,cRSprite *param_1)

{
  cRSprite *pcVar1;
  int iVar2;
  cRSprite *pcVar3;
  int iVar4;

  pcVar1 = *(cRSprite **)(this + (*(int *)(param_1 + 8) + 44000) * 4 + 4);
  do {
    pcVar3 = pcVar1;
    pcVar1 = *(cRSprite **)(pcVar3 + 0xc);
  } while (*(cRSprite **)(pcVar3 + 0xc) != (cRSprite *)0x0);
  if (param_1 == *(cRSprite **)(this + (*(int *)(param_1 + 8) + 44000) * 4 + 4)) {
    *(undefined4 *)(this + (*(int *)(param_1 + 8) + 44000) * 4 + 4) = *(undefined4 *)(param_1 + 0xc)
    ;
  }
  iVar4 = *(int *)(param_1 + 0x10);
  if (iVar4 != 0) {
    *(undefined4 *)(iVar4 + 0xc) = *(undefined4 *)(param_1 + 0xc);
  }
  iVar2 = *(int *)(param_1 + 0xc);
  *(cRSprite **)(pcVar3 + 0xc) = param_1;
  if (iVar2 != 0) {
    *(int *)(iVar2 + 0x10) = iVar4;
  }
  *(cRSprite **)(param_1 + 0x10) = pcVar3;
  *(undefined4 *)(param_1 + 0xc) = 0;
  return;
}
