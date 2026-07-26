/*
 * mangled: _ZN14OFReachability27networkReachabilityCallBackEPK23__SCNetworkReachabilityjPv
 * demangled: OFReachability::networkReachabilityCallBack(__SCNetworkReachability const*, unsigned int, void*)
 * address: 000d304c
 * size: 132
 */

/* OFReachability::networkReachabilityCallBack(__SCNetworkReachability const*, unsigned int, void*)
    */

OFReachability * __thiscall
OFReachability::networkReachabilityCallBack
          (OFReachability *this,__SCNetworkReachability *param_1,uint param_2,void *param_3)

{
  undefined4 *puVar1;
  uint uVar2;
  undefined4 uVar3;
  int *piVar4;
  undefined4 *puVar5;
  undefined4 uVar6;

  puVar1 = s_UniqueInstance;
  uVar2 = (uint)param_1 & 0x40000;
  if (uVar2 != 0) {
    param_3 = (void *)0x1;
  }
  uVar6 = *s_UniqueInstance;
  if (uVar2 == 0) {
    if (((uint)param_1 & 4) == 0) {
      param_3 = (void *)0x1;
    }
    else {
      param_3 = (void *)0x0;
    }
  }
  uVar3 = 0;
  if (((uint)param_3 & (uint)param_1 >> 1) != 0) {
    if (uVar2 == 0) {
      uVar3 = 2;
    }
    else {
      uVar3 = 1;
    }
  }
  piVar4 = (int *)s_UniqueInstance[2];
  puVar5 = s_UniqueInstance + 2;
  *s_UniqueInstance = uVar3;
  for (; puVar5 != piVar4; piVar4 = (int *)*piVar4) {
    this = (OFReachability *)(**(code **)(*(int *)piVar4[2] + 8))((int *)piVar4[2],uVar6,*puVar1);
  }
  return this;
}
