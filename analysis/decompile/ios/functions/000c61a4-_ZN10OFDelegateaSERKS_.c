/*
 * mangled: _ZN10OFDelegateaSERKS_
 * demangled: OFDelegate::operator=(OFDelegate const&)
 * address: 000c61a4
 * size: 156
 */

/* OFDelegate::TEMPNAMEPLACEHOLDERVALUE(OFDelegate const&) */

OFDelegate * __thiscall OFDelegate::operator=(OFDelegate *this,OFDelegate *param_1)

{
  ID IVar1;
  SEL pcVar2;

  _objc_msgSend(this->field0_0x0,"release");
  this->field0_0x0 = 0;
  _objc_msgSend(this->field2_0x8,"release");
  this->field2_0x8 = 0;
  _objc_msgSend(this->field1_0x4,"release");
  pcVar2 = param_1->field3_0xc;
  IVar1 = param_1->field0_0x0;
  this->field1_0x4 = 0;
  this->field3_0xc = pcVar2;
  IVar1 = _objc_msgSend(IVar1,"retain");
  this->field0_0x0 = IVar1;
  IVar1 = _objc_msgSend(param_1->field2_0x8,"retain");
  this->field2_0x8 = IVar1;
  IVar1 = _objc_msgSend(param_1->field1_0x4,"retain");
  this->field1_0x4 = IVar1;
  return this;
}
