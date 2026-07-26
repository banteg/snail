/*
 * mangled: _ZN16OFISerializerKeyD0Ev
 * demangled: OFISerializerKey::~OFISerializerKey()
 * address: 000c6a94
 * size: 36
 */

/* OFISerializerKey::~OFISerializerKey() */

void __thiscall OFISerializerKey::~OFISerializerKey(OFISerializerKey *this)

{
  *(undefined ***)this = &PTR_GetRTTI_001b7060;
  OFSmartObject::~OFSmartObject((OFSmartObject *)this);
  operator_delete(this);
  return;
}
