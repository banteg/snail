/*
 * mangled: _ZN8cRObject9ApplyToonEi
 * demangled: cRObject::ApplyToon(int)
 * address: 0001193c
 * size: 24
 */

/* cRObject::ApplyToon(int) */

void __thiscall cRObject::ApplyToon(cRObject *this,int param_1)

{
  *(uint *)this = *(uint *)this | 0x4001 | param_1;
  return;
}
