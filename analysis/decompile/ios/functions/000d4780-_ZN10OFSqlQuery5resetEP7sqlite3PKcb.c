/*
 * mangled: _ZN10OFSqlQuery5resetEP7sqlite3PKcb
 * demangled: OFSqlQuery::reset(sqlite3*, char const*, bool)
 * address: 000d4780
 * size: 224
 */

/* OFSqlQuery::reset(sqlite3*, char const*, bool) */

void OFSqlQuery::reset(sqlite3 *param_1,char *param_2,bool param_3)

{
  size_t nByte;
  int iVar1;
  char *pcVar2;
  undefined4 *puVar3;
  int iVar4;
  int N;
  undefined4 local_1c;

  pcVar2 = (char *)(uint)param_3;
  if (*(sqlite3_stmt **)(param_1 + 8) != (sqlite3_stmt *)0x0) {
    _sqlite3_finalize(*(sqlite3_stmt **)(param_1 + 8));
  }
  *(char **)(param_1 + 4) = param_2;
  *(undefined4 *)(param_1 + 8) = 0;
  *(char **)(param_1 + 0xc) = pcVar2;
  *(undefined4 *)param_1 = 0;
  nByte = _strlen(pcVar2);
  _sqlite3_prepare_v2((sqlite3 *)param_2,pcVar2,nByte,(sqlite3_stmt **)(param_1 + 8),(char **)0x0);
  *(undefined4 *)(param_1 + 0x14) = *(undefined4 *)(param_1 + 0x10);
  iVar1 = _sqlite3_column_count(*(sqlite3_stmt **)(param_1 + 8));
  if (iVar1 != 0) {
    N = 0;
    do {
      pcVar2 = _sqlite3_column_name(*(sqlite3_stmt **)(param_1 + 8),N);
      OFSdbmHashedString::OFSdbmHashedString((OFSdbmHashedString *)&local_1c,pcVar2);
      puVar3 = *(undefined4 **)(param_1 + 0x14);
      if (puVar3 == *(undefined4 **)(param_1 + 0x18)) {
        std::vector<OFSdbmHashedString,std::allocator<OFSdbmHashedString>>::_M_insert_aux
                  ((vector<OFSdbmHashedString,std::allocator<OFSdbmHashedString>> *)(param_1 + 0x10)
                   ,puVar3,&local_1c);
      }
      else {
        iVar4 = 0;
        if (puVar3 != (undefined4 *)0x0) {
          *puVar3 = local_1c;
          iVar4 = *(int *)(param_1 + 0x14);
        }
        *(int *)(param_1 + 0x14) = iVar4 + 4;
      }
      N = N + 1;
    } while (iVar1 != N);
  }
  return;
}
