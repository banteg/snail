/*
 * mangled: _ZN13OFISerializer36createSerializerForInnerStreamOfTypeEPK6OFRTTI
 * demangled: OFISerializer::createSerializerForInnerStreamOfType(OFRTTI const*)
 * address: 000cb784
 * size: 24
 */

/* OFISerializer::createSerializerForInnerStreamOfType(OFRTTI const*) */

void __thiscall
OFISerializer::createSerializerForInnerStreamOfType(OFISerializer *this,OFRTTI *param_1)

{
  *(OFRTTI **)this = param_1;
  if (param_1 != (OFRTTI *)0x0) {
    *(int *)(param_1 + 4) = *(int *)(param_1 + 4) + 1;
  }
  return;
}
