/*
 * mangled: _ZNSt8_Rb_treeI18OFSdbmHashedStringSt4pairIKS0_PK6OFRTTIESt10_Select1stIS6_ESt4lessIS0_ESaIS6_EE9_M_insertEPSt18_Rb_tree_node_baseSE_RKS6_
 * demangled: std::_Rb_tree<OFSdbmHashedString, std::pair<OFSdbmHashedString const, OFRTTI const*>, std::_Select1st<std::pair<OFSdbmHashedString const, OFRTTI const*>>, std::less<OFSdbmHashedString>, std::allocator<std::pair<OFSdbmHashedString const, OFRTTI const*>>>::_M_insert(std::_Rb_tree_node_base*, std::_Rb_tree_node_base*, std::pair<OFSdbmHashedString const, OFRTTI const*> const&)
 * address: 00003c44
 * size: 156
 */

/* std::_Rb_tree<OFSdbmHashedString, std::pair<OFSdbmHashedString const, OFRTTI const*>,
   std::_Select1st<std::pair<OFSdbmHashedString const, OFRTTI const*> >,
   std::less<OFSdbmHashedString>, std::allocator<std::pair<OFSdbmHashedString const, OFRTTI const*>
   > >::_M_insert(std::_Rb_tree_node_base*, std::_Rb_tree_node_base*, std::pair<OFSdbmHashedString
   const, OFRTTI const*> const&) */

_Rb_tree_node_base * __thiscall
std::
_Rb_tree<OFSdbmHashedString,std::pair<OFSdbmHashedString_const,OFRTTI_const*>,std::_Select1st<std::pair<OFSdbmHashedString_const,OFRTTI_const*>>,std::less<OFSdbmHashedString>,std::allocator<std::pair<OFSdbmHashedString_const,OFRTTI_const*>>>
::_M_insert(_Rb_tree<OFSdbmHashedString,std::pair<OFSdbmHashedString_const,OFRTTI_const*>,std::_Select1st<std::pair<OFSdbmHashedString_const,OFRTTI_const*>>,std::less<OFSdbmHashedString>,std::allocator<std::pair<OFSdbmHashedString_const,OFRTTI_const*>>>
            *this,_Rb_tree_node_base *param_1,_Rb_tree_node_base *param_2,pair *param_3)

{
  _Rb_tree_node_base *p_Var1;
  undefined4 uVar2;
  int iVar3;
  bool bVar4;

  if (((param_1 == (_Rb_tree_node_base *)0x0) &&
      (this + 4 !=
       (_Rb_tree<OFSdbmHashedString,std::pair<OFSdbmHashedString_const,OFRTTI_const*>,std::_Select1st<std::pair<OFSdbmHashedString_const,OFRTTI_const*>>,std::less<OFSdbmHashedString>,std::allocator<std::pair<OFSdbmHashedString_const,OFRTTI_const*>>>
        *)param_2)) &&
     (iVar3 = OFSdbmHashedString::operator<
                        ((OFSdbmHashedString *)param_3,(OFSdbmHashedString *)(param_2 + 0x10)),
     iVar3 == 0)) {
    bVar4 = false;
  }
  else {
    bVar4 = true;
  }
  p_Var1 = operator_new(0x18);
  if (p_Var1 != (_Rb_tree_node_base *)0xfffffff0) {
    uVar2 = *(undefined4 *)(param_3 + 4);
    *(undefined4 *)(p_Var1 + 0x10) = *(undefined4 *)param_3;
    *(undefined4 *)(p_Var1 + 0x14) = uVar2;
  }
  std::_Rb_tree_insert_and_rebalance(bVar4,p_Var1,param_2,(_Rb_tree_node_base *)(this + 4));
  *(int *)(this + 0x14) = *(int *)(this + 0x14) + 1;
  return p_Var1;
}
