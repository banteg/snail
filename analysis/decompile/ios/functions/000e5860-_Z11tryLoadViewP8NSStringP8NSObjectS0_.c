/*
 * mangled: _Z11tryLoadViewP8NSStringP8NSObjectS0_
 * demangled: tryLoadView(NSString*, NSObject*, NSString*)
 * address: 000e5860
 * size: 248
 */

/* tryLoadView(NSString*, NSObject*, NSString*) */

void tryLoadView(NSString *param_1,NSObject *param_2,NSString *param_3)

{
  ID IVar1;
  NSString *pNVar2;
  UIView *pUVar3;

  IVar1 = _objc_msgSend((ID)&objc::class_t::OpenFeint,"isLargeScreen");
  if ((IVar1 & 0xff) != 0) {
    pNVar2 = (NSString *)
             NSString::stringWithFormat_
                       ((ID)&_OBJC_CLASS___NSString,"stringWithFormat:",&cf___IPad__,param_1,param_3
                       );
    pUVar3 = loadObjectFromNib<UIView>(pNVar2,(objc_object *)param_2);
    if (pUVar3 != (UIView *)0x0) {
      return;
    }
  }
  IVar1 = _objc_msgSend((ID)&objc::class_t::OpenFeint,"isInLandscapeMode");
  if ((IVar1 & 0xff) != 0) {
    pNVar2 = (NSString *)
             NSString::stringWithFormat_
                       ((ID)&_OBJC_CLASS___NSString,"stringWithFormat:",&cf___Landscape__,param_1,
                        param_3);
    pUVar3 = loadObjectFromNib<UIView>(pNVar2,(objc_object *)param_2);
    if (pUVar3 != (UIView *)0x0) {
      return;
    }
  }
  pNVar2 = (NSString *)
           NSString::stringWithFormat_
                     ((ID)&_OBJC_CLASS___NSString,"stringWithFormat:",&cf_____,param_1,param_3);
  loadObjectFromNib<UIView>(pNVar2,(objc_object *)param_2);
  return;
}
