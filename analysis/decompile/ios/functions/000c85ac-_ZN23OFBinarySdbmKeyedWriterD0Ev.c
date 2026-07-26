/*
 * mangled: _ZN23OFBinarySdbmKeyedWriterD0Ev
 * demangled: OFBinarySdbmKeyedWriter::~OFBinarySdbmKeyedWriter()
 * address: 000c85ac
 * size: 36
 */

/* OFBinarySdbmKeyedWriter::~OFBinarySdbmKeyedWriter() */

void __thiscall OFBinarySdbmKeyedWriter::~OFBinarySdbmKeyedWriter(OFBinarySdbmKeyedWriter *this)

{
  *(undefined ***)this = &PTR_GetRTTI_001b7200;
  OFBinaryKeyedWriter::~OFBinaryKeyedWriter((OFBinaryKeyedWriter *)this);
  operator_delete(this);
  return;
}
