/*
 * mangled: _ZNSt6vectorIN23OFResourceControllerMap19ResourceDescriptionESaIS1_EE13_M_insert_auxEN9__gnu_cxx17__normal_iteratorIPS1_S3_EERKS1_
 * demangled: std::vector<OFResourceControllerMap::ResourceDescription, std::allocator<OFResourceControllerMap::ResourceDescription>>::_M_insert_aux(__gnu_cxx::__normal_iterator<OFResourceControllerMap::ResourceDescription*, std::vector<OFResourceControllerMap::ResourceDescription, std::allocator<OFResourceControllerMap::ResourceDescription>>>, OFResourceControllerMap::ResourceDescription const&)
 * address: 000fa2e4
 * size: 1796
 */

/* std::vector<OFResourceControllerMap::ResourceDescription,
   std::allocator<OFResourceControllerMap::ResourceDescription>
   >::_M_insert_aux(__gnu_cxx::__normal_iterator<OFResourceControllerMap::ResourceDescription*,
   std::vector<OFResourceControllerMap::ResourceDescription,
   std::allocator<OFResourceControllerMap::ResourceDescription> > >,
   OFResourceControllerMap::ResourceDescription const&) */

void __thiscall
std::
vector<OFResourceControllerMap::ResourceDescription,std::allocator<OFResourceControllerMap::ResourceDescription>>
::_M_insert_aux(vector<OFResourceControllerMap::ResourceDescription,std::allocator<OFResourceControllerMap::ResourceDescription>>
                *this,undefined4 *param_2,undefined4 *param_3)

{
  uint uVar1;
  ID IVar2;
  uint uVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined4 local_118;
  undefined4 *local_114;
  undefined4 *local_110;
  vector<OFResourceControllerMap::ResourceDescription,std::allocator<OFResourceControllerMap::ResourceDescription>>
  *local_10c;
  undefined4 *local_108;
  undefined4 *local_104;
  int local_100;
  char *local_fc;
  SEL local_f8;
  undefined4 *local_f4;
  undefined4 *local_f0;
  SEL local_ec;
  SEL local_e8;
  undefined4 *local_e4;
  SEL local_e0;
  SEL local_dc;
  SEL local_d8;
  undefined4 *local_d4;
  SEL local_d0;
  undefined4 *local_cc;
  ID local_c8;
  undefined4 local_c4;
  ulong local_c0;
  int local_bc;
  undefined4 *local_b8;
  undefined4 *local_b4;
  undefined4 *local_b0;
  undefined4 *local_ac;
  undefined4 *local_a8;
  undefined4 *local_a4;
  undefined4 *local_a0;
  undefined4 *local_9c;
  undefined4 *local_98;
  undefined1 auStack_94 [4];
  int local_90;
  undefined4 local_8c;
  undefined *local_7c;
  undefined *local_78;
  undefined1 *local_74;
  undefined4 local_70;
  undefined1 *local_6c;

  local_74 = &stack0xfffffff8;
  local_6c = (undefined1 *)&local_118;
  local_7c = PTR_001b615c;
  local_78 = &::GCC_except_table0;
  local_70 = 0xfa7dc;
  local_114 = param_3;
  local_110 = param_2;
  local_10c = this;
  IVar2 = __Unwind_SjLj_Register(auStack_94);
  local_cc = local_110;
  puVar5 = *(undefined4 **)(local_10c + 4);
  if (puVar5 != *(undefined4 **)(local_10c + 8)) {
    if (puVar5 != (undefined4 *)0x0) {
      IVar2 = puVar5[-1];
      *puVar5 = puVar5[-2];
      puVar5[1] = IVar2;
    }
    if (puVar5 != (undefined4 *)0x0 && IVar2 != 0) {
      local_90 = 6;
      _objc_msgSend(IVar2,"retain");
    }
    *(int *)(local_10c + 4) = *(int *)(local_10c + 4) + 8;
    local_c4 = *local_114;
    local_c8 = local_114[1];
    if (local_c8 != 0) {
      local_90 = 0xffffffff;
      _objc_msgSend(local_c8,"retain");
    }
    local_100 = (*(int *)(local_10c + 4) + -0x10) - (int)local_cc >> 3;
    if (0 < local_100) {
      local_f8 = "release";
      local_fc = "retain";
      local_bc = *(int *)(local_10c + 4);
      do {
        IVar2 = *(ID *)(local_bc + -0xc);
        *(undefined4 *)(local_bc + -0x10) = *(undefined4 *)(local_bc + -0x18);
        if (IVar2 != *(ID *)(local_bc + -0x14)) {
          if (IVar2 != 0) {
            local_90 = 10;
            _objc_msgSend(IVar2,local_f8);
          }
          IVar2 = *(ID *)(local_bc + -0x14);
          *(ID *)(local_bc + -0xc) = IVar2;
          if (IVar2 != 0) {
            local_90 = 10;
            _objc_msgSend(IVar2,local_fc);
          }
        }
        local_bc = local_bc + -8;
        local_100 = local_100 + -1;
      } while (local_100 != 0);
    }
    *local_cc = local_c4;
    IVar2 = local_cc[1];
    if (local_c8 != IVar2) {
      if (IVar2 != 0) {
        local_90 = 10;
        _objc_msgSend(IVar2,"release");
      }
      local_cc[1] = local_c8;
      if (local_c8 == 0) goto LAB_000fa500;
      local_90 = 10;
      _objc_msgSend(local_c8,"retain");
    }
    if (local_c8 != 0) {
      local_90 = 0xffffffff;
      _objc_msgSend(local_c8,"release");
    }
    goto LAB_000fa500;
  }
  uVar1 = (int)puVar5 - *(int *)local_10c >> 3;
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
      if (0x1fffffff < uVar3) goto LAB_000fa7d0;
      local_c0 = uVar3 << 3;
    }
    local_90 = 0xffffffff;
    puVar5 = operator_new(local_c0);
    local_f0 = *(undefined4 **)local_10c;
    local_108 = puVar5;
    local_f4 = puVar5;
    local_98 = puVar5;
    if (local_cc != local_f0) {
      local_ec = "retain";
      local_104 = puVar5;
      local_ac = puVar5 + 2;
      do {
        if (local_98 != (undefined4 *)0x0) {
          puVar5 = (undefined4 *)local_f0[1];
          *local_98 = *local_f0;
          local_98[1] = puVar5;
        }
        if (local_98 != (undefined4 *)0x0 && puVar5 != (undefined4 *)0x0) {
          local_90 = 4;
          puVar5 = (undefined4 *)_objc_msgSend((ID)puVar5,local_ec);
        }
        puVar4 = local_ac + 2;
        local_98 = local_ac;
        local_f0 = local_f0 + 2;
        local_ac = puVar4;
      } while (local_cc != local_f0);
    }
    local_104 = local_98;
    if (local_98 != (undefined4 *)0x0) {
      IVar2 = local_114[1];
      *local_98 = *local_114;
      local_98[1] = IVar2;
      puVar5 = (undefined4 *)0x0;
      if (IVar2 != 0) {
        local_90 = 3;
        puVar5 = (undefined4 *)_objc_msgSend(IVar2,"retain");
      }
    }
    local_104 = local_104 + 2;
    local_e4 = *(undefined4 **)(local_10c + 4);
    local_a8 = local_104;
    if (local_cc != local_e4) {
      local_b4 = local_cc;
      local_e0 = "retain";
      puVar4 = local_98 + 4;
      local_a4 = local_104;
      do {
        local_b0 = puVar4;
        if (local_a4 != (undefined4 *)0x0) {
          puVar5 = (undefined4 *)local_b4[1];
          *local_a4 = *local_b4;
          local_a4[1] = puVar5;
        }
        if (local_a4 != (undefined4 *)0x0 && puVar5 != (undefined4 *)0x0) {
          local_90 = 1;
          puVar5 = (undefined4 *)_objc_msgSend((ID)puVar5,local_e0);
        }
        local_a4 = local_b0;
        local_b4 = local_b4 + 2;
        puVar4 = local_b0 + 2;
      } while (local_e4 != local_b4);
      local_cc = *(undefined4 **)(local_10c + 4);
      local_a8 = local_b0;
      local_b0 = local_b0 + 2;
    }
    if (*(undefined4 **)local_10c != local_cc) {
      local_d8 = "release";
      local_b8 = *(undefined4 **)local_10c;
      do {
        if (local_b8[1] != 0) {
          local_90 = 7;
          _objc_msgSend(local_b8[1],local_d8);
        }
        local_b8 = local_b8 + 2;
      } while (local_b8 != local_cc);
      local_cc = *(undefined4 **)local_10c;
    }
    if (local_cc != (undefined4 *)0x0) {
      operator_delete(local_cc);
    }
    *(undefined4 **)local_10c = local_108;
    *(undefined4 **)(local_10c + 4) = local_a8;
    *(ulong *)(local_10c + 8) = (int)local_108 + local_c0;
