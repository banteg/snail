/*
 * mangled: _ZN6cRPath9SearchPosE7tVectorS0_P8cRSubLoc
 * demangled: cRPath::SearchPos(tVector, tVector, cRSubLoc*)
 * address: 0004c278
 * size: 324
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
  uint in_fpscr;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  int in_stack_0000000c;
  float local_44;
  float local_40;
  float local_3c;

  fVar10 = *(float *)(in_stack_0000000c + 0x10);
  iVar5 = *(int *)(this + 0x38) + -1;
  fVar8 = *(float *)(in_stack_0000000c + 0x18);
  fVar9 = *(float *)(in_stack_0000000c + 0x14);
  if (-1 < iVar5) {
    iVar6 = iVar5 * 0xa8;
    do {
      iVar4 = *(int *)(this + 0x50) + iVar6;
      local_44 = param_2 - (fVar10 + *(float *)(iVar4 + 0x30));
      local_3c = param_4 - (fVar8 + *(float *)(iVar4 + 0x38));
      local_40 = param_3 - (fVar9 + *(float *)(iVar4 + 0x34));
      tVector::Rotate((tVector *)&local_44,(tMatrix *)(iVar4 + 0x40));
      fVar7 = (float)VectorSignedToFloat(-(*(int *)(this + 0x48) / 2),(byte)(in_fpscr >> 0x16) & 3);
      fVar7 = fVar7 - 0.3;
      uVar1 = in_fpscr & 0xfffffff;
      uVar2 = uVar1 | (uint)(local_44 < fVar7) << 0x1f | (uint)(local_44 == fVar7) << 0x1e;
      in_fpscr = uVar2 | (uint)(NAN(local_44) || NAN(fVar7)) << 0x1c;
      bVar3 = (byte)(uVar2 >> 0x18);
      if (!(bool)(bVar3 >> 6 & 1) && bVar3 >> 7 == ((byte)(in_fpscr >> 0x1c) & 1)) {
        fVar7 = (float)VectorSignedToFloat(*(int *)(this + 0x48) / 2,(byte)(in_fpscr >> 0x16) & 3);
        in_fpscr = uVar1 | (uint)(local_44 < fVar7 + 0.3) << 0x1f;
        if ((((SUB41(in_fpscr >> 0x1f,0)) &&
             (uVar2 = uVar1 | (uint)(local_40 < -0.3) << 0x1f,
             in_fpscr = uVar2 | (uint)NAN(local_40) << 0x1c,
             (byte)(uVar2 >> 0x1f) == ((byte)(in_fpscr >> 0x1c) & 1))) &&
            (in_fpscr = uVar1 | (uint)(local_40 < 0.3) << 0x1f, SUB41(in_fpscr >> 0x1f,0))) &&
           ((uVar2 = uVar1 | (uint)(local_3c < 0.0) << 0x1f | (uint)(local_3c == 0.0) << 0x1e,
            in_fpscr = uVar2 | (uint)NAN(local_3c) << 0x1c, bVar3 = (byte)(uVar2 >> 0x18),
            !(bool)(bVar3 >> 6 & 1) && bVar3 >> 7 == ((byte)(in_fpscr >> 0x1c) & 1) &&
            (in_fpscr = uVar1 | (uint)(local_3c < *(float *)(*(int *)(this + 0x50) + iVar6 + 0x8c))
                                << 0x1f, SUB41(in_fpscr >> 0x1f,0))))) {
          return 1;
        }
      }
      iVar5 = iVar5 + -1;
      iVar6 = iVar6 + -0xa8;
    } while (-1 < iVar5);
  }
  return 0;
}
