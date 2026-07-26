/*
 * mangled: _ZNSt6vectorIN13OFViewDataMap14FieldReferenceESaIS1_EE13_M_insert_auxEN9__gnu_cxx17__normal_iteratorIPS1_S3_EERKS1_
 * demangled: std::vector<OFViewDataMap::FieldReference, std::allocator<OFViewDataMap::FieldReference>>::_M_insert_aux(__gnu_cxx::__normal_iterator<OFViewDataMap::FieldReference*, std::vector<OFViewDataMap::FieldReference, std::allocator<OFViewDataMap::FieldReference>>>, OFViewDataMap::FieldReference const&)
 * address: 000fcbd4
 * size: 1972
 */

/* std::vector<OFViewDataMap::FieldReference, std::allocator<OFViewDataMap::FieldReference>
   >::_M_insert_aux(__gnu_cxx::__normal_iterator<OFViewDataMap::FieldReference*,
   std::vector<OFViewDataMap::FieldReference, std::allocator<OFViewDataMap::FieldReference> > >,
   OFViewDataMap::FieldReference const&) */

void __thiscall
std::vector<OFViewDataMap::FieldReference,std::allocator<OFViewDataMap::FieldReference>>::
_M_insert_aux(vector<OFViewDataMap::FieldReference,std::allocator<OFViewDataMap::FieldReference>>
              *this,ID *param_2,ID *param_3)

