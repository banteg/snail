/*
 * mangled: _ZN12OFViewHelper13findViewByTagEP6UIViewi
 * demangled: OFViewHelper::findViewByTag(UIView*, int)
 * address: 000db27c
 * size: 312
 */

/* OFViewHelper::findViewByTag(UIView*, int) */

UIView * OFViewHelper::findViewByTag(UIView *param_1,int param_2)

{
  ID IVar1;
  ID IVar2;
  UIView *pUVar3;
  int iVar4;
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

  IVar1 = _objc_msgSend((ID)param_1,"tag");
  if (IVar1 != param_2) {
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
      iVar4 = iVar6;
      while( true ) {
        uVar5 = 0;
        while( true ) {
          if (iVar6 != iVar4) {
            _objc_msgSend((ID)param_1,"subviews");
            _objc_enumerationMutation();
          }
          pUVar3 = (UIView *)findViewByTag(*(UIView **)(local_3c + uVar5 * 4),param_2);
          if (pUVar3 != (UIView *)0x0) {
            return pUVar3;
          }
          uVar5 = uVar5 + 1;
          if (IVar2 <= uVar5) break;
          iVar4 = *local_38;
        }
        IVar2 = _objc_msgSend(IVar1,"countByEnumeratingWithState:objects:count:",&local_40,
                              auStack_80,0x10);
        if (IVar2 == 0) break;
        iVar4 = *local_38;
      }
    }
    param_1 = (UIView *)0x0;
  }
  return param_1;
}
