/*
 * mangled: _ZN13OFSmartObjectD0Ev
 * demangled: OFSmartObject::~OFSmartObject()
 * address: 000c6960
 * size: 32
 */

/* OFSmartObject::~OFSmartObject() */

void __thiscall OFSmartObject::~OFSmartObject(OFSmartObject *this)

{
  *(undefined ***)this = &PTR_GetRTTI_001b7028;
  *(undefined4 *)(this + 4) = 0;
  operator_delete(this);
  return;
}
