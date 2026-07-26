/*
 * mangled: _ZN10OFSqlQuery7getBlobEPKcRS1_Rj
 * demangled: OFSqlQuery::getBlob(char const*, char const*&, unsigned int&)
 * address: 000d4af4
 * size: 172
 */

/* OFSqlQuery::getBlob(char const*, char const*&, unsigned int&) */

void __thiscall OFSqlQuery::getBlob(OFSqlQuery *this,char *param_1,char **param_2,uint *param_3)

{
  int iVar1;
  char *pcVar2;
  uint uVar3;
  OFSdbmHashedString *pOVar4;
  uint uVar5;
  OFSdbmHashedString aOStack_1c [4];

  OFSdbmHashedString::OFSdbmHashedString(aOStack_1c,param_1);
  pOVar4 = (this->field4_0x10).field0_0x0.field0_0x0;
  if ((int)(this->field4_0x10).field0_0x0.field1_0x4 - (int)pOVar4 >> 2 == 0) {
    uVar3 = 0;
  }
  else {
    uVar5 = 0;
    do {
      uVar3 = uVar5;
      iVar1 = OFSdbmHashedString::operator==(pOVar4 + uVar3 * 4,aOStack_1c);
      if (iVar1 != 0) break;
      pOVar4 = (this->field4_0x10).field0_0x0.field0_0x0;
      uVar5 = uVar3 + 1;
      uVar3 = (int)(this->field4_0x10).field0_0x0.field1_0x4 - (int)pOVar4 >> 2;
    } while (uVar5 < uVar3);
  }
  pcVar2 = _sqlite3_column_blob((sqlite3_stmt *)this->field2_0x8,uVar3);
  *param_2 = pcVar2;
  uVar3 = _sqlite3_column_bytes((sqlite3_stmt *)this->field2_0x8,uVar3);
  *param_3 = uVar3;
  return;
}
