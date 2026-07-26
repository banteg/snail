/*
 * mangled: _ZN29OFHttpNestedQueryStringWriter5nviIoEP16OFISerializerKeyRSs
 * demangled: OFHttpNestedQueryStringWriter::nviIo(OFISerializerKey*, std::string&)
 * address: 000c980c
 * size: 228
 */

/* OFHttpNestedQueryStringWriter::nviIo(OFISerializerKey*, std::string&) */

void __thiscall
OFHttpNestedQueryStringWriter::nviIo
          (OFHttpNestedQueryStringWriter *this,OFISerializerKey *param_1,string *param_2)

{
  string *local_a8;
  OFISerializerKey *local_a4;
  OFHttpNestedQueryStringWriter *local_a0;
  undefined1 auStack_98 [4];
  undefined4 local_94;
  undefined *local_80;
  undefined *local_7c;
  undefined1 *local_78;
  undefined1 *local_74;
  undefined1 *local_70;
  ID local_64 [17];

  local_78 = &stack0xfffffff8;
  local_70 = (undefined1 *)&local_a8;
  local_80 = PTR_001b615c;
  local_7c = &::GCC_except_table1;
  local_74 = &LAB_000c98f0;
  local_a8 = param_2;
  local_a4 = param_1;
  local_a0 = this;
  __Unwind_SjLj_Register(auStack_98);
  local_94 = 0xffffffff;
  local_64[0] = NSString::stringWithUTF8String_
                          ((ID)&_OBJC_CLASS___NSString,"stringWithUTF8String:",
                           *(undefined4 *)local_a8);
  if (local_64[0] != 0) {
    NSString::retain(local_64[0],"retain");
  }
  local_94 = 1;
  (**(code **)(*(int *)local_a0 + 0x34))(local_a0,local_a4,local_64);
  if (local_64[0] != 0) {
    local_94 = 0xffffffff;
    _objc_msgSend(local_64[0],"release");
  }
  __Unwind_SjLj_Unregister(auStack_98);
  return;
}
