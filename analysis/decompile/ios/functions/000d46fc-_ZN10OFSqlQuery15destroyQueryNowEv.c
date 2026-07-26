/*
 * mangled: _ZN10OFSqlQuery15destroyQueryNowEv
 * demangled: OFSqlQuery::destroyQueryNow()
 * address: 000d46fc
 * size: 48
 */

/* OFSqlQuery::destroyQueryNow() */

void __thiscall OFSqlQuery::destroyQueryNow(OFSqlQuery *this)

{
  if ((sqlite3_stmt *)this->field2_0x8 != (sqlite3_stmt *)0x0) {
    _sqlite3_finalize((sqlite3_stmt *)this->field2_0x8);
  }
  this->field2_0x8 = (sqlite3_stmt *)0x0;
  this->field1_0x4 = (sqlite3 *)0x0;
  this->field3_0xc = (char *)0x0;
  return;
}
