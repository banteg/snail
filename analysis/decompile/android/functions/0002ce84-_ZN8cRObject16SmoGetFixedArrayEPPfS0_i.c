/*
 * mangled: _ZN8cRObject16SmoGetFixedArrayEPPfS0_i
 * demangled: cRObject::SmoGetFixedArray(float**, float*, int)
 * address: 0002ce84
 * size: 84
 */

/* cRObject::SmoGetFixedArray(float**, float*, int) */

void __thiscall
cRObject::SmoGetFixedArray(cRObject *this,float **param_1,float *param_2,int param_3)

{
  int iVar1;
  float *pfVar2;
  int iVar3;
  uint in_fpscr;
  float fVar4;

  pfVar2 = *param_1;
  if (0 < param_3) {
    iVar1 = 0;
    iVar3 = param_3;
    do {
      fVar4 = (float)VectorSignedToFloat((int)*(short *)((int)pfVar2 + iVar1),
                                         (byte)(in_fpscr >> 0x16) & 3);
      iVar3 = iVar3 + -1;
      *(float *)((int)param_2 + iVar1 * 2) = fVar4 * 0.0078125;
      iVar1 = iVar1 + 2;
    } while (iVar3 != 0);
    pfVar2 = (float *)((int)pfVar2 + param_3 * 2);
  }
  *param_1 = pfVar2;
  return;
}
