/*
 * mangled: _ZNSt6vectorI9OFPointerI12OFXmlElementESaIS2_EE13_M_insert_auxEN9__gnu_cxx17__normal_iteratorIPS2_S4_EERKS2_
 * demangled: std::vector<OFPointer<OFXmlElement>, std::allocator<OFPointer<OFXmlElement>>>::_M_insert_aux(__gnu_cxx::__normal_iterator<OFPointer<OFXmlElement>*, std::vector<OFPointer<OFXmlElement>, std::allocator<OFPointer<OFXmlElement>>>>, OFPointer<OFXmlElement> const&)
 * address: 000d635c
 * size: 976
 */

/* std::vector<OFPointer<OFXmlElement>, std::allocator<OFPointer<OFXmlElement> >
   >::_M_insert_aux(__gnu_cxx::__normal_iterator<OFPointer<OFXmlElement>*,
   std::vector<OFPointer<OFXmlElement>, std::allocator<OFPointer<OFXmlElement> > > >,
   OFPointer<OFXmlElement> const&) */

void __thiscall
std::vector<OFPointer<OFXmlElement>,std::allocator<OFPointer<OFXmlElement>>>::_M_insert_aux
          (vector<OFPointer<OFXmlElement>,std::allocator<OFPointer<OFXmlElement>>> *this,
          int *param_2,int *param_3)

