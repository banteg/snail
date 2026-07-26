/*
 * mangled: _ZN18OFOutputSerializerD0Ev
 * demangled: OFOutputSerializer::~OFOutputSerializer()
 * address: 000c7840
 * size: 260
 */

/* OFOutputSerializer::~OFOutputSerializer() */

void __thiscall OFOutputSerializer::~OFOutputSerializer(OFOutputSerializer *this)

{
  undefined4 *puVar1;
  OFOutputSerializer *local_ac;
  OFOutputSerializer *local_a8;
  OFOutputSerializer *local_a4;
  undefined4 *local_9c;
  undefined4 *local_98;
  undefined1 auStack_94 [4];
  undefined4 local_90;
  undefined *local_7c;
  undefined *local_78;
  undefined1 *local_74;
  undefined1 *local_70;
  undefined1 *local_6c;

  local_74 = &stack0xfffffff8;
  local_6c = (undefined1 *)&local_ac;
  local_7c = PTR_001b615c;
  local_78 = &::GCC_except_table2;
  local_70 = &LAB_000c7944;
  local_ac = this;
  __Unwind_SjLj_Register(auStack_94);
  *(undefined ***)local_ac = &PTR_GetRTTI_001b716c;
  local_a8 = local_ac;
  *(undefined **)local_ac = PTR_vtable_001b636c + 8;
  local_a4 = local_ac + 8;
  local_9c = *(undefined4 **)(local_ac + 0xc);
  puVar1 = *(undefined4 **)(local_ac + 8);
  if (*(undefined4 **)(local_ac + 8) != local_9c) {
    do {
      local_98 = puVar1;
      if ((OFSmartObject *)*local_98 != (OFSmartObject *)0x0) {
        local_90 = 1;
        OFSmartObject::Release((OFSmartObject *)*local_98);
      }
      local_98 = local_98 + 2;
      puVar1 = local_98;
    } while (local_9c != local_98);
  }
  if (*(void **)local_a4 != (void *)0x0) {
    operator_delete(*(void **)local_a4);
  }
  local_90 = 0xffffffff;
  OFSmartObject::~OFSmartObject((OFSmartObject *)local_a8);
  operator_delete(local_ac);
  __Unwind_SjLj_Unregister(auStack_94);
  return;
}
