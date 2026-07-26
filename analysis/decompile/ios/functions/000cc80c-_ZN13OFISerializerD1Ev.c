/*
 * mangled: _ZN13OFISerializerD1Ev
 * demangled: OFISerializer::~OFISerializer()
 * address: 000cc80c
 * size: 228
 */

/* OFISerializer::~OFISerializer() */

void __thiscall OFISerializer::~OFISerializer(OFISerializer *this)

{
  undefined4 *puVar1;
  OFISerializer *local_a8;
  OFISerializer *local_a4;
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
  local_6c = (undefined1 *)&local_a8;
  local_7c = PTR_001b615c;
  local_78 = &GCC_except_table6;
  local_70 = &LAB_000cc8f0;
  local_a8 = this;
  __Unwind_SjLj_Register(auStack_94);
  *(undefined ***)local_a8 = &PTR_GetRTTI_001b73f0;
  local_a4 = local_a8 + 8;
  local_9c = *(undefined4 **)(local_a8 + 0xc);
  puVar1 = *(undefined4 **)(local_a8 + 8);
  if (*(undefined4 **)(local_a8 + 8) != local_9c) {
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
  __Unwind_SjLj_Unregister(auStack_94);
  return;
}
