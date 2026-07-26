/*
 * mangled: _ZNSt8_Rb_treeI18OFSdbmHashedStringSt4pairIKS0_PK6OFRTTIESt10_Select1stIS6_ESt4lessIS0_ESaIS6_EE16_M_insert_uniqueERKS6_
 * demangled: std::_Rb_tree<OFSdbmHashedString, std::pair<OFSdbmHashedString const, OFRTTI const*>, std::_Select1st<std::pair<OFSdbmHashedString const, OFRTTI const*>>, std::less<OFSdbmHashedString>, std::allocator<std::pair<OFSdbmHashedString const, OFRTTI const*>>>::_M_insert_unique(std::pair<OFSdbmHashedString const, OFRTTI const*> const&)
 * address: 00003ce0
 * size: 204
 */

/* std::_Rb_tree<OFSdbmHashedString, std::pair<OFSdbmHashedString const, OFRTTI const*>,
   std::_Select1st<std::pair<OFSdbmHashedString const, OFRTTI const*> >,
   std::less<OFSdbmHashedString>, std::allocator<std::pair<OFSdbmHashedString const, OFRTTI const*>
   > >::_M_insert_unique(std::pair<OFSdbmHashedString const, OFRTTI const*> const&) */

pair * std::
       _Rb_tree<OFSdbmHashedString,std::pair<OFSdbmHashedString_const,OFRTTI_const*>,std::_Select1st<std::pair<OFSdbmHashedString_const,OFRTTI_const*>>,std::less<OFSdbmHashedString>,std::allocator<std::pair<OFSdbmHashedString_const,OFRTTI_const*>>>
       ::_M_insert_unique(pair *param_1)

{
  int iVar1;
  undefined4 uVar2;
  _Rb_tree_node_base *p_Var3;
  _Rb_tree<OFSdbmHashedString,std::pair<OFSdbmHashedString_const,OFRTTI_const*>,std::_Select1st<std::pair<OFSdbmHashedString_const,OFRTTI_const*>>,std::less<OFSdbmHashedString>,std::allocator<std::pair<OFSdbmHashedString_const,OFRTTI_const*>>>
  *in_r1;
  OFSdbmHashedString *in_r2;
  _Rb_tree<OFSdbmHashedString,std::pair<OFSdbmHashedString_const,OFRTTI_const*>,std::_Select1st<std::pair<OFSdbmHashedString_const,OFRTTI_const*>>,std::less<OFSdbmHashedString>,std::allocator<std::pair<OFSdbmHashedString_const,OFRTTI_const*>>>
  *p_Var4;
  _Rb_tree_node_base *p_Var5;

  p_Var5 = *(_Rb_tree_node_base **)(in_r1 + 8);
  p_Var4 = in_r1 + 4;
  if (*(_Rb_tree_node_base **)(in_r1 + 8) == (_Rb_tree_node_base *)0x0) {
LAB_00003d38:
    if (p_Var4 == (_Rb_tree<OFSdbmHashedString,std::pair<OFSdbmHashedString_const,OFRTTI_const*>,std::_Select1st<std::pair<OFSdbmHashedString_const,OFRTTI_const*>>,std::less<OFSdbmHashedString>,std::allocator<std::pair<OFSdbmHashedString_const,OFRTTI_const*>>>
                   *)*(_Rb_tree_node_base **)(in_r1 + 0xc)) goto LAB_00003d50;
    p_Var3 = (_Rb_tree_node_base *)std::_Rb_tree_decrement((_Rb_tree_node_base *)p_Var4);
  }
  else {
    do {
      p_Var3 = p_Var5;
      iVar1 = OFSdbmHashedString::operator<(in_r2,(OFSdbmHashedString *)(p_Var3 + 0x10));
      if (iVar1 == 0) {
        p_Var5 = *(_Rb_tree_node_base **)(p_Var3 + 0xc);
      }
      else {
        p_Var5 = *(_Rb_tree_node_base **)(p_Var3 + 8);
      }
    } while (p_Var5 != (_Rb_tree_node_base *)0x0);
    p_Var4 = (_Rb_tree<OFSdbmHashedString,std::pair<OFSdbmHashedString_const,OFRTTI_const*>,std::_Select1st<std::pair<OFSdbmHashedString_const,OFRTTI_const*>>,std::less<OFSdbmHashedString>,std::allocator<std::pair<OFSdbmHashedString_const,OFRTTI_const*>>>
              *)p_Var3;
    if (iVar1 != 0) goto LAB_00003d38;
  }
  iVar1 = OFSdbmHashedString::operator<((OFSdbmHashedString *)(p_Var3 + 0x10),in_r2);
  if (iVar1 == 0) {
    *(_Rb_tree_node_base **)param_1 = p_Var3;
    param_1[4] = (pair)0x0;
    return param_1;
  }
LAB_00003d50:
  uVar2 = _M_insert(in_r1,(_Rb_tree_node_base *)0x0,(_Rb_tree_node_base *)p_Var4,(pair *)in_r2);
  param_1[4] = (pair)0x1;
  *(undefined4 *)param_1 = uVar2;
  return param_1;
}
