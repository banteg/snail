/*
 * mangled: _ZN29OFHttpNestedQueryStringWriter5nviIoEP16OFISerializerKeyR13OFRetainedPtrI8NSStringE
 * demangled: OFHttpNestedQueryStringWriter::nviIo(OFISerializerKey*, OFRetainedPtr<NSString>&)
 * address: 000c9db0
 * size: 360
 */

/* OFHttpNestedQueryStringWriter::nviIo(OFISerializerKey*, OFRetainedPtr<NSString>&) */

void __thiscall
OFHttpNestedQueryStringWriter::nviIo
          (OFHttpNestedQueryStringWriter *this,OFISerializerKey *param_1,OFRetainedPtr *param_2)

{
  NSString *self;
  OFRetainedPtr *local_c0;
  OFISerializerKey *local_bc;
  OFHttpNestedQueryStringWriter *local_b8;
  NSString *local_b4;
  int local_b0;
  int local_ac;
  NSString *local_a0;
  undefined1 auStack_9c [4];
  undefined4 local_98;
  undefined *local_84;
  undefined *local_80;
  undefined1 *local_7c;
  undefined1 *local_78;
  undefined1 *local_74;
  NSString *local_68;
  ID local_64 [17];

  local_7c = &stack0xfffffff8;
  local_74 = (undefined1 *)&local_c0;
  local_84 = PTR_001b615c;
  local_80 = &GCC_except_table7;
  local_78 = &LAB_000c9f18;
  local_c0 = param_2;
  local_bc = param_1;
  local_b8 = this;
  __Unwind_SjLj_Register(auStack_9c);
  local_98 = 0xffffffff;
  local_b4 = (NSString *)formatScoped(local_b8,local_bc);
  local_b0 = 0;
  local_ac = 0;
  if (local_b8[0x24] == (OFHttpNestedQueryStringWriter)0x0) {
    local_68 = *(NSString **)local_c0;
  }
  else {
    local_64[0] = *(ID *)local_c0;
    if (local_64[0] != 0) {
      local_98 = 1;
      _objc_msgSend(local_64[0],"retain");
    }
    local_b0 = 1;
    local_98 = 1;
    OFStringUtility::convertToValidParameter((OFStringUtility *)&local_68,local_64);
    local_a0 = local_68;
    local_ac = local_b0;
  }
  self = (NSString *)0x1;
  local_98 = 1;
  local_b0 = local_ac;
  addAsciiParameter(local_b8,local_b4,local_68);
  if (local_ac != 0) {
    self = local_a0;
  }
  if (local_ac != 0 && self != (NSString *)0x0) {
    local_98 = 2;
    _objc_msgSend((ID)self,"release");
  }
  if ((local_b0 != 0) && (local_64[0] != 0)) {
    local_98 = 0xffffffff;
    _objc_msgSend(local_64[0],"release");
  }
  __Unwind_SjLj_Unregister(auStack_9c);
  return;
}
