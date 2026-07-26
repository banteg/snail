/*
 * mangled: _ZN29OFHttpServiceRequestContainerD0Ev
 * demangled: OFHttpServiceRequestContainer::~OFHttpServiceRequestContainer()
 * address: 000d1384
 * size: 372
 */

/* OFHttpServiceRequestContainer::~OFHttpServiceRequestContainer() */

void __thiscall
OFHttpServiceRequestContainer::~OFHttpServiceRequestContainer(OFHttpServiceRequestContainer *this)

{
  undefined1 auStack_9c [4];
  OFHttpServiceRequestContainer *local_98;
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
  local_70 = &LAB_000d14f8;
  local_98 = this;
  __Unwind_SjLj_Register(auStack_94);
  *(undefined ***)local_98 = &PTR_GetRTTI_001b7590;
  if (*(OFSmartObject **)(local_98 + 0x20) != (OFSmartObject *)0x0) {
    local_90 = 1;
    OFSmartObject::Release(*(OFSmartObject **)(local_98 + 0x20));
  }
  if (*(ID *)(local_98 + 0x1c) != 0) {
    local_90 = 2;
    _objc_msgSend(*(ID *)(local_98 + 0x1c),"release");
  }
  if (*(ID *)(local_98 + 0x18) != 0) {
    local_90 = 3;
    _objc_msgSend(*(ID *)(local_98 + 0x18),"release");
  }
  if (*(ID *)(local_98 + 0x14) != 0) {
    local_90 = 4;
    _objc_msgSend(*(ID *)(local_98 + 0x14),"release");
  }
  if (*(ID *)(local_98 + 0x10) != 0) {
    local_90 = 5;
    _objc_msgSend(*(ID *)(local_98 + 0x10),"release");
  }
  if (*(ID *)(local_98 + 0xc) != 0) {
    local_90 = 6;
    _objc_msgSend(*(ID *)(local_98 + 0xc),"release");
  }
  if (*(ID *)(local_98 + 8) != 0) {
    local_90 = 7;
    _objc_msgSend(*(ID *)(local_98 + 8),"release");
  }
  local_90 = 0xffffffff;
  OFSmartObject::~OFSmartObject((OFSmartObject *)local_98);
  operator_delete(local_98);
  __Unwind_SjLj_Unregister(auStack_94);
  return;
}
