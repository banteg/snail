/*
 * mangled: _ZN16OFRTTIRepository12RegisterTypeEP6OFRTTI
 * demangled: OFRTTIRepository::RegisterType(OFRTTI*)
 * address: 00003c10
 * size: 52
 */

/* OFRTTIRepository::RegisterType(OFRTTI*) */

void __thiscall OFRTTIRepository::RegisterType(OFRTTIRepository *this,OFRTTI *param_1)

{
  pair apStack_18 [8];
  undefined4 local_10;
  OFRTTI *local_c;

  local_10 = *(undefined4 *)(param_1 + 8);
  local_c = param_1;
  std::
  _Rb_tree<OFSdbmHashedString,std::pair<OFSdbmHashedString_const,OFRTTI_const*>,std::_Select1st<std::pair<OFSdbmHashedString_const,OFRTTI_const*>>,std::less<OFSdbmHashedString>,std::allocator<std::pair<OFSdbmHashedString_const,OFRTTI_const*>>>
  ::_M_insert_unique(apStack_18);
  return;
}
