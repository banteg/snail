/*
 * mangled: _ZN19OFBinaryKeyedWriter15beginEncodeTypeEPK6OFRTTI
 * demangled: OFBinaryKeyedWriter::beginEncodeType(OFRTTI const*)
 * address: 000c6dc8
 * size: 40
 */

/* OFBinaryKeyedWriter::beginEncodeType(OFRTTI const*) */

void __thiscall OFBinaryKeyedWriter::beginEncodeType(OFBinaryKeyedWriter *this,OFRTTI *param_1)

{
  undefined4 local_c;

  local_c = *(undefined4 *)(param_1 + 8);
  OFISerializer::io((OFISerializer *)this,"___type",(OFHashedString *)&local_c);
  return;
}
