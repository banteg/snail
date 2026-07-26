/*
 * mangled: _ZN8cRVapour4InitEP8cRObjectf
 * demangled: cRVapour::Init(cRObject*, float)
 * address: 0001c0d4
 * size: 76
 */

/* cRVapour::Init(cRObject*, float) */

void __thiscall cRVapour::Init(cRVapour *this,cRObject *param_1,float param_2)

{
  int iVar1;
  undefined4 uVar2;

  *(float *)(this + 0x7c) = param_2;
  iVar1 = *(int *)(*(int *)(this + 0x24) + 0xc0) + 1;
  *(int *)(this + 0x78) = iVar1;
  uVar2 = RShellMemoryMalloc(iVar1 * 0x40,"Vapour Trail");
  *(undefined4 *)(this + 0x80) = 0;
  *(uint *)(this + 4) = *(uint *)(this + 4) & 0xffffffdf;
  *(undefined4 *)(this + 0x74) = 0;
  *(undefined4 *)(this + 0x84) = uVar2;
  return;
}
