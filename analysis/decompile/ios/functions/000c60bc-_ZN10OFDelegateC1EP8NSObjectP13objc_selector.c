/*
 * mangled: _ZN10OFDelegateC1EP8NSObjectP13objc_selector
 * demangled: OFDelegate::OFDelegate(NSObject*, objc_selector*)
 * address: 000c60bc
 * size: 84
 */

/* OFDelegate::OFDelegate(NSObject*, objc_selector*) */

void __thiscall OFDelegate::OFDelegate(OFDelegate *this,NSObject *param_1,objc_selector *param_2)

{
  ID IVar1;

  this->field1_0x4 = 0;
  this->field3_0xc = (SEL)param_2;
  IVar1 = _objc_msgSend((ID)param_1,"retain");
  this->field0_0x0 = IVar1;
  IVar1 = NSThread::mainThread((ID)&_OBJC_CLASS___NSThread,"mainThread");
  IVar1 = NSThread::retain(IVar1,"retain");
  this->field2_0x8 = IVar1;
  return;
}
