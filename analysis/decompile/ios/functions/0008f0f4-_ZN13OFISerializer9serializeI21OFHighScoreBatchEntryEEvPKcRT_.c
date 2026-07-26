/*
 * mangled: _ZN13OFISerializer9serializeI21OFHighScoreBatchEntryEEvPKcRT_
 * demangled: void OFISerializer::serialize<OFHighScoreBatchEntry>(char const*, OFHighScoreBatchEntry&)
 * address: 0008f0f4
 * size: 168
 */

/* void OFISerializer::serialize<OFHighScoreBatchEntry>(char const*, OFHighScoreBatchEntry&) */

void __thiscall
OFISerializer::serialize<OFHighScoreBatchEntry>
          (OFISerializer *this,char *param_1,OFHighScoreBatchEntry *param_2)

{
  undefined1 auStack_ac [4];
  OFHighScoreBatchEntry *local_a8;
  char *local_a4;
  OFISerializer *local_a0;
  undefined1 auStack_9c [4];
  undefined4 local_98;
  undefined *local_84;
  undefined *local_80;
  undefined1 *local_7c;
  undefined1 *local_78;
  undefined1 *local_74;
  Scope aSStack_68 [72];

  local_7c = &stack0xfffffff8;
  local_74 = auStack_ac;
  local_84 = PTR_001b615c;
  local_80 = &::GCC_except_table1;
  local_78 = &LAB_0008f19c;
  local_a8 = param_2;
  local_a4 = param_1;
  local_a0 = this;
  __Unwind_SjLj_Register(auStack_9c);
  local_98 = 0xffffffff;
  Scope::Scope(aSStack_68,local_a0,local_a4,false);
  local_98 = 1;
  OFHighScoreBatchEntry::serialize(local_a8,local_a0);
  local_98 = 0xffffffff;
  Scope::~Scope(aSStack_68);
  __Unwind_SjLj_Unregister(auStack_9c);
  return;
}
