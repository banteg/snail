/*
 * mangled: _ZN6cRPath9SearchPosE7tVectorS0_P8cRSubLoc
 * demangled: cRPath::SearchPos(tVector, tVector, cRSubLoc*)
 * address: 0004f6e0
 * size: 352
 */

/* cRPath::SearchPos(tVector, tVector, cRSubLoc*) */

undefined4 __thiscall cRPath::SearchPos(cRPath *this,float param_2,float param_3,float param_4)

{
  uint uVar1;
  uint uVar2;
  byte bVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  uint in_fpscr;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  int in_stack_0000000c;
  float local_3c;
  float local_38;
  float local_34;

  iVar7 = *(int *)(this + 0x38);
  fVar11 = *(float *)(in_stack_0000000c + 0x18);
  fVar10 = *(float *)(in_stack_0000000c + 0x14);
  fVar9 = *(float *)(in_stack_0000000c + 0x10);
  if (-1 < iVar7 + -1) {
    iVar6 = 0;
    iVar5 = iVar7 * 0xa8;
    do {
      iVar5 = iVar5 + -0xa8;
      iVar4 = iVar5 + *(int *)(this + 0x50);
      local_3c = param_2 - (fVar9 + *(float *)(iVar4 + 0x30));
      local_38 = param_3 - (fVar10 + *(float *)(iVar4 + 0x34));
      local_34 = param_4 - (fVar11 + *(float *)(iVar4 + 0x38));
      tVector::Rotate((tVector *)&local_3c,(tMatrix *)(iVar4 + 0x40));
      fVar8 = (float)VectorSignedToFloat(-(*(int *)(this + 0x48) / 2),(byte)(in_fpscr >> 0x16) & 3);
      fVar8 = fVar8 - 0.3;
      uVar1 = in_fpscr & 0xfffffff;
      uVar2 = uVar1 | (uint)(local_3c < fVar8) << 0x1f | (uint)(local_3c == fVar8) << 0x1e;
      in_fpscr = uVar2 | (uint)(NAN(local_3c) || NAN(fVar8)) << 0x1c;
      bVar3 = (byte)(uVar2 >> 0x18);
      if (!(bool)(bVar3 >> 6 & 1) && bVar3 >> 7 == ((byte)(in_fpscr >> 0x1c) & 1)) {
        fVar8 = (float)VectorSignedToFloat(*(int *)(this + 0x48) / 2,(byte)(in_fpscr >> 0x16) & 3);
        in_fpscr = uVar1 | (uint)(local_3c < fVar8 + 0.3) << 0x1f;
        if ((((SUB41(in_fpscr >> 0x1f,0)) &&
             (uVar2 = uVar1 | (uint)(local_38 < -0.3) << 0x1f,
             in_fpscr = uVar2 | (uint)NAN(local_38) << 0x1c,
             (byte)(uVar2 >> 0x1f) == ((byte)(in_fpscr >> 0x1c) & 1))) &&
            (in_fpscr = uVar1 | (uint)(local_38 < 0.3) << 0x1f, SUB41(in_fpscr >> 0x1f,0))) &&
           ((uVar2 = uVar1 | (uint)(local_34 < 0.0) << 0x1f | (uint)(local_34 == 0.0) << 0x1e,
            in_fpscr = uVar2 | (uint)NAN(local_34) << 0x1c, bVar3 = (byte)(uVar2 >> 0x18),
            !(bool)(bVar3 >> 6 & 1) && bVar3 >> 7 == ((byte)(in_fpscr >> 0x1c) & 1) &&
            (in_fpscr = uVar1 | (uint)(local_34 < *(float *)(*(int *)(this + 0x50) + iVar5 + 0x8c))
                                << 0x1f, SUB41(in_fpscr >> 0x1f,0))))) {
          return 1;
        }
      }
      iVar6 = iVar6 + 1;
    } while (iVar6 != iVar7);
  }
  return 0;
}
