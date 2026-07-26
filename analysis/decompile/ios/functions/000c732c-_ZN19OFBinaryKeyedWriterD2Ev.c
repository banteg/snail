/*
 * mangled: _ZN19OFBinaryKeyedWriterD2Ev
 * demangled: OFBinaryKeyedWriter::~OFBinaryKeyedWriter()
 * address: 000c732c
 * size: 392
 */

/* OFBinaryKeyedWriter::~OFBinaryKeyedWriter() */

void __thiscall OFBinaryKeyedWriter::~OFBinaryKeyedWriter(OFBinaryKeyedWriter *this)

{
  undefined4 *puVar1;
  undefined1 auStack_c8 [4];
  OFBinaryKeyedWriter *local_c4;
  OFSmartObject *local_bc;
  OFBinaryKeyedWriter *local_ac;
  OFBinaryKeyedWriter *local_a8;
  undefined4 *local_a4;
  undefined4 *local_9c;
  undefined1 auStack_98 [4];
  undefined4 local_94;
  undefined *local_80;
  undefined *local_7c;
  undefined1 *local_78;
  undefined1 *local_74;
  undefined1 *local_70;
  OFSmartObject *local_64 [17];

  local_78 = &stack0xfffffff8;
  local_70 = auStack_c8;
  local_80 = PTR_001b615c;
  local_7c = &GCC_except_table6;
  local_74 = &LAB_000c74b4;
  local_c4 = this;
  __Unwind_SjLj_Register(auStack_98);
  *(undefined ***)local_c4 = &PTR_GetRTTI_001b70e8;
  local_94 = 4;
  OFISerializer::createKey((char *)local_64);
  local_bc = local_64[0];
  local_94 = 3;
  (**(code **)(**(int **)(local_c4 + 0x18) + 0xc))
            (*(int **)(local_c4 + 0x18),"*$&19OFSdbmSerializerKey",1);
  if (local_bc != (OFSmartObject *)0x0) {
    local_94 = 4;
    OFSmartObject::Release(local_bc);
  }
  if (*(OFSmartObject **)(local_c4 + 0x18) != (OFSmartObject *)0x0) {
    local_94 = 5;
    OFSmartObject::Release(*(OFSmartObject **)(local_c4 + 0x18));
  }
  *(undefined ***)local_c4 = &PTR_GetRTTI_001b716c;
  local_ac = local_c4;
  *(undefined **)local_c4 = PTR_vtable_001b636c + 8;
  local_a8 = local_c4 + 8;
  puVar1 = *(undefined4 **)(local_c4 + 8);
  local_a4 = *(undefined4 **)(local_c4 + 0xc);
  if (puVar1 != local_a4) {
    do {
      local_9c = puVar1;
      if ((OFSmartObject *)*puVar1 != (OFSmartObject *)0x0) {
        local_94 = 1;
        OFSmartObject::Release((OFSmartObject *)*puVar1);
      }
      puVar1 = local_9c + 2;
      local_9c = puVar1;
    } while (local_a4 != puVar1);
  }
  if (*(void **)local_a8 != (void *)0x0) {
    operator_delete(*(void **)local_a8);
  }
  local_94 = 0xffffffff;
  OFSmartObject::~OFSmartObject((OFSmartObject *)local_ac);
  __Unwind_SjLj_Unregister(auStack_98);
  return;
}
