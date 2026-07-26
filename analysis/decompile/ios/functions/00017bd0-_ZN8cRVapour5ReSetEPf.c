/*
 * mangled: _ZN8cRVapour5ReSetEPf
 * demangled: cRVapour::ReSet(float*)
 * address: 00017bd0
 * size: 28
 */

/* cRVapour::ReSet(float*) */

void __thiscall cRVapour::ReSet(cRVapour *this,float *param_1)

{
  *(float **)(this + 0x80) = param_1;
  *(uint *)(this + 4) = *(uint *)(this + 4) & 0xffffffdf;
  *(undefined4 *)(this + 0x74) = 0;
  return;
}
