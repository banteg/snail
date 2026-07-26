/*
 * mangled: _ZN19OFBinaryKeyedWriter5nviIoEP16OFISerializerKeyRi
 * demangled: OFBinaryKeyedWriter::nviIo(OFISerializerKey*, int&)
 * address: 000c7d0c
 * size: 140
 */

/* OFBinaryKeyedWriter::nviIo(OFISerializerKey*, int&) */

void __thiscall
OFBinaryKeyedWriter::nviIo(OFBinaryKeyedWriter *this,OFISerializerKey *param_1,int *param_2)

{
  undefined4 local_1c;

  local_1c = 4;
  (**(code **)(**(int **)(this + 0x18) + 0xc))(*(int **)(this + 0x18),"&19OFSdbmSerializerKey",1);
  (**(code **)(*(int *)this + 0x60))(this,param_1);
  (**(code **)(**(int **)(this + 0x18) + 0xc))(*(int **)(this + 0x18),&local_1c,4);
  (**(code **)(**(int **)(this + 0x18) + 0xc))(*(int **)(this + 0x18),param_2,local_1c);
  return;
}
