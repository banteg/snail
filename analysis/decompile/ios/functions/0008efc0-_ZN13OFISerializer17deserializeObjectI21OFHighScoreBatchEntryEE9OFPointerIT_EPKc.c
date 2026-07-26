/*
 * mangled: _ZN13OFISerializer17deserializeObjectI21OFHighScoreBatchEntryEE9OFPointerIT_EPKc
 * demangled: OFPointer<OFHighScoreBatchEntry> OFISerializer::deserializeObject<OFHighScoreBatchEntry>(char const*)
 * address: 0008efc0
 * size: 236
 */

/* OFPointer<OFHighScoreBatchEntry> OFISerializer::deserializeObject<OFHighScoreBatchEntry>(char
   const*) */

char * OFISerializer::deserializeObject<OFHighScoreBatchEntry>(char *param_1)

{
  OFISerializer *in_r1;
  char *in_r2;
  undefined1 auStack_b8 [4];
  char *local_b4;
  OFISerializer *local_b0;
  char *local_ac;
  OFHighScoreBatchEntry *local_a8;
  OFHighScoreBatchEntry *local_a4;
  char *local_a0;
  undefined1 auStack_9c [4];
  undefined4 local_98;
  undefined *local_84;
  undefined *local_80;
  undefined1 *local_7c;
  undefined1 *local_78;
  undefined1 *local_74;
  Scope aSStack_68 [72];

  local_7c = &stack0xfffffff8;
  local_74 = auStack_b8;
  local_84 = PTR_001b615c;
  local_80 = &::GCC_except_table0;
  local_78 = &LAB_0008f0ac;
  local_b4 = in_r2;
  local_b0 = in_r1;
  local_ac = param_1;
  __Unwind_SjLj_Register(auStack_9c);
  local_98 = 0xffffffff;
  Scope::Scope(aSStack_68,local_b0,local_b4,false);
  local_98 = 2;
  local_a0 = local_ac;
  local_a8 = operator_new(0x20);
  local_98 = 1;
  local_a4 = local_a8;
  OFHighScoreBatchEntry::OFHighScoreBatchEntry(local_a8,local_b0);
  *(OFHighScoreBatchEntry **)local_a0 = local_a4;
  if (local_a8 != (OFHighScoreBatchEntry *)0x0) {
    *(int *)(local_a4 + 4) = *(int *)(local_a4 + 4) + 1;
  }
  local_98 = 0xffffffff;
  Scope::~Scope(aSStack_68);
  __Unwind_SjLj_Unregister(auStack_9c);
  return local_ac;
}
