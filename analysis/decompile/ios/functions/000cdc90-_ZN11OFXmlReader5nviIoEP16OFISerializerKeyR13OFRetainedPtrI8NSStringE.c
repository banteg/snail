/*
 * mangled: _ZN11OFXmlReader5nviIoEP16OFISerializerKeyR13OFRetainedPtrI8NSStringE
 * demangled: OFXmlReader::nviIo(OFISerializerKey*, OFRetainedPtr<NSString>&)
 * address: 000cdc90
 * size: 396
 */

/* OFXmlReader::nviIo(OFISerializerKey*, OFRetainedPtr<NSString>&) */

void __thiscall
OFXmlReader::nviIo(OFXmlReader *this,OFISerializerKey *param_1,OFRetainedPtr *param_2)

{
  undefined4 uVar1;
  ID IVar2;
  OFRetainedPtr *local_b8;
  OFISerializerKey *local_b4;
  OFXmlReader *local_b0;
  ID local_a8;
  SEL local_a4;
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
  local_74 = (undefined1 *)&local_b8;
  local_84 = PTR_001b615c;
  local_80 = &GCC_except_table7;
  local_78 = &LAB_000cde1c;
  local_b8 = param_2;
  local_b4 = param_1;
  local_b0 = this;
  __Unwind_SjLj_Register(auStack_9c);
  local_a8 = *(ID *)(local_b0 + 0x18);
  local_a4 = "nextValueAtCurrentScopeWithKey:outValue:";
  local_98 = 0xffffffff;
  uVar1 = (**(code **)(*(int *)local_b4 + 0x14))(local_b4);
  IVar2 = _objc_msgSend(local_a8,local_a4,uVar1,local_64);
  if (IVar2 != 0) {
    local_a0 = local_64[0];
    if (*(code **)(local_b0 + 0x1c) == (code *)0x0) {
      if (local_64[0] != 0) {
        _objc_msgSend(local_64[0],"retain");
      }
    }
    else {
      local_98 = 0xffffffff;
      (**(code **)(local_b0 + 0x1c))(&local_68,local_64[0]);
      local_a0 = local_68;
    }
    IVar2 = *(ID *)local_b8;
    if (local_a0 != IVar2) {
      if (IVar2 != 0) {
        local_98 = 1;
        _objc_msgSend(IVar2,"release");
      }
      *(ID *)local_b8 = local_a0;
      if (local_a0 == 0) goto LAB_000cdddc;
      local_98 = 1;
      _objc_msgSend(local_a0,"retain");
    }
    if (local_a0 != 0) {
      local_98 = 0xffffffff;
      _objc_msgSend(local_a0,"release");
    }
  }
LAB_000cdddc:
  __Unwind_SjLj_Unregister(auStack_9c);
  return;
}
