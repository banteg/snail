/*
 * mangled: _ZN8cRObject18BuildGLVertexArrayEv
 * demangled: cRObject::BuildGLVertexArray()
 * address: 0002d604
 * size: 1280
 */

/* cRObject::BuildGLVertexArray() */

void __thiscall cRObject::BuildGLVertexArray(cRObject *this)

{
  size_t __n;
  ushort uVar1;
  ushort uVar2;
  ushort uVar3;
  undefined2 uVar4;
  cGLVertexUV *__src;
  void *pvVar5;
  undefined2 *puVar6;
  void *__src_00;
  int iVar7;
  undefined4 uVar8;
  uint uVar9;
  undefined4 *puVar10;
  undefined2 *puVar11;
  size_t sVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  float extraout_s0;
  float fVar16;
  float extraout_s0_00;
  float extraout_s0_01;
  float extraout_s0_02;
  float extraout_s0_03;
  float extraout_s0_04;
  float extraout_s0_05;
  float extraout_s1;
  float fVar17;
  float extraout_s1_00;
  float extraout_s1_01;
  float extraout_s1_02;
  float extraout_s1_03;
  float extraout_s1_04;
  float extraout_s1_05;
  int local_40;
  int local_2c [2];

  if ((*(int *)(this + 0xc0) != 0) && (*(int *)(this + 0xa0) != 0)) {
    if ((*(uint *)this & 0xc000000) == 0) {
      *(uint *)this = *(uint *)this | 0x4000000;
      __src = (cGLVertexUV *)RShellMemoryScratch();
      pvVar5 = (void *)RShellMemoryScratch();
      puVar6 = (undefined2 *)RShellMemoryScratch2();
      __src_00 = (void *)RShellMemoryScratch2();
      if ((*(uint *)this & 4) == 0) {
        local_2c[0] = 0;
        if (*(int *)(this + 0xc0) < 1) {
          iVar7 = 0;
          sVar12 = 0;
        }
        else {
          iVar7 = 0;
          iVar14 = 0;
          local_40 = 0;
          fVar16 = extraout_s0;
          fVar17 = extraout_s1;
          do {
            iVar14 = iVar14 + 1;
            uVar4 = AddVertexUV(__src,local_2c,
                                (tVector *)
                                (*(int *)(this + 0xa4) +
                                (uint)*(ushort *)(*(int *)(this + 200) + iVar7 + 2) * 0xc),fVar16,
                                fVar17);
            iVar15 = *(int *)(this + 200);
            *puVar6 = uVar4;
            uVar4 = AddVertexUV(__src,local_2c,
                                (tVector *)
                                (*(int *)(this + 0xa4) + (uint)*(ushort *)(iVar15 + iVar7 + 4) * 0xc
                                ),extraout_s0_00,extraout_s1_00);
            iVar15 = *(int *)(this + 200);
            puVar6[1] = uVar4;
            puVar11 = puVar6 + 3;
            uVar4 = AddVertexUV(__src,local_2c,
                                (tVector *)
                                (*(int *)(this + 0xa4) + (uint)*(ushort *)(iVar15 + iVar7 + 6) * 0xc
                                ),extraout_s0_01,extraout_s1_01);
            iVar13 = *(int *)(this + 200);
            puVar6[2] = uVar4;
            fVar16 = extraout_s0_02;
            fVar17 = extraout_s1_02;
            iVar15 = local_40 + 1;
            if ((*(ushort *)(iVar13 + iVar7) & 0x80) == 0) {
              uVar4 = AddVertexUV(__src,local_2c,
                                  (tVector *)
                                  (*(int *)(this + 0xa4) +
                                  (uint)*(ushort *)(iVar13 + iVar7 + 2) * 0xc),extraout_s0_02,
                                  extraout_s1_02);
              iVar15 = *(int *)(this + 200);
              puVar6[3] = uVar4;
              uVar4 = AddVertexUV(__src,local_2c,
                                  (tVector *)
                                  (*(int *)(this + 0xa4) +
                                  (uint)*(ushort *)(iVar15 + iVar7 + 6) * 0xc),extraout_s0_03,
                                  extraout_s1_03);
              iVar15 = *(int *)(this + 200);
              puVar6[4] = uVar4;
              puVar11 = puVar6 + 6;
              uVar4 = AddVertexUV(__src,local_2c,
                                  (tVector *)
                                  (*(int *)(this + 0xa4) +
                                  (uint)*(ushort *)(iVar15 + iVar7 + 8) * 0xc),extraout_s0_04,
                                  extraout_s1_04);
              puVar6[5] = uVar4;
              fVar16 = extraout_s0_05;
              fVar17 = extraout_s1_05;
              iVar15 = local_40 + 2;
            }
            local_40 = iVar15;
            iVar7 = iVar7 + 0x30;
            puVar6 = puVar11;
          } while (iVar14 < *(int *)(this + 0xc0));
          iVar7 = local_40 * 3;
          sVar12 = local_40 * 6;
        }
        iVar14 = RShellMemoryMalloc(0x5c,"Obj Vertex array");
        *(int *)(this + 0x10c) = iVar14;
        *(int *)(iVar14 + 4) = local_2c[0];
        uVar8 = RShellMemoryMalloc(local_2c[0] * 0x14,"Obj VertexUV");
        *(undefined4 *)(iVar14 + 8) = uVar8;
        memcpy(*(void **)(*(int *)(this + 0x10c) + 8),__src,local_2c[0] * 0x14);
        iVar14 = *(int *)(this + 0x10c);
        *(int *)(iVar14 + 0x14) = iVar7;
        uVar8 = RShellMemoryMalloc(sVar12,"Vertex Inded Array");
        iVar7 = *(int *)(this + 0x10c);
        *(undefined4 *)(iVar14 + 0x18) = uVar8;
        memcpy(*(void **)(iVar7 + 0x18),__src_00,sVar12);
        RShellMemoryFree(*(void **)(this + 0xa4));
        pvVar5 = *(void **)(this + 200);
        *(undefined4 *)(this + 0xa4) = 0;
        **(undefined4 **)(this + 0x10c) = *(undefined4 *)((int)pvVar5 + 0xc);
        RShellMemoryFree(pvVar5);
        *(undefined4 *)(this + 200) = 0;
      }
      else {
        iVar7 = *(int *)(this + 0xc0);
        if (iVar7 < 1) {
          sVar12 = 0;
          iVar7 = 0;
        }
        else {
          puVar10 = (undefined4 *)(*(int *)(this + 200) + 0x18);
          iVar14 = 0;
          iVar15 = 0;
          do {
            iVar14 = iVar14 + 1;
            iVar13 = iVar15 + 1;
            *puVar6 = *(undefined2 *)((int)puVar10 + -0x16);
            puVar6[1] = *(undefined2 *)(puVar10 + -5);
            puVar11 = puVar6 + 3;
            puVar6[2] = *(undefined2 *)((int)puVar10 + -0x12);
            uVar1 = *(ushort *)((int)puVar10 + -0x16);
            uVar2 = *(ushort *)(puVar10 + -6);
            *(undefined4 *)((int)pvVar5 + (uint)uVar1 * 8) = puVar10[-2];
            *(undefined4 *)((int)pvVar5 + (uint)uVar1 * 8 + 4) = puVar10[-1];
            uVar3 = *(ushort *)(puVar10 + -5);
            *(undefined4 *)((int)pvVar5 + (uint)uVar3 * 8) = *puVar10;
            *(undefined4 *)((int)pvVar5 + (uint)uVar3 * 8 + 4) = puVar10[1];
            uVar3 = *(ushort *)((int)puVar10 + -0x12);
            *(undefined4 *)((int)pvVar5 + (uint)uVar3 * 8) = puVar10[2];
            *(undefined4 *)((int)pvVar5 + (uint)uVar3 * 8 + 4) = puVar10[3];
            if ((uVar2 & 0x80) == 0) {
              puVar6[3] = uVar1;
              iVar13 = iVar15 + 2;
              puVar6[4] = *(undefined2 *)((int)puVar10 + -0x12);
              puVar11 = puVar6 + 6;
              puVar6[5] = *(undefined2 *)(puVar10 + -4);
              uVar1 = *(ushort *)((int)puVar10 + -0x16);
              *(undefined4 *)((int)pvVar5 + (uint)uVar1 * 8) = puVar10[-2];
              *(undefined4 *)((int)pvVar5 + (uint)uVar1 * 8 + 4) = puVar10[-1];
              uVar1 = *(ushort *)((int)puVar10 + -0x12);
              *(undefined4 *)((int)pvVar5 + (uint)uVar1 * 8) = puVar10[2];
              *(undefined4 *)((int)pvVar5 + (uint)uVar1 * 8 + 4) = puVar10[3];
              uVar1 = *(ushort *)(puVar10 + -4);
              *(undefined4 *)((int)pvVar5 + (uint)uVar1 * 8) = puVar10[4];
              *(undefined4 *)((int)pvVar5 + (uint)uVar1 * 8 + 4) = puVar10[5];
            }
            puVar10 = puVar10 + 0xc;
            puVar6 = puVar11;
            iVar15 = iVar13;
          } while (iVar14 != iVar7);
          iVar7 = iVar13 * 3;
          sVar12 = iVar13 * 6;
        }
        iVar15 = *(int *)(this + 0xa0);
        iVar14 = RShellMemoryMalloc(0x5c,"Obj Vertex array");
        __n = iVar15 << 3;
        *(int *)(this + 0x10c) = iVar14;
        *(int *)(iVar14 + 0xc) = iVar15;
        uVar8 = RShellMemoryMalloc(__n,"Obj UV");
        *(undefined4 *)(iVar14 + 0x10) = uVar8;
        memcpy(*(void **)(*(int *)(this + 0x10c) + 0x10),pvVar5,__n);
        iVar14 = *(int *)(this + 0x10c);
        *(int *)(iVar14 + 0x14) = iVar7;
        uVar8 = RShellMemoryMalloc(sVar12,"Vertex Index Array");
        iVar7 = *(int *)(this + 0x10c);
        *(undefined4 *)(iVar14 + 0x18) = uVar8;
        memcpy(*(void **)(iVar7 + 0x18),__src_00,sVar12);
        pvVar5 = *(void **)(this + 200);
        uVar9 = *(uint *)this;
        **(undefined4 **)(this + 0x10c) = *(undefined4 *)((int)pvVar5 + 0xc);
        if ((uVar9 & 0x200000) != 0) {
          RShellMemoryFree(*(void **)(this + 0xa4));
          pvVar5 = *(void **)(this + 200);
          *(undefined4 *)(this + 0xa4) = 0;
        }
        RShellMemoryFree(pvVar5);
        *(undefined4 *)(this + 200) = 0;
      }
    }
  }
  return;
}
