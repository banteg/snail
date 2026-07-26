/*
 * mangled: _ZN17OFResourceNameMap11addResourceEP8NSStringP10objc_class
 * demangled: OFResourceNameMap::addResource(NSString*, objc_class*)
 * address: 000fb990
 * size: 324
 */

/* OFResourceNameMap::addResource(NSString*, objc_class*) */

void __thiscall
OFResourceNameMap::addResource(OFResourceNameMap *this,NSString *param_1,objc_class *param_2)

{
  undefined1 auStack_b0 [4];
  objc_class *local_ac;
  NSString *local_a8;
  OFResourceNameMap *local_a4;
  ResourceDescription *local_a0;
  undefined1 auStack_9c [4];
  undefined4 local_98;
  undefined *local_84;
  undefined *local_80;
  undefined1 *local_7c;
  undefined1 *local_78;
  undefined1 *local_74;
  NSString *local_68;
  objc_class *local_64;

  local_7c = &stack0xfffffff8;
  local_74 = auStack_b0;
  local_84 = PTR_001b615c;
  local_80 = &::GCC_except_table1;
  local_78 = &LAB_000fbad4;
  local_ac = param_2;
  local_a8 = param_1;
  local_a4 = this;
  __Unwind_SjLj_Register(auStack_9c);
  local_68 = (NSString *)0x0;
  local_64 = local_ac;
  if (local_a8 != (NSString *)0x0) {
    local_68 = local_a8;
    local_98 = 2;
    _objc_msgSend((ID)local_a8,"retain");
  }
  local_a0 = (local_a4->field2_0x8).field0_0x0.field1_0x4;
  if (local_a0 == (local_a4->field2_0x8).field0_0x0.field2_0x8) {
    local_98 = 2;
    std::
    vector<OFResourceNameMap::ResourceDescription,std::allocator<OFResourceNameMap::ResourceDescription>>
    ::_M_insert_aux((vector<OFResourceNameMap::ResourceDescription,std::allocator<OFResourceNameMap::ResourceDescription>>
                     *)&local_a4->field2_0x8,local_a0,&local_68);
  }
  else {
    if (local_a0 != (ResourceDescription *)0x0) {
      *(NSString **)local_a0 = local_68;
      if (local_68 != (NSString *)0x0) {
        local_98 = 1;
        _objc_msgSend((ID)local_68,"retain");
      }
      *(objc_class **)(local_a0 + 4) = local_64;
    }
    (local_a4->field2_0x8).field0_0x0.field1_0x4 = (local_a4->field2_0x8).field0_0x0.field1_0x4 + 8;
  }
  if (local_68 != (NSString *)0x0) {
    local_98 = 0xffffffff;
    _objc_msgSend((ID)local_68,"release");
  }
  __Unwind_SjLj_Unregister(auStack_9c);
  return;
}
