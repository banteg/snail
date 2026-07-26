/*
 * mangled: _ZN11OFXmlReader13onScopePushedEP16OFISerializerKey
 * demangled: OFXmlReader::onScopePushed(OFISerializerKey*)
 * address: 000cd53c
 * size: 56
 */

/* OFXmlReader::onScopePushed(OFISerializerKey*) */

void __thiscall OFXmlReader::onScopePushed(OFXmlReader *this,OFISerializerKey *param_1)

{
  undefined4 uVar1;
  ID self;

  self = *(ID *)(this + 0x18);
  uVar1 = (**(code **)(*(int *)param_1 + 0x14))(param_1);
  _objc_msgSend(self,"pushNextScope:",uVar1);
  return;
}