{
  int iVar1;
  ID IVar2;
  uint uVar3;
  ID *pIVar4;
  uint uVar5;
  undefined4 local_124;
  ID *local_120;
  ID *local_11c;
  vector<OFViewDataMap::FieldReference,std::allocator<OFViewDataMap::FieldReference>> *local_118;
  ID *local_114;
  ID *local_110;
  ID *local_10c;
  ID *local_108;
  int local_104;
  char *local_100;
  SEL local_fc;
  ID *local_f8;
  ID *local_f4;
  SEL local_f0;
  SEL local_ec;
  ID *local_e8;
  SEL local_e4;
  SEL local_e0;
  SEL local_dc;
  ID *local_d8;
  SEL local_d4;
  ID *local_d0;
  ID local_cc;
  ID local_c8;
  ID local_c4;
  ulong local_c0;
  int local_bc;
  ID *local_b8;
  ID *local_b4;
  ID *local_b0;
  ID *local_ac;
  ID *local_a8;
  ID *local_a4;
  ID *local_a0;
  ID *local_9c;
  ID *local_98;
  undefined1 auStack_94 [4];
  int local_90;
  undefined4 local_8c;
  undefined *local_7c;
  undefined *local_78;
  undefined1 *local_74;
  undefined4 local_70;
  undefined1 *local_6c;

  local_74 = &stack0xfffffff8;
  local_6c = (undefined1 *)&local_124;
  local_7c = PTR_001b615c;
  local_78 = &::GCC_except_table0;
  local_70 = 0xfd178;
  local_120 = param_3;
  local_11c = param_2;
  local_118 = this;
  __Unwind_SjLj_Register(auStack_94);
  local_d0 = local_11c;
  local_114 = *(ID **)(local_118 + 4);
  if (local_114 != *(ID **)(local_118 + 8)) {
    if (local_114 != (ID *)0x0) {
      local_108 = local_114 + -3;
      IVar2 = local_114[-3];
      *local_114 = IVar2;
      if (IVar2 != 0) {
        local_90 = 6;
        _objc_msgSend(IVar2,"retain");
      }
      local_114[1] = local_108[1];
      local_114[2] = local_108[2];
    }
    *(int *)(local_118 + 4) = *(int *)(local_118 + 4) + 0xc;
    local_c4 = *local_120;
    if (local_c4 != 0) {
      local_90 = 0xffffffff;
      _objc_msgSend(local_c4,"retain");
    }
    local_c8 = local_120[1];
    local_cc = local_120[2];
    local_104 = ((*(int *)(local_118 + 4) + -0x18) - (int)local_d0 >> 2) * -0x55555555;
    if (0 < local_104) {
      local_fc = "release";
      local_100 = "retain";
      local_bc = *(int *)(local_118 + 4);
      do {
        IVar2 = *(ID *)(local_bc + -0x18);
        if (IVar2 != *(ID *)(local_bc + -0x24)) {
          if (IVar2 != 0) {
            local_90 = 10;
            _objc_msgSend(IVar2,local_fc);
          }
          IVar2 = *(ID *)(local_bc + -0x24);
          *(ID *)(local_bc + -0x18) = IVar2;
          if (IVar2 != 0) {
            local_90 = 10;
            _objc_msgSend(IVar2,local_100);
          }
        }
        *(undefined4 *)(local_bc + -0x14) = *(undefined4 *)(local_bc + -0x20);
        *(undefined4 *)(local_bc + -0x10) = *(undefined4 *)(local_bc + -0x1c);
        local_bc = local_bc + -0xc;
        local_104 = local_104 + -1;
      } while (local_104 != 0);
    }
    IVar2 = *local_d0;
    if (local_c4 != IVar2) {
      if (IVar2 != 0) {
        local_90 = 10;
        _objc_msgSend(IVar2,"release");
      }
      *local_d0 = local_c4;
      if (local_c4 == 0) {
        local_d0[1] = local_c8;
        local_d0[2] = local_cc;
        goto LAB_000fce40;
      }
      local_90 = 10;
      _objc_msgSend(local_c4,"retain");
    }
    local_d0[1] = local_c8;
    local_d0[2] = local_cc;
    if (local_c4 != 0) {
      local_90 = 0xffffffff;
      _objc_msgSend(local_c4,"release");
    }
    goto LAB_000fce40;
  }
  iVar1 = (int)local_114 - *(int *)local_118 >> 2;
  uVar5 = iVar1 * -0x55555555;
  if (uVar5 != 0x15555555) {
    if (uVar5 == 0) {
      uVar3 = 1;
    }
    else {
      uVar3 = iVar1 * 0x55555556;
    }
    if (uVar3 < uVar5) {
      local_c0 = 0xfffffffc;
    }
    else {
      if (0x15555555 < uVar3) goto LAB_000fd16c;
      local_c0 = uVar3 * 0xc;
    }
    local_90 = 0xffffffff;
    local_110 = operator_new(local_c0);
    local_f4 = *(ID **)local_118;
    local_f8 = local_110;
    local_98 = local_110;
    if (local_d0 != local_f4) {
      local_f0 = "retain";
      local_10c = local_110;
      local_ac = local_110 + 3;
      do {
        if (local_98 != (ID *)0x0) {
          IVar2 = *local_f4;
          *local_98 = IVar2;
          if (IVar2 != 0) {
            local_90 = 4;
            _objc_msgSend(IVar2,local_f0);
          }
          local_98[1] = local_f4[1];
          local_98[2] = local_f4[2];
        }
        pIVar4 = local_ac + 3;
        local_98 = local_ac;
        local_f4 = local_f4 + 3;
        local_ac = pIVar4;
      } while (local_d0 != local_f4);
    }
    local_10c = local_98;
    if (local_98 != (ID *)0x0) {
      IVar2 = *local_120;
      *local_98 = IVar2;
      if (IVar2 != 0) {
        local_90 = 3;
        _objc_msgSend(IVar2,"retain");
      }
      local_10c[1] = local_120[1];
      local_10c[2] = local_120[2];
    }
    local_10c = local_10c + 3;
    local_e8 = *(ID **)(local_118 + 4);
    local_a8 = local_10c;
    if (local_d0 != local_e8) {
      local_b4 = local_d0;
      local_e4 = "retain";
      pIVar4 = local_98 + 6;
      local_a4 = local_10c;
      do {
        local_b0 = pIVar4;
        if (local_a4 != (ID *)0x0) {
          IVar2 = *local_b4;
          *local_a4 = IVar2;
          if (IVar2 != 0) {
            local_90 = 1;
            _objc_msgSend(IVar2,local_e4);
          }
          local_a4[1] = local_b4[1];
          local_a4[2] = local_b4[2];
        }
        local_a4 = local_b0;
        local_b4 = local_b4 + 3;
        pIVar4 = local_b0 + 3;
      } while (local_e8 != local_b4);
      local_d0 = *(ID **)(local_118 + 4);
      local_a8 = local_b0;
      local_b0 = local_b0 + 3;
    }
    if (*(ID **)local_118 != local_d0) {
      local_dc = "release";
      local_b8 = *(ID **)local_118;
      do {
        if (*local_b8 != 0) {
          local_90 = 7;
          _objc_msgSend(*local_b8,local_dc);
        }
        local_b8 = local_b8 + 3;
      } while (local_b8 != local_d0);
      local_d0 = *(ID **)local_118;
    }
    if (local_d0 != (ID *)0x0) {
      operator_delete(local_d0);
    }
    *(ID **)local_118 = local_110;
    *(ID **)(local_118 + 4) = local_a8;
    *(ulong *)(local_118 + 8) = (int)local_110 + local_c0;
LAB_000fce40:
    __Unwind_SjLj_Unregister(auStack_94);
    return;
  }
  local_90 = 0xffffffff;
  std::__throw_length_error("vector::_M_insert_aux");
LAB_000fd16c:
  local_90 = -1;
  std::__throw_bad_alloc();
  local_124 = local_8c;
  if (local_90 != 1) {
    if (local_90 == 2) goto LAB_000fd300;
    if (local_90 == 3) {
      ___cxa_begin_catch(local_8c);
      if (local_110 != local_98) {
        local_ec = "release";
        local_a0 = local_110;
        do {
          if (*local_a0 != 0) {
            local_90 = 5;
            _objc_msgSend(*local_a0,local_ec);
          }
          local_a0 = local_a0 + 3;
        } while (local_a0 != local_98);
      }
      local_90 = 5;
                    /* WARNING: Subroutine does not return */
      ___cxa_rethrow();
    }
    if (local_90 != 4) {
      if ((local_90 != 5) && (local_90 != 6)) {
        if ((local_90 == 7) || (local_90 == 8)) {
          local_90 = 0;
          ___cxa_end_catch();
          local_90 = 0xffffffff;
                    /* WARNING: Subroutine does not return */
          __Unwind_SjLj_Resume(local_124);
        }
        if (local_90 != 9) {
          ___cxa_begin_catch(local_8c);
          if (local_a8 != local_a4) {
            local_e0 = "release";
            do {
              if (*local_a8 != 0) {
                local_90 = 2;
                _objc_msgSend(*local_a8,local_e0);
              }
              local_a8 = local_a8 + 3;
            } while (local_a8 != local_a4);
          }
          local_90 = 2;
                    /* WARNING: Subroutine does not return */
          ___cxa_rethrow();
        }
        if (local_c4 != 0) {
          local_90 = 0;
          _objc_msgSend(local_c4,"release");
        }
      }
      local_90 = 0xffffffff;
                    /* WARNING: Subroutine does not return */
      __Unwind_SjLj_Resume(local_124);
    }
  }
  local_90 = 0;
  ___cxa_end_catch();
LAB_000fd300:
  ___cxa_begin_catch(local_124);
  local_d8 = local_10c;
  if (local_110 != local_10c) {
    local_d4 = "release";
    local_9c = local_110;
    do {
      if (*local_9c != 0) {
        local_90 = 8;
        _objc_msgSend(*local_9c,local_d4);
      }
      local_9c = local_9c + 3;
    } while (local_d8 != local_9c);
  }
  if (local_f8 != (ID *)0x0) {
    operator_delete(local_110);
  }
  local_90 = 9;
                    /* WARNING: Subroutine does not return */
  ___cxa_rethrow();
}
