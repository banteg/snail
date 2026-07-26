/*
 * mangled: _ZNK13OFISerializer9StringKey6equalsEPK16OFISerializerKey
 * demangled: OFISerializer::StringKey::equals(OFISerializerKey const*) const
 * address: 000c97ec
 * size: 32
 */

/* OFISerializer::StringKey::equals(OFISerializerKey const*) const */

int __thiscall OFISerializer::StringKey::equals(StringKey *this,OFISerializerKey *param_1)

{
  uint uVar1;
  int iVar2;

  uVar1 = _strcmp(*(char **)(this + 8),*(char **)(param_1 + 8));
  iVar2 = 1 - uVar1;
  if (1 < uVar1) {
    iVar2 = 0;
  }
  return iVar2;
}
