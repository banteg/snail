/*
 * mangled: _ZN10OFSqlQuery4stepEv
 * demangled: OFSqlQuery::step()
 * address: 000d4a2c
 * size: 52
 */

/* OFSqlQuery::step() */

void __thiscall OFSqlQuery::step(OFSqlQuery *this)

{
  int iVar1;

  iVar1 = _sqlite3_step((sqlite3_stmt *)this->field2_0x8);
  this->field0_0x0 = iVar1;
  if (iVar1 != 0x65) {
    return;
  }
  _sqlite3_reset((sqlite3_stmt *)this->field2_0x8);
  this->field0_0x0 = 0;
  return;
}
