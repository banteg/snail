/*
 * mangled: _ZNK13OFISerializer9StringKey8lessthanEPK16OFISerializerKey
 * demangled: OFISerializer::StringKey::lessthan(OFISerializerKey const*) const
 * address: 000c97d0
 * size: 28
 */

/* OFISerializer::StringKey::lessthan(OFISerializerKey const*) const */

uint __thiscall OFISerializer::StringKey::lessthan(StringKey *this,OFISerializerKey *param_1)

{
  uint uVar1;

  uVar1 = _strcmp(*(char **)(this + 8),*(char **)(param_1 + 8));
  return uVar1 >> 0x1f;
}
