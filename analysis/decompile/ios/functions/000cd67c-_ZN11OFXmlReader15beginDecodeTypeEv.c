/*
 * mangled: _ZN11OFXmlReader15beginDecodeTypeEv
 * demangled: OFXmlReader::beginDecodeType()
 * address: 000cd67c
 * size: 404
 */

/* OFXmlReader::beginDecodeType() */

undefined4 __thiscall OFXmlReader::beginDecodeType(OFXmlReader *this)

{
  ID self;
  char *pcVar1;
  int iVar2;
  undefined1 auStack_ac [4];
  _Rb_tree<OFSdbmHashedString,std::pair<OFSdbmHashedString_const,OFRTTI_const*>,std::_Select1st<std::pair<OFSdbmHashedString_const,OFRTTI_const*>>,std::less<OFSdbmHashedString>,std::allocator<std::pair<OFSdbmHashedString_const,OFRTTI_const*>>>
  *local_a8;
  OFXmlReader *local_a4;
  undefined4 local_a0;
  _Rb_tree<OFSdbmHashedString,std::pair<OFSdbmHashedString_const,OFRTTI_const*>,std::_Select1st<std::pair<OFSdbmHashedString_const,OFRTTI_const*>>,std::less<OFSdbmHashedString>,std::allocator<std::pair<OFSdbmHashedString_const,OFRTTI_const*>>>
  *local_9c;
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
  local_6c = auStack_ac;
  local_7c = PTR_001b615c;
  local_78 = &::GCC_except_table2;
  local_70 = &DAT_000cd810;
  local_a4 = this;
  __Unwind_SjLj_Register(auStack_94);
  local_90 = 0xffffffff;
  _objc_msgSend(*(ID *)(local_a4 + 0x18),"pushNextUnreadScope");
  local_a8 = (_Rb_tree<OFSdbmHashedString,std::pair<OFSdbmHashedString_const,OFRTTI_const*>,std::_Select1st<std::pair<OFSdbmHashedString_const,OFRTTI_const*>>,std::less<OFSdbmHashedString>,std::allocator<std::pair<OFSdbmHashedString_const,OFRTTI_const*>>>
              *)(int)*DAT_001edf54;
  if ((local_a8 ==
       (_Rb_tree<OFSdbmHashedString,std::pair<OFSdbmHashedString_const,OFRTTI_const*>,std::_Select1st<std::pair<OFSdbmHashedString_const,OFRTTI_const*>>,std::less<OFSdbmHashedString>,std::allocator<std::pair<OFSdbmHashedString_const,OFRTTI_const*>>>
        *)0x0) && (iVar2 = ___cxa_guard_acquire(DAT_001edf54), iVar2 != 0)) {
    OFRTTIRepository::Instance()::sInstance = local_a8;
    ___cxa_guard_release(DAT_001edf54);
    ___cxa_atexit(::___tcf_0,local_a8,PTR_MACH_HEADER_001b6204);
  }
  local_9c = OFRTTIRepository::Instance()::sInstance;
  if (OFRTTIRepository::Instance()::sInstance ==
      (_Rb_tree<OFSdbmHashedString,std::pair<OFSdbmHashedString_const,OFRTTI_const*>,std::_Select1st<std::pair<OFSdbmHashedString_const,OFRTTI_const*>>,std::less<OFSdbmHashedString>,std::allocator<std::pair<OFSdbmHashedString_const,OFRTTI_const*>>>
       *)0x0) {
    local_90 = 0xffffffff;
    local_9c = operator_new(0x18);
    local_90 = 2;
    OFRTTIRepository::OFRTTIRepository((OFRTTIRepository *)local_9c);
    local_98 = OFRTTIRepository::Instance()::sInstance;
    if (local_9c != OFRTTIRepository::Instance()::sInstance) {
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
      OFRTTIRepository::Instance()::sInstance = local_9c;
    }
  }
  local_90 = 0xffffffff;
  self = _objc_msgSend(*(ID *)(local_a4 + 0x18),"getCurrentScopeShortName");
  pcVar1 = (char *)_objc_msgSend(self,"UTF8String");
  local_a0 = OFRTTIRepository::getType((OFRTTIRepository *)local_9c,pcVar1);
  __Unwind_SjLj_Unregister(auStack_94);
  return local_a0;
}
