/*
 * mangled: _ZNSt6vectorIN17OFResourceDataMap16FieldDescriptionESaIS1_EE13_M_insert_auxEN9__gnu_cxx17__normal_iteratorIPS1_S3_EERKS1_
 * demangled: std::vector<OFResourceDataMap::FieldDescription, std::allocator<OFResourceDataMap::FieldDescription>>::_M_insert_aux(__gnu_cxx::__normal_iterator<OFResourceDataMap::FieldDescription*, std::vector<OFResourceDataMap::FieldDescription, std::allocator<OFResourceDataMap::FieldDescription>>>, OFResourceDataMap::FieldDescription const&)
 * address: 000fb0f0
 * size: 2112
 */

/* std::vector<OFResourceDataMap::FieldDescription,
   std::allocator<OFResourceDataMap::FieldDescription>
   >::_M_insert_aux(__gnu_cxx::__normal_iterator<OFResourceDataMap::FieldDescription*,
   std::vector<OFResourceDataMap::FieldDescription,
   std::allocator<OFResourceDataMap::FieldDescription> > >, OFResourceDataMap::FieldDescription
   const&) */

void __thiscall
std::vector<OFResourceDataMap::FieldDescription,std::allocator<OFResourceDataMap::FieldDescription>>
::_M_insert_aux(vector<OFResourceDataMap::FieldDescription,std::allocator<OFResourceDataMap::FieldDescription>>
                *this,ID *param_2,ID *param_3)

