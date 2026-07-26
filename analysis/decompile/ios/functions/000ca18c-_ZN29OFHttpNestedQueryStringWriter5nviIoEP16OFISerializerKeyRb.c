/*
 * mangled: _ZN29OFHttpNestedQueryStringWriter5nviIoEP16OFISerializerKeyRb
 * demangled: OFHttpNestedQueryStringWriter::nviIo(OFISerializerKey*, bool&)
 * address: 000ca18c
 * size: 72
 */

/* OFHttpNestedQueryStringWriter::nviIo(OFISerializerKey*, bool&) */

void __thiscall
OFHttpNestedQueryStringWriter::nviIo
          (OFHttpNestedQueryStringWriter *this,OFISerializerKey *param_1,bool *param_2)

{
  NSString *pNVar1;
  NSString *pNVar2;

  pNVar1 = (NSString *)formatScoped(this,param_1);
  pNVar2 = (NSString *)
           NSString::stringWithFormat_
                     ((ID)&_OBJC_CLASS___NSString,"stringWithFormat:",&cf__d,(uint)*param_2);
  addAsciiParameter(this,pNVar1,pNVar2);
  return;
}
