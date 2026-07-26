/*
 * mangled: _ZN11OFXmlReader5nviIoEP16OFISerializerKeyRf
 * demangled: OFXmlReader::nviIo(OFISerializerKey*, float&)
 * address: 000cde70
 * size: 100
 */

/* OFXmlReader::nviIo(OFISerializerKey*, float&) */

void __thiscall OFXmlReader::nviIo(OFXmlReader *this,OFISerializerKey *param_1,float *param_2)

{
  undefined4 uVar1;
  float fVar2;
  ID IVar3;
  ID local_18;

  IVar3 = *(ID *)(this + 0x18);
  uVar1 = (**(code **)(*(int *)param_1 + 0x14))(param_1);
  IVar3 = _objc_msgSend(IVar3,"nextValueAtCurrentScopeWithKey:outValue:",uVar1,&local_18);
  if (IVar3 != 0) {
    fVar2 = (float)_objc_msgSend(local_18,"floatValue");
    *param_2 = fVar2;
  }
  return;
}
