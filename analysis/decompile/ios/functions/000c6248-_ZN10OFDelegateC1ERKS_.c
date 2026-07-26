/*
 * mangled: _ZN10OFDelegateC1ERKS_
 * demangled: OFDelegate::OFDelegate(OFDelegate const&)
 * address: 000c6248
 * size: 84
 */

/* OFDelegate::OFDelegate(OFDelegate const&) */

void __thiscall OFDelegate::OFDelegate(OFDelegate *this,OFDelegate *param_1)

{
  ID IVar1;

  this->field3_0xc = param_1->field3_0xc;
  IVar1 = _objc_msgSend(param_1->field0_0x0,"retain");
  this->field0_0x0 = IVar1;
  IVar1 = _objc_msgSend(param_1->field2_0x8,"retain");
  this->field2_0x8 = IVar1;
  IVar1 = _objc_msgSend(param_1->field1_0x4,"retain");
  this->field1_0x4 = IVar1;
  return;
}
