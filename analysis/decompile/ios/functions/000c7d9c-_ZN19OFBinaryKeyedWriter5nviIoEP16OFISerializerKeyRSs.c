/*
 * mangled: _ZN19OFBinaryKeyedWriter5nviIoEP16OFISerializerKeyRSs
 * demangled: OFBinaryKeyedWriter::nviIo(OFISerializerKey*, std::string&)
 * address: 000c7d9c
 * size: 132
 */

/* OFBinaryKeyedWriter::nviIo(OFISerializerKey*, std::string&) */

void __thiscall
OFBinaryKeyedWriter::nviIo(OFBinaryKeyedWriter *this,OFISerializerKey *param_1,string *param_2)

{
  int iVar1;
  undefined4 local_18;

  iVar1 = *(int *)param_2;
  local_18 = *(undefined4 *)(iVar1 + -0xc);
  (**(code **)(**(int **)(this + 0x18) + 0xc))(*(int **)(this + 0x18),"&19OFSdbmSerializerKey",1);
  (**(code **)(*(int *)this + 0x60))(this,param_1);
  (**(code **)(**(int **)(this + 0x18) + 0xc))(*(int **)(this + 0x18),&local_18,4);
  (**(code **)(**(int **)(this + 0x18) + 0xc))(*(int **)(this + 0x18),iVar1,local_18);
  return;
}
