/*
 * mangled: _ZN18OFControllerLoader8loadViewEP8NSStringP8NSObject
 * demangled: OFControllerLoader::loadView(NSString*, NSObject*)
 * address: 000e5978
 * size: 68
 */

/* OFControllerLoader::loadView(NSString*, NSObject*) */

void OFControllerLoader::loadView(NSString *param_1,NSObject *param_2)

{
  int iVar1;

  if (((anonymous_namespace)::gOverrideSuffixString != (NSString *)0x0) &&
     (iVar1 = tryLoadView(param_1,param_2,(anonymous_namespace)::gOverrideSuffixString), iVar1 != 0)
     ) {
    return;
  }
  tryLoadView(param_1,param_2,(anonymous_namespace)::gSuffixString);
  return;
}
