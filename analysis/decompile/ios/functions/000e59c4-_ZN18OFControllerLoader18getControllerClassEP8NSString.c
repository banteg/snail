/*
 * mangled: _ZN18OFControllerLoader18getControllerClassEP8NSString
 * demangled: OFControllerLoader::getControllerClass(NSString*)
 * address: 000e59c4
 * size: 148
 */

/* OFControllerLoader::getControllerClass(NSString*) */

void OFControllerLoader::getControllerClass(NSString *param_1)

{
  ID IVar1;
  int iVar2;

  IVar1 = NSString::stringWithFormat_
                    ((ID)&_OBJC_CLASS___NSString,"stringWithFormat:",&cf_____Controller,
                     (anonymous_namespace)::gOverrideClassNamePrefixString,param_1);
  NSString::UTF8String(IVar1,"UTF8String");
  iVar2 = _objc_lookUpClass();
  if (iVar2 == 0) {
    IVar1 = NSString::stringWithFormat_
                      ((ID)&_OBJC_CLASS___NSString,"stringWithFormat:",&cf_____Controller,
                       (anonymous_namespace)::gClassNamePrefixString,param_1);
    NSString::UTF8String(IVar1,"UTF8String");
    _objc_lookUpClass();
  }
  return;
}
