/*
 * mangled: _ZN19cRDuplicateVertices4InitEi
 * demangled: cRDuplicateVertices::Init(int)
 * address: 0003c718
 * size: 52
 */

/* cRDuplicateVertices::Init(int) */

void __thiscall cRDuplicateVertices::Init(cRDuplicateVertices *this,int param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;

  iVar1 = DAT_0003c750;
  iVar3 = DAT_0003c74c + 0x3c738;
  *(undefined4 *)this = 0;
  uVar2 = RShellMemoryMalloc(param_1 * 10,(char *)(iVar3 + iVar1));
  *(undefined4 *)(this + 4) = uVar2;
  return;
}
