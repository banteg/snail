/*
 * mangled: _ZN18OFControllerLoader26setOverrideAssetFileSuffixEP8NSString
 * demangled: OFControllerLoader::setOverrideAssetFileSuffix(NSString*)
 * address: 000e5794
 * size: 56
 */

/* OFControllerLoader::setOverrideAssetFileSuffix(NSString*) */

void OFControllerLoader::setOverrideAssetFileSuffix(NSString *param_1)

{
  _objc_msgSend((anonymous_namespace)::gOverrideSuffixString,"release");
  (anonymous_namespace)::gOverrideSuffixString = _objc_msgSend((ID)param_1,"retain");
  return;
}
