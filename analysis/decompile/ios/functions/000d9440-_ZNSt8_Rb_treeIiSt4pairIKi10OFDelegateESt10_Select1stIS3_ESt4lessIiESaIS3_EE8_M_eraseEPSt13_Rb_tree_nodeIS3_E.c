/*
 * mangled: _ZNSt8_Rb_treeIiSt4pairIKi10OFDelegateESt10_Select1stIS3_ESt4lessIiESaIS3_EE8_M_eraseEPSt13_Rb_tree_nodeIS3_E
 * demangled: std::_Rb_tree<int, std::pair<int const, OFDelegate>, std::_Select1st<std::pair<int const, OFDelegate>>, std::less<int>, std::allocator<std::pair<int const, OFDelegate>>>::_M_erase(std::_Rb_tree_node<std::pair<int const, OFDelegate>>*)
 * address: 000d9440
 * size: 904
 */

/* std::_Rb_tree<int, std::pair<int const, OFDelegate>, std::_Select1st<std::pair<int const,
   OFDelegate> >, std::less<int>, std::allocator<std::pair<int const, OFDelegate> >
   >::_M_erase(std::_Rb_tree_node<std::pair<int const, OFDelegate> >*) */

void __thiscall
std::
_Rb_tree<int,std::pair<int_const,OFDelegate>,std::_Select1st<std::pair<int_const,OFDelegate>>,std::less<int>,std::allocator<std::pair<int_const,OFDelegate>>>
::_M_erase(_Rb_tree<int,std::pair<int_const,OFDelegate>,std::_Select1st<std::pair<int_const,OFDelegate>>,std::less<int>,std::allocator<std::pair<int_const,OFDelegate>>>
           *this,_Rb_tree_node *param_1)

