/*
 * mangled: _ZN6OFRTTIC2EPKcPKS_PFPvP13OFISerializerE
 * demangled: OFRTTI::OFRTTI(char const*, OFRTTI const*, void* (*)(OFISerializer*))
 * address: 000037f0
 * size: 424
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
  *local_b0;
  _func_void_ptr_OFISerializer_ptr *local_ac;
  OFRTTI *local_a8;
  char *local_a4;
  OFRTTI *local_a0;
  OFRTTIRepository *local_9c;
  _Rb_tree<OFSdbmHashedString,std::pair<OFSdbmHashedString_const,OFRTTI_const*>,std::_Select1st<std::pair<OFSdbmHashedString_const,OFRTTI_const*>>,std::less<OFSdbmHashedString>,std::allocator<std::pair<OFSdbmHashedString_const,OFRTTI_const*>>>
  *local_98;
  undefined1 auStack_94 [4];
  undefined4 local_90;
  undefined *local_7c;
  undefined *local_78;
  undefined1 *local_74;
  undefined *local_70;
  undefined1 *local_6c;

  local_74 = &stack0xfffffff8;
  local_6c = auStack_b4;
  local_7c = PTR_001b615c;
  local_78 = &::GCC_except_table2;
  local_70 = &DAT_00003998;
  local_ac = param_3;
  local_a8 = param_2;
  local_a4 = param_1;
  local_a0 = this;
  __Unwind_SjLj_Register(auStack_94);
  local_90 = 0xffffffff;
  OFSdbmHashedString::OFSdbmHashedString((OFSdbmHashedString *)(local_a0 + 8),local_a4);
  sVar1 = _strlen(local_a4);
  pcVar2 = operator_new__(sVar1 + 1);
  *(char **)local_a0 = pcVar2;
  _strcpy(pcVar2,local_a4);
  *(OFRTTI **)(local_a0 + 4) = local_a8;
  *(_func_void_ptr_OFISerializer_ptr **)(local_a0 + 0xc) = local_ac;
  local_b0 = (_Rb_tree<OFSdbmHashedString,std::pair<OFSdbmHashedString_const,OFRTTI_const*>,std::_Select1st<std::pair<OFSdbmHashedString_const,OFRTTI_const*>>,std::less<OFSdbmHashedString>,std::allocator<std::pair<OFSdbmHashedString_const,OFRTTI_const*>>>
              *)(int)*DAT_001edf4c;
  if ((local_b0 ==
       (_Rb_tree<OFSdbmHashedString,std::pair<OFSdbmHashedString_const,OFRTTI_const*>,std::_Select1st<std::pair<OFSdbmHashedString_const,OFRTTI_const*>>,std::less<OFSdbmHashedString>,std::allocator<std::pair<OFSdbmHashedString_const,OFRTTI_const*>>>
        *)0x0) && (iVar3 = ___cxa_guard_acquire(DAT_001edf4c), iVar3 != 0)) {
    OFRTTIRepository::Instance()::sInstance = local_b0;
    ___cxa_guard_release(DAT_001edf4c);
    ___cxa_atexit(::___tcf_0,local_b0,PTR_MACH_HEADER_001b6204);
  }
  local_9c = (OFRTTIRepository *)OFRTTIRepository::Instance()::sInstance;
  if (OFRTTIRepository::Instance()::sInstance ==
      (_Rb_tree<OFSdbmHashedString,std::pair<OFSdbmHashedString_const,OFRTTI_const*>,std::_Select1st<std::pair<OFSdbmHashedString_const,OFRTTI_const*>>,std::less<OFSdbmHashedString>,std::allocator<std::pair<OFSdbmHashedString_const,OFRTTI_const*>>>
       *)0x0) {
    local_90 = 0xffffffff;
    local_9c = operator_new(0x18);
    local_90 = 2;
    OFRTTIRepository::OFRTTIRepository(local_9c);
    local_98 = OFRTTIRepository::Instance()::sInstance;
    if (local_9c != (OFRTTIRepository *)OFRTTIRepository::Instance()::sInstance) {
      if (OFRTTIRepository::Instance()::sInstance !=
          (_Rb_tree<OFSdbmHashedString,std::pair<OFSdbmHashedString_const,OFRTTI_const*>,std::_Select1st<std::pair<OFSdbmHashedString_const,OFRTTI_const*>>,std::less<OFSdbmHashedString>,std::allocator<std::pair<OFSdbmHashedString_const,OFRTTI_const*>>>
           *)0x0) {
        local_90 = 1;
        std::
        _Rb_tree<OFSdbmHashedString,std::pair<OFSdbmHashedString_const,OFRTTI_const*>,std::_Select1st<std::pair<OFSdbmHashedString_const,OFRTTI_const*>>,std::less<OFSdbmHashedString>,std::allocator<std::pair<OFSdbmHashedString_const,OFRTTI_const*>>>
        ::_M_erase(OFRTTIRepository::Instance()::sInstance,
                   *(_Rb_tree_node **)(OFRTTIRepository::Instance()::sInstance + 8));
        operator_delete(local_98);
      }
      OFRTTIRepository::Instance()::sInstance =
           (_Rb_tree<OFSdbmHashedString,std::pair<OFSdbmHashedString_const,OFRTTI_const*>,std::_Select1st<std::pair<OFSdbmHashedString_const,OFRTTI_const*>>,std::less<OFSdbmHashedString>,std::allocator<std::pair<OFSdbmHashedString_const,OFRTTI_const*>>>
            *)local_9c;
    }
  }
  local_90 = 0xffffffff;
  OFRTTIRepository::RegisterType(local_9c,local_a0);
  __Unwind_SjLj_Unregister(auStack_94);
  return;
}
