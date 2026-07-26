/*
 * mangled: _ZN8cRObject18BuildGLVertexArrayEv
 * demangled: cRObject::BuildGLVertexArray()
 * address: 00014944
 * size: 2520
 */

/* cRObject::BuildGLVertexArray() */

void __thiscall cRObject::BuildGLVertexArray(cRObject *this)

{
  ushort uVar1;
  float *pfVar2;
  void *pvVar3;
  undefined2 *puVar4;
  void *pvVar5;
  undefined4 uVar6;
  float *pfVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  undefined2 *puVar13;
  int iVar14;
  int iVar15;
  size_t sVar16;
  int iVar17;
  float fVar18;
  float fVar19;
  float fVar20;
  float fVar21;
  float fVar22;
  int local_30;
  int local_2c;
  size_t local_28;
  size_t local_24;

  if ((((*(int *)(this + 0xc0) != 0) && (*(int *)(this + 0xa0) != 0)) &&
      (uVar11 = *(uint *)this, (uVar11 & 0x4000000) == 0)) && ((uVar11 & 0x8000000) == 0)) {
    *(uint *)this = uVar11 | 0x4000000;
    pfVar2 = (float *)RShellMemoryScratch();
    pvVar3 = (void *)RShellMemoryScratch();
    puVar4 = (undefined2 *)RShellMemoryScratch2();
    pvVar5 = (void *)RShellMemoryScratch2();
    if ((*(uint *)this & 4) == 0) {
      uVar11 = 0;
      if (*(int *)(this + 0xc0) < 1) {
        sVar16 = 0;
        local_30 = 0;
        local_24 = 0;
      }
      else {
        iVar14 = 0;
        iVar17 = 0;
        iVar8 = 0;
        do {
          iVar9 = iVar17 + *(int *)(this + 200);
          fVar19 = *(float *)(iVar9 + 0x10);
          fVar18 = *(float *)(iVar9 + 0x14);
          pfVar7 = (float *)((uint)*(ushort *)(iVar9 + 2) * 0xc + *(int *)(this + 0xa4));
          if ((int)uVar11 < 1) {
            fVar22 = *pfVar7;
            fVar21 = pfVar7[1];
            fVar20 = pfVar7[2];
          }
          else {
            fVar22 = *pfVar7;
            fVar21 = pfVar7[1];
            fVar20 = pfVar7[2];
            uVar10 = 0;
            pfVar7 = pfVar2;
            do {
              if (((*pfVar7 == fVar22) && (pfVar7[1] == fVar21)) &&
                 ((pfVar7[2] == fVar20 &&
                  ((fVar19 == pfVar7[3] && (uVar12 = uVar11, fVar18 == pfVar7[4]))))))
              goto LAB_00014d78;
              uVar10 = uVar10 + 1;
              pfVar7 = pfVar7 + 5;
            } while (uVar10 != uVar11);
          }
          pfVar7 = pfVar2 + uVar11 * 5;
          uVar12 = uVar11 + 1;
          *pfVar7 = fVar22;
          pfVar7[1] = fVar21;
          pfVar7[2] = fVar20;
          pfVar7[3] = fVar19;
          pfVar7[4] = fVar18;
          uVar10 = uVar11;
LAB_00014d78:
          *puVar4 = (short)uVar10;
          iVar9 = iVar17 + *(int *)(this + 200);
          fVar19 = *(float *)(iVar9 + 0x18);
          fVar18 = *(float *)(iVar9 + 0x1c);
          pfVar7 = (float *)((uint)*(ushort *)(iVar9 + 4) * 0xc + *(int *)(this + 0xa4));
          if ((int)uVar12 < 1) {
            fVar22 = *pfVar7;
            fVar21 = pfVar7[1];
            fVar20 = pfVar7[2];
          }
          else {
            fVar22 = *pfVar7;
            fVar21 = pfVar7[1];
            fVar20 = pfVar7[2];
            uVar11 = 0;
            pfVar7 = pfVar2;
            do {
              if ((((*pfVar7 == fVar22) && (pfVar7[1] == fVar21)) && (pfVar7[2] == fVar20)) &&
                 ((fVar19 == pfVar7[3] && (uVar10 = uVar12, fVar18 == pfVar7[4]))))
              goto LAB_00014e4c;
              uVar11 = uVar11 + 1;
              pfVar7 = pfVar7 + 5;
            } while (uVar11 != uVar12);
          }
          pfVar7 = pfVar2 + uVar12 * 5;
          uVar10 = uVar12 + 1;
          *pfVar7 = fVar22;
          pfVar7[1] = fVar21;
          pfVar7[2] = fVar20;
          pfVar7[3] = fVar19;
          pfVar7[4] = fVar18;
          uVar11 = uVar12;
LAB_00014e4c:
          puVar4[1] = (short)uVar11;
          iVar9 = iVar17 + *(int *)(this + 200);
          fVar19 = *(float *)(iVar9 + 0x20);
          fVar18 = *(float *)(iVar9 + 0x24);
          pfVar7 = (float *)((uint)*(ushort *)(iVar9 + 6) * 0xc + *(int *)(this + 0xa4));
          if ((int)uVar10 < 1) {
            fVar22 = *pfVar7;
            fVar21 = pfVar7[1];
            fVar20 = pfVar7[2];
          }
          else {
            fVar22 = *pfVar7;
            fVar21 = pfVar7[1];
            fVar20 = pfVar7[2];
            uVar12 = 0;
            pfVar7 = pfVar2;
            do {
              if (((*pfVar7 == fVar22) && (pfVar7[1] == fVar21)) &&
                 ((pfVar7[2] == fVar20 &&
                  ((fVar19 == pfVar7[3] && (uVar11 = uVar10, fVar18 == pfVar7[4]))))))
              goto LAB_00014f1c;
              uVar12 = uVar12 + 1;
              pfVar7 = pfVar7 + 5;
            } while (uVar12 != uVar10);
          }
          pfVar7 = pfVar2 + uVar10 * 5;
          uVar11 = uVar10 + 1;
          *pfVar7 = fVar22;
          pfVar7[1] = fVar21;
          pfVar7[2] = fVar20;
          pfVar7[3] = fVar19;
          pfVar7[4] = fVar18;
          uVar12 = uVar10;
LAB_00014f1c:
          puVar13 = puVar4 + 3;
          puVar4[2] = (short)uVar12;
          iVar15 = iVar8 + 1;
          iVar9 = iVar17 + *(int *)(this + 200);
          uVar1 = *(ushort *)(iVar17 + *(int *)(this + 200));
          uVar10 = uVar1 & 0x80;
          if ((uVar1 & 0x80) == 0) {
            fVar19 = *(float *)(iVar9 + 0x10);
            fVar18 = *(float *)(iVar9 + 0x14);
            pfVar7 = (float *)((uint)*(ushort *)(iVar9 + 2) * 0xc + *(int *)(this + 0xa4));
            if ((int)uVar11 < 1) {
              fVar22 = *pfVar7;
              fVar21 = pfVar7[1];
              fVar20 = pfVar7[2];
            }
            else {
              fVar22 = *pfVar7;
              fVar21 = pfVar7[1];
              fVar20 = pfVar7[2];
              pfVar7 = pfVar2;
              do {
                if ((((fVar22 == *pfVar7) && (pfVar7[1] == fVar21)) && (pfVar7[2] == fVar20)) &&
                   ((fVar19 == pfVar7[3] && (uVar12 = uVar11, fVar18 == pfVar7[4]))))
                goto LAB_00014ffc;
                uVar10 = uVar10 + 1;
                pfVar7 = pfVar7 + 5;
              } while (uVar10 != uVar11);
            }
            pfVar7 = pfVar2 + uVar11 * 5;
            uVar12 = uVar11 + 1;
            *pfVar7 = fVar22;
            pfVar7[1] = fVar21;
            pfVar7[2] = fVar20;
            pfVar7[3] = fVar19;
            pfVar7[4] = fVar18;
            uVar10 = uVar11;
LAB_00014ffc:
            *puVar13 = (short)uVar10;
            iVar9 = iVar17 + *(int *)(this + 200);
            fVar19 = *(float *)(iVar9 + 0x20);
            fVar18 = *(float *)(iVar9 + 0x24);
            pfVar7 = (float *)((uint)*(ushort *)(iVar9 + 6) * 0xc + *(int *)(this + 0xa4));
            if ((int)uVar12 < 1) {
              fVar22 = *pfVar7;
              fVar21 = pfVar7[1];
              fVar20 = pfVar7[2];
            }
            else {
              fVar22 = *pfVar7;
              fVar21 = pfVar7[1];
              fVar20 = pfVar7[2];
              uVar11 = 0;
              pfVar7 = pfVar2;
              do {
                if (((fVar22 == *pfVar7) && (pfVar7[1] == fVar21)) &&
                   ((pfVar7[2] == fVar20 &&
                    ((fVar19 == pfVar7[3] && (uVar10 = uVar12, fVar18 == pfVar7[4]))))))
                goto LAB_000150d0;
                uVar11 = uVar11 + 1;
                pfVar7 = pfVar7 + 5;
              } while (uVar11 != uVar12);
            }
            pfVar7 = pfVar2 + uVar12 * 5;
            uVar10 = uVar12 + 1;
            *pfVar7 = fVar22;
            pfVar7[1] = fVar21;
            pfVar7[2] = fVar20;
            pfVar7[3] = fVar19;
            pfVar7[4] = fVar18;
            uVar11 = uVar12;
LAB_000150d0:
            puVar4[4] = (short)uVar11;
            iVar9 = iVar17 + *(int *)(this + 200);
            fVar19 = *(float *)(iVar9 + 0x28);
            fVar18 = *(float *)(iVar9 + 0x2c);
            pfVar7 = (float *)((uint)*(ushort *)(iVar9 + 8) * 0xc + *(int *)(this + 0xa4));
            if ((int)uVar10 < 1) {
              fVar22 = *pfVar7;
              fVar21 = pfVar7[1];
              fVar20 = pfVar7[2];
            }
            else {
              fVar22 = *pfVar7;
              fVar21 = pfVar7[1];
              fVar20 = pfVar7[2];
              uVar12 = 0;
              pfVar7 = pfVar2;
              do {
                if ((((fVar22 == *pfVar7) && (pfVar7[1] == fVar21)) && (pfVar7[2] == fVar20)) &&
                   ((fVar19 == pfVar7[3] && (uVar11 = uVar10, fVar18 == pfVar7[4]))))
                goto LAB_000151a0;
                uVar12 = uVar12 + 1;
                pfVar7 = pfVar7 + 5;
              } while (uVar12 != uVar10);
            }
            pfVar7 = pfVar2 + uVar10 * 5;
            uVar11 = uVar10 + 1;
            *pfVar7 = fVar22;
            pfVar7[1] = fVar21;
            pfVar7[2] = fVar20;
            pfVar7[3] = fVar19;
            pfVar7[4] = fVar18;
            uVar12 = uVar10;
LAB_000151a0:
            puVar13 = puVar4 + 6;
            puVar4[5] = (short)uVar12;
            iVar15 = iVar8 + 2;
          }
          iVar14 = iVar14 + 1;
          iVar17 = iVar17 + 0x30;
          puVar4 = puVar13;
          iVar8 = iVar15;
        } while (iVar14 < *(int *)(this + 0xc0));
        sVar16 = uVar11 * 0x14;
        local_30 = iVar15 * 3;
        local_24 = iVar15 * 6;
      }
      iVar14 = RShellMemoryMalloc(0x5c,"Obj Vertex array");
      *(int *)(this + 0x10c) = iVar14;
      *(uint *)(iVar14 + 4) = uVar11;
      iVar14 = *(int *)(this + 0x10c);
      uVar6 = RShellMemoryMalloc(sVar16,"Obj VertexUV");
      *(undefined4 *)(iVar14 + 8) = uVar6;
      _memcpy(*(void **)(*(int *)(this + 0x10c) + 8),pfVar2,sVar16);
      *(int *)(*(int *)(this + 0x10c) + 0x14) = local_30;
      iVar14 = *(int *)(this + 0x10c);
      uVar6 = RShellMemoryMalloc(local_24,"Vertex Inded Array");
      *(undefined4 *)(iVar14 + 0x18) = uVar6;
      _memcpy(*(void **)(*(int *)(this + 0x10c) + 0x18),pvVar5,local_24);
      RShellMemoryFree(*(void **)(this + 0xa4));
      *(undefined4 *)(this + 0xa4) = 0;
      **(undefined4 **)(this + 0x10c) = *(undefined4 *)(*(int *)(this + 200) + 0xc);
      RShellMemoryFree(*(void **)(this + 200));
      *(undefined4 *)(this + 200) = 0;
    }
    else {
      if (*(int *)(this + 0xc0) < 1) {
        local_2c = 0;
        local_28 = 0;
      }
      else {
        iVar14 = 0;
        iVar17 = 0;
        iVar8 = 0;
        do {
          iVar9 = iVar8 + 1;
          *puVar4 = *(undefined2 *)(*(int *)(this + 200) + iVar17 + 2);
          puVar4[1] = *(undefined2 *)(*(int *)(this + 200) + iVar17 + 4);
          puVar13 = puVar4 + 3;
          puVar4[2] = *(undefined2 *)(*(int *)(this + 200) + iVar17 + 6);
          *(undefined4 *)((uint)*(ushort *)(iVar17 + *(int *)(this + 200) + 2) * 8 + (int)pvVar3) =
               *(undefined4 *)(iVar17 + *(int *)(this + 200) + 0x10);
          *(undefined4 *)
           ((int)pvVar3 + (uint)*(ushort *)(iVar17 + *(int *)(this + 200) + 2) * 8 + 4) =
               *(undefined4 *)(iVar17 + *(int *)(this + 200) + 0x14);
          *(undefined4 *)((uint)*(ushort *)(iVar17 + *(int *)(this + 200) + 4) * 8 + (int)pvVar3) =
               *(undefined4 *)(iVar17 + *(int *)(this + 200) + 0x18);
          *(undefined4 *)
           ((int)pvVar3 + (uint)*(ushort *)(iVar17 + *(int *)(this + 200) + 4) * 8 + 4) =
               *(undefined4 *)(iVar17 + *(int *)(this + 200) + 0x1c);
          *(undefined4 *)((uint)*(ushort *)(iVar17 + *(int *)(this + 200) + 6) * 8 + (int)pvVar3) =
               *(undefined4 *)(iVar17 + *(int *)(this + 200) + 0x20);
          *(undefined4 *)
           ((int)pvVar3 + (uint)*(ushort *)(iVar17 + *(int *)(this + 200) + 6) * 8 + 4) =
               *(undefined4 *)(iVar17 + *(int *)(this + 200) + 0x24);
          if ((*(ushort *)(iVar17 + *(int *)(this + 200)) & 0x80) == 0) {
            iVar9 = iVar8 + 2;
            puVar4[3] = *(undefined2 *)(iVar17 + *(int *)(this + 200) + 2);
            puVar4[4] = *(undefined2 *)(*(int *)(this + 200) + iVar17 + 6);
            puVar4[5] = *(undefined2 *)(*(int *)(this + 200) + iVar17 + 8);
            puVar13 = puVar4 + 6;
            *(undefined4 *)((uint)*(ushort *)(iVar17 + *(int *)(this + 200) + 2) * 8 + (int)pvVar3)
                 = *(undefined4 *)(iVar17 + *(int *)(this + 200) + 0x10);
            *(undefined4 *)
             ((int)pvVar3 + (uint)*(ushort *)(iVar17 + *(int *)(this + 200) + 2) * 8 + 4) =
                 *(undefined4 *)(iVar17 + *(int *)(this + 200) + 0x14);
            *(undefined4 *)((uint)*(ushort *)(iVar17 + *(int *)(this + 200) + 6) * 8 + (int)pvVar3)
                 = *(undefined4 *)(iVar17 + *(int *)(this + 200) + 0x20);
            *(undefined4 *)
             ((int)pvVar3 + (uint)*(ushort *)(iVar17 + *(int *)(this + 200) + 6) * 8 + 4) =
                 *(undefined4 *)(iVar17 + *(int *)(this + 200) + 0x24);
            *(undefined4 *)((uint)*(ushort *)(iVar17 + *(int *)(this + 200) + 8) * 8 + (int)pvVar3)
                 = *(undefined4 *)(iVar17 + *(int *)(this + 200) + 0x28);
            *(undefined4 *)
             ((int)pvVar3 + (uint)*(ushort *)(iVar17 + *(int *)(this + 200) + 8) * 8 + 4) =
                 *(undefined4 *)(iVar17 + *(int *)(this + 200) + 0x2c);
          }
          iVar14 = iVar14 + 1;
          iVar17 = iVar17 + 0x30;
          iVar8 = iVar9;
          puVar4 = puVar13;
        } while (iVar14 < *(int *)(this + 0xc0));
        local_2c = iVar9 * 3;
        local_28 = iVar9 * 6;
      }
      iVar17 = *(int *)(this + 0xa0);
      iVar14 = RShellMemoryMalloc(0x5c,"Obj Vertex array");
      *(int *)(this + 0x10c) = iVar14;
      *(int *)(iVar14 + 0xc) = iVar17;
      iVar14 = *(int *)(this + 0x10c);
      uVar6 = RShellMemoryMalloc(iVar17 << 3,"Obj UV");
      *(undefined4 *)(iVar14 + 0x10) = uVar6;
      _memcpy(*(void **)(*(int *)(this + 0x10c) + 0x10),pvVar3,iVar17 << 3);
      *(int *)(*(int *)(this + 0x10c) + 0x14) = local_2c;
      iVar14 = *(int *)(this + 0x10c);
      uVar6 = RShellMemoryMalloc(local_28,"Vertex Index Array");
      *(undefined4 *)(iVar14 + 0x18) = uVar6;
      _memcpy(*(void **)(*(int *)(this + 0x10c) + 0x18),pvVar5,local_28);
      **(undefined4 **)(this + 0x10c) = *(undefined4 *)(*(int *)(this + 200) + 0xc);
      if ((*(uint *)this & 0x200000) != 0) {
        RShellMemoryFree(*(void **)(this + 0xa4));
        *(undefined4 *)(this + 0xa4) = 0;
      }
      RShellMemoryFree(*(void **)(this + 200));
      *(undefined4 *)(this + 200) = 0;
    }
  }
  return;
}
