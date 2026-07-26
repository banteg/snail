/*
 * mangled: _ZL17tryLoadControllerP8NSStringP8NSObjectS0_S0_
 * demangled: tryLoadController(NSString*, NSObject*, NSString*, NSString*)
 * address: 000e5b1c
 * size: 332
 */

/* tryLoadController(NSString*, NSObject*, NSString*, NSString*) */

UIViewController *
tryLoadController(NSString *param_1,NSObject *param_2,NSString *param_3,NSString *param_4)

{
  ID IVar1;
  NSString *pNVar2;
  UIViewController *pUVar3;
  int iVar4;
  cfstringStruct *pcVar5;

  IVar1 = _objc_msgSend((ID)&objc::class_t::OpenFeint,"isLargeScreen");
  if ((IVar1 & 0xff) == 0) {
    IVar1 = _objc_msgSend((ID)&objc::class_t::OpenFeint,"isInLandscapeMode");
    if ((IVar1 & 0xff) == 0) goto LAB_000e5bc0;
    pcVar5 = &cf___ControllerLandscape__;
  }
  else {
    pcVar5 = &cf___ControllerIPad__;
  }
  pNVar2 = (NSString *)
           NSString::stringWithFormat_
                     ((ID)&_OBJC_CLASS___NSString,"stringWithFormat:",pcVar5,param_1,param_3);
  pUVar3 = loadObjectFromNib<UIViewController>(pNVar2,(objc_object *)param_2);
  if (pUVar3 != (UIViewController *)0x0) {
    return pUVar3;
  }
LAB_000e5bc0:
  pNVar2 = (NSString *)
           NSString::stringWithFormat_
                     ((ID)&_OBJC_CLASS___NSString,"stringWithFormat:",&cf___Controller__,param_1,
                      param_3);
  pUVar3 = loadObjectFromNib<UIViewController>(pNVar2,(objc_object *)param_2);
  if (pUVar3 == (UIViewController *)0x0) {
    IVar1 = NSString::stringWithFormat_
                      ((ID)&_OBJC_CLASS___NSString,"stringWithFormat:",&cf_____Controller,param_4,
                       param_1);
    NSString::UTF8String(IVar1,"UTF8String");
    iVar4 = _objc_lookUpClass();
    if (iVar4 != 0) {
      pUVar3 = (UIViewController *)_class_createInstance(iVar4,0);
      _objc_msgSend((ID)pUVar3,"init");
      _objc_msgSend((ID)pUVar3,"autorelease");
    }
  }
  return pUVar3;
}