LAB_000fa500:
    __Unwind_SjLj_Unregister(auStack_94);
    return;
  }
  local_90 = 0xffffffff;
  std::__throw_length_error("vector::_M_insert_aux");
LAB_000fa7d0:
  local_90 = -1;
  std::__throw_bad_alloc();
  local_118 = local_8c;
  if (local_90 != 1) {
    if (local_90 == 2) goto LAB_000fa960;
    if (local_90 == 3) {
      ___cxa_begin_catch(local_8c);
      if (local_98 != local_108) {
        local_a0 = local_108;
        local_e8 = "release";
        do {
          if (local_a0[1] != 0) {
            local_90 = 5;
            _objc_msgSend(local_a0[1],local_e8);
          }
          local_a0 = local_a0 + 2;
        } while (local_98 != local_a0);
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
          __Unwind_SjLj_Resume(local_118);
        }
        if (local_90 != 9) {
          ___cxa_begin_catch(local_8c);
          if (local_a8 != local_a4) {
            local_dc = "release";
            do {
              if (local_a8[1] != 0) {
                local_90 = 2;
                _objc_msgSend(local_a8[1],local_dc);
              }
              local_a8 = local_a8 + 2;
            } while (local_a8 != local_a4);
          }
          local_90 = 2;
                    /* WARNING: Subroutine does not return */
          ___cxa_rethrow();
        }
        if (local_c8 != 0) {
          local_90 = 0;
          _objc_msgSend(local_c8,"release");
        }
      }
      local_90 = 0xffffffff;
                    /* WARNING: Subroutine does not return */
      __Unwind_SjLj_Resume(local_118);
    }
  }
  local_90 = 0;
  ___cxa_end_catch();
LAB_000fa960:
  ___cxa_begin_catch(local_118);
  local_d4 = local_104;
  if (local_108 != local_104) {
    local_d0 = "release";
    local_9c = local_108;
    do {
      if (local_9c[1] != 0) {
        local_90 = 8;
        _objc_msgSend(local_9c[1],local_d0);
      }
      local_9c = local_9c + 2;
    } while (local_d4 != local_9c);
  }
  if (local_f4 != (undefined4 *)0x0) {
    operator_delete(local_108);
  }
  local_90 = 9;
                    /* WARNING: Subroutine does not return */
  ___cxa_rethrow();
}
