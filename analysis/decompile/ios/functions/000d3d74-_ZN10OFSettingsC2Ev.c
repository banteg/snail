/*
 * mangled: _ZN10OFSettingsC2Ev
 * demangled: OFSettings::OFSettings()
 * address: 000d3d74
 * size: 556
 */

/* OFSettings::OFSettings() */

void __thiscall OFSettings::OFSettings(OFSettings *this)

{
  cfstringStruct *pcVar1;
  ID IVar2;
  undefined1 auStack_a0 [4];
  char *local_9c;
  OFSettings *local_98;
  undefined1 auStack_94 [4];
  undefined4 local_90;
  undefined *local_7c;
  undefined *local_78;
  undefined1 *local_74;
  undefined1 *local_70;
  undefined1 *local_6c;

  local_74 = &stack0xfffffff8;
  local_6c = auStack_a0;
  local_7c = PTR_001b615c;
  local_78 = &::GCC_except_table5;
  local_70 = &LAB_000d3fa0;
  local_98 = this;
  __Unwind_SjLj_Register(auStack_94);
  *(undefined4 *)(local_98 + 4) = 0;
  *(undefined4 *)(local_98 + 8) = 0;
  *(undefined4 *)(local_98 + 0xc) = 0;
  *(undefined4 *)(local_98 + 0x10) = 0;
  *(undefined4 *)(local_98 + 0x14) = 0;
  *(undefined4 *)(local_98 + 0x18) = 0;
  *(undefined4 *)(local_98 + 0x1c) = 0;
  *(undefined4 *)(local_98 + 0x20) = 0;
  *(undefined4 *)(local_98 + 0x24) = 0;
  *(undefined4 *)(local_98 + 0x28) = 0;
  *(undefined4 *)(local_98 + 0x2c) = 0;
  *(cfstringStruct **)local_98 = &cf_https___api_openfeint_com_;
  local_9c = "retain";
  local_90 = 1;
  _objc_msgSend(0x1ba694,"retain");
  pcVar1 = *(cfstringStruct **)(local_98 + 4);
  if (pcVar1 != &cf_presence_openfeint_com) {
    if (pcVar1 != (cfstringStruct *)0x0) {
      local_90 = 1;
      _objc_msgSend((ID)pcVar1,"release");
    }
    *(cfstringStruct **)(local_98 + 4) = &cf_presence_openfeint_com;
    local_90 = 1;
    _objc_msgSend(0x1ba6a4,local_9c);
  }
  pcVar1 = *(cfstringStruct **)(local_98 + 0xc);
  if (pcVar1 != &cf_1a2dcd0bdc7ce8056aeb1dac00c2a886) {
    if (pcVar1 != (cfstringStruct *)0x0) {
      local_90 = 1;
      _objc_msgSend((ID)pcVar1,"release");
    }
    *(cfstringStruct **)(local_98 + 0xc) = &cf_1a2dcd0bdc7ce8056aeb1dac00c2a886;
    local_90 = 1;
    _objc_msgSend(0x1ba6b4,"retain");
  }
  IVar2 = *(ID *)(local_98 + 8);
  if (*(ID *)local_98 != IVar2) {
    if (IVar2 != 0) {
      local_90 = 1;
      _objc_msgSend(IVar2,"release");
    }
    IVar2 = *(ID *)local_98;
    *(ID *)(local_98 + 8) = IVar2;
    if (IVar2 != 0) {
      local_90 = 1;
      _objc_msgSend(IVar2,"retain");
    }
  }
  if (*(ID *)(local_98 + 0x28) != 0) {
    local_90 = 1;
    _objc_msgSend(*(ID *)(local_98 + 0x28),"release");
    *(undefined4 *)(local_98 + 0x28) = 0;
  }
  if (*(ID *)(local_98 + 0x2c) != 0) {
    local_90 = 1;
    _objc_msgSend(*(ID *)(local_98 + 0x2c),"release");
    *(undefined4 *)(local_98 + 0x2c) = 0;
  }
  local_90 = 1;
  discoverLocalConfiguration(local_98);
  loadSettingsFile(local_98);
  __Unwind_SjLj_Unregister(auStack_94);
  return;
}
