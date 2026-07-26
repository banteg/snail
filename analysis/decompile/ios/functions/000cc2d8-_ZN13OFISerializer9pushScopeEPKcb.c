/*
 * mangled: _ZN13OFISerializer9pushScopeEPKcb
 * demangled: OFISerializer::pushScope(char const*, bool)
 * address: 000cc2d8
 * size: 372
 */

/* OFISerializer::pushScope(char const*, bool) */

void __thiscall OFISerializer::pushScope(OFISerializer *this,char *param_1,bool param_2)

{
  undefined4 *puVar1;
  OFSmartObject *pOVar2;
  undefined1 auStack_b4 [4];
  uint local_b0;
  OFSmartObject *local_ac;
  OFISerializer *local_a8;
  OFSmartObject *local_a4;
  undefined1 auStack_a0 [4];
  undefined4 local_9c;
  undefined *local_88;
  undefined *local_84;
  undefined1 *local_80;
  undefined1 *local_7c;
  undefined1 *local_78;
  OFSmartObject *local_6c;
  undefined1 local_68;
  OFSmartObject *local_64 [17];

  local_b0 = (uint)param_2;
  local_80 = &stack0xfffffff8;
  local_78 = auStack_b4;
  local_88 = PTR_001b615c;
  local_84 = &GCC_except_table16;
  local_7c = &LAB_000cc44c;
  local_ac = (OFSmartObject *)param_1;
  local_a8 = this;
  __Unwind_SjLj_Register(auStack_a0);
  local_9c = 0xffffffff;
  pOVar2 = local_ac;
  (**(code **)(*(int *)local_a8 + 0x14))(local_64,local_a8);
  if (local_64[0] != (OFSmartObject *)0x0) {
    pOVar2 = local_64[0];
  }
  local_a4 = local_64[0];
  local_6c = local_64[0];
  if (local_64[0] != (OFSmartObject *)0x0) {
    *(int *)(pOVar2 + 4) = *(int *)(pOVar2 + 4) + 1;
  }
  local_68 = (undefined1)local_b0;
  puVar1 = *(undefined4 **)(local_a8 + 0xc);
  if (puVar1 == *(undefined4 **)(local_a8 + 0x10)) {
    local_9c = 1;
    std::vector<OFISerializer::ScopeDescriptor,std::allocator<OFISerializer::ScopeDescriptor>>::
    _M_insert_aux((vector<OFISerializer::ScopeDescriptor,std::allocator<OFISerializer::ScopeDescriptor>>
                   *)(local_a8 + 8),puVar1,&local_6c);
  }
  else {
    if (puVar1 != (undefined4 *)0x0) {
      *puVar1 = local_64[0];
      if (local_64[0] != (OFSmartObject *)0x0) {
        *(int *)(local_64[0] + 4) = *(int *)(local_64[0] + 4) + 1;
      }
      *(undefined1 *)(puVar1 + 1) = local_68;
    }
    *(int *)(local_a8 + 0xc) = *(int *)(local_a8 + 0xc) + 8;
  }
  if (local_6c != (OFSmartObject *)0x0) {
    local_9c = 2;
    OFSmartObject::Release(local_6c);
  }
  local_9c = 2;
  (**(code **)(*(int *)local_a8 + 0x40))(local_a8,local_a4);
  if (local_a4 != (OFSmartObject *)0x0) {
    local_9c = 0xffffffff;
    OFSmartObject::Release(local_a4);
  }
  __Unwind_SjLj_Unregister(auStack_a0);
  return;
}
