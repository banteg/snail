/*
 * mangled: _ZN21OFHighScoreBatchEntryC1EP13OFISerializer
 * demangled: OFHighScoreBatchEntry::OFHighScoreBatchEntry(OFISerializer*)
 * address: 0008ca8c
 * size: 4
 */

/* OFHighScoreBatchEntry::OFHighScoreBatchEntry(OFISerializer*) */

void __thiscall
OFHighScoreBatchEntry::OFHighScoreBatchEntry(OFHighScoreBatchEntry *this,OFISerializer *param_1)

{
  OFISerializer *pOStack_a0;
  OFSmartObject *pOStack_9c;
  undefined1 auStack_94 [4];
  undefined4 uStack_90;
  undefined *puStack_7c;
  undefined *puStack_78;
  undefined1 *puStack_74;
  undefined1 *puStack_70;
  undefined1 *puStack_6c;

  puStack_74 = &stack0xfffffff8;
  puStack_6c = (undefined1 *)&pOStack_a0;
  puStack_7c = PTR_001b615c;
  puStack_78 = &::GCC_except_table1;
  puStack_70 = &LAB_0008c9c0;
  pOStack_a0 = param_1;
  pOStack_9c = (OFSmartObject *)this;
  __Unwind_SjLj_Register(auStack_94);
  uStack_90 = 0xffffffff;
  OFSmartObject::OFSmartObject(pOStack_9c);
  *(undefined ***)pOStack_9c = &PTR_GetRTTI_001b6eb8;
  *(undefined4 *)(pOStack_9c + 8) = 0;
  *(undefined4 *)(pOStack_9c + 0xc) = 0;
  *(undefined4 *)(pOStack_9c + 0x10) = 0;
  *(undefined4 *)(pOStack_9c + 0x14) = 0;
  uStack_90 = 1;
  serialize((OFHighScoreBatchEntry *)pOStack_9c,pOStack_a0);
  __Unwind_SjLj_Unregister(auStack_94);
  return;
}
