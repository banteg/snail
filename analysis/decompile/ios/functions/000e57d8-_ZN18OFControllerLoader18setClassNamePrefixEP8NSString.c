/*
 * mangled: _ZN18OFControllerLoader18setClassNamePrefixEP8NSString
 * demangled: OFControllerLoader::setClassNamePrefix(NSString*)
 * address: 000e57d8
 * size: 56
 */

/* OFControllerLoader::setClassNamePrefix(NSString*) */

void OFControllerLoader::setClassNamePrefix(NSString *param_1)

{
  _objc_msgSend((anonymous_namespace)::gClassNamePrefixString,"release");
  (anonymous_namespace)::gClassNamePrefixString = _objc_msgSend((ID)param_1,"retain");
  return;
}
