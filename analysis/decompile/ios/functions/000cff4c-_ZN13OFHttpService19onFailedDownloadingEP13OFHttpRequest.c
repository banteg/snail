/*
 * mangled: _ZN13OFHttpService19onFailedDownloadingEP13OFHttpRequest
 * demangled: OFHttpService::onFailedDownloading(OFHttpRequest*)
 * address: 000cff4c
 * size: 900
 */

/* OFHttpService::onFailedDownloading(OFHttpRequest*) */

void __thiscall OFHttpService::onFailedDownloading(OFHttpService *this,OFHttpRequest *param_1)

{
  OFSmartObject *this_00;
  OFHttpServiceRequestContainer *pOVar1;
  OFHttpServiceRequestContainer *pOVar2;
  OFHttpServiceRequestContainer *pOVar3;
  int iVar4;
  int iVar5;
  OFHttpRequest *pOVar6;
  OFHttpServiceRequestContainer *pOVar7;
  bool bVar8;
  undefined1 auStack_a8 [4];
  OFHttpRequest *local_a4;
  OFHttpService *local_a0;
  OFHttpServiceRequestContainer *local_9c;
  OFSmartObject *local_98;
  undefined1 auStack_94 [4];
  undefined4 local_90;
  undefined *local_7c;
  undefined *local_78;
  undefined1 *local_74;
  undefined1 *local_70;
  undefined1 *local_6c;

  local_74 = &stack0xfffffff8;
  local_6c = auStack_a8;
  local_7c = PTR_001b615c;
  local_78 = &::GCC_except_table5;
  local_70 = &LAB_000d02d0;
  local_a4 = param_1;
  local_a0 = this;
  __Unwind_SjLj_Register(auStack_94);
  pOVar7 = (local_a0->field5_0x14).field0_0x0.field1_0x4;
  pOVar3 = (local_a0->field5_0x14).field0_0x0.field0_0x0;
  iVar5 = ((int)pOVar7 - (int)pOVar3 >> 2) * 0x38e38e39;
  iVar4 = iVar5 >> 2;
  if (0 < iVar4) {
    pOVar6 = *(OFHttpRequest **)(pOVar3 + 8);
    bVar8 = pOVar6 != local_a4;
    local_9c = pOVar3;
    if (bVar8) {
      local_9c = pOVar3 + 0x24;
      pOVar6 = *(OFHttpRequest **)(pOVar3 + 0x2c);
    }
    if ((bVar8 && pOVar6 != local_a4) &&
       (local_9c = pOVar3 + 0x48, *(OFHttpRequest **)(pOVar3 + 0x50) != local_a4)) {
      pOVar6 = *(OFHttpRequest **)(pOVar3 + 0x74);
      pOVar1 = pOVar3 + 0x6c;
      while (local_9c = pOVar1, pOVar6 != local_a4) {
        iVar4 = iVar4 + -1;
        pOVar3 = pOVar1 + 0x24;
        if (iVar4 == 0) {
          iVar5 = ((int)pOVar7 - (int)pOVar3 >> 2) * 0x38e38e39;
          goto LAB_000d0064;
        }
        local_9c = pOVar3;
        if (((*(OFHttpRequest **)(pOVar1 + 0x2c) == local_a4) ||
            (local_9c = pOVar1 + 0x48, *(OFHttpRequest **)(pOVar1 + 0x50) == local_a4)) ||
           (local_9c = pOVar1 + 0x6c, *(OFHttpRequest **)(pOVar1 + 0x74) == local_a4)) break;
        pOVar6 = *(OFHttpRequest **)(pOVar1 + 0x98);
        pOVar1 = pOVar1 + 0x90;
      }
    }
    goto LAB_000d0080;
  }
LAB_000d0064:
  if (iVar5 == 2) {
LAB_000d02a0:
    local_9c = pOVar3;
    if (*(OFHttpRequest **)(pOVar3 + 8) != local_a4) {
      pOVar3 = pOVar3 + 0x24;
LAB_000d02b4:
      local_9c = pOVar3;
      if (*(OFHttpRequest **)(pOVar3 + 8) != local_a4) {
        local_9c = pOVar7;
      }
    }
  }
  else if (iVar5 == 3) {
    local_9c = pOVar3;
    if (*(OFHttpRequest **)(pOVar3 + 8) != local_a4) {
      pOVar3 = pOVar3 + 0x24;
      goto LAB_000d02a0;
    }
  }
  else {
    local_9c = pOVar7;
    if (iVar5 == 1) goto LAB_000d02b4;
  }
LAB_000d0080:
  if (pOVar7 == local_9c) goto LAB_000d0200;
  this_00 = *(OFSmartObject **)(local_9c + 0x20);
  if (this_00 != (OFSmartObject *)0x0) {
    *(int *)(this_00 + 4) = *(int *)(this_00 + 4) + 1;
    local_90 = 0xffffffff;
    OFSmartObject::Release(this_00);
    local_98 = *(OFSmartObject **)(local_9c + 0x20);
    if (local_98 != (OFSmartObject *)0x0) {
      *(int *)(local_98 + 4) = *(int *)(local_98 + 4) + 1;
    }
    local_90 = 1;
    (**(code **)(*(int *)local_98 + 0x10))(local_98,local_9c);
    local_90 = 0xffffffff;
    OFSmartObject::Release(local_98);
  }
  pOVar3 = (local_a0->field5_0x14).field0_0x0.field1_0x4;
  pOVar7 = (local_a0->field5_0x14).field0_0x0.field0_0x0;
  iVar5 = ((int)pOVar3 - (int)pOVar7 >> 2) * 0x38e38e39;
  iVar4 = iVar5 >> 2;
  if (iVar4 < 1) {
LAB_000d01d0:
    pOVar2 = pOVar3;
    if (iVar5 == 2) {
LAB_000d024c:
      if (local_a4 == *(OFHttpRequest **)(pOVar7 + 8)) goto LAB_000d0270;
      pOVar7 = pOVar7 + 0x24;
    }
    else {
      if (iVar5 == 3) {
        if (local_a4 == *(OFHttpRequest **)(pOVar7 + 8)) goto LAB_000d0270;
        pOVar7 = pOVar7 + 0x24;
        goto LAB_000d024c;
      }
      if (iVar5 != 1) goto LAB_000d01ec;
    }
    if (local_a4 == *(OFHttpRequest **)(pOVar7 + 8)) {
LAB_000d0270:
      local_90 = 0xffffffff;
      std::vector<OFHttpServiceRequestContainer,std::allocator<OFHttpServiceRequestContainer>>::
      erase((vector<OFHttpServiceRequestContainer,std::allocator<OFHttpServiceRequestContainer>> *)
            &local_a0->field5_0x14,pOVar7);
      goto LAB_000d0200;
    }
  }
  else {
    if (local_a4 == *(OFHttpRequest **)(pOVar7 + 8)) goto LAB_000d0270;
    pOVar1 = pOVar7 + 0x24;
    if ((local_a4 == *(OFHttpRequest **)(pOVar7 + 0x2c)) ||
       (pOVar1 = pOVar7 + 0x48, *(OFHttpRequest **)(pOVar7 + 0x50) == local_a4)) {
LAB_000d021c:
      local_90 = 0xffffffff;
      std::vector<OFHttpServiceRequestContainer,std::allocator<OFHttpServiceRequestContainer>>::
      erase((vector<OFHttpServiceRequestContainer,std::allocator<OFHttpServiceRequestContainer>> *)
            &local_a0->field5_0x14,pOVar1);
      goto LAB_000d0200;
    }
    pOVar6 = *(OFHttpRequest **)(pOVar7 + 0x74);
    pOVar2 = pOVar7 + 0x6c;
    while (pOVar6 != local_a4) {
      iVar4 = iVar4 + -1;
      pOVar7 = pOVar2 + 0x24;
      if (iVar4 == 0) {
        iVar5 = ((int)pOVar3 - (int)pOVar7 >> 2) * 0x38e38e39;
        goto LAB_000d01d0;
      }
      if (*(OFHttpRequest **)(pOVar2 + 0x2c) == local_a4) goto LAB_000d0270;
      pOVar1 = pOVar2 + 0x48;
      if ((*(OFHttpRequest **)(pOVar2 + 0x50) == local_a4) ||
         (pOVar1 = pOVar2 + 0x6c, *(OFHttpRequest **)(pOVar2 + 0x74) == local_a4))
      goto LAB_000d021c;
      pOVar6 = *(OFHttpRequest **)(pOVar2 + 0x98);
      pOVar2 = pOVar2 + 0x90;
    }
  }
LAB_000d01ec:
  local_90 = 0xffffffff;
  std::vector<OFHttpServiceRequestContainer,std::allocator<OFHttpServiceRequestContainer>>::erase
            ((vector<OFHttpServiceRequestContainer,std::allocator<OFHttpServiceRequestContainer>> *)
             &local_a0->field5_0x14,pOVar2);
LAB_000d0200:
  __Unwind_SjLj_Unregister(auStack_94);
  return;
}
