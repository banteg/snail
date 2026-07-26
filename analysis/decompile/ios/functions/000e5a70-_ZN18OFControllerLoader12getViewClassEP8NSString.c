/*
 * mangled: _ZN18OFControllerLoader12getViewClassEP8NSString
 * demangled: OFControllerLoader::getViewClass(NSString*)
 * address: 000e5a70
 * size: 148
 */

/* OFControllerLoader::getViewClass(NSString*) */

void OFControllerLoader::getViewClass(NSString *param_1)

{
  ID IVar1;
  int iVar2;

  IVar1 = NSString::stringWithFormat_
                    ((ID)&_OBJC_CLASS___NSString,"stringWithFormat:",&cf_____View,
                     (anonymous_namespace)::gOverrideClassNamePrefixString,param_1);
  NSString::UTF8String(IVar1,"UTF8String");
  iVar2 = _objc_lookUpClass();
  if (iVar2 == 0) {
    IVar1 = NSString::stringWithFormat_
                      ((ID)&_OBJC_CLASS___NSString,"stringWithFormat:",&cf_____View,
                       (anonymous_namespace)::gClassNamePrefixString,param_1);
    NSString::UTF8String(IVar1,"UTF8String");
    _objc_lookUpClass();
  }
  return;
}
