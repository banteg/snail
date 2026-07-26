/*
 * mangled: _ZN13OFISerializer5ScopeD1Ev
 * demangled: OFISerializer::Scope::~Scope()
 * address: 000cbd60
 * size: 20
 */

/* OFISerializer::Scope::~Scope() */

void __thiscall OFISerializer::Scope::~Scope(Scope *this)

{
  if (*(int *)this == 0) {
    return;
  }
  popScope(*(OFISerializer **)(this + 4));
  return;
}
