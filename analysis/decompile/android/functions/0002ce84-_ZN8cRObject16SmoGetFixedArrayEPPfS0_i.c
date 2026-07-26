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
  float fVar1;
  int iVar2;
  float *pfVar3;
  int iVar4;
  uint in_fpscr;
  float fVar5;

  fVar1 = DAT_0002ced8;
  pfVar3 = *param_1;
  if (0 < param_3) {
    iVar2 = 0;
    iVar4 = param_3;
    do {
      fVar5 = (float)VectorSignedToFloat((int)*(short *)((int)pfVar3 + iVar2),
                                         (byte)(in_fpscr >> 0x16) & 3);
      iVar4 = iVar4 + -1;
      *(float *)((int)param_2 + iVar2 * 2) = fVar5 * fVar1;
      iVar2 = iVar2 + 2;
    } while (iVar4 != 0);
    pfVar3 = (float *)((int)pfVar3 + param_3 * 2);
  }
  *param_1 = pfVar3;
  return;
}
