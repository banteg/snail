/*
 * mangled: _ZN10OFDelegateD1Ev
 * demangled: OFDelegate::~OFDelegate()
 * address: 000c62a0
 * size: 76
 */

/* OFDelegate::~OFDelegate() */

void __thiscall OFDelegate::~OFDelegate(OFDelegate *this)

{
  _objc_msgSend(this->field0_0x0,"release");
  this->field0_0x0 = 0;
  _objc_msgSend(this->field2_0x8,"release");
  this->field2_0x8 = 0;
  _objc_msgSend(this->field1_0x4,"release");
  this->field1_0x4 = 0;
  return;
}
