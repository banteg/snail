/*
 * mangled: _ZN11OFXmlReader5nviIoEP16OFISerializerKeyRb
 * demangled: OFXmlReader::nviIo(OFISerializerKey*, bool&)
 * address: 000cd8fc
 * size: 112
 */

/* OFXmlReader::nviIo(OFISerializerKey*, bool&) */

void __thiscall OFXmlReader::nviIo(OFXmlReader *this,OFISerializerKey *param_1,bool *param_2)

{
  undefined4 uVar1;
  ID IVar2;
  ID local_18;

  IVar2 = *(ID *)(this + 0x18);
  uVar1 = (**(code **)(*(int *)param_1 + 0x14))(param_1);
  IVar2 = _objc_msgSend(IVar2,"nextValueAtCurrentScopeWithKey:outValue:",uVar1);
  if (IVar2 != 0) {
    IVar2 = _objc_msgSend(local_18,"boolValue");
    *param_2 = (IVar2 & 0xff) != 0;
  }
  return;
}
