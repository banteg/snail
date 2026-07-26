/*
 * mangled: _ZN14OFReachabilityD1Ev
 * demangled: OFReachability::~OFReachability()
 * address: 000d2e34
 * size: 236
 */

/* OFReachability::~OFReachability() */

void __thiscall OFReachability::~OFReachability(OFReachability *this)

{
  undefined4 uVar1;
  OFReachability *pOVar2;
  OFReachability *local_b0 [4];
  OFReachability *local_a0;
  OFReachability *local_9c;
  undefined4 local_98;
  undefined1 auStack_94 [4];
  undefined4 local_90;
  undefined *local_7c;
  undefined *local_78;
  undefined1 *local_74;
  undefined1 *local_70;
  undefined1 *local_6c;

  local_74 = &stack0xfffffff8;
  local_6c = (undefined1 *)local_b0;
  local_7c = PTR_001b615c;
  local_78 = &::GCC_except_table0;
  local_70 = &LAB_000d2f20;
  local_b0[0] = this;
  __Unwind_SjLj_Register(auStack_94);
  local_90 = 1;
  _SCNetworkReachabilitySetCallback(*(undefined4 *)(local_b0[0] + 4),0,0);
  local_98 = *(undefined4 *)(local_b0[0] + 4);
  uVar1 = _CFRunLoopGetMain();
  _SCNetworkReachabilityUnscheduleFromRunLoop(local_98,uVar1,*(undefined4 *)PTR_001b6388);
  _CFRelease(*(undefined4 *)(local_b0[0] + 4));
  local_9c = local_b0[0] + 8;
  pOVar2 = *(OFReachability **)(local_b0[0] + 8);
  if (*(OFReachability **)(local_b0[0] + 8) != local_9c) {
    do {
      local_a0 = *(OFReachability **)pOVar2;
      operator_delete(pOVar2);
      pOVar2 = local_a0;
    } while (local_a0 != local_9c);
  }
  __Unwind_SjLj_Unregister(auStack_94);
  return;
}
