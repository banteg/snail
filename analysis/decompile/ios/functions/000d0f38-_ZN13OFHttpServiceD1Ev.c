/*
 * mangled: _ZN13OFHttpServiceD1Ev
 * demangled: OFHttpService::~OFHttpService()
 * address: 000d0f38
 * size: 280
 */

/* OFHttpService::~OFHttpService() */

void __thiscall OFHttpService::~OFHttpService(OFHttpService *this)

{
  OFHttpServiceRequestContainer *pOVar1;
  ID self;
  undefined1 auStack_a8 [4];
  OFHttpService *local_a4;
  vector<OFHttpServiceRequestContainer,std::allocator<OFHttpServiceRequestContainer>_> *local_a0;
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
  local_6c = auStack_a8;
  local_7c = PTR_001b615c;
  local_78 = &::GCC_except_table1;
  local_70 = &LAB_000d1050;
  local_a4 = this;
  __Unwind_SjLj_Register(auStack_94);
  local_a4->field0_0x0 = (undefined4 **)&PTR_GetRTTI_001b7528;
  local_a4->field2_0x8 = (undefined4 **)&PTR__OFHttpService_001b7550;
  local_a0 = &local_a4->field5_0x14;
  local_98 = (local_a4->field5_0x14).field0_0x0.field0_0x0;
  local_9c = (local_a4->field5_0x14).field0_0x0.field1_0x4;
  if (local_98 != local_9c) {
    do {
      local_90 = 1;
      (**(code **)(*(int *)local_98 + 4))(local_98);
      local_98 = local_98 + 0x24;
    } while (local_9c != local_98);
  }
  pOVar1 = (local_a0->field0_0x0).field0_0x0;
  if (pOVar1 != (OFHttpServiceRequestContainer *)0x0) {
    operator_delete(pOVar1);
  }
  self = (local_a4->field3_0xc).field0_0x0;
  if (self != 0) {
    local_90 = 2;
    _objc_msgSend(self,"release");
  }
  local_90 = 0xffffffff;
  OFSmartObject::~OFSmartObject((OFSmartObject *)local_a4);
  __Unwind_SjLj_Unregister(auStack_94);
  return;
}
