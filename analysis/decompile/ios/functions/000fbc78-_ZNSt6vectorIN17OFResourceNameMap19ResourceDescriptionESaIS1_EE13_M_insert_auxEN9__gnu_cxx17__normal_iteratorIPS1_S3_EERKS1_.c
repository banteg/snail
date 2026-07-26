/*
 * mangled: _ZNSt6vectorIN17OFResourceNameMap19ResourceDescriptionESaIS1_EE13_M_insert_auxEN9__gnu_cxx17__normal_iteratorIPS1_S3_EERKS1_
 * demangled: std::vector<OFResourceNameMap::ResourceDescription, std::allocator<OFResourceNameMap::ResourceDescription>>::_M_insert_aux(__gnu_cxx::__normal_iterator<OFResourceNameMap::ResourceDescription*, std::vector<OFResourceNameMap::ResourceDescription, std::allocator<OFResourceNameMap::ResourceDescription>>>, OFResourceNameMap::ResourceDescription const&)
 * address: 000fbc78
 * size: 1880
 */

/* std::vector<OFResourceNameMap::ResourceDescription,
   std::allocator<OFResourceNameMap::ResourceDescription>
   >::_M_insert_aux(__gnu_cxx::__normal_iterator<OFResourceNameMap::ResourceDescription*,
   std::vector<OFResourceNameMap::ResourceDescription,
   std::allocator<OFResourceNameMap::ResourceDescription> > >,
   OFResourceNameMap::ResourceDescription const&) */

void __thiscall
std::
vector<OFResourceNameMap::ResourceDescription,std::allocator<OFResourceNameMap::ResourceDescription>>
::_M_insert_aux(vector<OFResourceNameMap::ResourceDescription,std::allocator<OFResourceNameMap::ResourceDescription>>
                *this,ID *param_2,ID *param_3)

