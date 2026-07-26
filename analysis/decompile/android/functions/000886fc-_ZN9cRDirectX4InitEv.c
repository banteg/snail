/*
 * mangled: _ZN9cRDirectX4InitEv
 * demangled: cRDirectX::Init()
 * address: 000886fc
 * size: 64
 */

/* cRDirectX::Init() */

void __thiscall cRDirectX::Init(cRDirectX *this)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;

  iVar1 = DAT_00088740;
  iVar3 = DAT_0008873c + 0x88718;
  *(undefined4 *)(this + 4) = 0;
  uVar2 = RShellLoadFile((char *)(iVar3 + iVar1),(int *)0x0);
  *(undefined4 *)this = uVar2;
  cRDuplicateVertices::Init((cRDuplicateVertices *)(this + 0x5808),2000);
  return;
}
