/*
 * mangled: _Z16ObjectProcFringeP8cRObjectiiiiPc
 * demangled: ObjectProcFringe(cRObject*, int, int, int, int, char*)
 * address: 0003625c
 * size: 1268
 */

/* WARNING: Type propagation algorithm not settling */
/* ObjectProcFringe(cRObject*, int, int, int, int, char*) */

void ObjectProcFringe(cRObject *param_1,int param_2,int param_3,int param_4,int param_5,
                     char *param_6)

{
  uint uVar1;
  byte bVar2;
  undefined4 uVar3;
  float *pfVar4;
  uint uVar5;
  int iVar6;
  float *pfVar7;
  cRFaceQuad *this;
  float *pfVar8;
  bool bVar9;
  uint in_fpscr;
  float fVar10;
  float fVar11;
  float fVar12;

  fVar12 = (float)VectorSignedToFloat(param_4,(byte)(in_fpscr >> 0x16) & 3);
  fVar11 = (float)VectorSignedToFloat(param_5,(byte)(in_fpscr >> 0x16) & 3);
  fVar12 = fVar12 * 0.4;
  fVar11 = fVar11 * 0.4;
  cRObject::RequestVertices(param_1,4);
  cRObject::RequestFaceQuads(param_1,1);
  this = *(cRFaceQuad **)(param_1 + 200);
  pfVar7 = *(float **)(param_1 + 0xa4);
  uVar5 = *(uint *)param_1;
  pfVar7[1] = 0.0;
  *(undefined2 *)this = 0;
  *(uint *)param_1 = uVar5 | 0x8000000;
  pfVar7[4] = 0.0;
  pfVar7[7] = 0.0;
  pfVar7[10] = 0.0;
  *(undefined2 *)(this + 2) = 0;
  *(undefined2 *)(this + 4) = 1;
  *(undefined2 *)(this + 6) = 3;
  *(undefined2 *)(this + 8) = 2;
  uVar3 = cRTextures::Add((cRTextures *)gTextureList,param_6,(cTgaHeader *)0x0,0);
  *(undefined4 *)(this + 0x2c) = 0;
  *(undefined4 *)(this + 0x28) = 0x3f4ccccd;
  *(undefined4 *)(this + 0x10) = 0x3f4ccccd;
  *(undefined4 *)(this + 0x24) = 0;
  *(undefined4 *)(this + 0x1c) = 0x3f800000;
  *(undefined4 *)(this + 0x14) = 0x3f800000;
  *(undefined4 *)(this + 0x20) = 0x3e4ccccd;
  *(undefined4 *)(this + 0x18) = 0x3e4ccccd;
  *(undefined4 *)(this + 0xc) = uVar3;
  switch(param_3) {
  case 0:
    pfVar7[9] = -0.5;
    pfVar7[6] = 0.5;
    pfVar7[2] = 0.9;
    pfVar7[5] = 0.9;
    pfVar7[8] = 0.5;
    pfVar7[0xb] = 0.5;
    *pfVar7 = fVar12 + 0.5;
    pfVar7[3] = -0.5 - fVar11;
    break;
  case 1:
    cRFaceQuad::RotateUVCCW(this);
    pfVar7[9] = 0.5;
    pfVar7[3] = 0.5;
    pfVar7[6] = 0.9;
    *pfVar7 = 0.9;
    pfVar7[2] = fVar11 + 0.5;
    pfVar7[5] = 0.5;
    pfVar7[8] = -0.5 - fVar12;
    pfVar7[0xb] = -0.5;
    break;
  case 2:
    cRFaceQuad::RotateUVCCW(this);
    cRFaceQuad::RotateUVCCW(this);
    cRFaceQuad::RotateUVCCW(this);
    pfVar7[2] = 0.5;
    *pfVar7 = -0.5;
    pfVar7[6] = -0.5;
    pfVar7[9] = -0.9;
    pfVar7[3] = -0.9;
    pfVar7[5] = fVar12 + 0.5;
    pfVar7[8] = -0.5;
    pfVar7[0xb] = -0.5 - fVar11;
    break;
  case 3:
    cRFaceQuad::RotateUVCCW(this);
    cRFaceQuad::RotateUVCCW(this);
    *pfVar7 = 0.5;
    pfVar7[2] = -0.5;
    pfVar7[3] = -0.5;
    pfVar7[5] = -0.5;
    pfVar7[8] = -0.9;
    pfVar7[0xb] = -0.9;
    pfVar7[9] = -0.5 - fVar12;
    pfVar7[6] = fVar11 + 0.5;
  }
  iVar6 = 0;
  pfVar4 = pfVar7;
  do {
    switch(param_2) {
    case 1:
      uVar5 = in_fpscr & 0xfffffff;
      in_fpscr = uVar5 | (uint)(*(float *)((int)pfVar7 + iVar6) < 0.0) << 0x1f;
      if (SUB41(in_fpscr >> 0x1f,0)) {
        fVar11 = pfVar4[2];
        in_fpscr = uVar5 | (uint)(fVar11 < 0.0) << 0x1f;
        if (SUB41(in_fpscr >> 0x1f,0)) {
          *(float *)((int)pfVar7 + iVar6) = *(float *)((int)pfVar7 + iVar6) + 0.2;
          pfVar4[2] = fVar11 - -0.2;
          goto joined_r0x0003662c;
        }
      }
      break;
    case 2:
      uVar5 = in_fpscr & 0xfffffff;
      in_fpscr = uVar5 | (uint)(*(float *)((int)pfVar7 + iVar6) < 0.0) << 0x1f;
      if (SUB41(in_fpscr >> 0x1f,0)) {
        fVar11 = pfVar4[2];
        uVar1 = uVar5 | (uint)(fVar11 < 0.0) << 0x1f | (uint)(fVar11 == 0.0) << 0x1e;
        in_fpscr = uVar1 | (uint)NAN(fVar11) << 0x1c;
        bVar2 = (byte)(uVar1 >> 0x18);
        bVar9 = (bool)(bVar2 >> 7);
        if (!(bool)(bVar2 >> 6 & 1) && bVar9 == (bool)((byte)(in_fpscr >> 0x1c) & 1)) {
          *(float *)((int)pfVar7 + iVar6) = *(float *)((int)pfVar7 + iVar6) + 0.2;
          if (bVar9) {
            fVar12 = -0.2;
          }
          else {
            in_fpscr = uVar5 | (uint)(fVar11 == 0.0) << 0x1e;
            fVar12 = (float)VectorSignedToFloat((uint)!SUB41(in_fpscr >> 0x1e,0),
                                                (byte)(in_fpscr >> 0x16) & 3);
            fVar12 = fVar12 * 0.2;
          }
          pfVar4[2] = fVar11 - fVar12;
          goto joined_r0x0003662c;
        }
      }
      break;
    case 3:
      fVar11 = *(float *)((int)pfVar7 + iVar6);
      uVar5 = in_fpscr & 0xfffffff;
      uVar1 = uVar5 | (uint)(fVar11 < 0.0) << 0x1f | (uint)(fVar11 == 0.0) << 0x1e;
      in_fpscr = uVar1 | (uint)NAN(fVar11) << 0x1c;
      bVar2 = (byte)(uVar1 >> 0x18);
      if (!(bool)(bVar2 >> 6 & 1) && bVar2 >> 7 == ((byte)(in_fpscr >> 0x1c) & 1)) {
        fVar12 = pfVar4[2];
        in_fpscr = uVar5 | (uint)(fVar12 < 0.0) << 0x1f;
        if (SUB41(in_fpscr >> 0x1f,0)) {
          uVar5 = uVar5 | (uint)(fVar11 < 0.0) << 0x1f;
          if (SUB41(uVar5 >> 0x1f,0)) goto LAB_00036668;
LAB_0003640c:
          uVar1 = uVar5 & 0xfffffff | (uint)(fVar11 == 0.0) << 0x1e;
          fVar10 = (float)VectorSignedToFloat((uint)!SUB41(uVar1 >> 0x1e,0),
                                              (byte)(uVar1 >> 0x16) & 3);
          in_fpscr = uVar5 & 0xfffffff | (uint)(fVar12 < 0.0) << 0x1f;
          *(float *)((int)pfVar7 + iVar6) = fVar11 - fVar10 * 0.2;
          if (SUB41(in_fpscr >> 0x1f,0)) goto LAB_00036440;
LAB_00036684:
          in_fpscr = in_fpscr & 0xfffffff | (uint)(fVar12 == 0.0) << 0x1e;
          fVar11 = (float)VectorSignedToFloat((uint)!SUB41(in_fpscr >> 0x1e,0),
                                              (byte)(in_fpscr >> 0x16) & 3);
          fVar11 = fVar11 * 0.2;
LAB_00036444:
          pfVar4[2] = fVar12 - fVar11;
        }
      }
      break;
    case 4:
      fVar11 = *(float *)((int)pfVar7 + iVar6);
      uVar5 = in_fpscr & 0xfffffff;
      uVar1 = uVar5 | (uint)(fVar11 < 0.0) << 0x1f | (uint)(fVar11 == 0.0) << 0x1e;
      in_fpscr = uVar1 | (uint)NAN(fVar11) << 0x1c;
      bVar2 = (byte)(uVar1 >> 0x18);
      if (!(bool)(bVar2 >> 6 & 1) && bVar2 >> 7 == ((byte)(in_fpscr >> 0x1c) & 1)) {
        fVar12 = pfVar4[2];
        uVar1 = uVar5 | (uint)(fVar12 < 0.0) << 0x1f | (uint)(fVar12 == 0.0) << 0x1e;
        in_fpscr = uVar1 | (uint)NAN(fVar12) << 0x1c;
        bVar2 = (byte)(uVar1 >> 0x18);
        if (!(bool)(bVar2 >> 6 & 1) && bVar2 >> 7 == ((byte)(in_fpscr >> 0x1c) & 1)) {
          uVar5 = uVar5 | (uint)(fVar11 < 0.0) << 0x1f;
          if (!SUB41(uVar5 >> 0x1f,0)) goto LAB_0003640c;
LAB_00036668:
          in_fpscr = uVar5 & 0xfffffff | (uint)(fVar12 < 0.0) << 0x1f;
          *(float *)((int)pfVar7 + iVar6) = fVar11 - -0.2;
          if (!SUB41(in_fpscr >> 0x1f,0)) goto LAB_00036684;
LAB_00036440:
          fVar11 = -0.2;
          goto LAB_00036444;
        }
      }
      break;
    case 5:
      fVar11 = *(float *)((int)pfVar7 + iVar6);
      uVar5 = in_fpscr & 0xfffffff;
      uVar1 = uVar5 | (uint)(fVar11 < 0.0) << 0x1f | (uint)(fVar11 == 0.0) << 0x1e;
      in_fpscr = uVar1 | (uint)NAN(fVar11) << 0x1c;
      bVar2 = (byte)(uVar1 >> 0x18);
      if (!(bool)(bVar2 >> 6 & 1) && bVar2 >> 7 == ((byte)(in_fpscr >> 0x1c) & 1)) {
        fVar11 = pfVar4[2];
        uVar1 = uVar5 | (uint)(fVar11 < 0.0) << 0x1f | (uint)(fVar11 == 0.0) << 0x1e;
        in_fpscr = uVar1 | (uint)NAN(fVar11) << 0x1c;
        bVar2 = (byte)(uVar1 >> 0x18);
        if (!(bool)(bVar2 >> 6 & 1) && bVar2 >> 7 == ((byte)(in_fpscr >> 0x1c) & 1)) {
          in_fpscr = uVar5 | (uint)(fVar11 == 0.5) << 0x1e;
          if (SUB41(in_fpscr >> 0x1e,0)) goto LAB_00036484;
LAB_000364d4:
          *(float *)((int)pfVar7 + iVar6 + 4) = *(float *)((int)pfVar7 + iVar6 + 4) + 0.6;
          goto joined_r0x0003662c;
        }
      }
      break;
    case 6:
      fVar11 = pfVar4[2];
      uVar5 = in_fpscr & 0xfffffff;
      uVar1 = uVar5 | (uint)(fVar11 < 0.0) << 0x1f | (uint)(fVar11 == 0.0) << 0x1e;
      in_fpscr = uVar1 | (uint)NAN(fVar11) << 0x1c;
      bVar2 = (byte)(uVar1 >> 0x18);
      if ((bool)(bVar2 >> 6 & 1) || bVar2 >> 7 != ((byte)(in_fpscr >> 0x1c) & 1)) break;
      in_fpscr = uVar5 | (uint)(fVar11 == 0.5) << 0x1e;
      if (!SUB41(in_fpscr >> 0x1e,0)) goto LAB_000364d4;
LAB_00036484:
      *(float *)((int)pfVar7 + iVar6 + 4) = *(float *)((int)pfVar7 + iVar6 + 4) + 0.5;
      goto joined_r0x0003662c;
    case 7:
      pfVar8 = (float *)((int)pfVar7 + iVar6);
      uVar5 = in_fpscr & 0xfffffff;
      in_fpscr = uVar5 | (uint)(*pfVar8 < 0.0) << 0x1f;
      if (SUB41(in_fpscr >> 0x1f,0)) {
        fVar11 = pfVar4[2];
        uVar1 = uVar5 | (uint)(fVar11 < 0.0) << 0x1f | (uint)(fVar11 == 0.0) << 0x1e;
        in_fpscr = uVar1 | (uint)NAN(fVar11) << 0x1c;
        bVar2 = (byte)(uVar1 >> 0x18);
        if (!(bool)(bVar2 >> 6 & 1) && bVar2 >> 7 == ((byte)(in_fpscr >> 0x1c) & 1)) {
          in_fpscr = uVar5 | (uint)(fVar11 == 0.5) << 0x1e;
          if (!SUB41(in_fpscr >> 0x1e,0)) goto LAB_000364d4;
          pfVar8[1] = pfVar8[1] + 0.5;
          goto joined_r0x0003662c;
        }
      }
    }
joined_r0x0003662c:
    pfVar4 = pfVar4 + 3;
    iVar6 = iVar6 + 0xc;
    if (iVar6 == 0x30) {
      return;
    }
  } while( true );
}
