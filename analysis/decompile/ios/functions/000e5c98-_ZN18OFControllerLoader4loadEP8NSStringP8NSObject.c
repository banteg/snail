/*
 * mangled: _ZN18OFControllerLoader4loadEP8NSStringP8NSObject
 * demangled: OFControllerLoader::load(NSString*, NSObject*)
 * address: 000e5c98
 * size: 92
 */

/* OFControllerLoader::load(NSString*, NSObject*) */

void OFControllerLoader::load(NSString *param_1,NSObject *param_2)

{
  int iVar1;

  if ((((anonymous_namespace)::gOverrideClassNamePrefixString != (NSString *)0x0) &&
      ((anonymous_namespace)::gOverrideSuffixString != (NSString *)0x0)) &&
     (iVar1 = tryLoadController(param_1,param_2,(anonymous_namespace)::gOverrideSuffixString,
                                (anonymous_namespace)::gOverrideClassNamePrefixString), iVar1 != 0))
  {
    return;
  }
  tryLoadController(param_1,param_2,(anonymous_namespace)::gSuffixString,
                    (anonymous_namespace)::gClassNamePrefixString);
  return;
}
