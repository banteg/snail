/*
 * mangled: _ZN13OFViewDataMap17addFieldReferenceEP8NSStringi
 * demangled: OFViewDataMap::addFieldReference(NSString*, int)
 * address: 000fca38
 * size: 336
 */

/* OFViewDataMap::addFieldReference(NSString*, int) */

void __thiscall OFViewDataMap::addFieldReference(OFViewDataMap *this,NSString *param_1,int param_2)

{
  undefined1 auStack_b4 [4];
  int local_b0;
  NSString *local_ac;
  OFViewDataMap *local_a8;
  undefined4 *local_a4;
  undefined1 auStack_a0 [4];
  undefined4 local_9c;
  undefined *local_88;
  undefined *local_84;
  undefined1 *local_80;
  undefined1 *local_7c;
  undefined1 *local_78;
  NSString *local_6c;
  int local_68;
  undefined4 local_64;

  local_80 = &stack0xfffffff8;
  local_78 = auStack_b4;
  local_88 = PTR_001b615c;
  local_84 = &::GCC_except_table1;
  local_7c = &LAB_000fcb88;
  local_b0 = param_2;
  local_ac = param_1;
  local_a8 = this;
  __Unwind_SjLj_Register(auStack_a0);
  local_6c = (NSString *)0x0;
  if (local_ac != (NSString *)0x0) {
    local_6c = local_ac;
    local_9c = 2;
    _objc_msgSend((ID)local_ac,"retain");
  }
  local_68 = local_b0;
  local_a4 = *(undefined4 **)(local_a8 + 0xc);
  if (local_a4 == *(undefined4 **)(local_a8 + 0x10)) {
    local_9c = 2;
    std::vector<OFViewDataMap::FieldReference,std::allocator<OFViewDataMap::FieldReference>>::
    _M_insert_aux((vector<OFViewDataMap::FieldReference,std::allocator<OFViewDataMap::FieldReference>>
                   *)(local_a8 + 8),local_a4,&local_6c);
  }
  else {
    if (local_a4 != (undefined4 *)0x0) {
      *local_a4 = local_6c;
      if (local_6c != (NSString *)0x0) {
        local_9c = 1;
        _objc_msgSend((ID)local_6c,"retain");
      }
      local_a4[1] = local_68;
      local_a4[2] = local_64;
    }
    *(int *)(local_a8 + 0xc) = *(int *)(local_a8 + 0xc) + 0xc;
  }
  if (local_6c != (NSString *)0x0) {
    local_9c = 0xffffffff;
    _objc_msgSend((ID)local_6c,"release");
  }
  __Unwind_SjLj_Unregister(auStack_a0);
  return;
}
