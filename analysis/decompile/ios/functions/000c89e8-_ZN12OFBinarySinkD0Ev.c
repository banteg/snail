/*
 * mangled: _ZN12OFBinarySinkD0Ev
 * demangled: OFBinarySink::~OFBinarySink()
 * address: 000c89e8
 * size: 36
 */

/* OFBinarySink::~OFBinarySink() */

void __thiscall OFBinarySink::~OFBinarySink(OFBinarySink *this)

{
  *(undefined ***)this = &PTR_GetRTTI_001b72a8;
  OFSmartObject::~OFSmartObject((OFSmartObject *)this);
  operator_delete(this);
  return;
}
