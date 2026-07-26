/*
 * mangled: _ZN10OFSqlQuery7executeEv
 * demangled: OFSqlQuery::execute()
 * address: 000d4868
 * size: 84
 */

/* WARNING: Removing unreachable block (ram,0x000d48b0) */
/* OFSqlQuery::execute() */

bool __thiscall OFSqlQuery::execute(OFSqlQuery *this)

{
  int iVar1;

  iVar1 = _sqlite3_step((sqlite3_stmt *)this->field2_0x8);
  this->field0_0x0 = iVar1;
  if (iVar1 == 0x65) {
    _sqlite3_reset((sqlite3_stmt *)this->field2_0x8);
    this->field0_0x0 = 0;
    return false;
  }
  return iVar1 == 100;
}
