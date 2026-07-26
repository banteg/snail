/*
 * mangled: _ZN17OFResourceDataMap22addNestedResourceFieldEP8NSStringP13objc_selectorS3_P10objc_class
 * demangled: OFResourceDataMap::addNestedResourceField(NSString*, objc_selector*, objc_selector*, objc_class*)
 * address: 000fadbc
 * size: 380
 */

/* OFResourceDataMap::addNestedResourceField(NSString*, objc_selector*, objc_selector*, objc_class*)
    */

void __thiscall
OFResourceDataMap::addNestedResourceField
          (OFResourceDataMap *this,NSString *param_1,objc_selector *param_2,objc_selector *param_3,
          objc_class *param_4)

{
  undefined1 auStack_c0 [4];
  objc_selector *local_bc;
  objc_selector *local_b8;
  NSString *local_b4;
  OFResourceDataMap *local_b0;
  FieldDescription *local_ac;
  undefined1 auStack_a8 [4];
  undefined4 local_a4;
  undefined *local_90;
  undefined *local_8c;
  undefined1 *local_88;
  undefined1 *local_84;
  undefined1 *local_80;
  NSString *local_74;
  objc_selector *local_70;
  objc_selector *local_6c;
  objc_class *local_68;
  FieldDescription local_64;

  local_88 = &stack0xfffffff8;
  local_80 = auStack_c0;
  local_90 = PTR_001b615c;
  local_8c = &::GCC_except_table3;
  local_84 = &LAB_000faf38;
  local_bc = param_3;
  local_b8 = param_2;
  local_b4 = param_1;
  local_b0 = this;
  __Unwind_SjLj_Register(auStack_a8);
  local_74 = (NSString *)0x0;
  local_70 = local_b8;
  if (local_b4 != (NSString *)0x0) {
    local_74 = local_b4;
    local_a4 = 2;
    _objc_msgSend((ID)local_b4,"retain");
  }
  local_68 = param_4;
  local_64 = (FieldDescription)0x0;
  local_6c = local_bc;
  local_ac = (local_b0->field2_0x8).field0_0x0.field1_0x4;
  if (local_ac == (local_b0->field2_0x8).field0_0x0.field2_0x8) {
    local_a4 = 2;
    std::
    vector<OFResourceDataMap::FieldDescription,std::allocator<OFResourceDataMap::FieldDescription>>
    ::_M_insert_aux((vector<OFResourceDataMap::FieldDescription,std::allocator<OFResourceDataMap::FieldDescription>>
                     *)&local_b0->field2_0x8,local_ac,&local_74);
  }
  else {
    if (local_ac != (FieldDescription *)0x0) {
      *(NSString **)local_ac = local_74;
      if (local_74 != (NSString *)0x0) {
        local_a4 = 1;
        _objc_msgSend((ID)local_74,"retain");
      }
      *(objc_selector **)(local_ac + 4) = local_70;
      *(objc_selector **)(local_ac + 8) = local_6c;
      *(objc_class **)(local_ac + 0xc) = local_68;
      local_ac[0x10] = local_64;
    }
    (local_b0->field2_0x8).field0_0x0.field1_0x4 =
         (local_b0->field2_0x8).field0_0x0.field1_0x4 + 0x14;
  }
  if (local_74 != (NSString *)0x0) {
    local_a4 = 0xffffffff;
    _objc_msgSend((ID)local_74,"release");
  }
  __Unwind_SjLj_Unregister(auStack_a8);
  return;
}
