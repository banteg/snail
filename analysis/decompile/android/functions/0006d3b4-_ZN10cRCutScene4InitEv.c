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

  *(undefined4 *)(this + 0xc) = 0;
  iVar1 = Game + 0x81364;
  *(int *)this = Game + 0x83b64;
  *(int *)(this + 4) = iVar1;
  return;
}
