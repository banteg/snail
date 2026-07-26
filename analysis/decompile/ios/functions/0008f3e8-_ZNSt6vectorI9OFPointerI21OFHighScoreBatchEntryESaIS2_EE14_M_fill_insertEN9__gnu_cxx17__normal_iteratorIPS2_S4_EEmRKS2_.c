/*
 * mangled: _ZNSt6vectorI9OFPointerI21OFHighScoreBatchEntryESaIS2_EE14_M_fill_insertEN9__gnu_cxx17__normal_iteratorIPS2_S4_EEmRKS2_
 * demangled: std::vector<OFPointer<OFHighScoreBatchEntry>, std::allocator<OFPointer<OFHighScoreBatchEntry>>>::_M_fill_insert(__gnu_cxx::__normal_iterator<OFPointer<OFHighScoreBatchEntry>*, std::vector<OFPointer<OFHighScoreBatchEntry>, std::allocator<OFPointer<OFHighScoreBatchEntry>>>>, unsigned long, OFPointer<OFHighScoreBatchEntry> const&)
 * address: 0008f3e8
 * size: 1656
 */

/* std::vector<OFPointer<OFHighScoreBatchEntry>, std::allocator<OFPointer<OFHighScoreBatchEntry> >
   >::_M_fill_insert(__gnu_cxx::__normal_iterator<OFPointer<OFHighScoreBatchEntry>*,
   std::vector<OFPointer<OFHighScoreBatchEntry>, std::allocator<OFPointer<OFHighScoreBatchEntry> > >
   >, unsigned long, OFPointer<OFHighScoreBatchEntry> const&) */

void __thiscall
std::vector<OFPointer<OFHighScoreBatchEntry>,std::allocator<OFPointer<OFHighScoreBatchEntry>>>::
_M_fill_insert(vector<OFPointer<OFHighScoreBatchEntry>,std::allocator<OFPointer<OFHighScoreBatchEntry>>>
               *this,uint *param_2,uint param_3,undefined4 *param_4)

