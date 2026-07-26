/*
 * mangled: _ZN29OFHttpNestedQueryStringWriterD0Ev
 * demangled: OFHttpNestedQueryStringWriter::~OFHttpNestedQueryStringWriter()
 * address: 000ca1e0
 * size: 384
 */

/* OFHttpNestedQueryStringWriter::~OFHttpNestedQueryStringWriter() */

void __thiscall
OFHttpNestedQueryStringWriter::~OFHttpNestedQueryStringWriter(OFHttpNestedQueryStringWriter *this)

{
  undefined4 *puVar1;
  undefined1 auStack_cc [4];
  OFHttpNestedQueryStringWriter *local_c8;
  OFHttpNestedQueryStringWriter *local_c0;
  undefined4 *local_bc;
  OFHttpNestedQueryStringWriter *local_ac;
  OFHttpNestedQueryStringWriter *local_a8;
  undefined4 *local_a4;
  undefined4 *local_a0;
  undefined4 *local_98;
  undefined1 auStack_94 [4];
  undefined4 local_90;
  undefined *local_7c;
  undefined *local_78;
  undefined1 *local_74;
  undefined1 *local_70;
  undefined1 *local_6c;

  local_74 = &stack0xfffffff8;
  local_6c = auStack_cc;
  local_7c = PTR_001b615c;
  local_78 = &GCC_except_table11;
  local_70 = &LAB_000ca360;
  local_c8 = this;
  __Unwind_SjLj_Register(auStack_94);
  *(undefined ***)local_c8 = &PTR_GetRTTI_001b72c0;
  local_c0 = local_c8 + 0x18;
  local_bc = *(undefined4 **)(local_c8 + 0x1c);
  puVar1 = *(undefined4 **)(local_c8 + 0x18);
  if (*(undefined4 **)(local_c8 + 0x18) != local_bc) {
    do {
      local_98 = puVar1;
      if ((OFSmartObject *)*local_98 != (OFSmartObject *)0x0) {
        local_90 = 3;
        OFSmartObject::Release((OFSmartObject *)*local_98);
      }
      local_98 = local_98 + 1;
      puVar1 = local_98;
    } while (local_bc != local_98);
  }
  if (*(void **)local_c0 != (void *)0x0) {
    operator_delete(*(void **)local_c0);
  }
  *(undefined ***)local_c8 = &PTR_GetRTTI_001b716c;
  local_ac = local_c8;
  *(undefined **)local_c8 = PTR_vtable_001b636c + 8;
  local_a8 = local_c8 + 8;
  puVar1 = *(undefined4 **)(local_c8 + 8);
  local_a4 = *(undefined4 **)(local_c8 + 0xc);
  if (puVar1 != local_a4) {
    do {
      local_a0 = puVar1;
      if ((OFSmartObject *)*puVar1 != (OFSmartObject *)0x0) {
        local_90 = 1;
        OFSmartObject::Release((OFSmartObject *)*puVar1);
      }
      puVar1 = local_a0 + 2;
      local_a0 = puVar1;
    } while (local_a4 != puVar1);
  }
  if (*(void **)local_a8 != (void *)0x0) {
    operator_delete(*(void **)local_a8);
  }
  local_90 = 0xffffffff;
  OFSmartObject::~OFSmartObject((OFSmartObject *)local_ac);
  operator_delete(local_c8);
  __Unwind_SjLj_Unregister(auStack_94);
  return;
}
