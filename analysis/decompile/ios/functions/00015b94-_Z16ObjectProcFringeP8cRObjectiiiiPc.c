/*
 * mangled: _Z16ObjectProcFringeP8cRObjectiiiiPc
 * demangled: ObjectProcFringe(cRObject*, int, int, int, int, char*)
 * address: 00015b94
 * size: 2660
 */

/* ObjectProcFringe(cRObject*, int, int, int, int, char*) */

void ObjectProcFringe(cRObject *param_1,int param_2,int param_3,int param_4,int param_5,
                     char *param_6)

{
  undefined4 uVar1;
  int iVar2;
  cRFaceQuad *this;
  float *pfVar3;
  float *pfVar4;
  float *pfVar5;
  float *pfVar6;
  uint in_fpscr;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;

  fVar9 = (float)VectorSignedToFloat(param_4,(byte)(in_fpscr >> 0x16) & 3);
  fVar9 = fVar9 * 0.4;
  fVar10 = (float)VectorSignedToFloat(param_5,(byte)(in_fpscr >> 0x16) & 3);
  fVar10 = fVar10 * 0.4;
  cRObject::RequestVertices(param_1,4);
  cRObject::RequestFaceQuads(param_1,1);
  pfVar3 = *(float **)(param_1 + 0xa4);
  *(uint *)param_1 = *(uint *)param_1 | 0x8000000;
  this = *(cRFaceQuad **)(param_1 + 200);
  pfVar3[1] = 0.0;
  pfVar3[4] = 0.0;
  pfVar3[7] = 0.0;
  pfVar3[10] = 0.0;
  *(undefined2 *)this = 0;
  *(undefined2 *)(this + 2) = 0;
  *(undefined2 *)(this + 4) = 1;
  *(undefined2 *)(this + 6) = 3;
  *(undefined2 *)(this + 8) = 2;
  pfVar6 = pfVar3 + 9;
  uVar1 = cRTextures::Add((cRTextures *)PTR__gTextureList_001b61d0,param_6,(cTgaHeader *)0x0,0);
  *(undefined4 *)(this + 0x10) = 0x3f4ccccd;
  *(undefined4 *)(this + 0x14) = 0x3f800000;
  *(undefined4 *)(this + 0x18) = 0x3e4ccccd;
  *(undefined4 *)(this + 0x1c) = 0x3f800000;
  *(undefined4 *)(this + 0x20) = 0x3e4ccccd;
  *(undefined4 *)(this + 0x24) = 0;
  *(undefined4 *)(this + 0x28) = 0x3f4ccccd;
  *(undefined4 *)(this + 0x2c) = 0;
  pfVar4 = pfVar3 + 3;
  pfVar5 = pfVar3 + 6;
  *(undefined4 *)(this + 0xc) = uVar1;
  switch(param_3) {
  case 0:
    pfVar3[2] = 0.9;
    pfVar3[5] = 0.9;
    pfVar3[8] = 0.5;
    pfVar3[0xb] = 0.5;
    *pfVar3 = fVar9 + 0.5;
    *pfVar4 = -0.5 - fVar10;
    *pfVar5 = 0.5;
    *pfVar6 = -0.5;
    break;
  case 1:
    cRFaceQuad::RotateUVCCW(this);
    *pfVar3 = 0.9;
    *pfVar4 = 0.5;
    *pfVar5 = 0.9;
    pfVar3[2] = fVar10 + 0.5;
    pfVar3[5] = 0.5;
    pfVar3[8] = -0.5 - fVar9;
    *pfVar6 = 0.5;
    pfVar3[0xb] = -0.5;
    break;
  case 2:
    cRFaceQuad::RotateUVCCW(this);
    cRFaceQuad::RotateUVCCW(this);
    cRFaceQuad::RotateUVCCW(this);
    pfVar3[2] = 0.5;
    *pfVar3 = -0.5;
    *pfVar4 = -0.9;
    *pfVar5 = -0.5;
    pfVar3[5] = fVar9 + 0.5;
    pfVar3[8] = -0.5;
    *pfVar6 = -0.9;
    pfVar3[0xb] = -0.5 - fVar10;
    break;
  case 3:
    cRFaceQuad::RotateUVCCW(this);
    cRFaceQuad::RotateUVCCW(this);
    *pfVar3 = 0.5;
    *pfVar4 = -0.5;
    pfVar3[2] = -0.5;
    pfVar3[5] = -0.5;
    pfVar3[8] = -0.9;
    *pfVar5 = fVar10 + 0.5;
    pfVar3[0xb] = -0.9;
    *pfVar6 = -0.5 - fVar9;
  }
  iVar2 = param_2 + -1;
  switch(iVar2) {
  case 0:
    break;
  case 1:
    if ((0.0 <= *pfVar3) || (fVar9 = pfVar3[2], fVar9 <= 0.0)) goto switchD_00015ce8_default;
    fVar10 = -0.2;
    *pfVar3 = *pfVar3 - -0.2;
    if (0.0 <= fVar9) {
      if (fVar9 == 0.0) {
        fVar10 = 0.0;
      }
      else {
        fVar10 = 0.2;
      }
    }
    pfVar3[2] = fVar9 - fVar10;
switchD_00015d3c_caseD_1:
    if ((0.0 <= *pfVar4) || (fVar9 = pfVar3[5], fVar9 <= 0.0)) goto switchD_00015d3c_default;
    fVar10 = -0.2;
    *pfVar4 = *pfVar4 - -0.2;
    if (0.0 <= fVar9) {
      if (fVar9 == 0.0) {
        fVar10 = 0.0;
      }
      else {
        fVar10 = 0.2;
      }
    }
    pfVar3[5] = fVar9 - fVar10;
    goto switchD_00015da0_caseD_1;
  case 2:
    fVar9 = *pfVar3;
    if ((fVar9 <= 0.0) || (fVar10 = pfVar3[2], 0.0 <= fVar10)) goto switchD_00015ce8_default;
    fVar7 = -0.2;
    fVar8 = 0.2;
    if (fVar9 < 0.0) {
      fVar8 = fVar7;
    }
    *pfVar3 = fVar9 - fVar8;
    if ((0.0 <= fVar10) && (fVar7 = 0.2, fVar10 == 0.0)) {
      fVar7 = 0.0;
    }
    pfVar3[2] = fVar10 - fVar7;
switchD_00015d3c_caseD_2:
    fVar9 = *pfVar4;
    if ((fVar9 <= 0.0) || (fVar10 = pfVar3[5], 0.0 <= fVar10)) goto switchD_00015d3c_default;
    fVar7 = -0.2;
    fVar8 = 0.2;
    if (fVar9 < 0.0) {
      fVar8 = fVar7;
    }
    *pfVar4 = fVar9 - fVar8;
    if ((0.0 <= fVar10) && (fVar7 = 0.2, fVar10 == 0.0)) {
      fVar7 = 0.0;
    }
    pfVar3[5] = fVar10 - fVar7;
    goto switchD_00015da0_caseD_2;
  case 3:
    fVar9 = *pfVar3;
    if ((fVar9 <= 0.0) || (fVar10 = pfVar3[2], fVar10 <= 0.0)) goto switchD_00015ce8_default;
    fVar7 = -0.2;
    fVar8 = 0.2;
    if (fVar9 < 0.0) {
      fVar8 = fVar7;
    }
    *pfVar3 = fVar9 - fVar8;
    if ((0.0 <= fVar10) && (fVar7 = 0.2, fVar10 == 0.0)) {
      fVar7 = 0.0;
    }
    pfVar3[2] = fVar10 - fVar7;
switchD_00015d3c_caseD_3:
    fVar9 = *pfVar4;
    if ((fVar9 <= 0.0) || (fVar10 = pfVar3[5], fVar10 <= 0.0)) goto switchD_00015d3c_default;
    fVar7 = -0.2;
    fVar8 = 0.2;
    if (fVar9 < 0.0) {
      fVar8 = fVar7;
    }
    *pfVar4 = fVar9 - fVar8;
    if ((0.0 <= fVar10) && (fVar7 = 0.2, fVar10 == 0.0)) {
      fVar7 = 0.0;
    }
    pfVar3[5] = fVar10 - fVar7;
    goto switchD_00015da0_caseD_3;
  case 4:
    if ((*pfVar3 <= 0.0) || (pfVar3[2] <= 0.0)) goto switchD_00015ce8_default;
    if (pfVar3[2] == 0.5) {
      pfVar3[1] = pfVar3[1] + 0.5;
    }
    else {
      pfVar3[1] = pfVar3[1] + 0.6;
    }
switchD_00015d3c_caseD_4:
    if ((*pfVar4 <= 0.0) || (pfVar3[5] <= 0.0)) goto switchD_00015d3c_default;
    if (pfVar3[5] == 0.5) {
      pfVar3[4] = pfVar3[4] + 0.5;
    }
    else {
      pfVar3[4] = pfVar3[4] + 0.6;
    }
    goto switchD_00015da0_caseD_4;
  case 5:
    if (pfVar3[2] <= 0.0) goto switchD_00015ce8_default;
    if (pfVar3[2] == 0.5) {
      pfVar3[1] = pfVar3[1] + 0.5;
      goto switchD_00015ce8_default;
    }
    pfVar3[1] = pfVar3[1] + 0.6;
switchD_00015d3c_caseD_5:
    if (pfVar3[5] <= 0.0) goto switchD_00015d3c_default;
    if (pfVar3[5] == 0.5) {
      pfVar3[4] = pfVar3[4] + 0.5;
      goto switchD_00015d3c_default;
    }
    pfVar3[4] = pfVar3[4] + 0.6;
    goto switchD_00015da0_caseD_5;
  case 6:
    if ((0.0 <= *pfVar3) || (pfVar3[2] <= 0.0)) goto switchD_00015ce8_default;
    if (pfVar3[2] == 0.5) {
      pfVar3[1] = pfVar3[1] + 0.5;
    }
    else {
      pfVar3[1] = pfVar3[1] + 0.6;
    }
switchD_00015d3c_caseD_6:
    if ((0.0 <= *pfVar4) || (pfVar3[5] <= 0.0)) goto switchD_00015d3c_default;
    if (pfVar3[5] == 0.5) {
      pfVar3[4] = pfVar3[4] + 0.5;
    }
    else {
      pfVar3[4] = pfVar3[4] + 0.6;
    }
    goto switchD_00015da0_caseD_6;
  default:
switchD_00015ce8_default:
    switch(iVar2) {
    case 0:
      goto switchD_00015d3c_caseD_0;
    case 1:
      goto switchD_00015d3c_caseD_1;
    case 2:
      goto switchD_00015d3c_caseD_2;
    case 3:
      goto switchD_00015d3c_caseD_3;
    case 4:
      goto switchD_00015d3c_caseD_4;
    case 5:
      goto switchD_00015d3c_caseD_5;
    case 6:
      goto switchD_00015d3c_caseD_6;
    default:
      goto switchD_00015d3c_default;
    }
  }
  if ((0.0 <= *pfVar3) || (fVar9 = pfVar3[2], 0.0 <= fVar9)) goto switchD_00015ce8_default;
  fVar10 = -0.2;
  *pfVar3 = *pfVar3 - -0.2;
  if (0.0 <= fVar9) {
    if (fVar9 == 0.0) {
      fVar10 = 0.0;
    }
    else {
      fVar10 = 0.2;
    }
  }
  pfVar3[2] = fVar9 - fVar10;
switchD_00015d3c_caseD_0:
  if ((*pfVar4 < 0.0) && (fVar9 = pfVar3[5], fVar9 < 0.0)) {
    fVar10 = -0.2;
    *pfVar4 = *pfVar4 - -0.2;
    if (0.0 <= fVar9) {
      if (fVar9 == 0.0) {
        fVar10 = 0.0;
      }
      else {
        fVar10 = 0.2;
      }
    }
    pfVar3[5] = fVar9 - fVar10;
switchD_00015da0_caseD_0:
    if ((0.0 <= *pfVar5) || (fVar9 = pfVar3[8], 0.0 <= fVar9)) goto switchD_00015da0_default;
    fVar10 = -0.2;
    *pfVar5 = *pfVar5 - -0.2;
    if (0.0 <= fVar9) {
      if (fVar9 == 0.0) {
        fVar10 = 0.0;
      }
      else {
        fVar10 = 0.2;
      }
    }
    pfVar3[8] = fVar9 - fVar10;
switchD_00015e04_caseD_0:
    fVar9 = *pfVar6;
    if (0.0 <= fVar9) {
      return;
    }
    fVar10 = pfVar3[0xb];
    if (0.0 <= fVar10) {
      return;
    }
LAB_00015f20:
    fVar7 = -0.2;
    *pfVar6 = fVar9 - -0.2;
    if (0.0 <= fVar10) {
      if (fVar10 == 0.0) {
        fVar7 = 0.0;
      }
      else {
        fVar7 = 0.2;
      }
    }
    pfVar3[0xb] = fVar10 - fVar7;
    return;
  }
switchD_00015d3c_default:
  switch(iVar2) {
  case 0:
    goto switchD_00015da0_caseD_0;
  case 1:
switchD_00015da0_caseD_1:
    if ((0.0 <= *pfVar5) || (fVar9 = pfVar3[8], fVar9 <= 0.0)) break;
    fVar10 = -0.2;
    *pfVar5 = *pfVar5 - -0.2;
    if (0.0 <= fVar9) {
      if (fVar9 == 0.0) {
        fVar10 = 0.0;
      }
      else {
        fVar10 = 0.2;
      }
    }
    pfVar3[8] = fVar9 - fVar10;
    goto switchD_00015e04_caseD_1;
  case 2:
switchD_00015da0_caseD_2:
    fVar9 = *pfVar5;
    if ((fVar9 <= 0.0) || (fVar10 = pfVar3[8], 0.0 <= fVar10)) break;
    fVar7 = -0.2;
    fVar8 = 0.2;
    if (fVar9 < 0.0) {
      fVar8 = fVar7;
    }
    *pfVar5 = fVar9 - fVar8;
    if ((0.0 <= fVar10) && (fVar7 = 0.2, fVar10 == 0.0)) {
      fVar7 = 0.0;
    }
    pfVar3[8] = fVar10 - fVar7;
    goto switchD_00015e04_caseD_2;
  case 3:
switchD_00015da0_caseD_3:
    fVar9 = *pfVar5;
    if ((fVar9 <= 0.0) || (fVar10 = pfVar3[8], fVar10 <= 0.0)) break;
    fVar7 = -0.2;
    fVar8 = 0.2;
    if (fVar9 < 0.0) {
      fVar8 = fVar7;
    }
    *pfVar5 = fVar9 - fVar8;
    if ((0.0 <= fVar10) && (fVar7 = 0.2, fVar10 == 0.0)) {
      fVar7 = 0.0;
    }
    pfVar3[8] = fVar10 - fVar7;
    goto switchD_00015e04_caseD_3;
  case 4:
switchD_00015da0_caseD_4:
    if ((*pfVar5 <= 0.0) || (pfVar3[8] <= 0.0)) break;
    if (pfVar3[8] == 0.5) {
      pfVar3[7] = pfVar3[7] + 0.5;
    }
    else {
      pfVar3[7] = pfVar3[7] + 0.6;
    }
    goto switchD_00015e04_caseD_4;
  case 5:
switchD_00015da0_caseD_5:
    if (0.0 < pfVar3[8]) {
      if (pfVar3[8] != 0.5) {
        pfVar3[7] = pfVar3[7] + 0.6;
        goto switchD_00015e04_caseD_5;
      }
      pfVar3[7] = pfVar3[7] + 0.5;
    }
    break;
  case 6:
switchD_00015da0_caseD_6:
    if ((0.0 <= *pfVar5) || (pfVar3[8] <= 0.0)) break;
    if (pfVar3[8] == 0.5) {
      pfVar3[7] = pfVar3[7] + 0.5;
    }
    else {
      pfVar3[7] = pfVar3[7] + 0.6;
    }
    goto switchD_00015e04_caseD_6;
  }
switchD_00015da0_default:
  switch(iVar2) {
  case 0:
    goto switchD_00015e04_caseD_0;
  case 1:
switchD_00015e04_caseD_1:
    fVar9 = *pfVar6;
    if (0.0 <= fVar9) {
      return;
    }
    fVar10 = pfVar3[0xb];
    if (fVar10 <= 0.0) {
      return;
    }
    goto LAB_00015f20;
  case 2:
switchD_00015e04_caseD_2:
    fVar9 = *pfVar6;
    if (fVar9 <= 0.0) {
      return;
    }
    fVar10 = pfVar3[0xb];
    if (0.0 <= fVar10) {
      return;
    }
    fVar7 = 0.2;
    if (fVar9 < 0.0) {
      fVar7 = -0.2;
    }
    *pfVar6 = fVar9 - fVar7;
    goto joined_r0x0001647c;
  case 3:
switchD_00015e04_caseD_3:
    fVar9 = *pfVar6;
    if (fVar9 <= 0.0) {
      return;
    }
    fVar10 = pfVar3[0xb];
    if (fVar10 <= 0.0) {
      return;
    }
    fVar7 = 0.2;
    if (fVar9 < 0.0) {
      fVar7 = -0.2;
    }
    *pfVar6 = fVar9 - fVar7;
joined_r0x0001647c:
    if (fVar10 < 0.0) {
      fVar9 = -0.2;
    }
    else {
      fVar9 = 0.2;
      if (fVar10 == 0.0) {
        fVar9 = 0.0;
      }
    }
    pfVar3[0xb] = fVar10 - fVar9;
    return;
  case 4:
switchD_00015e04_caseD_4:
    if (*pfVar6 <= 0.0) {
      return;
    }
    break;
  case 5:
    break;
  case 6:
switchD_00015e04_caseD_6:
    if (0.0 <= *pfVar6) {
      return;
    }
    break;
  default:
    return;
  }
switchD_00015e04_caseD_5:
  if (0.0 < pfVar3[0xb]) {
    if (pfVar3[0xb] == 0.5) {
      pfVar3[10] = pfVar3[10] + 0.5;
    }
    else {
      pfVar3[10] = pfVar3[10] + 0.6;
    }
  }
  return;
}