{
  uint uVar1;
  OFSmartObject *pOVar2;
  int *piVar3;
  int iVar4;
  uint uVar5;
  int *piVar6;
  vector<OFPointer<OFXmlElement>,std::allocator<OFPointer<OFXmlElement>>> *pvVar7;
  bool bVar8;
  undefined4 local_c4;
  int *local_c0;
  int *local_bc;
  vector<OFPointer<OFXmlElement>,std::allocator<OFPointer<OFXmlElement>>> *local_b8;
  int *local_b4;
  vector<OFPointer<OFXmlElement>,std::allocator<OFPointer<OFXmlElement>>> *local_b0;
  int local_ac;
  int *local_a8;
  OFSmartObject *local_a4;
  ulong local_a0;
  int local_9c;
  int *local_98;
  undefined1 auStack_94 [4];
  int local_90;
  undefined4 local_8c;
  undefined *local_7c;
  undefined *local_78;
  undefined1 *local_74;
  undefined4 local_70;
  undefined1 *local_6c;

  local_74 = &stack0xfffffff8;
  local_6c = (undefined1 *)&local_c4;
  local_7c = PTR_001b615c;
  local_78 = &::GCC_except_table0;
  local_70 = 0xd66e8;
  local_c0 = param_3;
  local_bc = param_2;
  local_b8 = this;
  __Unwind_SjLj_Register(auStack_94);
  local_a8 = local_bc;
  piVar6 = *(int **)(local_b8 + 4);
  piVar3 = *(int **)(local_b8 + 8);
  if (piVar6 == piVar3) {
    uVar1 = (int)piVar6 - *(int *)local_b8 >> 2;
    if (uVar1 == 0x3fffffff) {
      local_90 = 0xffffffff;
      std::__throw_length_error("vector::_M_insert_aux");
LAB_000d66dc:
      local_90 = -1;
      std::__throw_bad_alloc();
      local_c4 = local_8c;
      if ((local_90 == 1) && (local_a4 != (OFSmartObject *)0x0)) {
        local_90 = 0;
        OFSmartObject::Release(local_a4);
      }
      local_90 = 0xffffffff;
                    /* WARNING: Subroutine does not return */
      __Unwind_SjLj_Resume(local_c4);
    }
    if (uVar1 == 0) {
      uVar5 = 1;
    }
    else {
      uVar5 = uVar1 << 1;
    }
    if (uVar5 < uVar1) {
      local_a0 = 0xfffffffc;
    }
    else {
      if (0x3fffffff < uVar5) goto LAB_000d66dc;
      local_a0 = uVar5 << 2;
    }
    local_90 = 0xffffffff;
    local_b4 = operator_new(local_a0);
    piVar3 = *(int **)local_b8;
    piVar6 = local_b4;
    pvVar7 = local_b8;
    while (local_a8 != piVar3) {
      bVar8 = piVar6 != (int *)0x0;
      if (bVar8) {
        pvVar7 = (vector<OFPointer<OFXmlElement>,std::allocator<OFPointer<OFXmlElement>>> *)*piVar3;
        *piVar6 = (int)pvVar7;
      }
      piVar3 = piVar3 + 1;
      piVar6 = piVar6 + 1;
      if (bVar8 && pvVar7 != (vector<OFPointer<OFXmlElement>,std::allocator<OFPointer<OFXmlElement>>>
                              *)0x0) {
        *(int *)(pvVar7 + 4) = *(int *)(pvVar7 + 4) + 1;
      }
    }
    if (piVar6 != (int *)0x0) {
      pvVar7 = (vector<OFPointer<OFXmlElement>,std::allocator<OFPointer<OFXmlElement>>> *)*local_c0;
      *piVar6 = (int)pvVar7;
    }
    if (piVar6 != (int *)0x0 &&
        pvVar7 != (vector<OFPointer<OFXmlElement>,std::allocator<OFPointer<OFXmlElement>>> *)0x0) {
      *(int *)(pvVar7 + 4) = *(int *)(pvVar7 + 4) + 1;
    }
    piVar3 = *(int **)(local_b8 + 4);
    pvVar7 = local_b8;
    local_b0 = (vector<OFPointer<OFXmlElement>,std::allocator<OFPointer<OFXmlElement>>> *)
               (piVar6 + 1);
    if (local_a8 != piVar3) {
      do {
        if (local_b0 !=
            (vector<OFPointer<OFXmlElement>,std::allocator<OFPointer<OFXmlElement>>> *)0x0) {
          pvVar7 = (vector<OFPointer<OFXmlElement>,std::allocator<OFPointer<OFXmlElement>>> *)
                   *local_a8;
          *(vector<OFPointer<OFXmlElement>,std::allocator<OFPointer<OFXmlElement>>> **)local_b0 =
               pvVar7;
        }
        local_a8 = local_a8 + 1;
        if (local_b0 !=
            (vector<OFPointer<OFXmlElement>,std::allocator<OFPointer<OFXmlElement>>> *)0x0 &&
            pvVar7 != (vector<OFPointer<OFXmlElement>,std::allocator<OFPointer<OFXmlElement>>> *)0x0
           ) {
          *(int *)(pvVar7 + 4) = *(int *)(pvVar7 + 4) + 1;
        }
        pvVar7 = local_b0 + 4;
        local_b0 = pvVar7;
      } while (piVar3 != local_a8);
      local_a8 = *(int **)(local_b8 + 4);
    }
    piVar3 = *(int **)local_b8;
    if (local_a8 != *(int **)local_b8) {
      do {
        local_98 = piVar3;
        if ((OFSmartObject *)*local_98 != (OFSmartObject *)0x0) {
          local_90 = 1;
          OFSmartObject::Release((OFSmartObject *)*local_98);
        }
        local_98 = local_98 + 1;
        piVar3 = local_98;
      } while (local_a8 != local_98);
      local_a8 = *(int **)local_b8;
    }
    if (local_a8 != (int *)0x0) {
      operator_delete(local_a8);
    }
    *(int **)local_b8 = local_b4;
    *(vector<OFPointer<OFXmlElement>,std::allocator<OFPointer<OFXmlElement>>> **)(local_b8 + 4) =
         local_b0;
    *(ulong *)(local_b8 + 8) = (int)local_b4 + local_a0;
  }
  else {
    if (piVar6 != (int *)0x0) {
      piVar3 = (int *)piVar6[-1];
      *piVar6 = (int)piVar3;
    }
    if (piVar6 != (int *)0x0 && piVar3 != (int *)0x0) {
      piVar3[1] = piVar3[1] + 1;
    }
    *(int *)(local_b8 + 4) = *(int *)(local_b8 + 4) + 4;
    local_a4 = (OFSmartObject *)*local_c0;
    if (local_a4 != (OFSmartObject *)0x0) {
      *(int *)(local_a4 + 4) = *(int *)(local_a4 + 4) + 1;
    }
    iVar4 = *(int *)(local_b8 + 4);
    local_ac = (iVar4 + -8) - (int)local_bc >> 2;
    if (0 < local_ac) {
      do {
        pOVar2 = *(OFSmartObject **)(iVar4 + -8);
        local_9c = iVar4;
        if (*(OFSmartObject **)(iVar4 + -0xc) != pOVar2) {
          if (pOVar2 != (OFSmartObject *)0x0) {
            local_90 = 2;
            OFSmartObject::Release(pOVar2);
          }
          iVar4 = *(int *)(local_9c + -0xc);
          *(int *)(local_9c + -8) = iVar4;
          if (iVar4 != 0) {
            *(int *)(iVar4 + 4) = *(int *)(iVar4 + 4) + 1;
          }
        }
        iVar4 = local_9c + -4;
        local_ac = local_ac + -1;
        local_9c = iVar4;
      } while (local_ac != 0);
    }
    pOVar2 = (OFSmartObject *)*local_a8;
    if (local_a4 == pOVar2) {
      if (local_a4 == (OFSmartObject *)0x0) goto LAB_000d64e8;
    }
    else {
      if (pOVar2 != (OFSmartObject *)0x0) {
        local_90 = 2;
        OFSmartObject::Release(pOVar2);
      }
      *local_a8 = (int)local_a4;
      if (local_a4 == (OFSmartObject *)0x0) goto LAB_000d64e8;
      *(int *)(local_a4 + 4) = *(int *)(local_a4 + 4) + 1;
    }
    local_90 = 0xffffffff;
    OFSmartObject::Release(local_a4);
  }
LAB_000d64e8:
  __Unwind_SjLj_Unregister(auStack_94);
  return;
}
