/*
 * mangled: _ZN19OFBinaryKeyedWriter5nviIoEP16OFISerializerKeyRb
 * demangled: OFBinaryKeyedWriter::nviIo(OFISerializerKey*, bool&)
 * address: 000c7ae0
 * size: 128
 */

/* OFBinaryKeyedWriter::nviIo(OFISerializerKey*, bool&) */

void __thiscall
OFBinaryKeyedWriter::nviIo(OFBinaryKeyedWriter *this,OFISerializerKey *param_1,bool *param_2)

{
  undefined4 local_18;

  local_18 = 1;
  (**(code **)(**(int **)(this + 0x18) + 0xc))(*(int **)(this + 0x18),"&19OFSdbmSerializerKey");
  (**(code **)(*(int *)this + 0x60))(this,param_1);
  (**(code **)(**(int **)(this + 0x18) + 0xc))(*(int **)(this + 0x18),&local_18,4);
  (**(code **)(**(int **)(this + 0x18) + 0xc))(*(int **)(this + 0x18),param_2,local_18);
  return;
}
