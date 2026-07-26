/*
 * mangled: _ZN8cRObject11SmoGetFixedEPPfS0_
 * demangled: cRObject::SmoGetFixed(float**, float*)
 * address: 0002ce5c
 * size: 36
 */

/* cRObject::SmoGetFixed(float**, float*) */

void __thiscall cRObject::SmoGetFixed(cRObject *this,float **param_1,float *param_2)

{
  float fVar1;
  uint in_fpscr;
  float fVar2;

  fVar1 = DAT_0002ce80;
  fVar2 = (float)VectorSignedToFloat((int)*(short *)*param_1,(byte)(in_fpscr >> 0x16) & 3);
  *param_1 = (float *)((int)*param_1 + 2);
  *param_2 = fVar2 * fVar1;
  return;
}
