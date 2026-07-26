/*
 * mangled: _ZN8cRObject16SmoGetFixedShortEPPfPs
 * demangled: cRObject::SmoGetFixedShort(float**, short*)
 * address: 0002cedc
 * size: 20
 */

/* cRObject::SmoGetFixedShort(float**, short*) */

void __thiscall cRObject::SmoGetFixedShort(cRObject *this,float **param_1,short *param_2)

{
  float *pfVar1;

  pfVar1 = *param_1;
  *param_2 = *(short *)pfVar1;
  *param_1 = (float *)((int)pfVar1 + 2);
  return;
}
