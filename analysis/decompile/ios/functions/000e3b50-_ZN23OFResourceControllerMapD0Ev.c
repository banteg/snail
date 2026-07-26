/*
 * mangled: _ZN23OFResourceControllerMapD0Ev
 * demangled: OFResourceControllerMap::~OFResourceControllerMap()
 * address: 000e3b50
 * size: 256
 */

/* OFResourceControllerMap::~OFResourceControllerMap() */

void __thiscall OFResourceControllerMap::~OFResourceControllerMap(OFResourceControllerMap *this)

{
  ResourceDescription *pRVar1;
  OFResourceControllerMap *local_ac;
  vector<OFResourceControllerMap::ResourceDescription,std::allocator<OFResourceControllerMap::ResourceDescription>_>
  *local_a8;
  ResourceDescription *local_a0;
  SEL local_9c;
  ResourceDescription *local_98;
  undefined1 auStack_94 [4];
  undefined4 local_90;
  undefined *local_7c;
  undefined *local_78;
  undefined1 *local_74;
  undefined1 *local_70;
  undefined1 *local_6c;

  local_74 = &stack0xfffffff8;
  local_6c = (undefined1 *)&local_ac;
  local_7c = PTR_001b615c;
  local_78 = &::GCC_except_table2;
  local_70 = &LAB_000e3c50;
  local_ac = this;
  __Unwind_SjLj_Register(auStack_94);
  local_ac->field0_0x0 = (undefined4 **)&PTR_GetRTTI_001b7624;
  local_a8 = &local_ac->field2_0x8;
  pRVar1 = (local_ac->field2_0x8).field0_0x0.field0_0x0;
  local_a0 = (local_ac->field2_0x8).field0_0x0.field1_0x4;
  if (pRVar1 != local_a0) {
    local_9c = "release";
    local_98 = pRVar1;
    do {
      if (*(ID *)(local_98 + 4) != 0) {
        local_90 = 1;
        _objc_msgSend(*(ID *)(local_98 + 4),local_9c);
      }
      local_98 = local_98 + 8;
    } while (local_a0 != local_98);
  }
  pRVar1 = (local_a8->field0_0x0).field0_0x0;
  if (pRVar1 != (ResourceDescription *)0x0) {
    operator_delete(pRVar1);
  }
  local_90 = 0xffffffff;
  OFSmartObject::~OFSmartObject((OFSmartObject *)local_ac);
  operator_delete(local_ac);
  __Unwind_SjLj_Unregister(auStack_94);
  return;
}
