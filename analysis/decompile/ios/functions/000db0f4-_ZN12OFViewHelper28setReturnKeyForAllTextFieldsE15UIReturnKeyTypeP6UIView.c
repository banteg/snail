/*
 * mangled: _ZN12OFViewHelper28setReturnKeyForAllTextFieldsE15UIReturnKeyTypeP6UIView
 * demangled: OFViewHelper::setReturnKeyForAllTextFields(UIReturnKeyType, UIView*)
 * address: 000db0f4
 * size: 236
 */

/* OFViewHelper::setReturnKeyForAllTextFields(UIReturnKeyType, UIView*) */

void OFViewHelper::setReturnKeyForAllTextFields(undefined4 param_1,ID param_2)

{
  ID self;
  ID IVar1;
  ID IVar2;
  int iVar3;

  iVar3 = 1;
  do {
    IVar1 = _objc_msgSend(param_2,"viewWithTag:",iVar3);
    IVar2 = 0;
    while( true ) {
      self = IVar1;
      if (self == 0) {
        if (IVar2 != 0) {
          _objc_msgSend(IVar2,"setReturnKeyType:",param_1);
        }
        return;
      }
      iVar3 = iVar3 + 1;
      IVar2 = UITextField::class((ID)&_OBJC_CLASS___UITextField,"class");
      IVar2 = _objc_msgSend(self,"isKindOfClass:",IVar2);
      if ((IVar2 & 0xff) == 0) break;
      _objc_msgSend(self,"setReturnKeyType:",4);
      IVar1 = _objc_msgSend(param_2,"viewWithTag:",iVar3);
      IVar2 = self;
    }
  } while( true );
}