{
  uint uVar1;
  ID IVar2;
  uint uVar3;
  ID *pIVar4;
  undefined4 local_120;
  ID *local_11c;
  ID *local_118;
  vector<OFResourceNameMap::ResourceDescription,std::allocator<OFResourceNameMap::ResourceDescription>>
  *local_114;
  ID *local_110;
  ID *local_10c;
  ID *local_108;
  ID *local_104;
  int local_100;
  char *local_fc;
  SEL local_f8;
  ID *local_f4;
  ID *local_f0;
  SEL local_ec;
  SEL local_e8;
  ID *local_e4;
  SEL local_e0;
  SEL local_dc;
  SEL local_d8;
  ID *local_d4;
  SEL local_d0;
  ID *local_cc;
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
  local_6c = (undefined1 *)&local_120;
  local_7c = PTR_001b615c;
  local_78 = &::GCC_except_table0;
  local_70 = 0xfc1c0;
  local_11c = param_3;
  local_118 = param_2;
  local_114 = this;
  __Unwind_SjLj_Register(auStack_94);
  local_cc = local_118;
  local_110 = *(ID **)(local_114 + 4);
  if (local_110 != *(ID **)(local_114 + 8)) {
    if (local_110 != (ID *)0x0) {
      local_104 = local_110 + -2;
      IVar2 = local_110[-2];
      *local_110 = IVar2;
      if (IVar2 != 0) {
        local_90 = 6;
        _objc_msgSend(IVar2,"retain");
      }
      local_110[1] = local_104[1];
    }
    *(int *)(local_114 + 4) = *(int *)(local_114 + 4) + 8;
    local_c4 = *local_11c;
    if (local_c4 != 0) {
      local_90 = 0xffffffff;
      _objc_msgSend(local_c4,"retain");
    }
    local_c8 = local_11c[1];
    local_100 = (*(int *)(local_114 + 4) + -0x10) - (int)local_cc >> 3;
    if (0 < local_100) {
      local_f8 = "release";
      local_fc = "retain";
      local_bc = *(int *)(local_114 + 4);
      do {
        IVar2 = *(ID *)(local_bc + -0x10);
        if (IVar2 != *(ID *)(local_bc + -0x18)) {
          if (IVar2 != 0) {
            local_90 = 10;
            _objc_msgSend(IVar2,local_f8);
          }
          IVar2 = *(ID *)(local_bc + -0x18);
          *(ID *)(local_bc + -0x10) = IVar2;
          if (IVar2 != 0) {
            local_90 = 10;
            _objc_msgSend(IVar2,local_fc);
          }
        }
        *(undefined4 *)(local_bc + -0xc) = *(undefined4 *)(local_bc + -0x14);
        local_bc = local_bc + -8;
        local_100 = local_100 + -1;
      } while (local_100 != 0);
    }
    IVar2 = *local_cc;
    if (local_c4 != IVar2) {
      if (IVar2 != 0) {
        local_90 = 10;
        _objc_msgSend(IVar2,"release");
      }
      *local_cc = local_c4;
      if (local_c4 == 0) {
        local_cc[1] = local_c8;
        goto LAB_000fbeb8;
      }
      local_90 = 10;
      _objc_msgSend(local_c4,"retain");
    }
    local_cc[1] = local_c8;
    if (local_c4 != 0) {
      local_90 = 0xffffffff;
      _objc_msgSend(local_c4,"release");
    }
    goto LAB_000fbeb8;
  }
  uVar1 = (int)local_110 - *(int *)local_114 >> 3;
  if (uVar1 != 0x1fffffff) {
    if (uVar1 == 0) {
      uVar3 = 1;
    }
    else {
      uVar3 = uVar1 << 1;
    }
    if (uVar3 < uVar1) {
      local_c0 = 0xfffffff8;
    }
    else {
      if (0x1fffffff < uVar3) goto LAB_000fc1b4;
      local_c0 = uVar3 << 3;
    }
    local_90 = 0xffffffff;
    local_10c = operator_new(local_c0);
    local_f0 = *(ID **)local_114;
    local_f4 = local_10c;
    local_98 = local_10c;
    if (local_cc != local_f0) {
      local_ec = "retain";
      local_108 = local_10c;
      local_ac = local_10c + 2;
      do {
        if (local_98 != (ID *)0x0) {
          IVar2 = *local_f0;
          *local_98 = IVar2;
          if (IVar2 != 0) {
            local_90 = 4;
            _objc_msgSend(IVar2,local_ec);
          }
          local_98[1] = local_f0[1];
        }
        pIVar4 = local_ac + 2;
        local_98 = local_ac;
        local_f0 = local_f0 + 2;
        local_ac = pIVar4;
      } while (local_cc != local_f0);
    }
    local_108 = local_98;
    if (local_98 != (ID *)0x0) {
      IVar2 = *local_11c;
      *local_98 = IVar2;
      if (IVar2 != 0) {
        local_90 = 3;
        _objc_msgSend(IVar2,"retain");
      }
      local_108[1] = local_11c[1];
    }
    local_108 = local_108 + 2;
    local_e4 = *(ID **)(local_114 + 4);
    local_a8 = local_108;
    if (local_cc != local_e4) {
      local_b4 = local_cc;
      local_e0 = "retain";
      pIVar4 = local_98 + 4;
      local_a4 = local_108;
      do {
        local_b0 = pIVar4;
        if (local_a4 != (ID *)0x0) {
          IVar2 = *local_b4;
          *local_a4 = IVar2;
          if (IVar2 != 0) {
            local_90 = 1;
            _objc_msgSend(IVar2,local_e0);
          }
          local_a4[1] = local_b4[1];
        }
        local_a4 = local_b0;
        local_b4 = local_b4 + 2;
        pIVar4 = local_b0 + 2;
      } while (local_e4 != local_b4);
      local_cc = *(ID **)(local_114 + 4);
      local_a8 = local_b0;
      local_b0 = local_b0 + 2;
    }
    if (*(ID **)local_114 != local_cc) {
      local_d8 = "release";
      local_b8 = *(ID **)local_114;
      do {
        if (*local_b8 != 0) {
          local_90 = 7;
          _objc_msgSend(*local_b8,local_d8);
        }
        local_b8 = local_b8 + 2;
      } while (local_b8 != local_cc);
      local_cc = *(ID **)local_114;
    }
    if (local_cc != (ID *)0x0) {
      operator_delete(local_cc);
    }
    *(ID **)local_114 = local_10c;
    *(ID **)(local_114 + 4) = local_a8;
    *(ulong *)(local_114 + 8) = (int)local_10c + local_c0;
LAB_000fbeb8:
    __Unwind_SjLj_Unregister(auStack_94);
    return;
  }
  local_90 = 0xffffffff;
  std::__throw_length_error("vector::_M_insert_aux");
LAB_000fc1b4:
  local_90 = -1;
  std::__throw_bad_alloc();
  local_120 = local_8c;
  if (local_90 != 1) {
    if (local_90 == 2) goto LAB_000fc348;
    if (local_90 == 3) {
      ___cxa_begin_catch(local_8c);
      if (local_10c != local_98) {
        local_e8 = "release";
        local_a0 = local_10c;
        do {
          if (*local_a0 != 0) {
            local_90 = 5;
            _objc_msgSend(*local_a0,local_e8);
          }
          local_a0 = local_a0 + 2;
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
          __Unwind_SjLj_Resume(local_120);
        }
        if (local_90 != 9) {
          ___cxa_begin_catch(local_8c);
          if (local_a8 != local_a4) {
            local_dc = "release";
            do {
              if (*local_a8 != 0) {
                local_90 = 2;
                _objc_msgSend(*local_a8,local_dc);
              }
              local_a8 = local_a8 + 2;
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
      __Unwind_SjLj_Resume(local_120);
    }
  }
  local_90 = 0;
  ___cxa_end_catch();
LAB_000fc348:
  ___cxa_begin_catch(local_120);
  local_d4 = local_108;
  if (local_10c != local_108) {
    local_d0 = "release";
    local_9c = local_10c;
    do {
      if (*local_9c != 0) {
        local_90 = 8;
        _objc_msgSend(*local_9c,local_d0);
      }
      local_9c = local_9c + 2;
    } while (local_d4 != local_9c);
  }
  if (local_f4 != (ID *)0x0) {
    operator_delete(local_10c);
  }
  local_90 = 9;
                    /* WARNING: Subroutine does not return */
  ___cxa_rethrow();
}
