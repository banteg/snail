/*
 * mangled: _ZN18OFControllerLoader18setAssetFileSuffixEP8NSString
 * demangled: OFControllerLoader::setAssetFileSuffix(NSString*)
 * address: 000e581c
 * size: 56
 */

/* OFControllerLoader::setAssetFileSuffix(NSString*) */

void OFControllerLoader::setAssetFileSuffix(NSString *param_1)

{
  _objc_msgSend((anonymous_namespace)::gSuffixString,"release");
  (anonymous_namespace)::gSuffixString = _objc_msgSend((ID)param_1,"retain");
  return;
}
