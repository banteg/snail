/*
 * mangled: _ZN29OFHttpNestedQueryStringWriter5nviIoEP16OFISerializerKeyRx
 * demangled: OFHttpNestedQueryStringWriter::nviIo(OFISerializerKey*, long long&)
 * address: 000ca084
 * size: 84
 */

/* OFHttpNestedQueryStringWriter::nviIo(OFISerializerKey*, long long&) */

void __thiscall
OFHttpNestedQueryStringWriter::nviIo
          (OFHttpNestedQueryStringWriter *this,OFISerializerKey *param_1,longlong *param_2)

{
  NSString *pNVar1;
  NSString *pNVar2;

  pNVar1 = (NSString *)formatScoped(this,param_1);
  pNVar2 = (NSString *)
           NSString::stringWithFormat_
                     ((ID)&_OBJC_CLASS___NSString,"stringWithFormat:",&cf__qi,(int)*param_2,
                      *(undefined4 *)((int)param_2 + 4));
  addAsciiParameter(this,pNVar1,pNVar2);
  return;
}
