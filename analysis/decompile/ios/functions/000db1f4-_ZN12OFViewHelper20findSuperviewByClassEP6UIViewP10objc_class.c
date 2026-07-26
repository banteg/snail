/*
 * mangled: _ZN12OFViewHelper20findSuperviewByClassEP6UIViewP10objc_class
 * demangled: OFViewHelper::findSuperviewByClass(UIView*, objc_class*)
 * address: 000db1f4
 * size: 128
 */

/* OFViewHelper::findSuperviewByClass(UIView*, objc_class*) */

UIView * OFViewHelper::findSuperviewByClass(UIView *param_1,objc_class *param_2)

{
  ID IVar1;
  UIView *pUVar2;

  pUVar2 = param_1;
  if (param_1 != (UIView *)0x0) {
    pUVar2 = (UIView *)0x0;
    do {
      IVar1 = _objc_msgSend((ID)param_1,"isKindOfClass:",param_2);
      if ((IVar1 & 0xff) != 0) {
        pUVar2 = param_1;
      }
      param_1 = (UIView *)_objc_msgSend((ID)param_1,"superview");
    } while (pUVar2 == (UIView *)0x0 && param_1 != (UIView *)0x0);
  }
  return pUVar2;
}
