/*
 * mangled: _ZN10OFSettingsD2Ev
 * demangled: OFSettings::~OFSettings()
 * address: 000d42b0
 * size: 536
 */

/* OFSettings::~OFSettings() */

void __thiscall OFSettings::~OFSettings(OFSettings *this)

{
  undefined1 auStack_a0 [4];
  OFSettings *local_9c;
  char *local_98;
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
  local_78 = &::GCC_except_table0;
  local_70 = &LAB_000d44c8;
  local_9c = this;
  __Unwind_SjLj_Register(auStack_94);
  if (*(ID *)(local_9c + 0x2c) != 0) {
    local_98 = "release";
    local_90 = 1;
    _objc_msgSend(*(ID *)(local_9c + 0x2c),"release");
  }
  if (*(ID *)(local_9c + 0x28) != 0) {
    local_90 = 2;
    _objc_msgSend(*(ID *)(local_9c + 0x28),"release");
  }
  if (*(ID *)(local_9c + 0x24) != 0) {
    local_90 = 3;
    _objc_msgSend(*(ID *)(local_9c + 0x24),"release");
  }
  if (*(ID *)(local_9c + 0x20) != 0) {
    local_90 = 4;
    _objc_msgSend(*(ID *)(local_9c + 0x20),"release");
  }
  if (*(ID *)(local_9c + 0x1c) != 0) {
    local_90 = 5;
    _objc_msgSend(*(ID *)(local_9c + 0x1c),"release");
  }
  if (*(ID *)(local_9c + 0x18) != 0) {
    local_90 = 6;
    _objc_msgSend(*(ID *)(local_9c + 0x18),"release");
  }
  if (*(ID *)(local_9c + 0x14) != 0) {
    local_90 = 7;
    _objc_msgSend(*(ID *)(local_9c + 0x14),"release");
  }
  if (*(ID *)(local_9c + 0x10) != 0) {
    local_90 = 8;
    _objc_msgSend(*(ID *)(local_9c + 0x10),"release");
  }
  if (*(ID *)(local_9c + 0xc) != 0) {
    local_90 = 9;
    _objc_msgSend(*(ID *)(local_9c + 0xc),"release");
  }
  if (*(ID *)(local_9c + 8) != 0) {
    local_90 = 10;
    _objc_msgSend(*(ID *)(local_9c + 8),"release");
  }
  if (*(ID *)(local_9c + 4) != 0) {
    local_90 = 0xb;
    _objc_msgSend(*(ID *)(local_9c + 4),"release");
  }
  if (*(ID *)local_9c != 0) {
    local_90 = 0xffffffff;
    _objc_msgSend(*(ID *)local_9c,"release");
  }
  __Unwind_SjLj_Unregister(auStack_94);
  return;
}
