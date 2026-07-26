/*
 * mangled: _ZN10OFSqlQuery4bindEPKcPKvj
 * demangled: OFSqlQuery::bind(char const*, void const*, unsigned int)
 * address: 000d49a8
 * size: 116
 */

/* OFSqlQuery::bind(char const*, void const*, unsigned int) */

void __thiscall OFSqlQuery::bind(OFSqlQuery *this,char *param_1,void *param_2,uint param_3)

{
  ID self;
  char *zName;
  int iVar1;
  sqlite3_stmt *psVar2;

  psVar2 = (sqlite3_stmt *)this->field2_0x8;
  self = NSString::stringWithFormat_
                   ((ID)&_OBJC_CLASS___NSString,"stringWithFormat:",&cf___s,param_1);
  zName = (char *)NSString::UTF8String(self,"UTF8String");
  iVar1 = _sqlite3_bind_parameter_index(psVar2,zName);
  _sqlite3_bind_blob(psVar2,iVar1,param_2,param_3,(void *)0xffffffff);
  return;
}
