/*
 * mangled: _ZN19OFBinaryKeyedWriter5nviIoEP16OFISerializerKeyR13OFRetainedPtrI8NSStringE
 * demangled: OFBinaryKeyedWriter::nviIo(OFISerializerKey*, OFRetainedPtr<NSString>&)
 * address: 000c7eac
 * size: 192
 */

/* OFBinaryKeyedWriter::nviIo(OFISerializerKey*, OFRetainedPtr<NSString>&) */

void __thiscall
OFBinaryKeyedWriter::nviIo
          (OFBinaryKeyedWriter *this,OFISerializerKey *param_1,OFRetainedPtr *param_2)

{
  ID IVar1;
  ID IVar2;
  ID local_1c;

  IVar1 = _objc_msgSend(*(ID *)param_2,"dataUsingEncoding:",2);
  IVar2 = _objc_msgSend(IVar1,"length");
  IVar1 = _objc_msgSend(IVar1,"bytes");
  local_1c = IVar2;
  (**(code **)(**(int **)(this + 0x18) + 0xc))(*(int **)(this + 0x18),"&19OFSdbmSerializerKey",1);
  (**(code **)(*(int *)this + 0x60))(this,param_1);
  (**(code **)(**(int **)(this + 0x18) + 0xc))(*(int **)(this + 0x18),&local_1c,4);
  (**(code **)(**(int **)(this + 0x18) + 0xc))(*(int **)(this + 0x18),IVar1,local_1c);
  return;
}
