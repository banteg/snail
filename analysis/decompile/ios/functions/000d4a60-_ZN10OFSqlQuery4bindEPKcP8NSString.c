/*
 * mangled: _ZN10OFSqlQuery4bindEPKcP8NSString
 * demangled: OFSqlQuery::bind(char const*, NSString*)
 * address: 000d4a60
 * size: 132
 */

/* OFSqlQuery::bind(char const*, NSString*) */

void __thiscall OFSqlQuery::bind(OFSqlQuery *this,char *param_1,NSString *param_2)

{
  ID self;
  char *pcVar1;
  int iVar2;
  sqlite3_stmt *psVar3;

  psVar3 = (sqlite3_stmt *)this->field2_0x8;
  self = NSString::stringWithFormat_
                   ((ID)&_OBJC_CLASS___NSString,"stringWithFormat:",&cf___s,param_1);
  pcVar1 = (char *)NSString::UTF8String(self,"UTF8String");
  iVar2 = _sqlite3_bind_parameter_index(psVar3,pcVar1);
  pcVar1 = (char *)_objc_msgSend((ID)param_2,"UTF8String");
  _sqlite3_bind_text(psVar3,iVar2,pcVar1,-1,(void *)0xffffffff);
  return;
}
