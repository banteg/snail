/*
 * mangled: _ZNSt6vectorI10OFDelegateSaIS0_EE13_M_insert_auxEN9__gnu_cxx17__normal_iteratorIPS0_S2_EERKS0_
 * demangled: std::vector<OFDelegate, std::allocator<OFDelegate>>::_M_insert_aux(__gnu_cxx::__normal_iterator<OFDelegate*, std::vector<OFDelegate, std::allocator<OFDelegate>>>, OFDelegate const&)
 * address: 0009dbe0
 * size: 1288
 */

/* std::vector<OFDelegate, std::allocator<OFDelegate>
   >::_M_insert_aux(__gnu_cxx::__normal_iterator<OFDelegate*, std::vector<OFDelegate,
   std::allocator<OFDelegate> > >, OFDelegate const&) */

void __thiscall
std::vector<OFDelegate,std::allocator<OFDelegate>>::_M_insert_aux
          (vector<OFDelegate,std::allocator<OFDelegate>> *this,OFDelegate *param_2,
          OFDelegate *param_3)

{
  uint uVar1;
  OFDelegate *pOVar2;
  uint uVar3;
  undefined4 local_100;
  OFDelegate *local_fc;
  OFDelegate *local_f8;
  vector<OFDelegate,std::allocator<OFDelegate>> *local_f4;
  OFDelegate *local_f0;
  OFDelegate *local_ec;
  int local_e8;
  OFDelegate *local_e4;
  OFDelegate *local_e0;
  OFDelegate *local_dc;
  OFDelegate *local_d8;
  OFDelegate *local_d4;
  OFDelegate *local_d0;
  ulong local_cc;
  OFDelegate *local_c8;
  OFDelegate *local_c4;
  OFDelegate *local_c0;
  OFDelegate *local_bc;
  OFDelegate *local_b8;
  OFDelegate *local_b4;
  OFDelegate *local_b0;
  OFDelegate *local_ac;
  OFDelegate *local_a8;
  undefined1 auStack_a4 [4];
  int local_a0;
  undefined4 local_9c;
  undefined *local_8c;
  undefined *local_88;
  undefined1 *local_84;
  undefined4 local_80;
  undefined1 *local_7c;
  OFDelegate aOStack_70 [5];

  local_84 = &stack0xfffffff8;
  local_7c = (undefined1 *)&local_100;
  local_8c = PTR_001b615c;
  local_88 = &::GCC_except_table3;
  local_80 = 0x9df54;
  local_fc = param_3;
  local_f8 = param_2;
  local_f4 = this;
  __Unwind_SjLj_Register(auStack_a4);
  local_d0 = local_f8;
  pOVar2 = *(OFDelegate **)(local_f4 + 4);
  if (pOVar2 != *(OFDelegate **)(local_f4 + 8)) {
    if (pOVar2 != (OFDelegate *)0x0) {
      local_a0 = 6;
      OFDelegate::OFDelegate(pOVar2,pOVar2 + -1);
    }
    *(int *)(local_f4 + 4) = *(int *)(local_f4 + 4) + 0x10;
    local_a0 = 0xffffffff;
    OFDelegate::OFDelegate(aOStack_70,local_fc);
    local_e8 = (*(int *)(local_f4 + 4) + -0x20) - (int)local_d0 >> 4;
    pOVar2 = (OFDelegate *)(*(int *)(local_f4 + 4) + -0x20);
    if (0 < local_e8) {
      do {
        local_a8 = pOVar2 + -1;
        local_a0 = 10;
        OFDelegate::operator=(pOVar2,pOVar2 + -1);
        local_e8 = local_e8 + -1;
        pOVar2 = local_a8;
      } while (local_e8 != 0);
    }
    local_a0 = 10;
    OFDelegate::operator=(local_d0,aOStack_70);
    local_a0 = 0xffffffff;
    OFDelegate::~OFDelegate(aOStack_70);
    goto LAB_0009dcf8;
  }
  uVar1 = (int)pOVar2 - *(int *)local_f4 >> 4;
  if (uVar1 != 0xfffffff) {
    if (uVar1 == 0) {
      uVar3 = 1;
    }
    else {
      uVar3 = uVar1 << 1;
    }
    if (uVar3 < uVar1) {
      local_cc = 0xfffffff0;
    }
    else {
      if (0xfffffff < uVar3) goto LAB_0009df48;
      local_cc = uVar3 << 4;
    }
    local_a0 = 0xffffffff;
    local_f0 = operator_new(local_cc);
    local_e0 = *(OFDelegate **)local_f4;
    local_e4 = local_f0;
    local_b4 = local_f0;
    if (local_d0 != local_e0) {
      local_ec = local_f0;
      local_c0 = local_f0 + 1;
      do {
        if (local_b4 != (OFDelegate *)0x0) {
          local_a0 = 4;
          OFDelegate::OFDelegate(local_b4,local_e0);
        }
        pOVar2 = local_c0 + 1;
        local_b4 = local_c0;
        local_e0 = local_e0 + 1;
        local_c0 = pOVar2;
      } while (local_d0 != local_e0);
    }
    local_ec = local_b4;
    if (local_b4 != (OFDelegate *)0x0) {
      local_a0 = 3;
      OFDelegate::OFDelegate(local_b4,local_fc);
    }
    local_ec = local_ec + 1;
    local_dc = *(OFDelegate **)(local_f4 + 4);
    local_b0 = local_ec;
    if (local_d0 != local_dc) {
      local_c8 = local_d0;
      pOVar2 = local_b4 + 2;
      local_ac = local_ec;
      do {
        local_c4 = pOVar2;
        if (local_ac != (OFDelegate *)0x0) {
          local_a0 = 1;
          OFDelegate::OFDelegate(local_ac,local_c8);
        }
        local_ac = local_c4;
        local_c8 = local_c8 + 1;
        pOVar2 = local_c4 + 1;
      } while (local_dc != local_c8);
      local_d0 = *(OFDelegate **)(local_f4 + 4);
      local_b0 = local_c4;
      local_c4 = local_c4 + 1;
    }
    local_d8 = *(OFDelegate **)local_f4;
    if (local_d8 != local_d0) {
      do {
        local_a0 = 7;
        OFDelegate::~OFDelegate(local_d8);
        local_d8 = local_d8 + 1;
      } while (local_d8 != local_d0);
      local_d0 = *(OFDelegate **)local_f4;
    }
    if (local_d0 != (OFDelegate *)0x0) {
      operator_delete(local_d0);
    }
    *(OFDelegate **)local_f4 = local_f0;
    *(OFDelegate **)(local_f4 + 4) = local_b0;
    *(ulong *)(local_f4 + 8) = (int)&local_f0->field0_0x0 + local_cc;
LAB_0009dcf8:
    __Unwind_SjLj_Unregister(auStack_a4);
    return;
  }
  local_a0 = 0xffffffff;
  std::__throw_length_error("vector::_M_insert_aux");
LAB_0009df48:
  local_a0 = -1;
  std::__throw_bad_alloc();
  local_100 = local_9c;
  if (local_a0 != 1) {
    if (local_a0 == 2) goto LAB_0009e000;
    if (local_a0 == 3) {
      ___cxa_begin_catch(local_9c);
      if (local_f0 != local_b4) {
        local_b8 = local_f0;
        do {
          local_a0 = 5;
          OFDelegate::~OFDelegate(local_b8);
          local_b8 = local_b8 + 1;
        } while (local_b4 != local_b8);
      }
      local_a0 = 5;
                    /* WARNING: Subroutine does not return */
      ___cxa_rethrow();
    }
    if (local_a0 != 4) {
      if ((local_a0 != 5) && (local_a0 != 6)) {
        if ((local_a0 == 7) || (local_a0 == 8)) {
          local_a0 = 0;
          ___cxa_end_catch();
        }
        else {
          if (local_a0 != 9) {
            ___cxa_begin_catch(local_9c);
            if (local_ac != local_b0) {
              do {
                local_a0 = 2;
                OFDelegate::~OFDelegate(local_b0);
                local_b0 = local_b0 + 1;
              } while (local_ac != local_b0);
            }
            local_a0 = 2;
                    /* WARNING: Subroutine does not return */
            ___cxa_rethrow();
          }
          local_a0 = 0;
          OFDelegate::~OFDelegate(aOStack_70);
        }
      }
      local_a0 = 0xffffffff;
                    /* WARNING: Subroutine does not return */
      __Unwind_SjLj_Resume(local_100);
    }
  }
  local_a0 = 0;
  ___cxa_end_catch();
LAB_0009e000:
  ___cxa_begin_catch(local_100);
  local_d4 = local_ec;
  if (local_f0 != local_ec) {
    local_bc = local_f0;
    do {
      local_a0 = 8;
      OFDelegate::~OFDelegate(local_bc);
      local_bc = local_bc + 1;
    } while (local_d4 != local_bc);
  }
  if (local_e4 != (OFDelegate *)0x0) {
    operator_delete(local_f0);
  }
  local_a0 = 9;
                    /* WARNING: Subroutine does not return */
  ___cxa_rethrow();
}
