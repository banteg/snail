/*
 * mangled: _ZNK19OFSdbmSerializerKey6equalsEPK16OFISerializerKey
 * demangled: OFSdbmSerializerKey::equals(OFISerializerKey const*) const
 * address: 000c7f94
 * size: 24
 */

/* OFSdbmSerializerKey::equals(OFISerializerKey const*) const */

void __thiscall OFSdbmSerializerKey::equals(OFSdbmSerializerKey *this,OFISerializerKey *param_1)

{
  OFSdbmHashedString::operator==
            ((OFSdbmHashedString *)(this + 8),(OFSdbmHashedString *)(param_1 + 8));
  return;
}
