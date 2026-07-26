/*
 * mangled: _ZN19OFBinaryKeyedWriter8writeKeyEP16OFISerializerKey
 * demangled: OFBinaryKeyedWriter::writeKey(OFISerializerKey*)
 * address: 000c6e38
 * size: 120
 */

/* OFBinaryKeyedWriter::writeKey(OFISerializerKey*) */

void __thiscall OFBinaryKeyedWriter::writeKey(OFBinaryKeyedWriter *this,OFISerializerKey *param_1)

{
  char *pcVar1;
  size_t sVar2;
  undefined4 uVar3;
  int *piVar4;
  code *pcVar5;
  undefined1 local_15;

  pcVar1 = (char *)(**(code **)(*(int *)param_1 + 0x14))(param_1);
  sVar2 = _strlen(pcVar1);
  local_15 = (undefined1)sVar2;
  (**(code **)(**(int **)(this + 0x18) + 0xc))(*(int **)(this + 0x18),&local_15,1);
  piVar4 = *(int **)(this + 0x18);
  pcVar5 = *(code **)(*piVar4 + 0xc);
  uVar3 = (**(code **)(*(int *)param_1 + 0x14))(param_1);
  (*pcVar5)(piVar4,uVar3,local_15);
  return;
}
