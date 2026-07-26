/*
 * mangled: _Z18ObjectProcSetAlphaP8cRObjectf
 * demangled: ObjectProcSetAlpha(cRObject*, float)
 * address: 000339f0
 * size: 44
 */

/* ObjectProcSetAlpha(cRObject*, float) */

void ObjectProcSetAlpha(cRObject *param_1,float param_2)

{
  undefined4 in_r1;
  int iVar1;
  int iVar2;
  int iVar3;

  iVar3 = *(int *)(param_1 + 0xa0);
  if (iVar3 < 1) {
    return;
  }
  iVar1 = *(int *)(param_1 + 0xb4);
  iVar2 = 0;
  do {
    iVar2 = iVar2 + 1;
    *(undefined4 *)(iVar1 + 0xc) = in_r1;
    iVar1 = iVar1 + 0x10;
  } while (iVar2 != iVar3);
  return;
}
