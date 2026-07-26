/*
 * mangled: _ZN10OFSqlQuery6getIntEPKc
 * demangled: OFSqlQuery::getInt(char const*)
 * address: 000d4ba0
 * size: 136
 */

/* OFSqlQuery::getInt(char const*) */

void __thiscall OFSqlQuery::getInt(OFSqlQuery *this,char *param_1)

{
  int iVar1;
  OFSdbmHashedString *pOVar2;
  uint uVar3;
  uint iCol;
  OFSdbmHashedString aOStack_14 [4];

  OFSdbmHashedString::OFSdbmHashedString(aOStack_14,param_1);
  pOVar2 = (this->field4_0x10).field0_0x0.field0_0x0;
  if ((int)(this->field4_0x10).field0_0x0.field1_0x4 - (int)pOVar2 >> 2 == 0) {
    iCol = 0;
  }
  else {
    uVar3 = 0;
    do {
      iCol = uVar3;
      iVar1 = OFSdbmHashedString::operator==(pOVar2 + iCol * 4,aOStack_14);
      if (iVar1 != 0) break;
      pOVar2 = (this->field4_0x10).field0_0x0.field0_0x0;
      uVar3 = iCol + 1;
      iCol = (int)(this->field4_0x10).field0_0x0.field1_0x4 - (int)pOVar2 >> 2;
    } while (uVar3 < iCol);
  }
  _sqlite3_column_int((sqlite3_stmt *)this->field2_0x8,iCol);
  return;
}
