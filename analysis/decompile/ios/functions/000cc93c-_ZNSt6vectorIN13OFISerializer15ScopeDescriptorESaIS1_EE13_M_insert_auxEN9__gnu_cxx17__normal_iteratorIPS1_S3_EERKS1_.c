/*
 * mangled: _ZNSt6vectorIN13OFISerializer15ScopeDescriptorESaIS1_EE13_M_insert_auxEN9__gnu_cxx17__normal_iteratorIPS1_S3_EERKS1_
 * demangled: std::vector<OFISerializer::ScopeDescriptor, std::allocator<OFISerializer::ScopeDescriptor>>::_M_insert_aux(__gnu_cxx::__normal_iterator<OFISerializer::ScopeDescriptor*, std::vector<OFISerializer::ScopeDescriptor, std::allocator<OFISerializer::ScopeDescriptor>>>, OFISerializer::ScopeDescriptor const&)
 * address: 000cc93c
 * size: 1096
 */

/* std::vector<OFISerializer::ScopeDescriptor, std::allocator<OFISerializer::ScopeDescriptor>
   >::_M_insert_aux(__gnu_cxx::__normal_iterator<OFISerializer::ScopeDescriptor*,
   std::vector<OFISerializer::ScopeDescriptor, std::allocator<OFISerializer::ScopeDescriptor> > >,
   OFISerializer::ScopeDescriptor const&) */

void __thiscall
std::vector<OFISerializer::ScopeDescriptor,std::allocator<OFISerializer::ScopeDescriptor>>::
_M_insert_aux(vector<OFISerializer::ScopeDescriptor,std::allocator<OFISerializer::ScopeDescriptor>>
              *this,int *param_2,int *param_3)

