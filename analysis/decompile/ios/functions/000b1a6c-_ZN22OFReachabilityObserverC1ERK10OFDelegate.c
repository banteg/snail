/*
 * mangled: _ZN22OFReachabilityObserverC1ERK10OFDelegate
 * demangled: OFReachabilityObserver::OFReachabilityObserver(OFDelegate const&)
 * address: 000b1a6c
 * size: 4
 */

/* OFReachabilityObserver::OFReachabilityObserver(OFDelegate const&) */

void __thiscall
OFReachabilityObserver::OFReachabilityObserver(OFReachabilityObserver *this,OFDelegate *param_1)

{
  OFReachability *this_00;
  undefined1 auStack_a4 [4];
  OFDelegate *pOStack_a0;
  OFIReachabilityObserver *pOStack_9c;
  OFIReachabilityObserver *pOStack_98;
  undefined1 auStack_94 [4];
  undefined4 uStack_90;
  undefined *puStack_7c;
  undefined *puStack_78;
  undefined1 *puStack_74;
  undefined1 *puStack_70;
  undefined1 *puStack_6c;

  puStack_74 = &stack0xfffffff8;
  puStack_6c = auStack_a4;
  puStack_7c = PTR_001b615c;
  puStack_78 = &::GCC_except_table2;
  puStack_70 = &LAB_000b19fc;
  pOStack_a0 = param_1;
  pOStack_9c = (OFIReachabilityObserver *)this;
  __Unwind_SjLj_Register(auStack_94);
  uStack_90 = 0xffffffff;
  OFIReachabilityObserver::OFIReachabilityObserver(pOStack_9c);
  uStack_90 = 3;
  OFSmartObject::OFSmartObject((OFSmartObject *)(pOStack_9c + 4));
  *(undefined ***)pOStack_9c = &PTR__OFReachabilityObserver_001b6fd0;
  *(undefined **)(pOStack_9c + 4) = &DAT_001b6fe4;
  pOStack_98 = pOStack_9c + 0xc;
  uStack_90 = 2;
  OFDelegate::OFDelegate((OFDelegate *)(pOStack_9c + 0xc),pOStack_a0);
  uStack_90 = 1;
  this_00 = (OFReachability *)OFReachability::Instance();
  OFReachability::addObserver(this_00,pOStack_9c);
  __Unwind_SjLj_Unregister(auStack_94);
  return;
}
