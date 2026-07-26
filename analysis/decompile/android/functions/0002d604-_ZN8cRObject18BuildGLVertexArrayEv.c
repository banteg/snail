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
  char *pcVar9;
  uint uVar10;
  undefined4 *puVar11;
  int iVar12;
  undefined2 *puVar13;
  size_t sVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  float extraout_s0;
  float fVar18;
  float extraout_s0_00;
  float extraout_s0_01;
  float extraout_s0_02;
  float extraout_s0_03;
  float extraout_s0_04;
  float extraout_s0_05;
  float extraout_s1;
  float fVar19;
  float extraout_s1_00;
  float extraout_s1_01;
  float extraout_s1_02;
  float extraout_s1_03;
  float extraout_s1_04;
  float extraout_s1_05;
  int local_40;
  int local_2c [2];

  iVar12 = DAT_0002db04 + 0x2d624;
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
          sVar14 = 0;
        }
        else {
          iVar7 = 0;
          iVar16 = 0;
          local_40 = 0;
          fVar18 = extraout_s0;
          fVar19 = extraout_s1;
          do {
            iVar16 = iVar16 + 1;
            uVar4 = AddVertexUV(__src,local_2c,
                                (tVector *)
                                (*(int *)(this + 0xa4) +
                                (uint)*(ushort *)(*(int *)(this + 200) + iVar7 + 2) * 0xc),fVar18,
                                fVar19);
            iVar17 = *(int *)(this + 200);
            *puVar6 = uVar4;
            uVar4 = AddVertexUV(__src,local_2c,
                                (tVector *)
                                (*(int *)(this + 0xa4) + (uint)*(ushort *)(iVar17 + iVar7 + 4) * 0xc
                                ),extraout_s0_00,extraout_s1_00);
            iVar17 = *(int *)(this + 200);
            puVar6[1] = uVar4;
            puVar13 = puVar6 + 3;
            uVar4 = AddVertexUV(__src,local_2c,
                                (tVector *)
                                (*(int *)(this + 0xa4) + (uint)*(ushort *)(iVar17 + iVar7 + 6) * 0xc
                                ),extraout_s0_01,extraout_s1_01);
            iVar15 = *(int *)(this + 200);
            puVar6[2] = uVar4;
            fVar18 = extraout_s0_02;
            fVar19 = extraout_s1_02;
            iVar17 = local_40 + 1;
            if ((*(ushort *)(iVar15 + iVar7) & 0x80) == 0) {
              uVar4 = AddVertexUV(__src,local_2c,
                                  (tVector *)
                                  (*(int *)(this + 0xa4) +
                                  (uint)*(ushort *)(iVar15 + iVar7 + 2) * 0xc),extraout_s0_02,
                                  extraout_s1_02);
              iVar17 = *(int *)(this + 200);
              puVar6[3] = uVar4;
              uVar4 = AddVertexUV(__src,local_2c,
                                  (tVector *)
                                  (*(int *)(this + 0xa4) +
                                  (uint)*(ushort *)(iVar17 + iVar7 + 6) * 0xc),extraout_s0_03,
                                  extraout_s1_03);
              iVar17 = *(int *)(this + 200);
              puVar6[4] = uVar4;
              puVar13 = puVar6 + 6;
              uVar4 = AddVertexUV(__src,local_2c,
                                  (tVector *)
                                  (*(int *)(this + 0xa4) +
                                  (uint)*(ushort *)(iVar17 + iVar7 + 8) * 0xc),extraout_s0_04,
                                  extraout_s1_04);
              puVar6[5] = uVar4;
              fVar18 = extraout_s0_05;
              fVar19 = extraout_s1_05;
              iVar17 = local_40 + 2;
            }
            local_40 = iVar17;
            iVar7 = iVar7 + 0x30;
            puVar6 = puVar13;
          } while (iVar16 < *(int *)(this + 0xc0));
          iVar7 = local_40 * 3;
          sVar14 = local_40 * 6;
        }
        iVar16 = RShellMemoryMalloc(0x5c,(char *)(iVar12 + DAT_0002db08));
        pcVar9 = (char *)(iVar12 + DAT_0002db14);
        *(int *)(this + 0x10c) = iVar16;
        *(int *)(iVar16 + 4) = local_2c[0];
        uVar8 = RShellMemoryMalloc(local_2c[0] * 0x14,pcVar9);
        *(undefined4 *)(iVar16 + 8) = uVar8;
        memcpy(*(void **)(*(int *)(this + 0x10c) + 8),__src,local_2c[0] * 0x14);
        iVar16 = *(int *)(this + 0x10c);
        pcVar9 = (char *)(iVar12 + DAT_0002db18);
        *(int *)(iVar16 + 0x14) = iVar7;
        uVar8 = RShellMemoryMalloc(sVar14,pcVar9);
        iVar12 = *(int *)(this + 0x10c);
        *(undefined4 *)(iVar16 + 0x18) = uVar8;
        memcpy(*(void **)(iVar12 + 0x18),__src_00,sVar14);
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
          sVar14 = 0;
          iVar7 = 0;
        }
        else {
          puVar11 = (undefined4 *)(*(int *)(this + 200) + 0x18);
          iVar16 = 0;
          iVar17 = 0;
          do {
            iVar16 = iVar16 + 1;
            iVar15 = iVar17 + 1;
            *puVar6 = *(undefined2 *)((int)puVar11 + -0x16);
            puVar6[1] = *(undefined2 *)(puVar11 + -5);
            puVar13 = puVar6 + 3;
            puVar6[2] = *(undefined2 *)((int)puVar11 + -0x12);
            uVar1 = *(ushort *)((int)puVar11 + -0x16);
            uVar2 = *(ushort *)(puVar11 + -6);
            *(undefined4 *)((int)pvVar5 + (uint)uVar1 * 8) = puVar11[-2];
            *(undefined4 *)((int)pvVar5 + (uint)uVar1 * 8 + 4) = puVar11[-1];
            uVar3 = *(ushort *)(puVar11 + -5);
            *(undefined4 *)((int)pvVar5 + (uint)uVar3 * 8) = *puVar11;
            *(undefined4 *)((int)pvVar5 + (uint)uVar3 * 8 + 4) = puVar11[1];
            uVar3 = *(ushort *)((int)puVar11 + -0x12);
            *(undefined4 *)((int)pvVar5 + (uint)uVar3 * 8) = puVar11[2];
            *(undefined4 *)((int)pvVar5 + (uint)uVar3 * 8 + 4) = puVar11[3];
            if ((uVar2 & 0x80) == 0) {
              puVar6[3] = uVar1;
              iVar15 = iVar17 + 2;
              puVar6[4] = *(undefined2 *)((int)puVar11 + -0x12);
              puVar13 = puVar6 + 6;
              puVar6[5] = *(undefined2 *)(puVar11 + -4);
              uVar1 = *(ushort *)((int)puVar11 + -0x16);
              *(undefined4 *)((int)pvVar5 + (uint)uVar1 * 8) = puVar11[-2];
              *(undefined4 *)((int)pvVar5 + (uint)uVar1 * 8 + 4) = puVar11[-1];
              uVar1 = *(ushort *)((int)puVar11 + -0x12);
              *(undefined4 *)((int)pvVar5 + (uint)uVar1 * 8) = puVar11[2];
              *(undefined4 *)((int)pvVar5 + (uint)uVar1 * 8 + 4) = puVar11[3];
              uVar1 = *(ushort *)(puVar11 + -4);
              *(undefined4 *)((int)pvVar5 + (uint)uVar1 * 8) = puVar11[4];
              *(undefined4 *)((int)pvVar5 + (uint)uVar1 * 8 + 4) = puVar11[5];
            }
            puVar11 = puVar11 + 0xc;
            puVar6 = puVar13;
            iVar17 = iVar15;
          } while (iVar16 != iVar7);
          iVar7 = iVar15 * 3;
          sVar14 = iVar15 * 6;
        }
        iVar17 = *(int *)(this + 0xa0);
        iVar16 = RShellMemoryMalloc(0x5c,(char *)(iVar12 + DAT_0002db08));
        __n = iVar17 << 3;
        pcVar9 = (char *)(iVar12 + DAT_0002db0c);
        *(int *)(this + 0x10c) = iVar16;
        *(int *)(iVar16 + 0xc) = iVar17;
        uVar8 = RShellMemoryMalloc(__n,pcVar9);
        *(undefined4 *)(iVar16 + 0x10) = uVar8;
        memcpy(*(void **)(*(int *)(this + 0x10c) + 0x10),pvVar5,__n);
        iVar16 = DAT_0002db10;
        iVar17 = *(int *)(this + 0x10c);
        *(int *)(iVar17 + 0x14) = iVar7;
        uVar8 = RShellMemoryMalloc(sVar14,(char *)(iVar12 + iVar16));
        iVar12 = *(int *)(this + 0x10c);
        *(undefined4 *)(iVar17 + 0x18) = uVar8;
        memcpy(*(void **)(iVar12 + 0x18),__src_00,sVar14);
        pvVar5 = *(void **)(this + 200);
        uVar10 = *(uint *)this;
        **(undefined4 **)(this + 0x10c) = *(undefined4 *)((int)pvVar5 + 0xc);
        if ((uVar10 & 0x200000) != 0) {
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
