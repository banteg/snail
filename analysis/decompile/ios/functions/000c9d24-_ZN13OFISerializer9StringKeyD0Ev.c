/*
 * mangled: _ZN13OFISerializer9StringKeyD0Ev
 * demangled: OFISerializer::StringKey::~StringKey()
 * address: 000c9d24
 * size: 36
 */

/* OFISerializer::StringKey::~StringKey() */

void __thiscall OFISerializer::StringKey::~StringKey(StringKey *this)

{
  *(undefined ***)this = &PTR_GetRTTI_001b7060;
  OFSmartObject::~OFSmartObject((OFSmartObject *)this);
  operator_delete(this);
  return;
}
