/*
 * mangled: _Z17loadObjectFromNibI15UITableViewCellEPT_P8NSStringP11objc_object
 * demangled: UITableViewCell* loadObjectFromNib<UITableViewCell>(NSString*, objc_object*)
 * address: 000e5638
 * size: 244
 */

/* UITableViewCell* loadObjectFromNib<UITableViewCell>(NSString*, objc_object*) */

UITableViewCell * loadObjectFromNib<UITableViewCell>(NSString *param_1,objc_object *param_2)

{
  ID IVar1;
  UITableViewCell *self;
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
      return (UITableViewCell *)0x0;
    }
    self = (UITableViewCell *)NSBundle::objectAtIndex_(IVar1,"objectAtIndex:",uVar3);
    IVar2 = UITableViewCell::class((ID)&_OBJC_CLASS___UITableViewCell,"class");
    IVar2 = NSBundle::isKindOfClass_((ID)self,"isKindOfClass:",IVar2);
    if ((IVar2 & 0xff) != 0) break;
    uVar3 = uVar3 + 1;
  }
  return self;
}
