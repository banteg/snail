/*
 * mangled: _ZN18OFControllerLoader24loadWithParamsDictionaryEP8NSStringP12NSDictionaryP8NSObject
 * demangled: OFControllerLoader::loadWithParamsDictionary(NSString*, NSDictionary*, NSObject*)
 * address: 000e6024
 * size: 684
 */

/* OFControllerLoader::loadWithParamsDictionary(NSString*, NSDictionary*, NSObject*) */

ID OFControllerLoader::loadWithParamsDictionary
             (NSString *param_1,NSDictionary *param_2,NSObject *param_3)

{
  ID self;
  ID IVar1;
  ID IVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  ID self_00;
  int iVar6;
  uint local_a0;
  undefined1 auStack_80 [64];
  int *local_40;
  int *local_3c;
  int *local_38;
  int *local_34;
  int *local_30;
  int *local_2c;
  int *local_28;
  int *local_24;

  if (((((anonymous_namespace)::gOverrideClassNamePrefixString != (NSString *)0x0) &&
       ((anonymous_namespace)::gOverrideSuffixString != (NSString *)0x0)) &&
      (self = tryLoadController(param_1,param_3,(anonymous_namespace)::gOverrideSuffixString,
                                (anonymous_namespace)::gOverrideClassNamePrefixString), self != 0))
     || (self = tryLoadController(param_1,param_3,(anonymous_namespace)::gSuffixString,
                                  (anonymous_namespace)::gClassNamePrefixString), self != 0)) {
    IVar1 = _objc_msgSend(self,"respondsToSelector:","customLoader:");
    local_40 = (int *)(IVar1 & 0xff);
    if (local_40 == (int *)0x0) {
      local_3c = local_40;
      local_38 = local_40;
      local_34 = local_40;
      local_30 = local_40;
      local_2c = local_40;
      local_28 = local_40;
      local_24 = local_40;
      local_a0 = _objc_msgSend((ID)param_2,"countByEnumeratingWithState:objects:count:",&local_40,
                               auStack_80,0x10);
      if (local_a0 != 0) {
        iVar4 = *local_38;
        iVar5 = iVar4;
        while( true ) {
          iVar6 = 0;
          while( true ) {
            if (iVar4 != iVar5) {
              _objc_enumerationMutation(param_2);
            }
            self_00 = local_3c[iVar6];
            IVar1 = _objc_msgSend(self_00,"substringToIndex:",1);
            IVar2 = _objc_msgSend(self_00,"substringFromIndex:",1);
            IVar1 = _objc_msgSend(IVar1,"capitalizedString");
            NSString::stringWithFormat_
                      ((ID)&_OBJC_CLASS___NSString,"stringWithFormat:",&cf_set_____,IVar1,IVar2);
            uVar3 = _NSSelectorFromString();
            IVar1 = _objc_msgSend(self,"respondsToSelector:",uVar3);
            if ((IVar1 & 0xff) == 0) {
              IVar1 = _objc_msgSend((ID)param_2,"objectForKey:",self_00);
              _NSLog(&cf_ControllerLoaderreceivedunknownkey_____,self_00,IVar1);
            }
            else {
              IVar1 = _objc_msgSend((ID)param_2,"objectForKey:",self_00);
              _objc_msgSend(self,"performSelector:withObject:",uVar3,IVar1);
            }
            if (local_a0 <= iVar6 + 1U) break;
            iVar6 = iVar6 + 1;
            iVar5 = *local_38;
          }
          local_a0 = _objc_msgSend((ID)param_2,"countByEnumeratingWithState:objects:count:",
                                   &local_40,auStack_80,0x10);
          if (local_a0 == 0) break;
          iVar5 = *local_38;
        }
      }
    }
    else {
      _objc_msgSend(self,"performSelector:withObject:","customLoader:",param_2);
    }
  }
  return self;
}
