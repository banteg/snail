/*
 * mangled: _ZN10OFSqlQuery10resetQueryEv
 * demangled: OFSqlQuery::resetQuery()
 * address: 000d46dc
 * size: 32
 */

/* OFSqlQuery::resetQuery() */

void __thiscall OFSqlQuery::resetQuery(OFSqlQuery *this)

{
  _sqlite3_reset((sqlite3_stmt *)this->field2_0x8);
  this->field0_0x0 = 0;
  return;
}
