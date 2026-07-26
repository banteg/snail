/*
 * mangled: _ZN10OFDelegateC1EP8NSObjectP13objc_selectorS1_
 * demangled: OFDelegate::OFDelegate(NSObject*, objc_selector*, NSObject*)
 * address: 000c6050
 * size: 96
 */

/* OFDelegate::OFDelegate(NSObject*, objc_selector*, NSObject*) */

void __thiscall
OFDelegate::OFDelegate(OFDelegate *this,NSObject *param_1,objc_selector *param_2,NSObject *param_3)

{
  ID IVar1;

  this->field3_0xc = (SEL)param_2;
  IVar1 = _objc_msgSend((ID)param_1,"retain");
  this->field0_0x0 = IVar1;
  IVar1 = NSThread::mainThread((ID)&_OBJC_CLASS___NSThread,"mainThread");
  IVar1 = NSThread::retain(IVar1,"retain");
  this->field2_0x8 = IVar1;
  IVar1 = _objc_msgSend((ID)param_3,"retain");
  this->field1_0x4 = IVar1;
  return;
}
