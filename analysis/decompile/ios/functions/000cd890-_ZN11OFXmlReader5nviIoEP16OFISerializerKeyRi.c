/*
 * mangled: _ZN11OFXmlReader5nviIoEP16OFISerializerKeyRi
 * demangled: OFXmlReader::nviIo(OFISerializerKey*, int&)
 * address: 000cd890
 * size: 100
 */

/* OFXmlReader::nviIo(OFISerializerKey*, int&) */

void __thiscall OFXmlReader::nviIo(OFXmlReader *this,OFISerializerKey *param_1,int *param_2)

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
