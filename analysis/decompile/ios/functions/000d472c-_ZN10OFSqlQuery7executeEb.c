/*
 * mangled: _ZN10OFSqlQuery7executeEb
 * demangled: OFSqlQuery::execute(bool)
 * address: 000d472c
 * size: 84
 */

/* WARNING: Removing unreachable block (ram,0x000d4774) */
/* OFSqlQuery::execute(bool) */

bool OFSqlQuery::execute(bool param_1)

{
  int *piVar1;
  int iVar2;

  piVar1 = (int *)(uint)param_1;
  iVar2 = _sqlite3_step((sqlite3_stmt *)piVar1[2]);
  *piVar1 = iVar2;
  if (iVar2 == 0x65) {
    _sqlite3_reset((sqlite3_stmt *)piVar1[2]);
    *piVar1 = 0;
    return false;
  }
  return iVar2 == 100;
}
