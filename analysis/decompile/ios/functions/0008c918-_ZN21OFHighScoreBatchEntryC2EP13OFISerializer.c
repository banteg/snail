/*
 * mangled: _ZN21OFHighScoreBatchEntryC2EP13OFISerializer
 * demangled: OFHighScoreBatchEntry::OFHighScoreBatchEntry(OFISerializer*)
 * address: 0008c918
 * size: 168
 */

/* OFHighScoreBatchEntry::OFHighScoreBatchEntry(OFISerializer*) */

void __thiscall
OFHighScoreBatchEntry::OFHighScoreBatchEntry(OFHighScoreBatchEntry *this,OFISerializer *param_1)

{
  OFISerializer *local_a0;
  OFSmartObject *local_9c;
  undefined1 auStack_94 [4];
  undefined4 local_90;
  undefined *local_7c;
  undefined *local_78;
  undefined1 *local_74;
  undefined1 *local_70;
  undefined1 *local_6c;

  local_74 = &stack0xfffffff8;
  local_6c = (undefined1 *)&local_a0;
  local_7c = PTR_001b615c;
  local_78 = &::GCC_except_table1;
  local_70 = &LAB_0008c9c0;
  local_a0 = param_1;
  local_9c = (OFSmartObject *)this;
  __Unwind_SjLj_Register(auStack_94);
  local_90 = 0xffffffff;
  OFSmartObject::OFSmartObject(local_9c);
  *(undefined ***)local_9c = &PTR_GetRTTI_001b6eb8;
  *(undefined4 *)(local_9c + 8) = 0;
  *(undefined4 *)(local_9c + 0xc) = 0;
  *(undefined4 *)(local_9c + 0x10) = 0;
  *(undefined4 *)(local_9c + 0x14) = 0;
  local_90 = 1;
  serialize((OFHighScoreBatchEntry *)local_9c,local_a0);
  __Unwind_SjLj_Unregister(auStack_94);
  return;
}
