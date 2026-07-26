/*
 * mangled: _ZNSt8_Rb_treeImSt4pairIKmP17SoundEngineEffectESt10_Select1stIS4_ESt4lessIjESaIS4_EE9_M_insertEPSt18_Rb_tree_node_baseSC_RKS4_
 * demangled: std::_Rb_tree<unsigned long, std::pair<unsigned long const, SoundEngineEffect*>, std::_Select1st<std::pair<unsigned long const, SoundEngineEffect*>>, std::less<unsigned int>, std::allocator<std::pair<unsigned long const, SoundEngineEffect*>>>::_M_insert(std::_Rb_tree_node_base*, std::_Rb_tree_node_base*, std::pair<unsigned long const, SoundEngineEffect*> const&)
 * address: 00073508
 * size: 152
 */

/* std::_Rb_tree<unsigned long, std::pair<unsigned long const, SoundEngineEffect*>,
   std::_Select1st<std::pair<unsigned long const, SoundEngineEffect*> >, std::less<unsigned int>,
   std::allocator<std::pair<unsigned long const, SoundEngineEffect*> >
   >::_M_insert(std::_Rb_tree_node_base*, std::_Rb_tree_node_base*, std::pair<unsigned long const,
   SoundEngineEffect*> const&) */

_Rb_tree_node_base * __thiscall
std::
_Rb_tree<unsigned_long,std::pair<unsigned_long_const,SoundEngineEffect*>,std::_Select1st<std::pair<unsigned_long_const,SoundEngineEffect*>>,std::less<unsigned_int>,std::allocator<std::pair<unsigned_long_const,SoundEngineEffect*>>>
::_M_insert(_Rb_tree<unsigned_long,std::pair<unsigned_long_const,SoundEngineEffect*>,std::_Select1st<std::pair<unsigned_long_const,SoundEngineEffect*>>,std::less<unsigned_int>,std::allocator<std::pair<unsigned_long_const,SoundEngineEffect*>>>
            *this,_Rb_tree_node_base *param_1,_Rb_tree_node_base *param_2,pair *param_3)

{
  _Rb_tree_node_base *p_Var1;
  undefined4 uVar2;
  bool bVar3;

  if ((param_1 == (_Rb_tree_node_base *)0x0) &&
     (this + 4 !=
      (_Rb_tree<unsigned_long,std::pair<unsigned_long_const,SoundEngineEffect*>,std::_Select1st<std::pair<unsigned_long_const,SoundEngineEffect*>>,std::less<unsigned_int>,std::allocator<std::pair<unsigned_long_const,SoundEngineEffect*>>>
       *)param_2)) {
    bVar3 = *(uint *)param_3 < *(uint *)(param_2 + 0x10);
  }
  else {
    bVar3 = true;
  }
  p_Var1 = operator_new(0x18);
  if (p_Var1 != (_Rb_tree_node_base *)0xfffffff0) {
    uVar2 = *(undefined4 *)(param_3 + 4);
    *(undefined4 *)(p_Var1 + 0x10) = *(undefined4 *)param_3;
    *(undefined4 *)(p_Var1 + 0x14) = uVar2;
  }
  std::_Rb_tree_insert_and_rebalance(bVar3,p_Var1,param_2,(_Rb_tree_node_base *)(this + 4));
  *(int *)(this + 0x14) = *(int *)(this + 0x14) + 1;
  return p_Var1;
}
