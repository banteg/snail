/*
 * mangled: _ZNSt8_Rb_treeI18OFSdbmHashedStringSt4pairIKS0_PK6OFRTTIESt10_Select1stIS6_ESt4lessIS0_ESaIS6_EE8_M_eraseEPSt13_Rb_tree_nodeIS6_E
 * demangled: std::_Rb_tree<OFSdbmHashedString, std::pair<OFSdbmHashedString const, OFRTTI const*>, std::_Select1st<std::pair<OFSdbmHashedString const, OFRTTI const*>>, std::less<OFSdbmHashedString>, std::allocator<std::pair<OFSdbmHashedString const, OFRTTI const*>>>::_M_erase(std::_Rb_tree_node<std::pair<OFSdbmHashedString const, OFRTTI const*>>*)
 * address: 00003a14
 * size: 444
 */

/* std::_Rb_tree<OFSdbmHashedString, std::pair<OFSdbmHashedString const, OFRTTI const*>,
   std::_Select1st<std::pair<OFSdbmHashedString const, OFRTTI const*> >,
   std::less<OFSdbmHashedString>, std::allocator<std::pair<OFSdbmHashedString const, OFRTTI const*>
   > >::_M_erase(std::_Rb_tree_node<std::pair<OFSdbmHashedString const, OFRTTI const*> >*) */

void __thiscall
std::
_Rb_tree<OFSdbmHashedString,std::pair<OFSdbmHashedString_const,OFRTTI_const*>,std::_Select1st<std::pair<OFSdbmHashedString_const,OFRTTI_const*>>,std::less<OFSdbmHashedString>,std::allocator<std::pair<OFSdbmHashedString_const,OFRTTI_const*>>>
::_M_erase(_Rb_tree<OFSdbmHashedString,std::pair<OFSdbmHashedString_const,OFRTTI_const*>,std::_Select1st<std::pair<OFSdbmHashedString_const,OFRTTI_const*>>,std::less<OFSdbmHashedString>,std::allocator<std::pair<OFSdbmHashedString_const,OFRTTI_const*>>>
           *this,_Rb_tree_node *param_1)

{
  void *pvVar1;
  void *pvVar2;
  void *pvVar3;
  void *pvVar4;
  void *pvVar5;
  void *pvVar6;
  void *pvVar7;
  void *pvVar8;
  _Rb_tree_node *p_Var9;
  void *pvVar10;

  while (param_1 != (_Rb_tree_node *)0x0) {
    pvVar1 = *(void **)(param_1 + 0xc);
    while (pvVar1 != (void *)0x0) {
      pvVar8 = *(void **)((int)pvVar1 + 0xc);
      while (pvVar8 != (void *)0x0) {
        pvVar7 = *(void **)((int)pvVar8 + 0xc);
        while (pvVar7 != (void *)0x0) {
          pvVar6 = *(void **)((int)pvVar7 + 0xc);
          while (pvVar6 != (void *)0x0) {
            pvVar5 = *(void **)((int)pvVar6 + 0xc);
            while (pvVar5 != (void *)0x0) {
              pvVar4 = *(void **)((int)pvVar5 + 0xc);
              while (pvVar4 != (void *)0x0) {
                pvVar3 = *(void **)((int)pvVar4 + 0xc);
                while (pvVar3 != (void *)0x0) {
                  pvVar2 = *(void **)((int)pvVar3 + 0xc);
                  while (pvVar2 != (void *)0x0) {
                    _M_erase(this,*(_Rb_tree_node **)((int)pvVar2 + 0xc));
                    pvVar10 = *(void **)((int)pvVar2 + 8);
                    operator_delete(pvVar2);
                    pvVar2 = pvVar10;
                  }
                  pvVar2 = *(void **)((int)pvVar3 + 8);
                  operator_delete(pvVar3);
                  pvVar3 = pvVar2;
                }
                pvVar3 = *(void **)((int)pvVar4 + 8);
                operator_delete(pvVar4);
                pvVar4 = pvVar3;
              }
              pvVar4 = *(void **)((int)pvVar5 + 8);
              operator_delete(pvVar5);
              pvVar5 = pvVar4;
            }
            pvVar5 = *(void **)((int)pvVar6 + 8);
            operator_delete(pvVar6);
            pvVar6 = pvVar5;
          }
          pvVar6 = *(void **)((int)pvVar7 + 8);
          operator_delete(pvVar7);
          pvVar7 = pvVar6;
        }
        pvVar7 = *(void **)((int)pvVar8 + 8);
        operator_delete(pvVar8);
        pvVar8 = pvVar7;
      }
      pvVar8 = *(void **)((int)pvVar1 + 8);
      operator_delete(pvVar1);
      pvVar1 = pvVar8;
    }
    p_Var9 = *(_Rb_tree_node **)(param_1 + 8);
    operator_delete(param_1);
    param_1 = p_Var9;
  }
  return;
}
