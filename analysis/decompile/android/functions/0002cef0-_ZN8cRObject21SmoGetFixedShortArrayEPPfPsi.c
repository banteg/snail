/*
 * mangled: _ZN8cRObject21SmoGetFixedShortArrayEPPfPsi
 * demangled: cRObject::SmoGetFixedShortArray(float**, short*, int)
 * address: 0002cef0
 * size: 64
 */

/* cRObject::SmoGetFixedShortArray(float**, short*, int) */

void __thiscall
cRObject::SmoGetFixedShortArray(cRObject *this,float **param_1,short *param_2,int param_3)

{
  int iVar1;
  float *pfVar2;
  int iVar3;

  pfVar2 = *param_1;
  if (0 < param_3) {
    iVar1 = 0;
    iVar3 = param_3;
    do {
      iVar3 = iVar3 + -1;
      *(undefined2 *)((int)param_2 + iVar1) = *(undefined2 *)((int)pfVar2 + iVar1);
      iVar1 = iVar1 + 2;
    } while (iVar3 != 0);
    pfVar2 = (float *)((int)pfVar2 + param_3 * 2);
  }
  *param_1 = pfVar2;
  return;
}
