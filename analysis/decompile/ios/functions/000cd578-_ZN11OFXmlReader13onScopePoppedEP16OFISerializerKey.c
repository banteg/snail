/*
 * mangled: _ZN11OFXmlReader13onScopePoppedEP16OFISerializerKey
 * demangled: OFXmlReader::onScopePopped(OFISerializerKey*)
 * address: 000cd578
 * size: 28
 */

/* OFXmlReader::onScopePopped(OFISerializerKey*) */

void OFXmlReader::onScopePopped(OFISerializerKey *param_1)

{
  _objc_msgSend(*(ID *)(param_1 + 0x18),"popScope");
  return;
}
