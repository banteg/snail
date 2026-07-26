/*
 * mangled: _Z17loadObjectFromNibI16UIViewControllerEPT_P8NSStringP11objc_object
 * demangled: UIViewController* loadObjectFromNib<UIViewController>(NSString*, objc_object*)
 * address: 000e5520
 * size: 244
 */

/* UIViewController* loadObjectFromNib<UIViewController>(NSString*, objc_object*) */

UIViewController * loadObjectFromNib<UIViewController>(NSString *param_1,objc_object *param_2)

{
  ID IVar1;
  UIViewController *self;
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
      return (UIViewController *)0x0;
    }
    self = (UIViewController *)NSBundle::objectAtIndex_(IVar1,"objectAtIndex:",uVar3);
    IVar2 = UIViewController::class((ID)&_OBJC_CLASS___UIViewController,"class");
    IVar2 = NSBundle::isKindOfClass_((ID)self,"isKindOfClass:",IVar2);
    if ((IVar2 & 0xff) != 0) break;
    uVar3 = uVar3 + 1;
  }
  return self;
}
