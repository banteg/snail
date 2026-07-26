/*
 * mangled: _ZN18OFControllerLoader26setOverrideClassNamePrefixEP8NSString
 * demangled: OFControllerLoader::setOverrideClassNamePrefix(NSString*)
 * address: 000e5750
 * size: 56
 */

/* OFControllerLoader::setOverrideClassNamePrefix(NSString*) */

void OFControllerLoader::setOverrideClassNamePrefix(NSString *param_1)

{
  _objc_msgSend((anonymous_namespace)::gOverrideClassNamePrefixString,"release");
  (anonymous_namespace)::gOverrideClassNamePrefixString = _objc_msgSend((ID)param_1,"retain");
  return;
}
