/*
 * mangled: _ZN29OFHttpNestedQueryStringWriter5nviIoEP16OFISerializerKeyR13OFRetainedPtrI6NSDataE
 * demangled: OFHttpNestedQueryStringWriter::nviIo(OFISerializerKey*, OFRetainedPtr<NSData>&)
 * address: 000c9d4c
 * size: 92
 */

/* OFHttpNestedQueryStringWriter::nviIo(OFISerializerKey*, OFRetainedPtr<NSData>&) */

void __thiscall
OFHttpNestedQueryStringWriter::nviIo
          (OFHttpNestedQueryStringWriter *this,OFISerializerKey *param_1,OFRetainedPtr *param_2)

{
  undefined4 uVar1;
  NSString *pNVar2;

  uVar1 = (**(code **)(*(int *)param_1 + 0x14))(param_1);
  pNVar2 = (NSString *)
           NSString::stringWithUTF8String_
                     ((ID)&_OBJC_CLASS___NSString,"stringWithUTF8String:",uVar1);
  addBlobParameter(this,pNVar2,*(NSData **)param_2);
  return;
}
