/*
 * mangled: _Z11G0SetColourP12tColourSmall
 * demangled: G0SetColour(tColourSmall*)
 * address: 0008acfc
 * size: 124
 */

/* G0SetColour(tColourSmall*) */

void G0SetColour(tColourSmall *param_1)

{
  uint in_fpscr;
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;

  if (GLColour == *(int *)param_1) {
    return;
  }
  fVar1 = (float)VectorSignedToFloat((uint)(byte)param_1[3],(byte)(in_fpscr >> 0x16) & 3);
  fVar2 = (float)VectorSignedToFloat((uint)(byte)param_1[2],(byte)(in_fpscr >> 0x16) & 3);
  fVar3 = (float)VectorSignedToFloat((uint)(byte)param_1[1],(byte)(in_fpscr >> 0x16) & 3);
  fVar4 = (float)VectorSignedToFloat((uint)(byte)*param_1,(byte)(in_fpscr >> 0x16) & 3);
  GLColour = *(int *)param_1;
  glColor4f(fVar2 / 255.0,fVar3 / 255.0,fVar4 / 255.0,fVar1 / 255.0);
  return;
}