{
  uint uVar1;
  OFSmartObject *pOVar2;
  int iVar3;
  uint uVar4;
  int *piVar5;
  undefined4 local_c8;
  int *local_c4;
  int *local_c0;
  vector<OFISerializer::ScopeDescriptor,std::allocator<OFISerializer::ScopeDescriptor>> *local_bc;
  int *local_b8;
  int local_b4;
  int *local_b0;
  uint local_ac;
  OFSmartObject *local_a8;
  ulong local_a4;
  int local_a0;
  int *local_9c;
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
  local_6c = (undefined1 *)&local_c8;
  local_7c = PTR_001b615c;
  local_78 = &GCC_except_table15;
  local_70 = 0xccd40;
  local_c4 = param_3;
  local_c0 = param_2;
  local_bc = this;
  __Unwind_SjLj_Register(auStack_94);
  local_b0 = local_c0;
  piVar5 = *(int **)(local_bc + 4);
  if (piVar5 == *(int **)(local_bc + 8)) {
    uVar1 = (int)piVar5 - *(int *)local_bc >> 3;
    if (uVar1 == 0x1fffffff) {
      local_90 = 0xffffffff;
      std::__throw_length_error("vector::_M_insert_aux");
LAB_000ccd34:
      local_90 = -1;
      std::__throw_bad_alloc();
      local_c8 = local_8c;
      if ((local_90 == 1) && (local_a8 != (OFSmartObject *)0x0)) {
        local_90 = 0;
        OFSmartObject::Release(local_a8);
      }
      local_90 = 0xffffffff;
                    /* WARNING: Subroutine does not return */
      __Unwind_SjLj_Resume(local_c8);
    }
    if (uVar1 == 0) {
      uVar4 = 1;
    }
    else {
      uVar4 = uVar1 << 1;
    }
    if (uVar4 < uVar1) {
      local_a4 = 0xfffffff8;
    }
    else {
      if (0x1fffffff < uVar4) goto LAB_000ccd34;
      local_a4 = uVar4 << 3;
    }
    local_90 = 0xffffffff;
    local_b8 = operator_new(local_a4);
    local_98 = local_b8;
    for (piVar5 = *(int **)local_bc; local_b0 != piVar5; piVar5 = piVar5 + 2) {
      if (local_98 != (int *)0x0) {
        iVar3 = *piVar5;
        *local_98 = iVar3;
        if (iVar3 != 0) {
          *(int *)(iVar3 + 4) = *(int *)(iVar3 + 4) + 1;
        }
        *(char *)(local_98 + 1) = (char)piVar5[1];
      }
      local_98 = local_98 + 2;
    }
    if (local_98 != (int *)0x0) {
      iVar3 = *local_c4;
      *local_98 = iVar3;
      if (iVar3 != 0) {
        *(int *)(iVar3 + 4) = *(int *)(iVar3 + 4) + 1;
      }
      *(char *)(local_98 + 1) = (char)local_c4[1];
    }
    local_98 = local_98 + 2;
    piVar5 = *(int **)(local_bc + 4);
    if (local_b0 != piVar5) {
      do {
        if (local_98 != (int *)0x0) {
          iVar3 = *local_b0;
          *local_98 = iVar3;
          if (iVar3 != 0) {
            *(int *)(iVar3 + 4) = *(int *)(iVar3 + 4) + 1;
          }
          *(char *)(local_98 + 1) = (char)local_b0[1];
        }
        local_b0 = local_b0 + 2;
        local_98 = local_98 + 2;
      } while (piVar5 != local_b0);
      local_b0 = *(int **)(local_bc + 4);
    }
    piVar5 = *(int **)local_bc;
    if (*(int **)local_bc != local_b0) {
      do {
        local_9c = piVar5;
        if ((OFSmartObject *)*local_9c != (OFSmartObject *)0x0) {
          local_90 = 1;
          OFSmartObject::Release((OFSmartObject *)*local_9c);
        }
        local_9c = local_9c + 2;
        piVar5 = local_9c;
      } while (local_9c != local_b0);
      local_b0 = *(int **)local_bc;
    }
    if (local_b0 != (int *)0x0) {
      operator_delete(local_b0);
    }
    *(int **)local_bc = local_b8;
    *(int **)(local_bc + 4) = local_98;
    *(ulong *)(local_bc + 8) = (int)local_b8 + local_a4;
  }
  else {
    if (piVar5 != (int *)0x0) {
      iVar3 = piVar5[-2];
      *piVar5 = iVar3;
      if (iVar3 != 0) {
        *(int *)(iVar3 + 4) = *(int *)(iVar3 + 4) + 1;
      }
      *(char *)(piVar5 + 1) = (char)piVar5[-1];
    }
    *(int *)(local_bc + 4) = *(int *)(local_bc + 4) + 8;
    local_a8 = (OFSmartObject *)*local_c4;
    if (local_a8 != (OFSmartObject *)0x0) {
      *(int *)(local_a8 + 4) = *(int *)(local_a8 + 4) + 1;
    }
    local_ac = (uint)*(byte *)(local_c4 + 1);
    iVar3 = *(int *)(local_bc + 4);
    local_b4 = (iVar3 + -0x10) - (int)local_c0 >> 3;
    if (0 < local_b4) {
      do {
        pOVar2 = *(OFSmartObject **)(iVar3 + -0x10);
        local_a0 = iVar3;
        if (pOVar2 != *(OFSmartObject **)(iVar3 + -0x18)) {
          if (pOVar2 != (OFSmartObject *)0x0) {
            local_90 = 2;
            OFSmartObject::Release(pOVar2);
          }
          iVar3 = *(int *)(local_a0 + -0x18);
          *(int *)(local_a0 + -0x10) = iVar3;
          if (iVar3 != 0) {
            *(int *)(iVar3 + 4) = *(int *)(iVar3 + 4) + 1;
          }
        }
        *(undefined1 *)(local_a0 + -0xc) = *(undefined1 *)(local_a0 + -0x14);
        iVar3 = local_a0 + -8;
        local_b4 = local_b4 + -1;
        local_a0 = iVar3;
      } while (local_b4 != 0);
    }
    pOVar2 = (OFSmartObject *)*local_b0;
    if (local_a8 == pOVar2) {
      *(char *)(local_b0 + 1) = (char)local_ac;
      if (local_a8 == (OFSmartObject *)0x0) goto LAB_000ccaf8;
    }
    else {
      if (pOVar2 != (OFSmartObject *)0x0) {
        local_90 = 2;
        OFSmartObject::Release(pOVar2);
      }
      *local_b0 = (int)local_a8;
      if (local_a8 == (OFSmartObject *)0x0) {
        *(char *)(local_b0 + 1) = (char)local_ac;
        goto LAB_000ccaf8;
      }
      *(int *)(local_a8 + 4) = *(int *)(local_a8 + 4) + 1;
      *(char *)(local_b0 + 1) = (char)local_ac;
    }
    local_90 = 0xffffffff;
    OFSmartObject::Release(local_a8);
  }
LAB_000ccaf8:
  __Unwind_SjLj_Unregister(auStack_94);
  return;
}
