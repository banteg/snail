/*
 * mangled: _ZN21OFHighScoreBatchEntryD1Ev
 * demangled: OFHighScoreBatchEntry::~OFHighScoreBatchEntry()
 * address: 0008cc6c
 * size: 272
 */

/* OFHighScoreBatchEntry::~OFHighScoreBatchEntry() */

void __thiscall OFHighScoreBatchEntry::~OFHighScoreBatchEntry(OFHighScoreBatchEntry *this)

{
  undefined1 auStack_a0 [4];
  OFHighScoreBatchEntry *local_9c;
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
  local_78 = &::GCC_except_table3;
  local_70 = &LAB_0008cd7c;
  local_9c = this;
  __Unwind_SjLj_Register(auStack_94);
  *(undefined ***)local_9c = &PTR_GetRTTI_001b6eb8;
  if (*(ID *)(local_9c + 0x14) != 0) {
    local_98 = "release";
    local_90 = 1;
    _objc_msgSend(*(ID *)(local_9c + 0x14),"release");
  }
  if (*(ID *)(local_9c + 0x10) != 0) {
    local_90 = 2;
    _objc_msgSend(*(ID *)(local_9c + 0x10),"release");
  }
  if (*(ID *)(local_9c + 0xc) != 0) {
    local_90 = 3;
    _objc_msgSend(*(ID *)(local_9c + 0xc),"release");
  }
  if (*(ID *)(local_9c + 8) != 0) {
    local_90 = 4;
    _objc_msgSend(*(ID *)(local_9c + 8),"release");
  }
  local_90 = 0xffffffff;
  OFSmartObject::~OFSmartObject((OFSmartObject *)local_9c);
  __Unwind_SjLj_Unregister(auStack_94);
  return;
}
