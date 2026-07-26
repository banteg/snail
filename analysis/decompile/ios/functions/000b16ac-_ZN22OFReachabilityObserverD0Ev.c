/*
 * mangled: _ZN22OFReachabilityObserverD0Ev
 * demangled: OFReachabilityObserver::~OFReachabilityObserver()
 * address: 000b16ac
 * size: 200
 */

/* OFReachabilityObserver::~OFReachabilityObserver() */

void __thiscall OFReachabilityObserver::~OFReachabilityObserver(OFReachabilityObserver *this)

{
  OFReachability *this_00;
  undefined1 auStack_9c [4];
  OFReachabilityObserver *local_98;
  undefined1 auStack_94 [4];
  undefined4 local_90;
  undefined *local_7c;
  undefined *local_78;
  undefined1 *local_74;
  undefined1 *local_70;
  undefined1 *local_6c;

  local_74 = &stack0xfffffff8;
  local_6c = auStack_9c;
  local_7c = PTR_001b615c;
  local_78 = &::GCC_except_table0;
  local_70 = &LAB_000b1774;
  local_98 = this;
  __Unwind_SjLj_Register(auStack_94);
  *(undefined ***)local_98 = &PTR__OFReachabilityObserver_001b6fd0;
  *(undefined **)(local_98 + 4) = &DAT_001b6fe4;
  local_90 = 1;
  this_00 = (OFReachability *)OFReachability::Instance();
  OFReachability::removeObserver(this_00,(OFIReachabilityObserver *)local_98);
  local_90 = 2;
  OFDelegate::~OFDelegate((OFDelegate *)(local_98 + 0xc));
  local_90 = 3;
  OFSmartObject::~OFSmartObject((OFSmartObject *)(local_98 + 4));
  local_90 = 0xffffffff;
  OFIReachabilityObserver::~OFIReachabilityObserver((OFIReachabilityObserver *)local_98);
  operator_delete(local_98);
  __Unwind_SjLj_Unregister(auStack_94);
  return;
}
