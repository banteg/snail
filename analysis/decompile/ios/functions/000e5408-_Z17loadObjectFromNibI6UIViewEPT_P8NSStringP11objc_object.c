/*
 * mangled: _Z17loadObjectFromNibI6UIViewEPT_P8NSStringP11objc_object
 * demangled: UIView* loadObjectFromNib<UIView>(NSString*, objc_object*)
 * address: 000e5408
 * size: 244
 */

/* UIView* loadObjectFromNib<UIView>(NSString*, objc_object*) */

UIView * loadObjectFromNib<UIView>(NSString *param_1,objc_object *param_2)

{
  ID IVar1;
  UIView *self;
  ID IVar2;
  cfstringStruct *unaff_r4;
  uint uVar3;

  if (param_2 != (objc_object *)0x0) {
    unaff_r4 = (cfstringStruct *)param_2;
  }
  uVar3 = 0;
  if (param_2 == (objc_object *)0x0) {
    unaff_r4 = &cf___;
  }
  IVar1 = NSBundle::mainBundle((ID)&_OBJC_CLASS___NSBundle,"mainBundle");
  IVar1 = NSBundle::loadNibNamed_owner_options_
                    (IVar1,"loadNibNamed:owner:options:",param_1,unaff_r4,0);
  while( true ) {
    IVar2 = NSBundle::count(IVar1,"count");
    if (IVar2 <= uVar3) {
      return (UIView *)0x0;
    }
    self = (UIView *)NSBundle::objectAtIndex_(IVar1,"objectAtIndex:",uVar3);
    IVar2 = _objc_msgSend((ID)&_OBJC_CLASS___UIView,"class");
    IVar2 = NSBundle::isKindOfClass_((ID)self,"isKindOfClass:",IVar2);
    if ((IVar2 & 0xff) != 0) break;
    uVar3 = uVar3 + 1;
  }
  return self;
}
