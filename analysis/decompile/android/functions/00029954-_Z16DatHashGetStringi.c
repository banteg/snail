/*
 * mangled: _Z16DatHashGetStringi
 * demangled: DatHashGetString(int)
 * address: 00029954
 * size: 36
 */

/* DatHashGetString(int) */

undefined4 DatHashGetString(int param_1)

{
  return *(undefined4 *)(gDat + param_1 * 0x18 + 4);
}
