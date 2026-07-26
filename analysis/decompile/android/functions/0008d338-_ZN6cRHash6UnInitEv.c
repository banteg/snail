/*
 * mangled: _ZN6cRHash6UnInitEv
 * demangled: cRHash::UnInit()
 * address: 0008d338
 * size: 20
 */

/* cRHash::UnInit() */

void __thiscall cRHash::UnInit(cRHash *this)

{
  free(*(void **)(this + 0x800));
  return;
}
