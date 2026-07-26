/*
 * mangled: _ZN12OFViewHelper19findFirstScrollViewEP6UIView
 * demangled: OFViewHelper::findFirstScrollView(UIView*)
 * address: 000db5b8
 * size: 328
 */

/* OFViewHelper::findFirstScrollView(UIView*) */

UIView * OFViewHelper::findFirstScrollView(UIView *param_1)

{
  ID IVar1;
  ID IVar2;
  UIView *pUVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  undefined1 auStack_80 [64];
  int *local_40;
  int *local_3c;
  int *local_38;
  int *local_34;
  int *local_30;
  int *local_2c;
  int *local_28;
  int *local_24;

  IVar1 = UIScrollView::class((ID)&_OBJC_CLASS___UIScrollView,"class");
  IVar1 = _objc_msgSend((ID)param_1,"isKindOfClass:",IVar1);
  local_40 = (int *)(IVar1 & 0xff);
  pUVar3 = param_1;
  if (local_40 == (int *)0x0) {
    local_3c = local_40;
    local_38 = local_40;
    local_34 = local_40;
    local_30 = local_40;
    local_2c = local_40;
    local_28 = local_40;
    local_24 = local_40;
    IVar1 = _objc_msgSend((ID)param_1,"subviews");
    IVar2 = _objc_msgSend(IVar1,"countByEnumeratingWithState:objects:count:",&local_40,auStack_80,
                          0x10);
    if (IVar2 == 0) {
      pUVar3 = (UIView *)0x0;
    }
    else {
      iVar6 = *local_38;
      iVar4 = iVar6;
      while( true ) {
        uVar5 = 0;
        while( true ) {
          if (iVar6 != iVar4) {
            _objc_msgSend((ID)param_1,"subviews");
            _objc_enumerationMutation();
          }
          pUVar3 = (UIView *)findFirstScrollView((UIView *)local_3c[uVar5]);
          if (pUVar3 != (UIView *)0x0) {
            return pUVar3;
          }
          uVar5 = uVar5 + 1;
          if (IVar2 <= uVar5) break;
          iVar4 = *local_38;
        }
        IVar2 = _objc_msgSend(IVar1,"countByEnumeratingWithState:objects:count:",&local_40,
                              auStack_80,0x10);
        pUVar3 = (UIView *)0x0;
        if (IVar2 == 0) break;
        iVar4 = *local_38;
      }
    }
  }
  return pUVar3;
}
