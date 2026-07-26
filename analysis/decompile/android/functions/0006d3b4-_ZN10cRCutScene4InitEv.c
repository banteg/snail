/*
 * mangled: _ZN10cRCutScene4InitEv
 * demangled: cRCutScene::Init()
 * address: 0006d3b4
 * size: 56
 */

/* cRCutScene::Init() */

void __thiscall cRCutScene::Init(cRCutScene *this)

{
  int iVar1;

  iVar1 = DAT_0006d3ec;
  *(undefined4 *)(this + 0xc) = 0;
  iVar1 = **(int **)(iVar1 + 0x6d3d0 + DAT_0006d3f0);
  *(int *)this = iVar1 + 0x83b64;
  *(int *)(this + 4) = iVar1 + 0x81364;
  return;
}
