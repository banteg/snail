/*
 * mangled: _ZN22OFReachabilityObserverC2ERK10OFDelegate
 * demangled: OFReachabilityObserver::OFReachabilityObserver(OFDelegate const&)
 * address: 000b1930
 * size: 204
 */

/* OFReachabilityObserver::OFReachabilityObserver(OFDelegate const&) */

void __thiscall
OFReachabilityObserver::OFReachabilityObserver(OFReachabilityObserver *this,OFDelegate *param_1)

{
  OFReachability *this_00;
  undefined1 auStack_a4 [4];
  OFDelegate *local_a0;
  OFIReachabilityObserver *local_9c;
  OFIReachabilityObserver *local_98;
  undefined1 auStack_94 [4];
  undefined4 local_90;
  undefined *local_7c;
  undefined *local_78;
  undefined1 *local_74;
  undefined1 *local_70;
  undefined1 *local_6c;

  local_74 = &stack0xfffffff8;
  local_6c = auStack_a4;
  local_7c = PTR_001b615c;
  local_78 = &::GCC_except_table2;
  local_70 = &LAB_000b19fc;
  local_a0 = param_1;
  local_9c = (OFIReachabilityObserver *)this;
  __Unwind_SjLj_Register(auStack_94);
  local_90 = 0xffffffff;
  OFIReachabilityObserver::OFIReachabilityObserver(local_9c);
  local_90 = 3;
  OFSmartObject::OFSmartObject((OFSmartObject *)(local_9c + 4));
  *(undefined ***)local_9c = &PTR__OFReachabilityObserver_001b6fd0;
  *(undefined **)(local_9c + 4) = &DAT_001b6fe4;
  local_98 = local_9c + 0xc;
  local_90 = 2;
  OFDelegate::OFDelegate((OFDelegate *)(local_9c + 0xc),local_a0);
  local_90 = 1;
  this_00 = (OFReachability *)OFReachability::Instance();
  OFReachability::addObserver(this_00,local_9c);
  __Unwind_SjLj_Unregister(auStack_94);
  return;
}
