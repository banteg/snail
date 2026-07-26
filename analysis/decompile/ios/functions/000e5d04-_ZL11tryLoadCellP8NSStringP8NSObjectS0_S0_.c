/*
 * mangled: _ZL11tryLoadCellP8NSStringP8NSObjectS0_S0_
 * demangled: tryLoadCell(NSString*, NSObject*, NSString*, NSString*)
 * address: 000e5d04
 * size: 396
 */

/* tryLoadCell(NSString*, NSObject*, NSString*, NSString*) */

UITableViewCell *
tryLoadCell(NSString *param_1,NSObject *param_2,NSString *param_3,NSString *param_4)

{
  ID IVar1;
  NSString *pNVar2;
  UITableViewCell *pUVar3;
  int iVar4;
  cfstringStruct *pcVar5;

  IVar1 = _objc_msgSend((ID)&objc::class_t::OpenFeint,"isLargeScreen");
  if ((IVar1 & 0xff) == 0) {
    IVar1 = _objc_msgSend((ID)&objc::class_t::OpenFeint,"isInLandscapeMode");
    if ((IVar1 & 0xff) == 0) goto LAB_000e5da8;
    pcVar5 = &cf___LandscapeCell__;
  }
  else {
    pcVar5 = &cf___IPadCell__;
  }
  pNVar2 = (NSString *)
           NSString::stringWithFormat_
                     ((ID)&_OBJC_CLASS___NSString,"stringWithFormat:",pcVar5,param_1,param_3);
  pUVar3 = loadObjectFromNib<UITableViewCell>(pNVar2,(objc_object *)param_2);
  if (pUVar3 != (UITableViewCell *)0x0) {
    return pUVar3;
  }
LAB_000e5da8:
  pNVar2 = (NSString *)
           NSString::stringWithFormat_
                     ((ID)&_OBJC_CLASS___NSString,"stringWithFormat:",&cf___Cell__,param_1,param_3);
  pUVar3 = loadObjectFromNib<UITableViewCell>(pNVar2,(objc_object *)param_2);
  if (pUVar3 == (UITableViewCell *)0x0) {
    IVar1 = NSString::stringWithFormat_
                      ((ID)&_OBJC_CLASS___NSString,"stringWithFormat:",&cf_____Cell,param_4,param_1)
    ;
    NSString::UTF8String(IVar1,"UTF8String");
    iVar4 = _objc_lookUpClass();
    if (iVar4 != 0) {
      pUVar3 = (UITableViewCell *)_class_createInstance(iVar4,0);
      _objc_msgSend((ID)pUVar3,"initOFTableCellHelper:",param_1);
      _objc_msgSend((ID)pUVar3,"autorelease");
      IVar1 = _objc_msgSend((ID)pUVar3,"respondsToSelector:","setOwner:");
      if ((IVar1 & 0xff) != 0) {
        _objc_msgSend((ID)pUVar3,"performSelector:withObject:","setOwner:",param_2);
      }
    }
  }
  return pUVar3;
}
