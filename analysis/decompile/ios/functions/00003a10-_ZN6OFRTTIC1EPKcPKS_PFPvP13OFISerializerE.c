/*
 * mangled: _ZN6OFRTTIC1EPKcPKS_PFPvP13OFISerializerE
 * demangled: OFRTTI::OFRTTI(char const*, OFRTTI const*, void* (*)(OFISerializer*))
 * address: 00003a10
 * size: 4
 */

/* OFRTTI::OFRTTI(char const*, OFRTTI const*, void* (*)(OFISerializer*)) */

void __thiscall
OFRTTI::OFRTTI(OFRTTI *this,char *param_1,OFRTTI *param_2,_func_void_ptr_OFISerializer_ptr *param_3)

{
  size_t sVar1;
  char *pcVar2;
  int iVar3;
  undefined1 auStack_b4 [4];
  _Rb_tree<OFSdbmHashedString,std::pair<OFSdbmHashedString_const,OFRTTI_const*>,std::_Select1st<std::pair<OFSdbmHashedString_const,OFRTTI_const*>>,std::less<OFSdbmHashedString>,std::allocator<std::pair<OFSdbmHashedString_const,OFRTTI_const*>>>
  *p_Stack_b0;
  _func_void_ptr_OFISerializer_ptr *p_Stack_ac;
  OFRTTI *pOStack_a8;
  char *pcStack_a4;
  OFRTTI *pOStack_a0;
  OFRTTIRepository *pOStack_9c;
  _Rb_tree<OFSdbmHashedString,std::pair<OFSdbmHashedString_const,OFRTTI_const*>,std::_Select1st<std::pair<OFSdbmHashedString_const,OFRTTI_const*>>,std::less<OFSdbmHashedString>,std::allocator<std::pair<OFSdbmHashedString_const,OFRTTI_const*>>>
  *p_Stack_98;
  undefined1 auStack_94 [4];
  undefined4 uStack_90;
  undefined *puStack_7c;
  undefined *puStack_78;
  undefined1 *puStack_74;
  undefined *puStack_70;
  undefined1 *puStack_6c;

  puStack_74 = &stack0xfffffff8;
  puStack_6c = auStack_b4;
  puStack_7c = PTR_001b615c;
  puStack_78 = &::GCC_except_table2;
  puStack_70 = &DAT_00003998;
  p_Stack_ac = param_3;
  pOStack_a8 = param_2;
  pcStack_a4 = param_1;
  pOStack_a0 = this;
  __Unwind_SjLj_Register(auStack_94);
  uStack_90 = 0xffffffff;
  OFSdbmHashedString::OFSdbmHashedString((OFSdbmHashedString *)(pOStack_a0 + 8),pcStack_a4);
  sVar1 = _strlen(pcStack_a4);
  pcVar2 = operator_new__(sVar1 + 1);
  *(char **)pOStack_a0 = pcVar2;
  _strcpy(pcVar2,pcStack_a4);
  *(OFRTTI **)(pOStack_a0 + 4) = pOStack_a8;
  *(_func_void_ptr_OFISerializer_ptr **)(pOStack_a0 + 0xc) = p_Stack_ac;
  p_Stack_b0 = (_Rb_tree<OFSdbmHashedString,std::pair<OFSdbmHashedString_const,OFRTTI_const*>,std::_Select1st<std::pair<OFSdbmHashedString_const,OFRTTI_const*>>,std::less<OFSdbmHashedString>,std::allocator<std::pair<OFSdbmHashedString_const,OFRTTI_const*>>>
                *)(int)*DAT_001edf4c;
  if ((p_Stack_b0 ==
       (_Rb_tree<OFSdbmHashedString,std::pair<OFSdbmHashedString_const,OFRTTI_const*>,std::_Select1st<std::pair<OFSdbmHashedString_const,OFRTTI_const*>>,std::less<OFSdbmHashedString>,std::allocator<std::pair<OFSdbmHashedString_const,OFRTTI_const*>>>
        *)0x0) && (iVar3 = ___cxa_guard_acquire(DAT_001edf4c), iVar3 != 0)) {
    OFRTTIRepository::Instance()::sInstance = p_Stack_b0;
    ___cxa_guard_release(DAT_001edf4c);
    ___cxa_atexit(::___tcf_0,p_Stack_b0,PTR_MACH_HEADER_001b6204);
  }
  pOStack_9c = (OFRTTIRepository *)OFRTTIRepository::Instance()::sInstance;
  if (OFRTTIRepository::Instance()::sInstance ==
      (_Rb_tree<OFSdbmHashedString,std::pair<OFSdbmHashedString_const,OFRTTI_const*>,std::_Select1st<std::pair<OFSdbmHashedString_const,OFRTTI_const*>>,std::less<OFSdbmHashedString>,std::allocator<std::pair<OFSdbmHashedString_const,OFRTTI_const*>>>
       *)0x0) {
    uStack_90 = 0xffffffff;
    pOStack_9c = operator_new(0x18);
    uStack_90 = 2;
    OFRTTIRepository::OFRTTIRepository(pOStack_9c);
    p_Stack_98 = OFRTTIRepository::Instance()::sInstance;
    if (pOStack_9c != (OFRTTIRepository *)OFRTTIRepository::Instance()::sInstance) {
      if (OFRTTIRepository::Instance()::sInstance !=
          (_Rb_tree<OFSdbmHashedString,std::pair<OFSdbmHashedString_const,OFRTTI_const*>,std::_Select1st<std::pair<OFSdbmHashedString_const,OFRTTI_const*>>,std::less<OFSdbmHashedString>,std::allocator<std::pair<OFSdbmHashedString_const,OFRTTI_const*>>>
           *)0x0) {
        uStack_90 = 1;
        std::
        _Rb_tree<OFSdbmHashedString,std::pair<OFSdbmHashedString_const,OFRTTI_const*>,std::_Select1st<std::pair<OFSdbmHashedString_const,OFRTTI_const*>>,std::less<OFSdbmHashedString>,std::allocator<std::pair<OFSdbmHashedString_const,OFRTTI_const*>>>
        ::_M_erase(OFRTTIRepository::Instance()::sInstance,
                   *(_Rb_tree_node **)(OFRTTIRepository::Instance()::sInstance + 8));
        operator_delete(p_Stack_98);
      }
      OFRTTIRepository::Instance()::sInstance =
           (_Rb_tree<OFSdbmHashedString,std::pair<OFSdbmHashedString_const,OFRTTI_const*>,std::_Select1st<std::pair<OFSdbmHashedString_const,OFRTTI_const*>>,std::less<OFSdbmHashedString>,std::allocator<std::pair<OFSdbmHashedString_const,OFRTTI_const*>>>
            *)pOStack_9c;
    }
  }
  uStack_90 = 0xffffffff;
  OFRTTIRepository::RegisterType(pOStack_9c,pOStack_a0);
  __Unwind_SjLj_Unregister(auStack_94);
  return;
}
