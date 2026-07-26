/*
 * mangled: _ZN30OFImageViewHttpServiceObserverD1Ev
 * demangled: OFImageViewHttpServiceObserver::~OFImageViewHttpServiceObserver()
 * address: 000ed7a8
 * size: 172
 */

/* OFImageViewHttpServiceObserver::~OFImageViewHttpServiceObserver() */

void __thiscall
OFImageViewHttpServiceObserver::~OFImageViewHttpServiceObserver
          (OFImageViewHttpServiceObserver *this)

{
  undefined1 auStack_9c [4];
  OFImageViewHttpServiceObserver *local_98;
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
  local_78 = &::GCC_except_table3;
  local_70 = &LAB_000ed854;
  local_98 = this;
  __Unwind_SjLj_Register(auStack_94);
  *(undefined ***)local_98 = &PTR_GetRTTI_001b7644;
  local_90 = 1;
  OFDelegate::~OFDelegate((OFDelegate *)(local_98 + 0x18));
  local_90 = 2;
  OFDelegate::~OFDelegate((OFDelegate *)(local_98 + 8));
  *(undefined ***)local_98 = &PTR_GetRTTI_001b750c;
  local_90 = 0xffffffff;
  OFSmartObject::~OFSmartObject((OFSmartObject *)local_98);
  __Unwind_SjLj_Unregister(auStack_94);
  return;
}
