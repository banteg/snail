/*
 * mangled: _ZN29OFHttpNestedQueryStringWriter22storeInnerStreamOfTypeEP13OFISerializerPK6OFRTTI
 * demangled: OFHttpNestedQueryStringWriter::storeInnerStreamOfType(OFISerializer*, OFRTTI const*)
 * address: 000c8e4c
 * size: 688
 */

/* OFHttpNestedQueryStringWriter::storeInnerStreamOfType(OFISerializer*, OFRTTI const*) */

void OFHttpNestedQueryStringWriter::storeInnerStreamOfType(OFISerializer *param_1,OFRTTI *param_2)

{
  OFHttpBinaryParameter *pOVar1;
  undefined *puVar2;
  undefined4 *puVar3;
  OFHttpBinaryParameter *pOVar4;
  undefined1 auStack_d0 [4];
  OFRTTI *local_cc;
  OFISerializer *local_c8;
  undefined4 local_c4;
  undefined *local_c0;
  SEL local_bc;
  ID local_b8;
  OFHttpBinaryParameter *local_b4;
  OFHttpBinaryParameter *local_b0;
  OFRTTI *local_ac;
  OFRTTI *local_a8;
  OFSmartObject *local_a4;
  undefined1 auStack_a0 [4];
  undefined4 local_9c;
  undefined *local_88;
  undefined *local_84;
  undefined1 *local_80;
  undefined1 *local_7c;
  undefined1 *local_78;
  OFHttpBinaryParameter *local_6c;
  OFSmartObject *local_68;
  OFSmartObject *local_64;

  local_80 = &stack0xfffffff8;
  local_78 = auStack_d0;
  local_88 = PTR_001b615c;
  local_84 = &::GCC_except_table4;
  local_7c = &LAB_000c90fc;
  local_cc = param_2;
  local_c8 = param_1;
  __Unwind_SjLj_Register(auStack_a0);
  local_a8 = local_cc;
  local_9c = 0xffffffff;
  for (puVar2 = (undefined *)(*(code *)**(undefined4 **)local_cc)(local_cc);
      puVar2 != (undefined *)0x0; puVar2 = *(undefined **)(puVar2 + 4)) {
    if (puVar2 == PTR_s_RTTI_001b637c) {
      if (local_a8 != (OFRTTI *)0x0) {
        local_ac = local_a8;
        local_9c = 0xffffffff;
        OFBinaryKeyedWriter::getDataSink();
        local_a4 = local_64;
        local_9c = 4;
        puVar2 = (undefined *)(*(code *)**(undefined4 **)local_64)(local_64);
        goto joined_r0x000c8f50;
      }
      break;
    }
  }
LAB_000c8eec:
  __Unwind_SjLj_Unregister(auStack_a0);
  return;
joined_r0x000c8f50:
  if (puVar2 == (undefined *)0x0) goto LAB_000c8f84;
  if (puVar2 == PTR_s_RTTI_001b6380) {
    local_9c = 0xffffffff;
    OFSmartObject::Release(local_a4);
    if (local_a4 != (OFSmartObject *)0x0) {
      local_9c = 0xffffffff;
      local_c4 = getCurrentScope((OFHttpNestedQueryStringWriter *)local_c8);
      local_68 = local_a4;
      *(int *)(local_a4 + 4) = *(int *)(local_a4 + 4) + 1;
      local_c0 = &_OBJC_CLASS___NSString;
      local_bc = "stringWithUTF8String:";
      local_9c = 3;
      puVar3 = (undefined4 *)(*(code *)**(undefined4 **)local_ac)(local_ac);
      local_b8 = _objc_msgSend((ID)local_c0,local_bc,*puVar3);
      local_b4 = operator_new(0x14);
      local_9c = 2;
      local_b0 = local_b4;
      OFHttpBinaryParameter::OFHttpBinaryParameter(local_b4,local_c4,&local_68,local_b8);
      pOVar4 = (OFHttpBinaryParameter *)0x0;
      if (local_b0 != (OFHttpBinaryParameter *)0x0) {
        pOVar4 = local_b4;
      }
      local_6c = local_b4;
      if (local_b0 != (OFHttpBinaryParameter *)0x0) {
        *(int *)(pOVar4 + 4) = *(int *)(pOVar4 + 4) + 1;
      }
      pOVar4 = *(OFHttpBinaryParameter **)(local_c8 + 0x1c);
      if (pOVar4 == *(OFHttpBinaryParameter **)(local_c8 + 0x20)) {
        local_9c = 1;
        std::vector<OFPointer<OFHttpQueryParameter>,std::allocator<OFPointer<OFHttpQueryParameter>>>
        ::_M_insert_aux((vector<OFPointer<OFHttpQueryParameter>,std::allocator<OFPointer<OFHttpQueryParameter>>>
                         *)(local_c8 + 0x18),pOVar4,&local_6c);
      }
      else {
        pOVar1 = *(OFHttpBinaryParameter **)(local_c8 + 0x20);
        if (pOVar4 != (OFHttpBinaryParameter *)0x0) {
          *(OFHttpBinaryParameter **)pOVar4 = local_b4;
          pOVar1 = local_b4;
        }
        if (pOVar4 != (OFHttpBinaryParameter *)0x0 && pOVar1 != (OFHttpBinaryParameter *)0x0) {
          *(int *)(pOVar1 + 4) = *(int *)(pOVar1 + 4) + 1;
        }
        *(int *)(local_c8 + 0x1c) = *(int *)(local_c8 + 0x1c) + 4;
      }
      if (local_6c != (OFHttpBinaryParameter *)0x0) {
        local_9c = 3;
        OFSmartObject::Release((OFSmartObject *)local_6c);
      }
      if (local_68 != (OFSmartObject *)0x0) {
        local_9c = 0xffffffff;
        OFSmartObject::Release(local_68);
      }
    }
    goto LAB_000c8eec;
  }
  puVar2 = *(undefined **)(puVar2 + 4);
  goto joined_r0x000c8f50;
LAB_000c8f84:
  local_9c = 0xffffffff;
  OFSmartObject::Release(local_a4);
  goto LAB_000c8eec;
}