{
  int iVar1;
  ID IVar2;
  uint uVar3;
  ID *pIVar4;
  uint uVar5;
  undefined4 local_12c;
  ID *local_128;
  ID *local_124;
  vector<OFResourceDataMap::FieldDescription,std::allocator<OFResourceDataMap::FieldDescription>>
  *local_120;
  ID *local_11c;
  ID *local_118;
  ID *local_114;
  ID *local_110;
  int local_10c;
  char *local_108;
  SEL local_104;
  ID *local_100;
  ID *local_fc;
  SEL local_f8;
  SEL local_f4;
  ID *local_f0;
  SEL local_ec;
  SEL local_e8;
  SEL local_e4;
  ID *local_e0;
  SEL local_dc;
  ID *local_d8;
  uint local_d4;
  ID local_d0;
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
  local_6c = (undefined1 *)&local_12c;
  local_7c = PTR_001b615c;
  local_78 = &::GCC_except_table0;
  local_70 = 0xfb720;
  local_128 = param_3;
  local_124 = param_2;
  local_120 = this;
  __Unwind_SjLj_Register(auStack_94);
  local_d8 = local_124;
  local_11c = *(ID **)(local_120 + 4);
  if (local_11c != *(ID **)(local_120 + 8)) {
    if (local_11c != (ID *)0x0) {
      local_110 = local_11c + -5;
      IVar2 = local_11c[-5];
      *local_11c = IVar2;
      if (IVar2 != 0) {
        local_90 = 6;
        _objc_msgSend(IVar2,"retain");
      }
      local_11c[1] = local_110[1];
      local_11c[2] = local_110[2];
      local_11c[3] = local_110[3];
      *(char *)(local_11c + 4) = (char)local_110[4];
    }
    *(int *)(local_120 + 4) = *(int *)(local_120 + 4) + 0x14;
    local_c4 = *local_128;
    if (local_c4 != 0) {
      local_90 = 0xffffffff;
      _objc_msgSend(local_c4,"retain");
    }
    local_c8 = local_128[1];
    local_cc = local_128[2];
    local_d0 = local_128[3];
    local_d4 = (uint)(byte)local_128[4];
    local_10c = ((*(int *)(local_120 + 4) + -0x28) - (int)local_d8 >> 2) * -0x33333333;
    if (0 < local_10c) {
      local_104 = "release";
      local_108 = "retain";
      local_bc = *(int *)(local_120 + 4);
      do {
        IVar2 = *(ID *)(local_bc + -0x28);
        if (IVar2 != *(ID *)(local_bc + -0x3c)) {
          if (IVar2 != 0) {
            local_90 = 10;
            _objc_msgSend(IVar2,local_104);
          }
          IVar2 = *(ID *)(local_bc + -0x3c);
          *(ID *)(local_bc + -0x28) = IVar2;
          if (IVar2 != 0) {
            local_90 = 10;
            _objc_msgSend(IVar2,local_108);
          }
        }
        *(undefined4 *)(local_bc + -0x24) = *(undefined4 *)(local_bc + -0x38);
        *(undefined4 *)(local_bc + -0x20) = *(undefined4 *)(local_bc + -0x34);
        *(undefined4 *)(local_bc + -0x1c) = *(undefined4 *)(local_bc + -0x30);
        *(undefined1 *)(local_bc + -0x18) = *(undefined1 *)(local_bc + -0x2c);
        local_bc = local_bc + -0x14;
        local_10c = local_10c + -1;
      } while (local_10c != 0);
    }
    IVar2 = *local_d8;
    if (local_c4 != IVar2) {
      if (IVar2 != 0) {
        local_90 = 10;
        _objc_msgSend(IVar2,"release");
      }
      *local_d8 = local_c4;
      if (local_c4 == 0) {
        local_d8[1] = local_c8;
        local_d8[2] = local_cc;
        local_d8[3] = local_d0;
        *(char *)(local_d8 + 4) = (char)local_d4;
        goto LAB_000fb3a4;
      }
      local_90 = 10;
      _objc_msgSend(local_c4,"retain");
    }
    local_d8[1] = local_c8;
    local_d8[2] = local_cc;
    local_d8[3] = local_d0;
    *(char *)(local_d8 + 4) = (char)local_d4;
    if (local_c4 != 0) {
      local_90 = 0xffffffff;
      _objc_msgSend(local_c4,"release");
    }
    goto LAB_000fb3a4;
  }
  iVar1 = (int)local_11c - *(int *)local_120 >> 2;
  uVar5 = iVar1 * -0x33333333;
  if (uVar5 != 0xccccccc) {
    if (uVar5 == 0) {
      uVar3 = 1;
    }
    else {
      uVar3 = iVar1 * -0x66666666;
    }
    if (uVar3 < uVar5) {
      local_c0 = 0xfffffff0;
    }
    else {
      if (0xccccccc < uVar3) goto LAB_000fb714;
      local_c0 = uVar3 * 0x14;
    }
    local_90 = 0xffffffff;
    local_118 = operator_new(local_c0);
    local_fc = *(ID **)local_120;
    local_100 = local_118;
    local_98 = local_118;
    if (local_d8 != local_fc) {
      local_f8 = "retain";
      local_114 = local_118;
      local_ac = local_118 + 5;
      do {
        if (local_98 != (ID *)0x0) {
          IVar2 = *local_fc;
          *local_98 = IVar2;
          if (IVar2 != 0) {
            local_90 = 4;
            _objc_msgSend(IVar2,local_f8);
          }
          local_98[1] = local_fc[1];
          local_98[2] = local_fc[2];
          local_98[3] = local_fc[3];
          *(char *)(local_98 + 4) = (char)local_fc[4];
        }
        pIVar4 = local_ac + 5;
        local_98 = local_ac;
        local_fc = local_fc + 5;
        local_ac = pIVar4;
      } while (local_d8 != local_fc);
    }
    local_114 = local_98;
    if (local_98 != (ID *)0x0) {
      IVar2 = *local_128;
      *local_98 = IVar2;
      if (IVar2 != 0) {
        local_90 = 3;
        _objc_msgSend(IVar2,"retain");
      }
      local_114[1] = local_128[1];
      local_114[2] = local_128[2];
      local_114[3] = local_128[3];
      *(char *)(local_114 + 4) = (char)local_128[4];
    }
    local_114 = local_114 + 5;
    local_f0 = *(ID **)(local_120 + 4);
    local_a8 = local_114;
    if (local_d8 != local_f0) {
      local_b4 = local_d8;
      local_ec = "retain";
      pIVar4 = local_98 + 10;
      local_a4 = local_114;
      do {
        local_b0 = pIVar4;
        if (local_a4 != (ID *)0x0) {
          IVar2 = *local_b4;
          *local_a4 = IVar2;
          if (IVar2 != 0) {
            local_90 = 1;
            _objc_msgSend(IVar2,local_ec);
          }
          local_a4[1] = local_b4[1];
          local_a4[2] = local_b4[2];
          local_a4[3] = local_b4[3];
          *(char *)(local_a4 + 4) = (char)local_b4[4];
        }
        local_a4 = local_b0;
        local_b4 = local_b4 + 5;
        pIVar4 = local_b0 + 5;
      } while (local_f0 != local_b4);
      local_d8 = *(ID **)(local_120 + 4);
      local_a8 = local_b0;
      local_b0 = local_b0 + 5;
    }
    if (*(ID **)local_120 != local_d8) {
      local_e4 = "release";
      local_b8 = *(ID **)local_120;
      do {
        if (*local_b8 != 0) {
          local_90 = 7;
          _objc_msgSend(*local_b8,local_e4);
        }
        local_b8 = local_b8 + 5;
      } while (local_b8 != local_d8);
      local_d8 = *(ID **)local_120;
    }
    if (local_d8 != (ID *)0x0) {
      operator_delete(local_d8);
    }
    *(ID **)local_120 = local_118;
    *(ID **)(local_120 + 4) = local_a8;
    *(ulong *)(local_120 + 8) = (int)local_118 + local_c0;
LAB_000fb3a4:
    __Unwind_SjLj_Unregister(auStack_94);
    return;
  }
  local_90 = 0xffffffff;
  std::__throw_length_error("vector::_M_insert_aux");
LAB_000fb714:
  local_90 = -1;
  std::__throw_bad_alloc();
  local_12c = local_8c;
  if (local_90 != 1) {
    if (local_90 == 2) goto LAB_000fb8a8;
    if (local_90 == 3) {
      ___cxa_begin_catch(local_8c);
      if (local_118 != local_98) {
        local_f4 = "release";
        local_a0 = local_118;
        do {
          if (*local_a0 != 0) {
            local_90 = 5;
            _objc_msgSend(*local_a0,local_f4);
          }
          local_a0 = local_a0 + 5;
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
          __Unwind_SjLj_Resume(local_12c);
        }
        if (local_90 != 9) {
          ___cxa_begin_catch(local_8c);
          if (local_a8 != local_a4) {
            local_e8 = "release";
            do {
              if (*local_a8 != 0) {
                local_90 = 2;
                _objc_msgSend(*local_a8,local_e8);
              }
              local_a8 = local_a8 + 5;
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
      __Unwind_SjLj_Resume(local_12c);
    }
  }
  local_90 = 0;
  ___cxa_end_catch();
LAB_000fb8a8:
  ___cxa_begin_catch(local_12c);
  local_e0 = local_114;
  if (local_118 != local_114) {
    local_dc = "release";
    local_9c = local_118;
    do {
      if (*local_9c != 0) {
        local_90 = 8;
        _objc_msgSend(*local_9c,local_dc);
      }
      local_9c = local_9c + 5;
    } while (local_e0 != local_9c);
  }
  if (local_100 != (ID *)0x0) {
    operator_delete(local_118);
  }
  local_90 = 9;
                    /* WARNING: Subroutine does not return */
  ___cxa_rethrow();
}
