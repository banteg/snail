/*
 * mangled: _ZN29OFHttpNestedQueryStringWriter5nviIoEP16OFISerializerKeyRi
 * demangled: OFHttpNestedQueryStringWriter::nviIo(OFISerializerKey*, int&)
 * address: 000ca138
 * size: 72
 */

/* OFHttpNestedQueryStringWriter::nviIo(OFISerializerKey*, int&) */

void __thiscall
OFHttpNestedQueryStringWriter::nviIo
          (OFHttpNestedQueryStringWriter *this,OFISerializerKey *param_1,int *param_2)

{
  NSString *pNVar1;
  NSString *pNVar2;

  pNVar1 = (NSString *)formatScoped(this,param_1);
  pNVar2 = (NSString *)
           NSString::stringWithFormat_
                     ((ID)&_OBJC_CLASS___NSString,"stringWithFormat:",&cf__d,*param_2);
  addAsciiParameter(this,pNVar1,pNVar2);
  return;
}
