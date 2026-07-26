/*
 * mangled: _ZN11OFXmlReaderD1Ev
 * demangled: OFXmlReader::~OFXmlReader()
 * address: 000ce498
 * size: 300
 */

/* OFXmlReader::~OFXmlReader() */

void __thiscall OFXmlReader::~OFXmlReader(OFXmlReader *this)

{
  undefined4 *puVar1;
  undefined1 auStack_c0 [4];
  OFXmlReader *local_bc;
  OFXmlReader *local_a8;
  OFXmlReader *local_a4;
  undefined4 *local_a0;
  undefined4 *local_9c;
  undefined1 auStack_94 [4];
  undefined4 local_90;
  undefined *local_7c;
  undefined *local_78;
  undefined1 *local_74;
  undefined1 *local_70;
  undefined1 *local_6c;

  local_74 = &stack0xfffffff8;
  local_6c = auStack_c0;
  local_7c = PTR_001b615c;
  local_78 = &GCC_except_table10;
  local_70 = &LAB_000ce5c4;
  local_bc = this;
  __Unwind_SjLj_Register(auStack_94);
  *(undefined ***)local_bc = &PTR_GetRTTI_001b7464;
  if (*(ID *)(local_bc + 0x18) != 0) {
    local_90 = 3;
    _objc_msgSend(*(ID *)(local_bc + 0x18),"release");
  }
  *(undefined ***)local_bc = &PTR_GetRTTI_001b7080;
  local_a8 = local_bc;
  *(undefined **)local_bc = PTR_vtable_001b636c + 8;
  local_a4 = local_bc + 8;
  puVar1 = *(undefined4 **)(local_bc + 8);
  local_a0 = *(undefined4 **)(local_bc + 0xc);
  if (puVar1 != local_a0) {
    do {
      local_9c = puVar1;
      if ((OFSmartObject *)*puVar1 != (OFSmartObject *)0x0) {
        local_90 = 1;
        OFSmartObject::Release((OFSmartObject *)*puVar1);
      }
      puVar1 = local_9c + 2;
      local_9c = puVar1;
    } while (local_a0 != puVar1);
  }
  if (*(void **)local_a4 != (void *)0x0) {
    operator_delete(*(void **)local_a4);
  }
  local_90 = 0xffffffff;
  OFSmartObject::~OFSmartObject((OFSmartObject *)local_a8);
  __Unwind_SjLj_Unregister(auStack_94);
  return;
}
