/*
 * mangled: _ZN29OFHttpNestedQueryStringWriter5nviIoEP16OFISerializerKeyRf
 * demangled: OFHttpNestedQueryStringWriter::nviIo(OFISerializerKey*, float&)
 * address: 000ca018
 * size: 96
 */

/* OFHttpNestedQueryStringWriter::nviIo(OFISerializerKey*, float&) */

void __thiscall
OFHttpNestedQueryStringWriter::nviIo
          (OFHttpNestedQueryStringWriter *this,OFISerializerKey *param_1,float *param_2)

{
  NSString *pNVar1;
  NSString *pNVar2;

  pNVar1 = (NSString *)formatScoped(this,param_1);
  pNVar2 = (NSString *)
           NSString::stringWithFormat_
                     ((ID)&_OBJC_CLASS___NSString,"stringWithFormat:",&cf__f,
                      SUB84((double)*param_2,0),(int)((ulonglong)(double)*param_2 >> 0x20));
  addAsciiParameter(this,pNVar1,pNVar2);
  return;
}
