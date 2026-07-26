/*
 * mangled: _ZN19cRDuplicateVertices4InitEi
 * demangled: cRDuplicateVertices::Init(int)
 * address: 000169a4
 * size: 48
 */

/* cRDuplicateVertices::Init(int) */

void __thiscall cRDuplicateVertices::Init(cRDuplicateVertices *this,int param_1)

{
  undefined4 uVar1;

  *(undefined4 *)this = 0;
  uVar1 = RShellMemoryMalloc(param_1 * 10,"Duplicate vertices");
  *(undefined4 *)(this + 4) = uVar1;
  return;
}