{
  _Rb_tree_node *p_Var1;
  void *pvVar2;
  void *pvVar3;
  void *pvVar4;
  _Rb_tree_node *local_124;
  _Rb_tree<int,std::pair<int_const,OFDelegate>,std::_Select1st<std::pair<int_const,OFDelegate>>,std::less<int>,std::allocator<std::pair<int_const,OFDelegate>>>
  *local_120;
  _Rb_tree_node *local_11c;
  _Rb_tree_node *local_118;
  _Rb_tree_node *local_114;
  void *local_110;
  void *local_10c;
  void *local_108;
  void *local_104;
  void *local_100;
  void *local_fc;
  void *local_f8;
  void *local_f4;
  void *local_f0;
  void *local_ec;
  void *local_e8;
  void *local_e4;
  void *local_e0;
  void *local_dc;
  void *local_d8;
  void *local_d4;
  void *local_d0;
  void *local_cc;
  void *local_c8;
  void *local_c4;
  void *local_c0;
  void *local_bc;
  void *local_b8;
  void *local_b4;
  void *local_b0;
  void *local_ac;
  void *local_a8;
  void *local_a4;
  void *local_a0;
  void *local_9c;
  void *local_98;
  undefined1 auStack_94 [4];
  undefined4 local_90;
  undefined *local_7c;
  undefined *local_78;
  undefined1 *local_74;
  undefined *local_70;
  undefined1 *local_6c;

  local_74 = &stack0xfffffff8;
  local_6c = (undefined1 *)&local_124;
  local_7c = PTR_001b615c;
  local_78 = &::GCC_except_table3;
  local_70 = &DAT_000d97c8;
  local_124 = param_1;
  local_120 = this;
  __Unwind_SjLj_Register(auStack_94);
  p_Var1 = local_124;
  while (p_Var1 != (_Rb_tree_node *)0x0) {
    local_118 = local_124;
    pvVar3 = *(void **)(local_124 + 0xc);
    if (*(void **)(local_124 + 0xc) != (void *)0x0) {
      while( true ) {
        local_b8 = pvVar3;
        local_110 = local_b8;
        pvVar3 = *(void **)((int)local_b8 + 0xc);
        if (*(void **)((int)local_b8 + 0xc) != (void *)0x0) {
          while( true ) {
            local_bc = pvVar3;
            local_108 = local_bc;
            pvVar3 = *(void **)((int)local_bc + 0xc);
            if (*(void **)((int)local_bc + 0xc) != (void *)0x0) {
              while( true ) {
                local_c0 = pvVar3;
                local_100 = local_c0;
                pvVar3 = *(void **)((int)local_c0 + 0xc);
                if (*(void **)((int)local_c0 + 0xc) != (void *)0x0) {
                  while( true ) {
                    local_c4 = pvVar3;
                    local_f8 = local_c4;
                    pvVar3 = *(void **)((int)local_c4 + 0xc);
                    if (*(void **)((int)local_c4 + 0xc) != (void *)0x0) {
                      while( true ) {
                        local_c8 = pvVar3;
                        local_f0 = local_c8;
                        pvVar3 = *(void **)((int)local_c8 + 0xc);
                        if (*(void **)((int)local_c8 + 0xc) != (void *)0x0) {
                          while( true ) {
                            local_cc = pvVar3;
                            local_e8 = local_cc;
                            pvVar3 = *(void **)((int)local_cc + 0xc);
                            if (*(void **)((int)local_cc + 0xc) != (void *)0x0) {
                              while( true ) {
                                local_d0 = pvVar3;
                                pvVar4 = *(void **)((int)local_d0 + 0xc);
                                pvVar3 = local_d4;
                                local_e0 = local_d0;
                                pvVar2 = *(void **)((int)local_d0 + 0xc);
                                while (local_d4 = pvVar4, pvVar2 != (void *)0x0) {
                                  local_90 = 0xffffffff;
                                  _M_erase(local_120,*(_Rb_tree_node **)((int)local_d4 + 0xc));
                                  local_d8 = *(void **)((int)local_d4 + 8);
                                  local_90 = 9;
                                  local_98 = local_d8;
                                  OFDelegate::~OFDelegate((OFDelegate *)((int)local_d4 + 0x14));
                                  operator_delete(local_d4);
                                  pvVar4 = local_98;
                                  pvVar3 = local_d4;
                                  pvVar2 = local_d8;
                                }
                                local_dc = *(void **)((int)local_e0 + 8);
                                local_90 = 8;
                                local_d4 = pvVar3;
                                local_9c = local_dc;
                                OFDelegate::~OFDelegate((OFDelegate *)((int)local_d0 + 0x14));
                                operator_delete(local_d0);
                                if (local_dc == (void *)0x0) break;
                                local_d0 = local_9c;
                                pvVar3 = local_d0;
                              }
                            }
                            local_e4 = *(void **)((int)local_e8 + 8);
                            local_90 = 7;
                            local_a0 = local_e4;
                            OFDelegate::~OFDelegate((OFDelegate *)((int)local_cc + 0x14));
                            operator_delete(local_cc);
                            if (local_e4 == (void *)0x0) break;
                            local_cc = local_a0;
                            pvVar3 = local_cc;
                          }
                        }
                        local_ec = *(void **)((int)local_f0 + 8);
                        local_90 = 6;
                        local_a4 = local_ec;
                        OFDelegate::~OFDelegate((OFDelegate *)((int)local_c8 + 0x14));
                        operator_delete(local_c8);
                        if (local_ec == (void *)0x0) break;
                        local_c8 = local_a4;
                        pvVar3 = local_c8;
                      }
                    }
                    local_f4 = *(void **)((int)local_f8 + 8);
                    local_90 = 5;
                    local_a8 = local_f4;
                    OFDelegate::~OFDelegate((OFDelegate *)((int)local_c4 + 0x14));
                    operator_delete(local_c4);
                    if (local_f4 == (void *)0x0) break;
                    local_c4 = local_a8;
                    pvVar3 = local_c4;
                  }
                }
                local_fc = *(void **)((int)local_100 + 8);
                local_90 = 4;
                local_ac = local_fc;
                OFDelegate::~OFDelegate((OFDelegate *)((int)local_c0 + 0x14));
                operator_delete(local_c0);
                if (local_fc == (void *)0x0) break;
                local_c0 = local_ac;
                pvVar3 = local_c0;
              }
            }
            local_104 = *(void **)((int)local_108 + 8);
            local_90 = 3;
            local_b0 = local_104;
            OFDelegate::~OFDelegate((OFDelegate *)((int)local_bc + 0x14));
            operator_delete(local_bc);
            if (local_104 == (void *)0x0) break;
            local_bc = local_b0;
            pvVar3 = local_bc;
          }
        }
        local_10c = *(void **)((int)local_110 + 8);
        local_90 = 2;
        local_b4 = local_10c;
        OFDelegate::~OFDelegate((OFDelegate *)((int)local_b8 + 0x14));
        operator_delete(local_b8);
        if (local_10c == (void *)0x0) break;
        local_b8 = local_b4;
        pvVar3 = local_b8;
      }
    }
    local_11c = *(_Rb_tree_node **)(local_118 + 8);
    local_90 = 1;
    local_114 = local_11c;
    OFDelegate::~OFDelegate((OFDelegate *)(local_124 + 0x14));
    operator_delete(local_124);
    local_124 = local_11c;
    p_Var1 = local_114;
  }
  __Unwind_SjLj_Unregister(auStack_94);
  return;
}
