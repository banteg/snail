/*
 * mangled: _ZN30OFImageViewHttpServiceObserverC2ERK10OFDelegateS2_
 * demangled: OFImageViewHttpServiceObserver::OFImageViewHttpServiceObserver(OFDelegate const&, OFDelegate const&)
 * address: 000eced0
 * size: 184
 */

/* OFImageViewHttpServiceObserver::OFImageViewHttpServiceObserver(OFDelegate const&, OFDelegate
   const&) */

void __thiscall
OFImageViewHttpServiceObserver::OFImageViewHttpServiceObserver
          (OFImageViewHttpServiceObserver *this,OFDelegate *param_1,OFDelegate *param_2)

{
  undefined1 auStack_a8 [4];
  OFDelegate *local_a4;
  OFDelegate *local_a0;
  OFSmartObject *local_9c;
  OFSmartObject *local_98;
  undefined1 auStack_94 [4];
  undefined4 local_90;
  undefined *local_7c;
  undefined *local_78;
  undefined1 *local_74;
  undefined1 *local_70;
  undefined1 *local_6c;

  local_74 = &stack0xfffffff8;
  local_6c = auStack_a8;
  local_7c = PTR_001b615c;
  local_78 = &::GCC_except_table0;
  local_70 = &LAB_000ecf88;
  local_a4 = param_2;
  local_a0 = param_1;
  local_9c = (OFSmartObject *)this;
  __Unwind_SjLj_Register(auStack_94);
  local_90 = 0xffffffff;
  OFSmartObject::OFSmartObject(local_9c);
  *(undefined ***)local_9c = &PTR_GetRTTI_001b7644;
  local_98 = local_9c + 8;
  local_90 = 2;
  OFDelegate::OFDelegate((OFDelegate *)(local_9c + 8),local_a0);
  local_90 = 1;
  OFDelegate::OFDelegate((OFDelegate *)(local_9c + 0x18),local_a4);
  __Unwind_SjLj_Unregister(auStack_94);
  return;
}
