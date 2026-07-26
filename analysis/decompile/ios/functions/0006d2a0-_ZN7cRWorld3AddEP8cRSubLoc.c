/*
 * mangled: _ZN7cRWorld3AddEP8cRSubLoc
 * demangled: cRWorld::Add(cRSubLoc*)
 * address: 0006d2a0
 * size: 1816
 */

/* cRWorld::Add(cRSubLoc*) */

void __thiscall cRWorld::Add(cRWorld *this,cRSubLoc *param_1)

{
  uint uVar1;
  cRSubLoc cVar2;
  byte bVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  uint in_fpscr;
  uint uVar11;
  float fVar12;
  float fVar13;

  fVar12 = *(float *)(this + 0x18) + 120.0;
  fVar13 = *(float *)(param_1 + 0x18);
  uVar7 = in_fpscr & 0xfffffff | (uint)(fVar13 < fVar12) << 0x1f | (uint)(fVar13 == fVar12) << 0x1e;
  uVar11 = uVar7 | (uint)(NAN(fVar13) || NAN(fVar12)) << 0x1c;
  bVar3 = (byte)(uVar7 >> 0x18);
  if (!(bool)(bVar3 >> 6 & 1) && bVar3 >> 7 == ((byte)(uVar11 >> 0x1c) & 1)) {
    *(float *)(this + 0x18) = fVar12;
    *(float *)(this + 0x44) = *(float *)(this + 0x44) + 120.0;
    iVar8 = *(int *)(*(int *)(this + 0x24) + 0x10c);
    if (0 < *(int *)(iVar8 + 0x3c)) {
      iVar4 = 0;
      iVar6 = 0;
      do {
        iVar4 = iVar4 + 1;
        iVar8 = iVar6 + *(int *)(iVar8 + 8);
        fVar12 = (float)VectorSignedToFloat((int)*(short *)(iVar8 + 4),(byte)(uVar11 >> 0x16) & 3);
        *(short *)(iVar8 + 4) = (short)(int)(fVar12 - 15360.0);
        iVar8 = iVar6 + *(int *)(*(int *)(*(int *)(this + 0x50) + 0x10c) + 8);
        iVar6 = iVar6 + 10;
        fVar12 = (float)VectorSignedToFloat((int)*(short *)(iVar8 + 4),(byte)(uVar11 >> 0x16) & 3);
        *(short *)(iVar8 + 4) = (short)(int)(fVar12 - 15360.0);
        iVar8 = *(int *)(*(int *)(this + 0x24) + 0x10c);
      } while (iVar4 < *(int *)(iVar8 + 0x3c));
    }
  }
  iVar10 = 0;
  cRSubGame::GetSkirtColour
            ((cRSubGame *)(*(int *)PTR__Game_001b60b8 + 0x72b78),(tColourSmall *)(this + 0x54));
  iVar8 = cRSubLoc::Yi(param_1);
  iVar6 = *(int *)(*(int *)(this + 0x24) + 0x10c);
  iVar4 = ___modsi3(iVar8,*(undefined4 *)(this + 0x5c));
  iVar9 = *(int *)(iVar6 + 0x1c);
  uVar5 = ___modsi3(*(undefined4 *)(iVar6 + 0x24),*(undefined4 *)(iVar6 + 0x28));
  *(undefined4 *)(iVar9 + iVar4 * 8) = uVar5;
  iVar6 = *(int *)(*(int *)(this + 0x24) + 0x10c);
  iVar4 = ___modsi3(iVar8,*(undefined4 *)(this + 0x5c));
  *(undefined4 *)(iVar4 * 8 + *(int *)(iVar6 + 0x1c) + 4) = 0;
  iVar6 = *(int *)(*(int *)(this + 0x50) + 0x10c);
  iVar4 = ___modsi3(iVar8,*(undefined4 *)(this + 0x5c));
  iVar9 = *(int *)(iVar6 + 0x1c);
  uVar5 = ___modsi3(*(undefined4 *)(iVar6 + 0x24),*(undefined4 *)(iVar6 + 0x28));
  *(undefined4 *)(iVar9 + iVar4 * 8) = uVar5;
  iVar6 = *(int *)(*(int *)(this + 0x50) + 0x10c);
  iVar4 = ___modsi3(iVar8,*(undefined4 *)(this + 0x5c));
  *(undefined4 *)(iVar4 * 8 + *(int *)(iVar6 + 0x1c) + 4) = 0;
  if (0 < *(int *)(this + 0x60)) {
    do {
      if (((((*(uint *)(param_1 + 4) & 0x200) != 0) && (((byte)param_1[0x33] & 0x40) != 0)) &&
          (cVar2 = param_1[0x30],
          (((cVar2 != (cRSubLoc)0x1d && cVar2 != (cRSubLoc)0x1e) && cVar2 != (cRSubLoc)0xe) &&
          cVar2 != (cRSubLoc)0x2) && cVar2 != (cRSubLoc)0x3)) &&
         (((((((cVar2 != (cRSubLoc)0x4 && cVar2 != (cRSubLoc)0x8) && cVar2 != (cRSubLoc)0x9) &&
             cVar2 != (cRSubLoc)0xa) && cVar2 != (cRSubLoc)0xb) && cVar2 != (cRSubLoc)0xc &&
           (((((cVar2 != (cRSubLoc)0xd && cVar2 != (cRSubLoc)0x5) && cVar2 != (cRSubLoc)0x6) &&
             cVar2 != (cRSubLoc)0x7) && cVar2 != (cRSubLoc)0x0) && cVar2 != (cRSubLoc)0x16)) &&
          ((cVar2 != (cRSubLoc)0x1c && cVar2 != (cRSubLoc)0x1f) && cVar2 != (cRSubLoc)0x20)))) {
        **(undefined4 **)(*(int *)(this + 0x24) + 0x10c) =
             *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x24) + 200) + 0xc);
        fVar12 = *(float *)(param_1 + 0x18);
        uVar7 = uVar11 & 0xfffffff;
        uVar1 = uVar7 | (uint)(fVar12 < 10.0) << 0x1f | (uint)(fVar12 == 10.0) << 0x1e;
        uVar11 = uVar1 | (uint)NAN(fVar12) << 0x1c;
        bVar3 = (byte)(uVar1 >> 0x18);
        if ((bool)(bVar3 >> 6 & 1) || bVar3 >> 7 != ((byte)(uVar11 >> 0x1c) & 1)) {
LAB_0006d51c:
          fVar12 = 0.0;
        }
        else {
          fVar13 = (float)VectorSignedToFloat(*(undefined4 *)(*(int *)PTR__Game_001b60b8 + 0x72be8),
                                              (byte)(uVar11 >> 0x16) & 3);
          uVar11 = uVar7 | (uint)(fVar12 < fVar13) << 0x1f;
          if (!SUB41(uVar11 >> 0x1f,0)) goto LAB_0006d51c;
          fVar12 = 0.03125;
        }
        cGLVertexArray::WorldAdd
                  (*(cGLVertexArray **)(*(int *)(this + 0x24) + 0x10c),(tVector *)(param_1 + 0x10),
                   *(float *)(param_1 + 0x1c),*(float *)(param_1 + 0x20),
                   *(cRObject **)(param_1 + 0x24),fVar12,*(float *)(this + 0x18));
        iVar6 = *(int *)(*(int *)(this + 0x24) + 0x10c);
        iVar4 = ___modsi3(iVar8,*(undefined4 *)(this + 0x5c));
        iVar4 = iVar4 * 8 + *(int *)(iVar6 + 0x1c);
        *(int *)(iVar4 + 4) = *(int *)(iVar4 + 4) + 6;
        uVar7 = *(uint *)(param_1 + 4);
        param_1[0x33] = (cRSubLoc)((byte)param_1[0x33] & 0xbf);
        *(uint *)(param_1 + 4) = uVar7 & 0xffffffdf;
        iVar4 = *(int *)PTR__Game_001b60b8;
        if ((uVar7 & 0x200) == 0) {
          RShellError("List remove");
        }
        else if ((uVar7 & 0x40) == 0) {
          iVar6 = *(int *)(param_1 + 0xc);
          if (iVar6 != 0) {
            *(undefined4 *)(iVar6 + 8) = *(undefined4 *)(param_1 + 8);
          }
          if (*(int *)(param_1 + 8) == 0) {
            *(int *)(iVar4 + 0x35c) = iVar6;
          }
          else {
            *(int *)(*(int *)(param_1 + 8) + 0xc) = iVar6;
          }
          *(undefined4 *)(param_1 + 0xc) = *(undefined4 *)(iVar4 + 0x360);
          *(cRSubLoc **)(iVar4 + 0x360) = param_1;
          *(uint *)(param_1 + 4) = *(uint *)(param_1 + 4) & 0xfffffdff;
        }
        else {
          RShellError("List remove NEXTBOD");
        }
      }
      if (*(undefined4 **)(param_1 + 0x34) != (undefined4 *)0x0) {
        cGLVertexArray::WorldAdd
                  (*(cGLVertexArray **)(*(int *)(this + 0x50) + 0x10c),(tVector *)(param_1 + 0x10),
                   0.0,0.0,(cRObject *)**(undefined4 **)(param_1 + 0x34),0.0,*(float *)(this + 0x18)
                  );
        iVar6 = *(int *)(*(int *)(this + 0x50) + 0x10c);
        iVar4 = ___modsi3(iVar8,*(undefined4 *)(this + 0x5c));
        iVar4 = iVar4 * 8 + *(int *)(iVar6 + 0x1c);
        *(int *)(iVar4 + 4) = *(int *)(iVar4 + 4) + 6;
      }
      if (*(undefined4 **)(param_1 + 0x38) != (undefined4 *)0x0) {
        cGLVertexArray::WorldAdd
                  (*(cGLVertexArray **)(*(int *)(this + 0x50) + 0x10c),(tVector *)(param_1 + 0x10),
                   0.0,0.0,(cRObject *)**(undefined4 **)(param_1 + 0x38),0.0,*(float *)(this + 0x18)
                  );
        iVar6 = *(int *)(*(int *)(this + 0x50) + 0x10c);
        iVar4 = ___modsi3(iVar8,*(undefined4 *)(this + 0x5c));
        iVar4 = iVar4 * 8 + *(int *)(iVar6 + 0x1c);
        *(int *)(iVar4 + 4) = *(int *)(iVar4 + 4) + 6;
      }
      if (*(undefined4 **)(param_1 + 0x3c) != (undefined4 *)0x0) {
        cGLVertexArray::WorldAdd
                  (*(cGLVertexArray **)(*(int *)(this + 0x50) + 0x10c),(tVector *)(param_1 + 0x10),
                   0.0,0.0,(cRObject *)**(undefined4 **)(param_1 + 0x3c),0.0,*(float *)(this + 0x18)
                  );
        iVar6 = *(int *)(*(int *)(this + 0x50) + 0x10c);
        iVar4 = ___modsi3(iVar8,*(undefined4 *)(this + 0x5c));
        iVar4 = iVar4 * 8 + *(int *)(iVar6 + 0x1c);
        *(int *)(iVar4 + 4) = *(int *)(iVar4 + 4) + 6;
      }
      if (*(undefined4 **)(param_1 + 0x40) != (undefined4 *)0x0) {
        cGLVertexArray::WorldAdd
                  (*(cGLVertexArray **)(*(int *)(this + 0x50) + 0x10c),(tVector *)(param_1 + 0x10),
                   0.0,0.0,(cRObject *)**(undefined4 **)(param_1 + 0x40),0.0,*(float *)(this + 0x18)
                  );
        iVar6 = *(int *)(*(int *)(this + 0x50) + 0x10c);
        iVar4 = ___modsi3(iVar8,*(undefined4 *)(this + 0x5c));
        iVar4 = iVar4 * 8 + *(int *)(iVar6 + 0x1c);
        *(int *)(iVar4 + 4) = *(int *)(iVar4 + 4) + 6;
      }
      iVar10 = iVar10 + 1;
      param_1 = param_1 + 0x44;
    } while (iVar10 < *(int *)(this + 0x60));
  }
  iVar4 = *(int *)(this + 0x5c);
  if (iVar8 < iVar4) {
    iVar6 = 0;
    iVar9 = *(int *)(*(int *)(this + 0x24) + 0x10c);
    iVar4 = ___modsi3(iVar8,iVar4);
    uVar11 = ___modsi3(*(int *)(iVar4 * 8 + *(int *)(iVar9 + 0x1c) + 4) +
                       *(int *)(iVar4 * 8 + *(int *)(iVar9 + 0x1c)),*(undefined4 *)(iVar9 + 0x28));
    if (0x7fffffff < uVar11) goto LAB_0006d8f0;
LAB_0006d7f8:
    *(int *)(iVar9 + 0x2c) = iVar6;
    *(uint *)(*(int *)(*(int *)(this + 0x24) + 0x10c) + 0x30) = uVar11 - iVar6;
    *(undefined4 *)(*(int *)(*(int *)(this + 0x24) + 0x10c) + 0x38) = 0;
    iVar4 = *(int *)(this + 0x5c);
  }
  else {
    iVar9 = *(int *)(*(int *)(this + 0x24) + 0x10c);
    iVar6 = ___modsi3(iVar8 - (iVar4 + -10),iVar4);
    iVar10 = *(int *)(iVar9 + 0x1c);
    iVar6 = *(int *)(iVar10 + iVar6 * 8);
    iVar4 = ___modsi3(iVar8,iVar4);
    uVar11 = ___modsi3(*(int *)(iVar10 + iVar4 * 8 + 4) + *(int *)(iVar10 + iVar4 * 8),
                       *(undefined4 *)(iVar9 + 0x28));
    if (iVar6 <= (int)uVar11) goto LAB_0006d7f8;
LAB_0006d8f0:
    *(int *)(iVar9 + 0x2c) = iVar6;
    *(int *)(*(int *)(*(int *)(this + 0x24) + 0x10c) + 0x30) =
         *(int *)(*(int *)(*(int *)(this + 0x24) + 0x10c) + 0x28) - iVar6;
    *(undefined4 *)(*(int *)(*(int *)(this + 0x24) + 0x10c) + 0x34) = 0;
    *(uint *)(*(int *)(*(int *)(this + 0x24) + 0x10c) + 0x38) = uVar11;
    iVar4 = *(int *)(this + 0x5c);
  }
  if (iVar8 < iVar4) {
    iVar6 = 0;
    iVar9 = *(int *)(*(int *)(this + 0x50) + 0x10c);
    iVar8 = ___modsi3(iVar8,iVar4);
    uVar11 = ___modsi3(*(int *)(iVar8 * 8 + *(int *)(iVar9 + 0x1c) + 4) +
                       *(int *)(iVar8 * 8 + *(int *)(iVar9 + 0x1c)),*(undefined4 *)(iVar9 + 0x28));
    if (0x7fffffff < uVar11) {
LAB_0006d984:
      *(int *)(iVar9 + 0x2c) = iVar6;
      *(int *)(*(int *)(*(int *)(this + 0x50) + 0x10c) + 0x30) =
           *(int *)(*(int *)(*(int *)(this + 0x50) + 0x10c) + 0x28) - iVar6;
      *(undefined4 *)(*(int *)(*(int *)(this + 0x50) + 0x10c) + 0x34) = 0;
      *(uint *)(*(int *)(*(int *)(this + 0x50) + 0x10c) + 0x38) = uVar11;
      return;
    }
  }
  else {
    iVar9 = *(int *)(*(int *)(this + 0x50) + 0x10c);
    iVar6 = ___modsi3(iVar8 - (iVar4 + -10),iVar4);
    iVar10 = *(int *)(iVar9 + 0x1c);
    iVar6 = *(int *)(iVar10 + iVar6 * 8);
    iVar8 = ___modsi3(iVar8,iVar4);
    uVar11 = ___modsi3(*(int *)(iVar10 + iVar8 * 8 + 4) + *(int *)(iVar10 + iVar8 * 8),
                       *(undefined4 *)(iVar9 + 0x28));
    if ((int)uVar11 < iVar6) goto LAB_0006d984;
  }
  *(int *)(iVar9 + 0x2c) = iVar6;
  *(uint *)(*(int *)(*(int *)(this + 0x50) + 0x10c) + 0x30) = uVar11 - iVar6;
  *(undefined4 *)(*(int *)(*(int *)(this + 0x50) + 0x10c) + 0x38) = 0;
  return;
}
