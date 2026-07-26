/*
 * mangled: _ZNSt6vectorI13OFRetainedPtrI8NSStringESaIS2_EE13_M_insert_auxEN9__gnu_cxx17__normal_iteratorIPS2_S4_EERKS2_
 * demangled: std::vector<OFRetainedPtr<NSString>, std::allocator<OFRetainedPtr<NSString>>>::_M_insert_aux(__gnu_cxx::__normal_iterator<OFRetainedPtr<NSString>*, std::vector<OFRetainedPtr<NSString>, std::allocator<OFRetainedPtr<NSString>>>>, OFRetainedPtr<NSString> const&)
 * address: 0007e4fc
 * size: 1736
 */

/* std::vector<OFRetainedPtr<NSString>, std::allocator<OFRetainedPtr<NSString> >
   >::_M_insert_aux(__gnu_cxx::__normal_iterator<OFRetainedPtr<NSString>*,
   std::vector<OFRetainedPtr<NSString>, std::allocator<OFRetainedPtr<NSString> > > >,
   OFRetainedPtr<NSString> const&) */

void __thiscall
std::vector<OFRetainedPtr<NSString>,std::allocator<OFRetainedPtr<NSString>>>::_M_insert_aux
          (vector<OFRetainedPtr<NSString>,std::allocator<OFRetainedPtr<NSString>>> *this,ID *param_2
          ,ID *param_3)

