/*
 * mangled: _ZNK13OFISerializer21isCurrentScopeASeriesEv
 * demangled: OFISerializer::isCurrentScopeASeries() const
 * address: 000cb79c
 * size: 36
 */

/* OFISerializer::isCurrentScopeASeries() const */

bool __thiscall OFISerializer::isCurrentScopeASeries(OFISerializer *this)

{
  if (*(int *)(this + 0xc) != *(int *)(this + 8)) {
    return *(char *)(*(int *)(this + 0xc) + -4) != '\0';
  }
  return false;
}
