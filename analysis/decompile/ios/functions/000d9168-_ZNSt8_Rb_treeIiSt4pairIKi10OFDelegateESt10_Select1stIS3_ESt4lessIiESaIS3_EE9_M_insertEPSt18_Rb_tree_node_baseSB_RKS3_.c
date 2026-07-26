/*
 * mangled: _ZNSt8_Rb_treeIiSt4pairIKi10OFDelegateESt10_Select1stIS3_ESt4lessIiESaIS3_EE9_M_insertEPSt18_Rb_tree_node_baseSB_RKS3_
 * demangled: std::_Rb_tree<int, std::pair<int const, OFDelegate>, std::_Select1st<std::pair<int const, OFDelegate>>, std::less<int>, std::allocator<std::pair<int const, OFDelegate>>>::_M_insert(std::_Rb_tree_node_base*, std::_Rb_tree_node_base*, std::pair<int const, OFDelegate> const&)
 * address: 000d9168
 * size: 300
 */

/* WARNING: Type propagation algorithm not settling */
/* std::_Rb_tree<int, std::pair<int const, OFDelegate>, std::_Select1st<std::pair<int const,
   OFDelegate> >, std::less<int>, std::allocator<std::pair<int const, OFDelegate> >
   >::_M_insert(std::_Rb_tree_node_base*, std::_Rb_tree_node_base*, std::pair<int const, OFDelegate>
   const&) */

_Rb_tree_node_base * __thiscall
std::
_Rb_tree<int,std::pair<int_const,OFDelegate>,std::_Select1st<std::pair<int_const,OFDelegate>>,std::less<int>,std::allocator<std::pair<int_const,OFDelegate>>>
::_M_insert(_Rb_tree<int,std::pair<int_const,OFDelegate>,std::_Select1st<std::pair<int_const,OFDelegate>>,std::less<int>,std::allocator<std::pair<int_const,OFDelegate>>>
            *this,_Rb_tree_node_base *param_1,_Rb_tree_node_base *param_2,pair *param_3)

{
  OFDelegate *pOVar1;
  undefined1 auStack_b0 [4];
  OFDelegate *local_ac;
  _Rb_tree<int,std::pair<int_const,OFDelegate>,std::_Select1st<std::pair<int_const,OFDelegate>>,std::less<int>,std::allocator<std::pair<int_const,OFDelegate>>>
  *local_a8;
  _Rb_tree_node_base *local_a4;
  _Rb_tree<int,std::pair<int_const,OFDelegate>,std::_Select1st<std::pair<int_const,OFDelegate>>,std::less<int>,std::allocator<std::pair<int_const,OFDelegate>>>
  *local_a0;
  uint local_9c;
  _Rb_tree_node_base *local_98;
  undefined1 auStack_94 [4];
  undefined4 local_90;
  undefined *local_7c;
  undefined *local_78;
  undefined1 *local_74;
  undefined1 *local_70;
  undefined1 *local_6c;

  local_74 = &stack0xfffffff8;
  local_6c = auStack_b0;
  local_7c = PTR_001b615c;
  local_78 = &::GCC_except_table0;
  local_70 = &LAB_000d9294;
  local_ac = (OFDelegate *)param_3;
  local_a8 = (_Rb_tree<int,std::pair<int_const,OFDelegate>,std::_Select1st<std::pair<int_const,OFDelegate>>,std::less<int>,std::allocator<std::pair<int_const,OFDelegate>>>
              *)param_2;
  local_a4 = param_1;
  local_a0 = this;
  __Unwind_SjLj_Register(auStack_94);
  if ((local_a4 == (_Rb_tree_node_base *)0x0) && (local_a0 + 4 != local_a8)) {
    local_9c = (uint)((int)local_ac->field0_0x0 < *(int *)(local_a8 + 0x10));
  }
  else {
    local_9c = 1;
  }
  local_90 = 0xffffffff;
  local_98 = operator_new(0x24);
  if (local_98 != (_Rb_tree_node_base *)0xfffffff0) {
    pOVar1 = (OFDelegate *)&local_ac->field1_0x4;
    *(ID *)(local_98 + 0x10) = local_ac->field0_0x0;
    local_90 = 1;
    local_ac = pOVar1;
    OFDelegate::OFDelegate((OFDelegate *)(local_98 + 0x14),pOVar1);
  }
  local_90 = 0xffffffff;
  std::_Rb_tree_insert_and_rebalance
            (SUB41(local_9c,0),local_98,(_Rb_tree_node_base *)local_a8,
             (_Rb_tree_node_base *)(local_a0 + 4));
  *(int *)(local_a0 + 0x14) = *(int *)(local_a0 + 0x14) + 1;
  __Unwind_SjLj_Unregister(auStack_94);
  return local_98;
}
