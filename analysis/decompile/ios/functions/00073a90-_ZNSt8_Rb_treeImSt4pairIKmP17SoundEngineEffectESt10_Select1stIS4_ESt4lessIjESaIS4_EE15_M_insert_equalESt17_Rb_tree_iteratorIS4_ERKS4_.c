/*
 * mangled: _ZNSt8_Rb_treeImSt4pairIKmP17SoundEngineEffectESt10_Select1stIS4_ESt4lessIjESaIS4_EE15_M_insert_equalESt17_Rb_tree_iteratorIS4_ERKS4_
 * demangled: std::_Rb_tree<unsigned long, std::pair<unsigned long const, SoundEngineEffect*>, std::_Select1st<std::pair<unsigned long const, SoundEngineEffect*>>, std::less<unsigned int>, std::allocator<std::pair<unsigned long const, SoundEngineEffect*>>>::_M_insert_equal(std::_Rb_tree_iterator<std::pair<unsigned long const, SoundEngineEffect*>>, std::pair<unsigned long const, SoundEngineEffect*> const&)
 * address: 00073a90
 * size: 572
 */

/* std::_Rb_tree<unsigned long, std::pair<unsigned long const, SoundEngineEffect*>,
   std::_Select1st<std::pair<unsigned long const, SoundEngineEffect*> >, std::less<unsigned int>,
   std::allocator<std::pair<unsigned long const, SoundEngineEffect*> >
   >::_M_insert_equal(std::_Rb_tree_iterator<std::pair<unsigned long const, SoundEngineEffect*> >,
   std::pair<unsigned long const, SoundEngineEffect*> const&) */

_Rb_tree_node_base * __thiscall
std::
_Rb_tree<unsigned_long,std::pair<unsigned_long_const,SoundEngineEffect*>,std::_Select1st<std::pair<unsigned_long_const,SoundEngineEffect*>>,std::less<unsigned_int>,std::allocator<std::pair<unsigned_long_const,SoundEngineEffect*>>>
::_M_insert_equal(_Rb_tree<unsigned_long,std::pair<unsigned_long_const,SoundEngineEffect*>,std::_Select1st<std::pair<unsigned_long_const,SoundEngineEffect*>>,std::less<unsigned_int>,std::allocator<std::pair<unsigned_long_const,SoundEngineEffect*>>>
                  *this,_Rb_tree_node_base *param_2,pair *param_3)

{
  _Rb_tree_node_base *p_Var1;
  _Rb_tree_node_base *p_Var2;
  undefined4 uVar3;
  uint uVar4;
  _Rb_tree_node_base *p_Var5;
  bool bVar6;

  p_Var5 = (_Rb_tree_node_base *)(this + 4);
  if (p_Var5 == param_2) {
    if (((*(int *)(this + 0x14) == 0) ||
        (p_Var1 = *(_Rb_tree_node_base **)(this + 0x10),
        *(uint *)param_3 < *(uint *)(*(_Rb_tree_node_base **)(this + 0x10) + 0x10))) &&
       (p_Var1 = p_Var5, *(_Rb_tree_node_base **)(this + 8) != (_Rb_tree_node_base *)0x0)) {
      p_Var5 = *(_Rb_tree_node_base **)(this + 8);
      do {
        p_Var1 = p_Var5;
        if (*(uint *)param_3 < *(uint *)(p_Var1 + 0x10)) {
          p_Var5 = *(_Rb_tree_node_base **)(p_Var1 + 8);
        }
        else {
          p_Var5 = *(_Rb_tree_node_base **)(p_Var1 + 0xc);
        }
      } while (p_Var5 != (_Rb_tree_node_base *)0x0);
    }
LAB_00073c18:
    p_Var5 = (_Rb_tree_node_base *)_M_insert(this,(_Rb_tree_node_base *)0x0,p_Var1,param_3);
  }
  else {
    uVar4 = *(uint *)param_3;
    if (*(uint *)(param_2 + 0x10) < uVar4) {
      if (param_2 == *(_Rb_tree_node_base **)(this + 0x10)) {
        p_Var1 = (_Rb_tree_node_base *)0x0;
      }
      else {
        p_Var1 = (_Rb_tree_node_base *)std::_Rb_tree_increment(param_2);
        uVar4 = *(uint *)param_3;
        if (*(uint *)(p_Var1 + 0x10) < uVar4) {
          p_Var1 = p_Var5;
          p_Var2 = *(_Rb_tree_node_base **)(this + 8);
          while (p_Var2 != (_Rb_tree_node_base *)0x0) {
            p_Var1 = p_Var2;
            if (*(uint *)(p_Var2 + 0x10) < uVar4) {
              p_Var2 = *(_Rb_tree_node_base **)(p_Var2 + 0xc);
            }
            else {
              p_Var2 = *(_Rb_tree_node_base **)(p_Var2 + 8);
            }
          }
          if (p_Var5 == p_Var1) {
            bVar6 = true;
          }
          else if (*(uint *)(p_Var1 + 0x10) < uVar4) {
            bVar6 = false;
          }
          else {
            bVar6 = true;
          }
          p_Var2 = operator_new(0x18);
          if (p_Var2 != (_Rb_tree_node_base *)0xfffffff0) {
            uVar3 = *(undefined4 *)(param_3 + 4);
            *(undefined4 *)(p_Var2 + 0x10) = *(undefined4 *)param_3;
            *(undefined4 *)(p_Var2 + 0x14) = uVar3;
          }
          std::_Rb_tree_insert_and_rebalance(bVar6,p_Var2,p_Var1,p_Var5);
          *(int *)(this + 0x14) = *(int *)(this + 0x14) + 1;
          return p_Var2;
        }
        if (*(int *)(param_2 + 0xc) != 0) {
          p_Var5 = (_Rb_tree_node_base *)_M_insert(this,p_Var1,p_Var1,param_3);
          return p_Var5;
        }
        p_Var1 = (_Rb_tree_node_base *)0x0;
      }
    }
    else {
      p_Var1 = param_2;
      if (*(_Rb_tree_node_base **)(this + 0xc) != param_2) {
        p_Var1 = (_Rb_tree_node_base *)std::_Rb_tree_decrement(param_2);
        if (*(uint *)(p_Var1 + 0x10) <= uVar4) {
          if (*(int *)(p_Var1 + 0xc) != 0) {
            p_Var5 = (_Rb_tree_node_base *)_M_insert(this,param_2,param_2,param_3);
            return p_Var5;
          }
          p_Var5 = (_Rb_tree_node_base *)_M_insert(this,(_Rb_tree_node_base *)0x0,p_Var1,param_3);
          return p_Var5;
        }
        p_Var1 = p_Var5;
        if (*(_Rb_tree_node_base **)(this + 8) != (_Rb_tree_node_base *)0x0) {
          p_Var5 = *(_Rb_tree_node_base **)(this + 8);
          do {
            p_Var1 = p_Var5;
            if (*(uint *)param_3 < *(uint *)(p_Var1 + 0x10)) {
              p_Var5 = *(_Rb_tree_node_base **)(p_Var1 + 8);
            }
            else {
              p_Var5 = *(_Rb_tree_node_base **)(p_Var1 + 0xc);
            }
          } while (p_Var5 != (_Rb_tree_node_base *)0x0);
        }
        goto LAB_00073c18;
      }
    }
    p_Var5 = (_Rb_tree_node_base *)_M_insert(this,p_Var1,param_2,param_3);
  }
  return p_Var5;
}
