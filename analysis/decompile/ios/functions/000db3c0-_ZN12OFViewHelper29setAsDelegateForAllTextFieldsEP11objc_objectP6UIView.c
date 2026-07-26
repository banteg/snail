/*
 * mangled: _ZN12OFViewHelper29setAsDelegateForAllTextFieldsEP11objc_objectP6UIView
 * demangled: OFViewHelper::setAsDelegateForAllTextFields(objc_object*, UIView*)
 * address: 000db3c0
 * size: 472
 */

/* OFViewHelper::setAsDelegateForAllTextFields(objc_object*, UIView*) */

void OFViewHelper::setAsDelegateForAllTextFields(objc_object *param_1,UIView *param_2)

{
  ID self;
  ID IVar1;
  ID IVar2;
  int iVar3;
  int iVar4;
  UIView *self_00;
  int iVar5;
  undefined1 local_80 [64];
  undefined4 local_40;
  int local_3c;
  int *local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;

  local_40 = 0;
  local_3c = 0;
  local_38 = (int *)0x0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  self = _objc_msgSend((ID)param_2,"subviews");
  IVar1 = _objc_msgSend(self,"countByEnumeratingWithState:objects:count:",&local_40,local_80,0x10);
  if (IVar1 == 0) {
    return;
  }
  iVar3 = *local_38;
  iVar4 = iVar3;
LAB_000db490:
  iVar5 = 0;
  do {
    if (iVar3 != iVar4) {
      _objc_msgSend((ID)param_2,"subviews");
      _objc_enumerationMutation();
    }
    self_00 = *(UIView **)(local_3c + iVar5 * 4);
    IVar2 = UITextField::class((ID)&_OBJC_CLASS___UITextField,"class");
    IVar2 = _objc_msgSend((ID)self_00,"isKindOfClass:",IVar2);
    if ((IVar2 & 0xff) == 0) {
      IVar2 = UITextView::class((ID)&_OBJC_CLASS___UITextView,"class");
      IVar2 = _objc_msgSend((ID)self_00,"isKindOfClass:",IVar2);
      if ((IVar2 & 0xff) != 0) goto LAB_000db520;
LAB_000db4bc:
      setAsDelegateForAllTextFields(param_1,self_00);
    }
    else {
LAB_000db520:
      IVar2 = _objc_msgSend((ID)self_00,"delegate");
      if (IVar2 != 0) goto LAB_000db4bc;
      _objc_msgSend((ID)self_00,"setDelegate:",param_1);
      setAsDelegateForAllTextFields(param_1,self_00);
    }
    if (IVar1 <= iVar5 + 1U) break;
    iVar5 = iVar5 + 1;
    iVar4 = *local_38;
  } while( true );
  IVar1 = _objc_msgSend(self,"countByEnumeratingWithState:objects:count:",&local_40,local_80,0x10);
  if (IVar1 == 0) {
    return;
  }
  iVar4 = *local_38;
  goto LAB_000db490;
}
