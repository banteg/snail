/*
 * mangled: _ZN10OFSqlQueryC1EP7sqlite3PKc
 * demangled: OFSqlQuery::OFSqlQuery(sqlite3*, char const*)
 * address: 000d4ea0
 * size: 168
 */

/* OFSqlQuery::OFSqlQuery(sqlite3*, char const*) */

void __thiscall OFSqlQuery::OFSqlQuery(OFSqlQuery *this,sqlite3 *param_1,char *param_2)

{
  char *local_a4;
  sqlite3 *local_a0;
  OFSqlQuery *local_9c;
  undefined1 auStack_94 [4];
  undefined4 local_90;
  undefined *local_7c;
  undefined *local_78;
  undefined1 *local_74;
  undefined1 *local_70;
  undefined1 *local_6c;

  local_74 = &stack0xfffffff8;
  local_6c = (undefined1 *)&local_a4;
  local_7c = PTR_001b615c;
  local_78 = &::GCC_except_table5;
  local_70 = &LAB_000d4f48;
  local_a4 = param_2;
  local_a0 = (sqlite3 *)param_1;
  local_9c = this;
  __Unwind_SjLj_Register(auStack_94);
  local_9c->field0_0x0 = 0;
  local_9c->field1_0x4 = local_a0;
  local_9c->field2_0x8 = (sqlite3_stmt *)0x0;
  (local_9c->field4_0x10).field0_0x0.field0_0x0 = (OFSdbmHashedString *)0x0;
  (local_9c->field4_0x10).field0_0x0.field1_0x4 = (OFSdbmHashedString *)0x0;
  (local_9c->field4_0x10).field0_0x0.field2_0x8 = (OFSdbmHashedString *)0x0;
  local_9c->field3_0xc = local_a4;
  local_90 = 1;
  reset((sqlite3 *)local_9c,(char *)local_a0,SUB41(local_a4,0));
  __Unwind_SjLj_Unregister(auStack_94);
  return;
}
