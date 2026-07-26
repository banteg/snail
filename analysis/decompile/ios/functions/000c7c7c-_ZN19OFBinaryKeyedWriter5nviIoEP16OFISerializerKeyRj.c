/*
 * mangled: _ZN19OFBinaryKeyedWriter5nviIoEP16OFISerializerKeyRj
 * demangled: OFBinaryKeyedWriter::nviIo(OFISerializerKey*, unsigned int&)
 * address: 000c7c7c
 * size: 140
 */

/* OFBinaryKeyedWriter::nviIo(OFISerializerKey*, unsigned int&) */

void __thiscall
OFBinaryKeyedWriter::nviIo(OFBinaryKeyedWriter *this,OFISerializerKey *param_1,uint *param_2)

{
  undefined4 local_1c;

  local_1c = 4;
  (**(code **)(**(int **)(this + 0x18) + 0xc))(*(int **)(this + 0x18),"&19OFSdbmSerializerKey",1);
  (**(code **)(*(int *)this + 0x60))(this,param_1);
  (**(code **)(**(int **)(this + 0x18) + 0xc))(*(int **)(this + 0x18),&local_1c,4);
  (**(code **)(**(int **)(this + 0x18) + 0xc))(*(int **)(this + 0x18),param_2,local_1c);
  return;
}