{
  uint uVar1;
  ID IVar2;
  uint uVar3;
  ID *pIVar4;
  int iVar5;
  ID *pIVar6;
  undefined4 local_110;
  ID *local_10c;
  ID *local_108;
  vector<OFRetainedPtr<NSString>,std::allocator<OFRetainedPtr<NSString>>> *local_104;
  ID *local_100;
  ID *local_fc;
  int local_f8;
  char *local_f4;
  SEL local_f0;
  ID *local_ec;
  ID *local_e8;
  SEL local_e4;
  SEL local_e0;
  ID *local_dc;
  SEL local_d8;
  SEL local_d4;
  SEL local_d0;
  ID *local_cc;
  SEL local_c8;
  ID *local_c4;
  ID local_c0;
  ulong local_bc;
  int local_b8;
  ID *local_b4;
  int local_b0;
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
  local_6c = (undefined1 *)&local_110;
  local_7c = PTR_001b615c;
  local_78 = &GCC_except_table6;
  local_70 = 0x7e9b8;
  local_10c = param_3;
  local_108 = param_2;
  local_104 = this;
  IVar2 = __Unwind_SjLj_Register(auStack_94);
  local_c4 = local_108;
  pIVar6 = *(ID **)(local_104 + 4);
  if (pIVar6 != *(ID **)(local_104 + 8)) {
    if (pIVar6 != (ID *)0x0) {
      IVar2 = pIVar6[-1];
      *pIVar6 = IVar2;
    }
    if (pIVar6 != (ID *)0x0 && IVar2 != 0) {
      local_90 = 6;
      _objc_msgSend(IVar2,"retain");
    }
    *(int *)(local_104 + 4) = *(int *)(local_104 + 4) + 4;
    local_c0 = *local_10c;
    if (local_c0 != 0) {
      local_90 = 0xffffffff;
      _objc_msgSend(local_c0,"retain");
    }
    local_f8 = (*(int *)(local_104 + 4) + -8) - (int)local_c4 >> 2;
    if (0 < local_f8) {
      local_f0 = "release";
      local_f4 = "retain";
      local_b8 = *(int *)(local_104 + 4);
      do {
        IVar2 = *(ID *)(local_b8 + -8);
        if (*(ID *)(local_b8 + -0xc) != IVar2) {
          if (IVar2 != 0) {
            local_90 = 10;
            _objc_msgSend(IVar2,local_f0);
          }
          IVar2 = *(ID *)(local_b8 + -0xc);
          *(ID *)(local_b8 + -8) = IVar2;
          if (IVar2 != 0) {
            local_90 = 10;
            _objc_msgSend(IVar2,local_f4);
          }
        }
        local_b8 = local_b8 + -4;
        local_f8 = local_f8 + -1;
      } while (local_f8 != 0);
    }
    IVar2 = *local_c4;
    if (local_c0 != IVar2) {
      if (IVar2 != 0) {
        local_90 = 10;
        _objc_msgSend(IVar2,"release");
      }
      *local_c4 = local_c0;
      if (local_c0 == 0) goto LAB_0007e6f4;
      local_90 = 10;
      _objc_msgSend(local_c0,"retain");
    }
    if (local_c0 != 0) {
      local_90 = 0xffffffff;
      _objc_msgSend(local_c0,"release");
    }
    goto LAB_0007e6f4;
  }
  uVar1 = (int)pIVar6 - *(int *)local_104 >> 2;
  if (uVar1 != 0x3fffffff) {
    if (uVar1 == 0) {
      uVar3 = 1;
    }
    else {
      uVar3 = uVar1 << 1;
    }
    if (uVar3 < uVar1) {
      local_bc = 0xfffffffc;
    }
    else {
      if (0x3fffffff < uVar3) goto LAB_0007e9ac;
      local_bc = uVar3 << 2;
    }
    local_90 = 0xffffffff;
    pIVar6 = operator_new(local_bc);
    local_e8 = *(ID **)local_104;
    local_100 = pIVar6;
    local_ec = pIVar6;
    local_a0 = pIVar6;
    if (local_c4 != local_e8) {
      local_e4 = "retain";
      local_fc = pIVar6;
      local_ac = pIVar6 + 1;
      do {
        if (local_a0 != (ID *)0x0) {
          pIVar6 = (ID *)*local_e8;
          *local_a0 = (ID)pIVar6;
        }
        if (local_a0 != (ID *)0x0 && pIVar6 != (ID *)0x0) {
          local_90 = 4;
          pIVar6 = (ID *)_objc_msgSend((ID)pIVar6,local_e4);
        }
        pIVar4 = local_ac + 1;
        local_a0 = local_ac;
        local_e8 = local_e8 + 1;
        local_ac = pIVar4;
      } while (local_c4 != local_e8);
    }
    local_fc = local_a0;
    if (local_a0 != (ID *)0x0) {
      IVar2 = *local_10c;
      *local_a0 = IVar2;
      pIVar6 = (ID *)0x0;
      if (IVar2 != 0) {
        local_90 = 3;
        pIVar6 = (ID *)_objc_msgSend(IVar2,"retain");
      }
    }
    local_fc = local_fc + 1;
    local_dc = *(ID **)(local_104 + 4);
    local_9c = local_fc;
    if (local_c4 != local_dc) {
      local_b0 = 0;
      local_d8 = "retain";
      local_9c = local_fc;
      local_98 = local_fc;
      do {
        if (local_98 != (ID *)0x0) {
          pIVar6 = *(ID **)(local_b0 + (int)local_c4);
          *local_98 = (ID)pIVar6;
        }
        if (local_98 != (ID *)0x0 && pIVar6 != (ID *)0x0) {
          local_90 = 1;
          pIVar6 = (ID *)_objc_msgSend((ID)pIVar6,local_d8);
        }
        iVar5 = local_b0 + 4;
        local_98 = (ID *)((int)local_a0 + local_b0 + 8);
        local_b0 = iVar5;
      } while (local_dc != (ID *)((int)local_c4 + iVar5));
      local_c4 = *(ID **)(local_104 + 4);
      local_9c = local_98;
    }
    if (*(ID **)local_104 != local_c4) {
      local_d0 = "release";
      local_b4 = *(ID **)local_104;
      do {
        if (*local_b4 != 0) {
          local_90 = 7;
          _objc_msgSend(*local_b4,local_d0);
        }
        local_b4 = local_b4 + 1;
      } while (local_b4 != local_c4);
      local_c4 = *(ID **)local_104;
    }
    if (local_c4 != (ID *)0x0) {
      operator_delete(local_c4);
    }
    *(ID **)local_104 = local_100;
    *(ID **)(local_104 + 4) = local_9c;
    *(ulong *)(local_104 + 8) = (int)local_100 + local_bc;
LAB_0007e6f4:
    __Unwind_SjLj_Unregister(auStack_94);
    return;
  }
  local_90 = 0xffffffff;
  std::__throw_length_error("vector::_M_insert_aux");
LAB_0007e9ac:
  local_90 = -1;
  std::__throw_bad_alloc();
  local_110 = local_8c;
  if (local_90 != 1) {
    if (local_90 == 2) goto LAB_0007eb3c;
    if (local_90 == 3) {
      ___cxa_begin_catch(local_8c);
      if (local_a0 != local_100) {
        local_a8 = local_100;
        local_e0 = "release";
        do {
          if (*local_a8 != 0) {
            local_90 = 5;
            _objc_msgSend(*local_a8,local_e0);
          }
          local_a8 = local_a8 + 1;
        } while (local_a0 != local_a8);
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
          __Unwind_SjLj_Resume(local_110);
        }
        if (local_90 != 9) {
          ___cxa_begin_catch(local_8c);
          if (local_98 != local_9c) {
            local_d4 = "release";
            do {
              if (*local_9c != 0) {
                local_90 = 2;
                _objc_msgSend(*local_9c,local_d4);
              }
              local_9c = local_9c + 1;
            } while (local_98 != local_9c);
          }
          local_90 = 2;
                    /* WARNING: Subroutine does not return */
          ___cxa_rethrow();
        }
        if (local_c0 != 0) {
          local_90 = 0;
          _objc_msgSend(local_c0,"release");
        }
      }
      local_90 = 0xffffffff;
                    /* WARNING: Subroutine does not return */
      __Unwind_SjLj_Resume(local_110);
    }
  }
  local_90 = 0;
  ___cxa_end_catch();
LAB_0007eb3c:
  ___cxa_begin_catch(local_110);
  local_cc = local_fc;
  if (local_100 != local_fc) {
    local_c8 = "release";
    local_a4 = local_100;
    do {
      if (*local_a4 != 0) {
        local_90 = 8;
        _objc_msgSend(*local_a4,local_c8);
      }
      local_a4 = local_a4 + 1;
    } while (local_cc != local_a4);
  }
  if (local_ec != (ID *)0x0) {
    operator_delete(local_100);
  }
  local_90 = 9;
                    /* WARNING: Subroutine does not return */
  ___cxa_rethrow();
}
