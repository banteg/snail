/*
 * mangled: _ZN12OFViewHelper20resignFirstResponderEP6UIView
 * demangled: OFViewHelper::resignFirstResponder(UIView*)
 * address: 000db714
 * size: 384
 */

/* OFViewHelper::resignFirstResponder(UIView*) */

undefined4 OFViewHelper::resignFirstResponder(UIView *param_1)

{
  ID IVar1;
  ID IVar2;
  int iVar3;
  undefined4 uVar4;
  uint uVar5;
  int iVar6;
  undefined1 auStack_80 [64];
  undefined4 local_40;
  int local_3c;
  int *local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;

  IVar1 = UIResponder::class((ID)&_OBJC_CLASS___UIResponder,"class");
  IVar1 = _objc_msgSend((ID)param_1,"isKindOfClass:",IVar1);
  if (((IVar1 & 0xff) == 0) ||
     (IVar1 = _objc_msgSend((ID)param_1,"isFirstResponder"), (IVar1 & 0xff) == 0)) {
    local_40 = 0;
    local_3c = 0;
    local_38 = (int *)0x0;
    local_34 = 0;
    local_30 = 0;
    local_2c = 0;
    local_28 = 0;
    local_24 = 0;
    IVar1 = _objc_msgSend((ID)param_1,"subviews");
    IVar2 = _objc_msgSend(IVar1,"countByEnumeratingWithState:objects:count:",&local_40,auStack_80,
                          0x10);
    if (IVar2 != 0) {
      iVar6 = *local_38;
      iVar3 = iVar6;
      while( true ) {
        uVar5 = 0;
        while( true ) {
          if (iVar6 != iVar3) {
            _objc_msgSend((ID)param_1,"subviews");
            _objc_enumerationMutation();
          }
          iVar3 = resignFirstResponder(*(UIView **)(local_3c + uVar5 * 4));
          if (iVar3 != 0) {
            return 1;
          }
          uVar5 = uVar5 + 1;
          if (IVar2 <= uVar5) break;
          iVar3 = *local_38;
        }
        IVar2 = _objc_msgSend(IVar1,"countByEnumeratingWithState:objects:count:",&local_40,
                              auStack_80,0x10);
        if (IVar2 == 0) break;
        iVar3 = *local_38;
      }
    }
    uVar4 = 0;
  }
  else {
    _objc_msgSend((ID)param_1,"resignFirstResponder");
    uVar4 = 1;
  }
  return uVar4;
}
