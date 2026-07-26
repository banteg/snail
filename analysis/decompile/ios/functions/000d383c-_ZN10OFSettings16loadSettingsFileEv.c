/*
 * mangled: _ZN10OFSettings16loadSettingsFileEv
 * demangled: OFSettings::loadSettingsFile()
 * address: 000d383c
 * size: 580
 */

/* OFSettings::loadSettingsFile() */

void __thiscall OFSettings::loadSettingsFile(OFSettings *this)

{
  char *pcVar1;
  undefined1 auStack_fc [4];
  OFSettings *local_f8;
  ID local_f4;
  undefined4 *local_d8;
  undefined4 *local_cc;
  undefined1 auStack_c4 [4];
  undefined4 local_c0;
  undefined *local_ac;
  undefined *local_a8;
  undefined1 *local_a4;
  undefined1 *local_a0;
  undefined1 *local_9c;
  undefined *local_90 [2];
  undefined4 *local_88;
  undefined4 *local_84;
  ID local_78;
  Scope aSStack_70 [8];
  Scope aSStack_68 [72];

  local_a4 = &stack0xfffffff8;
  local_9c = auStack_fc;
  local_ac = PTR_001b615c;
  local_a8 = &::GCC_except_table4;
  local_a0 = &LAB_000d3a80;
  local_f8 = this;
  __Unwind_SjLj_Register(auStack_c4);
  local_c0 = 0xffffffff;
  OFXmlReader::OFXmlReader
            ((OFXmlReader *)local_90,"openfeint_internal_settings",
             (_func_OFRetainedPtr_NSString_ptr *)0x0);
  local_c0 = 9;
  local_f4 = NSMutableString::stringWithString_
                       ((ID)&_OBJC_CLASS___NSMutableString,"stringWithString:",&cf_environment_);
  NSMutableString::appendString_(local_f4,"appendString:",&cf_release);
  OFISerializer::Scope::Scope(aSStack_68,(OFISerializer *)local_90,"config",false);
  local_c0 = 8;
  pcVar1 = (char *)_objc_msgSend(local_f4,"cStringUsingEncoding:",4);
  OFISerializer::Scope::Scope(aSStack_70,(OFISerializer *)local_90,pcVar1,false);
  local_c0 = 7;
  OFISerializer::io((OFISerializer *)local_90,"server-url",(OFRetainedPtr *)local_f8);
  OFISerializer::io((OFISerializer *)local_90,"presence-host",(OFRetainedPtr *)(local_f8 + 4));
  OFISerializer::io((OFISerializer *)local_90,"facebook-callback-url",
                    (OFRetainedPtr *)(local_f8 + 8));
  OFISerializer::io((OFISerializer *)local_90,"facebook-application-key",
                    (OFRetainedPtr *)(local_f8 + 0xc));
  OFISerializer::io((OFISerializer *)local_90,"debug-override-key",
                    (OFRetainedPtr *)(local_f8 + 0x28));
  OFISerializer::io((OFISerializer *)local_90,"debug-override-secret",
                    (OFRetainedPtr *)(local_f8 + 0x2c));
  local_c0 = 8;
  OFISerializer::Scope::~Scope(aSStack_70);
  local_c0 = 9;
  OFISerializer::Scope::~Scope(aSStack_68);
  local_90[0] = PTR_vtable_001b638c + 8;
  if (local_78 != 0) {
    local_c0 = 3;
    _objc_msgSend(local_78,"release");
  }
  local_d8 = local_84;
  local_90[0] = PTR_vtable_001b636c + 8;
  if (local_88 != local_84) {
    local_cc = local_88;
    do {
      if ((OFSmartObject *)*local_cc != (OFSmartObject *)0x0) {
        local_c0 = 1;
        OFSmartObject::Release((OFSmartObject *)*local_cc);
      }
      local_cc = local_cc + 2;
    } while (local_d8 != local_cc);
  }
  if (local_88 != (undefined4 *)0x0) {
    operator_delete(local_88);
  }
  local_c0 = 0xffffffff;
  OFSmartObject::~OFSmartObject((OFSmartObject *)local_90);
  __Unwind_SjLj_Unregister(auStack_c4);
  return;
}
