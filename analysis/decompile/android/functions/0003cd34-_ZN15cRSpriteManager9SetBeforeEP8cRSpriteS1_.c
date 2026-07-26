/*
 * mangled: _ZN15cRSpriteManager9SetBeforeEP8cRSpriteS1_
 * demangled: cRSpriteManager::SetBefore(cRSprite*, cRSprite*)
 * address: 0003cd34
 * size: 112
 */

/* cRSpriteManager::SetBefore(cRSprite*, cRSprite*) */

void __thiscall
cRSpriteManager::SetBefore(cRSpriteManager *this,cRSprite *param_1,cRSprite *param_2)

{
  int iVar1;
  cRSprite *pcVar2;
  cRSprite *pcVar3;

  pcVar2 = *(cRSprite **)(param_1 + 0xc);
  if (pcVar2 != param_2) {
    pcVar3 = *(cRSprite **)(this + (*(int *)(param_1 + 8) + 44000) * 4 + 4);
    if (pcVar3 != param_1) {
      if (param_2 == pcVar3) {
        *(cRSprite **)(this + (*(int *)(param_1 + 8) + 44000) * 4 + 4) = param_1;
      }
      iVar1 = *(int *)(param_1 + 0x10);
      if (param_2 == pcVar3) {
        pcVar2 = *(cRSprite **)(param_1 + 0xc);
      }
      if (iVar1 != 0) {
        *(cRSprite **)(iVar1 + 0xc) = pcVar2;
        pcVar2 = *(cRSprite **)(param_1 + 0xc);
      }
      if (pcVar2 != (cRSprite *)0x0) {
        *(int *)(pcVar2 + 0x10) = iVar1;
      }
      iVar1 = *(int *)(param_2 + 0x10);
      *(int *)(param_1 + 0x10) = iVar1;
      if (iVar1 != 0) {
        *(cRSprite **)(iVar1 + 0xc) = param_1;
      }
      *(cRSprite **)(param_2 + 0x10) = param_1;
      *(cRSprite **)(param_1 + 0xc) = param_2;
    }
  }
  return;
}
