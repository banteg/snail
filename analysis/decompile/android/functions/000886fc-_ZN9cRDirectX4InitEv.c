/*
 * mangled: _ZN9cRDirectX4InitEv
 * demangled: cRDirectX::Init()
 * address: 000886fc
 * size: 64
 */

/* cRDirectX::Init() */

void __thiscall cRDirectX::Init(cRDirectX *this)

{
  undefined4 uVar1;

  *(undefined4 *)(this + 4) = 0;
  uVar1 = RShellLoadFile("X/_Animation.txt",(int *)0x0);
  *(undefined4 *)this = uVar1;
  cRDuplicateVertices::Init((cRDuplicateVertices *)(this + 0x5808),2000);
  return;
}
