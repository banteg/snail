/*
 * mangled: _ZN29OFHttpServiceRequestContainerC2ERKS_
 * demangled: OFHttpServiceRequestContainer::OFHttpServiceRequestContainer(OFHttpServiceRequestContainer const&)
 * address: 000d10d4
 * size: 396
 */

/* OFHttpServiceRequestContainer::OFHttpServiceRequestContainer(OFHttpServiceRequestContainer
   const&) */

void __thiscall
OFHttpServiceRequestContainer::OFHttpServiceRequestContainer
          (OFHttpServiceRequestContainer *this,OFHttpServiceRequestContainer *param_1)

{
  ID IVar1;
  int iVar2;
  undefined1 auStack_a0 [4];
  OFHttpServiceRequestContainer *local_9c;
  OFHttpServiceRequestContainer *local_98;
  undefined1 auStack_94 [4];
  undefined4 local_90;
  undefined *local_7c;
  undefined *local_78;
  undefined1 *local_74;
  undefined1 *local_70;
  undefined1 *local_6c;

  local_74 = &stack0xfffffff8;
  local_6c = auStack_a0;
  local_7c = PTR_001b615c;
  local_78 = &::GCC_except_table2;
  local_70 = &LAB_000d1260;
  local_9c = param_1;
  local_98 = this;
  __Unwind_SjLj_Register(auStack_94);
  *(undefined4 *)(local_98 + 4) = *(undefined4 *)(local_9c + 4);
  *(undefined ***)local_98 = &PTR_GetRTTI_001b7590;
  IVar1 = *(ID *)(local_9c + 8);
  *(ID *)(local_98 + 8) = IVar1;
  if (IVar1 != 0) {
    local_90 = 6;
    _objc_msgSend(IVar1,"retain");
  }
  IVar1 = *(ID *)(local_9c + 0xc);
  *(ID *)(local_98 + 0xc) = IVar1;
  if (IVar1 != 0) {
    local_90 = 5;
    _objc_msgSend(IVar1,"retain");
  }
  IVar1 = *(ID *)(local_9c + 0x10);
  *(ID *)(local_98 + 0x10) = IVar1;
  if (IVar1 != 0) {
    local_90 = 4;
    _objc_msgSend(IVar1,"retain");
  }
  IVar1 = *(ID *)(local_9c + 0x14);
  *(ID *)(local_98 + 0x14) = IVar1;
  if (IVar1 != 0) {
    local_90 = 3;
    _objc_msgSend(IVar1,"retain");
  }
  IVar1 = *(ID *)(local_9c + 0x18);
  *(ID *)(local_98 + 0x18) = IVar1;
  if (IVar1 != 0) {
    local_90 = 2;
    _objc_msgSend(IVar1,"retain");
  }
  IVar1 = *(ID *)(local_9c + 0x1c);
  *(ID *)(local_98 + 0x1c) = IVar1;
  if (IVar1 != 0) {
    local_90 = 1;
    _objc_msgSend(IVar1,"retain");
  }
  iVar2 = *(int *)(local_9c + 0x20);
  *(int *)(local_98 + 0x20) = iVar2;
  if (iVar2 != 0) {
    *(int *)(iVar2 + 4) = *(int *)(iVar2 + 4) + 1;
  }
  __Unwind_SjLj_Unregister(auStack_94);
  return;
}
