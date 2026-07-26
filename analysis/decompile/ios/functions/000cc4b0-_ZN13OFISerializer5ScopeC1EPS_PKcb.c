/*
 * mangled: _ZN13OFISerializer5ScopeC1EPS_PKcb
 * demangled: OFISerializer::Scope::Scope(OFISerializer*, char const*, bool)
 * address: 000cc4b0
 * size: 36
 */

/* OFISerializer::Scope::Scope(OFISerializer*, char const*, bool) */

void __thiscall
OFISerializer::Scope::Scope(Scope *this,OFISerializer *param_1,char *param_2,bool param_3)

{
  *(char **)this = param_2;
  if (param_2 == (char *)0x0) {
    return;
  }
  *(OFISerializer **)(this + 4) = param_1;
  pushScope(param_1,param_2,param_3);
  return;
}
