/*
 * mangled: _ZN19OFBinaryKeyedWriter5nviIoEP16OFISerializerKeyRx
 * demangled: OFBinaryKeyedWriter::nviIo(OFISerializerKey*, long long&)
 * address: 000c7bf4
 * size: 132
 */

/* OFBinaryKeyedWriter::nviIo(OFISerializerKey*, long long&) */

void __thiscall
OFBinaryKeyedWriter::nviIo(OFBinaryKeyedWriter *this,OFISerializerKey *param_1,longlong *param_2)

{
  undefined4 local_18;

  local_18 = 8;
  (**(code **)(**(int **)(this + 0x18) + 0xc))(*(int **)(this + 0x18),"&19OFSdbmSerializerKey",1);
  (**(code **)(*(int *)this + 0x60))(this,param_1);
  (**(code **)(**(int **)(this + 0x18) + 0xc))(*(int **)(this + 0x18),&local_18,4);
  (**(code **)(**(int **)(this + 0x18) + 0xc))(*(int **)(this + 0x18),param_2,local_18);
  return;
}
