/*
 * mangled: _ZN23OFBinarySdbmKeyedWriter8writeKeyEP16OFISerializerKey
 * demangled: OFBinarySdbmKeyedWriter::writeKey(OFISerializerKey*)
 * address: 000c8250
 * size: 180
 */

/* OFBinarySdbmKeyedWriter::writeKey(OFISerializerKey*) */

void __thiscall
OFBinarySdbmKeyedWriter::writeKey(OFBinarySdbmKeyedWriter *this,OFISerializerKey *param_1)

{
  undefined1 auStack_a8 [4];
  OFISerializerKey *local_a4;
  OFBinarySdbmKeyedWriter *local_a0;
  OFSmartObject *local_9c;
  undefined1 auStack_98 [4];
  undefined4 local_94;
  undefined *local_80;
  undefined *local_7c;
  undefined1 *local_78;
  undefined1 *local_74;
  undefined1 *local_70;
  OFSmartObject *local_64;

  local_78 = &stack0xfffffff8;
  local_70 = auStack_a8;
  local_80 = PTR_001b615c;
  local_7c = &::GCC_except_table0;
  local_74 = &LAB_000c8304;
  local_a4 = param_1;
  local_a0 = this;
  __Unwind_SjLj_Register(auStack_98);
  local_94 = 0xffffffff;
  OFBinaryKeyedWriter::getDataSink();
  local_9c = local_64;
  local_94 = 1;
  (**(code **)(*(int *)local_64 + 0xc))(local_64,local_a4 + 8,4);
  local_94 = 0xffffffff;
  OFSmartObject::Release(local_9c);
  __Unwind_SjLj_Unregister(auStack_98);
  return;
}
