/*
 * mangled: _ZN11OFXmlReader5nviIoEP16OFISerializerKeyRSs
 * demangled: OFXmlReader::nviIo(OFISerializerKey*, std::string&)
 * address: 000cdab8
 * size: 384
 */

/* OFXmlReader::nviIo(OFISerializerKey*, std::string&) */

void __thiscall OFXmlReader::nviIo(OFXmlReader *this,OFISerializerKey *param_1,string *param_2)

{
  undefined4 uVar1;
  ID IVar2;
  string *local_c0;
  OFISerializerKey *local_bc;
  OFXmlReader *local_b8;
  ID local_b0;
  SEL local_ac;
  ID local_a8;
  char *local_a4;
  ID local_a0;
  undefined1 auStack_9c [4];
  undefined4 local_98;
  undefined *local_84;
  undefined *local_80;
  undefined1 *local_7c;
  undefined1 *local_78;
  undefined1 *local_74;
  ID local_68;
  ID local_64 [17];

  local_7c = &stack0xfffffff8;
  local_74 = (undefined1 *)&local_c0;
  local_84 = PTR_001b615c;
  local_80 = &GCC_except_table6;
  local_78 = &LAB_000cdc38;
  local_c0 = param_2;
  local_bc = param_1;
  local_b8 = this;
  __Unwind_SjLj_Register(auStack_9c);
  local_b0 = *(ID *)(local_b8 + 0x18);
  local_ac = "nextValueAtCurrentScopeWithKey:outValue:";
  local_98 = 0xffffffff;
  uVar1 = (**(code **)(*(int *)local_bc + 0x14))(local_bc);
  IVar2 = _objc_msgSend(local_b0,local_ac,uVar1,local_64);
  if (IVar2 != 0) {
    local_a8 = local_64[0];
    if (*(code **)(local_b8 + 0x1c) == (code *)0x0) {
      local_a0 = local_64[0];
      if (local_64[0] != 0) {
        local_98 = 0xffffffff;
        _objc_msgSend(local_64[0],"retain");
      }
    }
    else {
      local_98 = 0xffffffff;
      (**(code **)(local_b8 + 0x1c))(&local_68,local_64[0]);
      local_a0 = local_68;
      local_a8 = local_68;
    }
    local_98 = 1;
    local_a4 = (char *)_objc_msgSend(local_a0,"UTF8String");
    _strlen(local_a4);
    std::string::assign((char *)local_c0,(ulong)local_a4);
    if (local_a8 != 0) {
      local_98 = 0xffffffff;
      _objc_msgSend(local_a0,"release");
    }
  }
  __Unwind_SjLj_Unregister(auStack_9c);
  return;
}
