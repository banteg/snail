/*
 * mangled: _ZNK19OFSdbmSerializerKey8lessthanEPK16OFISerializerKey
 * demangled: OFSdbmSerializerKey::lessthan(OFISerializerKey const*) const
 * address: 000c7f7c
 * size: 24
 */

/* OFSdbmSerializerKey::lessthan(OFISerializerKey const*) const */

void __thiscall OFSdbmSerializerKey::lessthan(OFSdbmSerializerKey *this,OFISerializerKey *param_1)

{
  OFSdbmHashedString::operator<
            ((OFSdbmHashedString *)(this + 8),(OFSdbmHashedString *)(param_1 + 8));
  return;
}
