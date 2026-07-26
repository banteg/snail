/*
 * mangled: _ZN10OFSqlQueryD1Ev
 * demangled: OFSqlQuery::~OFSqlQuery()
 * address: 000d4d38
 * size: 160
 */

/* OFSqlQuery::~OFSqlQuery() */

void __thiscall OFSqlQuery::~OFSqlQuery(OFSqlQuery *this)

{
  OFSdbmHashedString *pOVar1;
  OFSqlQuery *local_9c [2];
  undefined1 auStack_94 [4];
  undefined4 local_90;
  undefined *local_7c;
  undefined *local_78;
  undefined1 *local_74;
  undefined1 *local_70;
  undefined1 *local_6c;

  local_74 = &stack0xfffffff8;
  local_6c = (undefined1 *)local_9c;
  local_7c = PTR_001b615c;
  local_78 = &::GCC_except_table4;
  local_70 = &LAB_000d4dd8;
  local_9c[0] = this;
  __Unwind_SjLj_Register(auStack_94);
  if ((sqlite3_stmt *)local_9c[0]->field2_0x8 != (sqlite3_stmt *)0x0) {
    local_90 = 1;
    _sqlite3_finalize((sqlite3_stmt *)local_9c[0]->field2_0x8);
  }
  pOVar1 = (local_9c[0]->field4_0x10).field0_0x0.field0_0x0;
  local_9c[0]->field2_0x8 = (sqlite3_stmt *)0x0;
  local_9c[0]->field1_0x4 = (sqlite3 *)0x0;
  local_9c[0]->field3_0xc = (char *)0x0;
  if (pOVar1 != (OFSdbmHashedString *)0x0) {
    operator_delete(pOVar1);
  }
  __Unwind_SjLj_Unregister(auStack_94);
  return;
}
