/*
 * mangled: _ZN23OFTransactionalSaveFile18getSavePathForFileEP8NSString
 * demangled: OFTransactionalSaveFile::getSavePathForFile(NSString*)
 * address: 000cd4d4
 * size: 64
 */

/* OFTransactionalSaveFile::getSavePathForFile(NSString*) */

void OFTransactionalSaveFile::getSavePathForFile(NSString *param_1)

{
  ID IVar1;

  IVar1 = _NSSearchPathForDirectoriesInDomains(9,1,1);
  IVar1 = _objc_msgSend(IVar1,"objectAtIndex:",0);
  _objc_msgSend(IVar1,"stringByAppendingPathComponent:",param_1);
  return;
}