{
  undefined4 *puVar1;
  OFSmartObject *pOVar2;
  uint *puVar3;
  undefined4 *puVar4;
  int extraout_r1;
  int iVar5;
  uint uVar6;
  uint *puVar7;
  vector<OFPointer<OFHighScoreBatchEntry>,std::allocator<OFPointer<OFHighScoreBatchEntry>>> *pvVar8;
  uint in_r12;
  bool bVar9;
  undefined1 auStack_e8 [4];
  undefined4 *local_e4;
  uint *local_e0;
  vector<OFPointer<OFHighScoreBatchEntry>,std::allocator<OFPointer<OFHighScoreBatchEntry>>>
  *local_dc;
  uint *local_d8;
  undefined4 *local_d4;
  vector<OFPointer<OFHighScoreBatchEntry>,std::allocator<OFPointer<OFHighScoreBatchEntry>>>
  *local_d0;
  int local_cc;
  uint *local_c8;
  uint *local_c4;
  OFSmartObject *local_c0;
  ulong local_bc;
  uint *local_b8;
  uint *local_b4;
  uint *local_b0;
  uint *local_ac;
  uint *local_a8;
  uint *local_a4;
  uint *local_a0;
  undefined1 auStack_9c [4];
  undefined4 local_98;
  undefined *local_84;
  undefined *local_80;
  undefined1 *local_7c;
  undefined1 *local_78;
  undefined1 *local_74;
  uint local_68;
  uint local_64 [17];

  local_7c = &stack0xfffffff8;
  local_74 = auStack_e8;
  local_84 = PTR_001b615c;
  local_80 = &::GCC_except_table4;
  local_78 = &LAB_0008f99c;
  local_e4 = param_4;
  local_e0 = param_2;
  local_dc = this;
  local_68 = param_3;
  __Unwind_SjLj_Register(auStack_9c);
  local_c4 = local_e0;
  if (local_68 == 0) goto LAB_0008f640;
  local_d8 = *(uint **)(local_dc + 4);
  if ((uint)(*(int *)(local_dc + 8) - (int)local_d8 >> 2) < local_68) {
    local_64[0] = (int)local_d8 - *(int *)local_dc >> 2;
    if (local_68 <= 0x3fffffff - local_64[0]) {
      if (local_64[0] < local_68) {
        puVar3 = &local_68;
      }
      else {
        puVar3 = local_64;
      }
      uVar6 = local_64[0] + *puVar3;
      if (CARRY4(local_64[0],*puVar3)) {
        local_bc = 0xfffffffc;
      }
      else {
        if (0x3fffffff < uVar6) {
          local_98 = 0xffffffff;
          puVar1 = (undefined4 *)std::__throw_bad_alloc();
          goto LAB_0008f930;
        }
        local_bc = uVar6 * 4;
      }
      local_98 = 0xffffffff;
      local_d4 = operator_new(local_bc);
      puVar3 = *(uint **)local_dc;
      puVar1 = local_d4;
      puVar7 = local_c4;
      while (local_c4 != puVar3) {
        bVar9 = puVar1 != (undefined4 *)0x0;
        if (bVar9) {
          puVar7 = (uint *)*puVar3;
          *puVar1 = puVar7;
        }
        puVar3 = puVar3 + 1;
        puVar1 = puVar1 + 1;
        if (bVar9 && puVar7 != (uint *)0x0) {
          puVar7[1] = puVar7[1] + 1;
        }
      }
      uVar6 = local_68;
      puVar4 = puVar1;
      if (local_68 != 0) {
        while( true ) {
          if (puVar4 != (undefined4 *)0x0) {
            puVar7 = (uint *)*local_e4;
            *puVar4 = puVar7;
          }
          if (puVar4 != (undefined4 *)0x0 && puVar7 != (uint *)0x0) {
            puVar7[1] = puVar7[1] + 1;
          }
          if (uVar6 - 1 == 0) break;
          uVar6 = uVar6 - 1;
          puVar4 = puVar4 + 1;
        }
      }
      puVar3 = *(uint **)(local_dc + 4);
      pvVar8 = local_dc;
      local_d0 = (vector<OFPointer<OFHighScoreBatchEntry>,std::allocator<OFPointer<OFHighScoreBatchEntry>>>
                  *)(puVar1 + local_68);
      if (local_c4 != puVar3) {
        do {
          if (local_d0 !=
              (vector<OFPointer<OFHighScoreBatchEntry>,std::allocator<OFPointer<OFHighScoreBatchEntry>>>
               *)0x0) {
            pvVar8 = (vector<OFPointer<OFHighScoreBatchEntry>,std::allocator<OFPointer<OFHighScoreBatchEntry>>>
                      *)*local_c4;
            *(vector<OFPointer<OFHighScoreBatchEntry>,std::allocator<OFPointer<OFHighScoreBatchEntry>>>
              **)local_d0 = pvVar8;
          }
          local_c4 = local_c4 + 1;
          if (local_d0 !=
              (vector<OFPointer<OFHighScoreBatchEntry>,std::allocator<OFPointer<OFHighScoreBatchEntry>>>
               *)0x0 && pvVar8 != (vector<OFPointer<OFHighScoreBatchEntry>,std::allocator<OFPointer<OFHighScoreBatchEntry>>>
                                   *)0x0) {
            *(int *)(pvVar8 + 4) = *(int *)(pvVar8 + 4) + 1;
          }
          pvVar8 = local_d0 + 4;
          local_d0 = pvVar8;
        } while (puVar3 != local_c4);
        local_c4 = *(uint **)(local_dc + 4);
      }
      puVar3 = *(uint **)local_dc;
      if (*(uint **)local_dc != local_c4) {
        do {
          local_a8 = puVar3;
          if ((OFSmartObject *)*local_a8 != (OFSmartObject *)0x0) {
            local_98 = 1;
            OFSmartObject::Release((OFSmartObject *)*local_a8);
          }
          local_a8 = local_a8 + 1;
          puVar3 = local_a8;
        } while (local_a8 != local_c4);
        local_c4 = *(uint **)local_dc;
      }
      if (local_c4 != (uint *)0x0) {
        operator_delete(local_c4);
      }
      *(undefined4 **)local_dc = local_d4;
      *(vector<OFPointer<OFHighScoreBatchEntry>,std::allocator<OFPointer<OFHighScoreBatchEntry>>> **
       )(local_dc + 4) = local_d0;
      *(ulong *)(local_dc + 8) = (int)local_d4 + local_bc;
      goto LAB_0008f640;
    }
    local_98 = 0xffffffff;
    std::__throw_length_error("vector::_M_fill_insert");
    iVar5 = extraout_r1;
    puVar3 = local_d8;
LAB_0008f974:
    while( true ) {
      if (puVar3 != (uint *)0x0) {
        *puVar3 = (uint)local_c0;
        *(int *)(local_c0 + 4) = *(int *)(local_c0 + 4) + 1;
      }
      iVar5 = iVar5 + -1;
      if (iVar5 == 0) break;
      puVar3 = puVar3 + 1;
    }
LAB_0008f6d0:
    puVar1 = (undefined4 *)((local_68 - in_r12) * 4 + *(int *)(local_dc + 4));
    *(undefined4 **)(local_dc + 4) = puVar1;
    if (local_c4 == local_d8) {
LAB_0008f930:
      *(undefined4 **)(local_dc + 4) = puVar1 + in_r12;
      goto LAB_0008f940;
    }
    local_a0 = local_c4;
    local_a4 = local_c4;
    while( true ) {
      puVar3 = local_d8;
      if (puVar1 != (undefined4 *)0x0) {
        puVar3 = (uint *)*local_a4;
        *puVar1 = puVar3;
      }
      if (puVar1 != (undefined4 *)0x0 && puVar3 != (uint *)0x0) {
        puVar3[1] = puVar3[1] + 1;
      }
      local_a4 = local_a4 + 1;
      if (local_a4 == local_d8) break;
      puVar1 = puVar1 + 1;
    }
    *(uint *)(local_dc + 4) = *(int *)(local_dc + 4) + in_r12 * 4;
    if (local_c0 == (OFSmartObject *)0x0) {
      do {
        if ((OFSmartObject *)*local_a0 != (OFSmartObject *)0x0) {
          local_98 = 2;
          OFSmartObject::Release((OFSmartObject *)*local_a0);
          *local_a0 = 0;
        }
        local_a0 = local_a0 + 1;
      } while (local_d8 != local_a0);
      goto LAB_0008f640;
    }
    do {
      pOVar2 = (OFSmartObject *)*local_a0;
      if (local_c0 != pOVar2) {
        if (pOVar2 != (OFSmartObject *)0x0) {
          local_98 = 2;
          OFSmartObject::Release(pOVar2);
        }
        *local_a0 = (uint)local_c0;
        *(int *)(local_c0 + 4) = *(int *)(local_c0 + 4) + 1;
      }
      local_a0 = local_a0 + 1;
    } while (local_a0 != local_a4);
  }
  else {
    local_c0 = (OFSmartObject *)*local_e4;
    if (local_c0 != (OFSmartObject *)0x0) {
      *(int *)(local_c0 + 4) = *(int *)(local_c0 + 4) + 1;
      local_d8 = *(uint **)(local_dc + 4);
    }
    in_r12 = (int)local_d8 - (int)local_e0 >> 2;
    if (in_r12 <= local_68) {
      iVar5 = local_68 - in_r12;
      if (iVar5 != 0) {
        puVar3 = local_d8;
        if (local_c0 != (OFSmartObject *)0x0) goto LAB_0008f974;
        while( true ) {
          if (puVar3 != (uint *)0x0) {
            *puVar3 = 0;
          }
          iVar5 = iVar5 + -1;
          if (iVar5 == 0) break;
          puVar3 = puVar3 + 1;
        }
      }
      goto LAB_0008f6d0;
    }
    puVar3 = local_d8 + -local_68;
    puVar7 = local_d8;
    uVar6 = local_68;
    if (puVar3 != local_d8) {
      while( true ) {
        if (puVar7 != (uint *)0x0) {
          uVar6 = *puVar3;
          *puVar7 = uVar6;
        }
        puVar3 = puVar3 + 1;
        if (puVar7 != (uint *)0x0 && uVar6 != 0) {
          *(int *)(uVar6 + 4) = *(int *)(uVar6 + 4) + 1;
        }
        if (puVar3 == local_d8) break;
        puVar7 = puVar7 + 1;
      }
    }
    *(uint *)(local_dc + 4) = *(int *)(local_dc + 4) + local_68 * 4;
    local_cc = (int)(local_d8 + -local_68) - (int)local_e0 >> 2;
    if (0 < local_cc) {
      local_b0 = local_d8;
      local_ac = local_d8 + -local_68;
      do {
        pOVar2 = (OFSmartObject *)local_b0[-1];
        if ((OFSmartObject *)local_ac[-1] != pOVar2) {
          if (pOVar2 != (OFSmartObject *)0x0) {
            local_98 = 2;
            OFSmartObject::Release(pOVar2);
          }
          uVar6 = local_ac[-1];
          local_b0[-1] = uVar6;
          if (uVar6 != 0) {
            *(int *)(uVar6 + 4) = *(int *)(uVar6 + 4) + 1;
          }
        }
        local_b0 = local_b0 + -1;
        local_ac = local_ac + -1;
        local_cc = local_cc + -1;
      } while (local_cc != 0);
    }
    local_c8 = local_c4 + local_68;
    if (local_c4 != local_c8) {
      if (local_c0 == (OFSmartObject *)0x0) {
        local_b8 = local_c4;
        do {
          if ((OFSmartObject *)*local_b8 != (OFSmartObject *)0x0) {
            local_98 = 2;
            OFSmartObject::Release((OFSmartObject *)*local_b8);
            *local_b8 = 0;
          }
          local_b8 = local_b8 + 1;
        } while (local_c8 != local_b8);
        goto LAB_0008f640;
      }
      local_b4 = local_c4;
      do {
        pOVar2 = (OFSmartObject *)*local_b4;
        if (local_c0 != pOVar2) {
          if (pOVar2 != (OFSmartObject *)0x0) {
            local_98 = 2;
            OFSmartObject::Release(pOVar2);
          }
          *local_b4 = (uint)local_c0;
          *(int *)(local_c0 + 4) = *(int *)(local_c0 + 4) + 1;
        }
        local_b4 = local_b4 + 1;
      } while (local_c8 != local_b4);
      goto LAB_0008f94c;
    }
LAB_0008f940:
    if (local_c0 == (OFSmartObject *)0x0) goto LAB_0008f640;
  }
LAB_0008f94c:
  local_98 = 0xffffffff;
  OFSmartObject::Release(local_c0);
LAB_0008f640:
  __Unwind_SjLj_Unregister(auStack_9c);
  return;
}
