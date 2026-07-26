/*
 * mangled: _ZN29OFHttpNestedQueryStringWriter5nviIoEP16OFISerializerKeyRd
 * demangled: OFHttpNestedQueryStringWriter::nviIo(OFISerializerKey*, double&)
 * address: 000c9fb4
 * size: 88
 */

/* OFHttpNestedQueryStringWriter::nviIo(OFISerializerKey*, double&) */

void __thiscall
OFHttpNestedQueryStringWriter::nviIo
          (OFHttpNestedQueryStringWriter *this,OFISerializerKey *param_1,double *param_2)

{
  NSString *pNVar1;
  NSString *pNVar2;

  pNVar1 = (NSString *)formatScoped(this,param_1);
  pNVar2 = (NSString *)
           NSString::stringWithFormat_
                     ((ID)&_OBJC_CLASS___NSString,"stringWithFormat:",&cf__f,*(undefined4 *)param_2,
                      *(undefined4 *)((int)param_2 + 4));
  addAsciiParameter(this,pNVar1,pNVar2);
  return;
}
