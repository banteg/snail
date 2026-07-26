/*
 * mangled: _ZNK19OFBinaryKeyedWriter11getDataSinkEv
 * demangled: OFBinaryKeyedWriter::getDataSink() const
 * address: 000c6dac
 * size: 28
 */

/* OFBinaryKeyedWriter::getDataSink() const */

void OFBinaryKeyedWriter::getDataSink(void)

{
  int *in_r0;
  int in_r1;
  int iVar1;

  iVar1 = *(int *)(in_r1 + 0x18);
  *in_r0 = iVar1;
  if (iVar1 != 0) {
    *(int *)(iVar1 + 4) = *(int *)(iVar1 + 4) + 1;
  }
  return;
}
