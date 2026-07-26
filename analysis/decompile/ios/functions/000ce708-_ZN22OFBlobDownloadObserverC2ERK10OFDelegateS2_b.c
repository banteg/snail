/*
 * mangled: _ZN22OFBlobDownloadObserverC2ERK10OFDelegateS2_b
 * demangled: OFBlobDownloadObserver::OFBlobDownloadObserver(OFDelegate const&, OFDelegate const&, bool)
 * address: 000ce708
 * size: 204
 */

/* OFBlobDownloadObserver::OFBlobDownloadObserver(OFDelegate const&, OFDelegate const&, bool) */

void __thiscall
OFBlobDownloadObserver::OFBlobDownloadObserver
          (OFBlobDownloadObserver *this,OFDelegate *param_1,OFDelegate *param_2,bool param_3)

{
  undefined1 auStack_ac [4];
  uint local_a8;
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

  local_a8 = (uint)param_3;
  local_74 = &stack0xfffffff8;
  local_6c = auStack_ac;
  local_7c = PTR_001b615c;
  local_78 = &::GCC_except_table0;
  local_70 = &LAB_000ce7d4;
  local_a4 = param_2;
  local_a0 = param_1;
  local_9c = (OFSmartObject *)this;
  __Unwind_SjLj_Register(auStack_94);
  local_90 = 0xffffffff;
  OFSmartObject::OFSmartObject(local_9c);
  *(undefined ***)local_9c = &PTR_GetRTTI_001b74d8;
  local_98 = local_9c + 8;
  local_90 = 2;
  OFDelegate::OFDelegate((OFDelegate *)(local_9c + 8),local_a0);
  local_90 = 1;
  OFDelegate::OFDelegate((OFDelegate *)(local_9c + 0x18),local_a4);
  local_9c[0x28] = SUB41(local_a8,0);
  __Unwind_SjLj_Unregister(auStack_94);
  return;
}
