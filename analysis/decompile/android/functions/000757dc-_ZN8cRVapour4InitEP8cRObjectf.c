/*
 * mangled: _ZN8cRVapour4InitEP8cRObjectf
 * demangled: cRVapour::Init(cRObject*, float)
 * address: 000757dc
 * size: 72
 */

/* cRVapour::Init(cRObject*, float) */

void __thiscall cRVapour::Init(cRVapour *this,cRObject *param_1,float param_2)

{
  int iVar1;
  undefined4 uVar2;
  char *pcVar3;
  undefined4 in_r2;

  iVar1 = *(int *)(*(int *)(this + 0x24) + 0xc0);
  pcVar3 = (char *)(DAT_00075824 + 0x757fc + DAT_00075828);
  *(undefined4 *)(this + 0x7c) = in_r2;
  iVar1 = iVar1 + 1;
  *(int *)(this + 0x78) = iVar1;
  uVar2 = RShellMemoryMalloc(iVar1 * 0x40,pcVar3);
  *(undefined4 *)(this + 0x84) = uVar2;
  ReSet(this,(float *)0x0);
  return;
}
