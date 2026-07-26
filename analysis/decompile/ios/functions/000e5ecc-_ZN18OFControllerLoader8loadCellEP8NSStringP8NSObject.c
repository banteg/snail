/*
 * mangled: _ZN18OFControllerLoader8loadCellEP8NSStringP8NSObject
 * demangled: OFControllerLoader::loadCell(NSString*, NSObject*)
 * address: 000e5ecc
 * size: 308
 */

/* OFControllerLoader::loadCell(NSString*, NSObject*) */

ID OFControllerLoader::loadCell(NSString *param_1,NSObject *param_2)

{
  ID self;
  uint uVar1;
  float fVar2;
  undefined4 local_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined4 local_4c;
  undefined4 uStack_48;
  undefined4 local_44;
  float fStack_40;
  undefined4 local_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  float local_30;
  undefined auStack_2c [12];
  float local_20;

  if ((((anonymous_namespace)::gOverrideClassNamePrefixString == (NSString *)0x0) ||
      ((anonymous_namespace)::gOverrideSuffixString == (NSString *)0x0)) ||
     (self = tryLoadCell(param_1,param_2,(anonymous_namespace)::gOverrideSuffixString,
                         (anonymous_namespace)::gOverrideClassNamePrefixString), self == 0)) {
    self = tryLoadCell(param_1,param_2,(anonymous_namespace)::gSuffixString,
                       (anonymous_namespace)::gClassNamePrefixString);
    uVar1 = _objc_msgSend((ID)&objc::class_t::OpenFeint,"isLargeScreen");
  }
  else {
    uVar1 = _objc_msgSend((ID)&objc::class_t::OpenFeint,"isLargeScreen");
  }
  if ((uVar1 & 0xff) != 0) {
    fVar2 = 60.0;
    _objc_msgSend_stret(auStack_2c,self,"frame");
    if (local_20 < fVar2) {
      _objc_msgSend_stret((undefined *)&local_5c,self,"frame");
      local_3c = local_5c;
      uStack_38 = uStack_58;
      uStack_34 = uStack_54;
      local_4c = local_5c;
      uStack_48 = uStack_58;
      local_44 = uStack_54;
      fStack_40 = fVar2;
      local_30 = fVar2;
      _objc_msgSend(self,"setFrame:",local_5c,uStack_58,uStack_54,fVar2);
    }
  }
  return self;
}
