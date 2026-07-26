/*
 * mangled: _Z21ParsifalInputCallbackPhiPiPv
 * demangled: ParsifalInputCallback(unsigned char*, int, int*, void*)
 * address: 000d51b0
 * size: 132
 */

/* ParsifalInputCallback(unsigned char*, int, int*, void*) */

bool ParsifalInputCallback(uchar *param_1,int param_2,int *param_3,void *param_4)

{
  ID IVar1;
  ID IVar2;
  uint uVar3;

  IVar1 = _objc_msgSend(*(ID *)param_4,"bytes");
  IVar2 = _objc_msgSend(*(ID *)param_4,"length");
  uVar3 = IVar2 - *(int *)((int)param_4 + 4);
  if ((uint)param_2 <= uVar3) {
    uVar3 = param_2;
  }
  _memcpy(param_1,(void *)(*(int *)((int)param_4 + 4) + IVar1),uVar3);
  *(uint *)((int)param_4 + 4) = *(int *)((int)param_4 + 4) + uVar3;
  *param_3 = uVar3;
  return uVar3 < (uint)param_2;
}
