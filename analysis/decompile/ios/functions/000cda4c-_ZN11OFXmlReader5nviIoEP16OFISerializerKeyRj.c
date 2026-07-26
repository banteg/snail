/*
 * mangled: _ZN11OFXmlReader5nviIoEP16OFISerializerKeyRj
 * demangled: OFXmlReader::nviIo(OFISerializerKey*, unsigned int&)
 * address: 000cda4c
 * size: 100
 */

/* OFXmlReader::nviIo(OFISerializerKey*, unsigned int&) */

void __thiscall OFXmlReader::nviIo(OFXmlReader *this,OFISerializerKey *param_1,uint *param_2)

{
  undefined4 uVar1;
  ID IVar2;
  ID local_18;

  IVar2 = *(ID *)(this + 0x18);
  uVar1 = (**(code **)(*(int *)param_1 + 0x14))(param_1);
  IVar2 = _objc_msgSend(IVar2,"nextValueAtCurrentScopeWithKey:outValue:",uVar1,&local_18);
  if (IVar2 != 0) {
    IVar2 = _objc_msgSend(local_18,"intValue");
    *param_2 = IVar2;
  }
  return;
}
