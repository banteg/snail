/*
 * mangled: _ZN8cRObject4LoadEPc
 * demangled: cRObject::Load(char*)
 * address: 000133d8
 * size: 3216
 */

/* cRObject::Load(char*) */

void __thiscall cRObject::Load(cRObject *this,char *param_1)

{
  uint uVar1;
  undefined *puVar2;
  uint *puVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  undefined2 *puVar6;
  size_t sVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  uint *puVar11;
  int iVar12;
  undefined4 uVar13;
  uint uVar14;
  uint uVar15;
  int iVar16;
  undefined4 *puVar17;
  uint *puVar18;
  uint uVar19;
  int iVar20;
  bool bVar21;
  uint in_fpscr;
  float fVar22;
  char acStack_820 [2048];

  uVar14 = *(uint *)this;
  puVar3 = (uint *)RShellMemoryScratch();
  RShellLoadFile(param_1,puVar3,(int *)0x0);
  _sprintf((char *)(this + 0x20),param_1);
LAB_00013428:
  do {
    puVar18 = puVar3;
    puVar3 = puVar18 + 1;
    uVar8 = *puVar18;
    switch(uVar8) {
    case 0:
      uVar8 = *puVar3;
      *(uint *)this = uVar8 | 0x2000000;
      *(uint *)(this + 0xa0) = puVar18[2];
      puVar3 = puVar18 + 3;
      if ((uVar14 & 0x1000) != 0) {
        *(uint *)this = uVar8 | 0x2001000;
      }
      goto LAB_00013428;
    case 1:
      if ((*(uint *)this & 0x1000) == 0) {
        uVar4 = RShellMemoryMalloc(*(int *)(this + 0xa0) * 0xc,"Object Vertex List");
        *(undefined4 *)(this + 0xa4) = uVar4;
      }
      else {
        uVar4 = RShellMemoryMalloc(*(int *)(this + 0xa0) * 6,"Object Vertex List");
        *(undefined4 *)(this + 0xa4) = uVar4;
      }
      if (0 < *(int *)(this + 0xa0)) {
        iVar9 = 0;
        puVar18 = (uint *)((int)puVar18 + 10);
        iVar20 = iVar9;
        do {
          puVar3 = puVar18;
          if ((*(uint *)this & 0x1000) == 0) {
            iVar16 = iVar9 * 2;
            fVar22 = (float)VectorSignedToFloat((int)*(short *)((int)puVar3 + -6),
                                                (byte)(in_fpscr >> 0x16) & 3);
            *(float *)(*(int *)(this + 0xa4) + iVar16) = fVar22 * 0.0078125;
            fVar22 = (float)VectorSignedToFloat((int)(short)puVar3[-1],(byte)(in_fpscr >> 0x16) & 3)
            ;
            *(float *)(*(int *)(this + 0xa4) + iVar16 + 4) = fVar22 * 0.0078125;
            fVar22 = (float)VectorSignedToFloat((int)*(short *)((int)puVar3 + -2),
                                                (byte)(in_fpscr >> 0x16) & 3);
            *(float *)(*(int *)(this + 0xa4) + iVar16 + 8) = fVar22 * 0.0078125;
          }
          else {
            *(short *)(*(int *)(this + 0xa4) + iVar9) = *(short *)((int)puVar3 + -6);
            *(short *)(*(int *)(this + 0xa4) + iVar9 + 2) = (short)puVar3[-1];
            *(short *)(*(int *)(this + 0xa4) + iVar9 + 4) = *(short *)((int)puVar3 + -2);
          }
          iVar20 = iVar20 + 1;
          iVar9 = iVar9 + 6;
          puVar18 = (uint *)((int)puVar3 + 6);
        } while (iVar20 < *(int *)(this + 0xa0));
      }
      goto LAB_00013428;
    case 2:
      uVar19 = *puVar3;
      if (uVar19 == 0) {
        *(undefined4 *)(this + 0xc0) = 0;
        puVar3 = puVar18 + 2;
        goto LAB_00013428;
      }
      uVar15 = *(uint *)(this + 0xc4);
      bVar21 = uVar15 == 0;
      uVar1 = uVar15;
      if (0 < (int)uVar15) {
        uVar1 = uVar19 - uVar15;
        bVar21 = uVar19 == uVar15;
      }
      if (bVar21 || (int)uVar1 < 0 != (0 < (int)uVar15 && SBORROW4(uVar19,uVar15))) {
        if (*(int *)(this + 0xc0) == 0) goto LAB_0001348c;
      }
      else {
        RShellError("Reallocation of FaceQuads impending\n");
        RShellMemoryFree(*(void **)(this + 200));
        *(undefined4 *)(this + 0xc0) = 0;
LAB_0001348c:
        uVar4 = RShellMemoryMalloc(uVar19 * 0x30,"Object FaceQuad List");
        if (*(int *)(this + 0xc4) < (int)uVar19) {
          *(uint *)(this + 0xc4) = uVar19;
        }
        *(undefined4 *)(this + 200) = uVar4;
      }
      *(uint *)(this + 0xc0) = uVar19;
      puVar3 = puVar18 + 2;
      if (0 < (int)uVar19) {
        iVar9 = 0;
        iVar20 = 0;
        puVar18 = puVar18 + 10;
        do {
          puVar3 = puVar18;
          *(short *)(*(int *)(this + 200) + iVar20) = (short)puVar3[-8];
          iVar16 = *(int *)(this + 200);
          iVar9 = iVar9 + 1;
          uVar4 = cRTextures::Add((cRTextures *)PTR__gTextureList_001b61d0,
                                  acStack_820 + puVar3[-7] * 0x40,(cTgaHeader *)0x0,0);
          *(undefined4 *)(iVar20 + iVar16 + 0xc) = uVar4;
          fVar22 = (float)VectorSignedToFloat((int)(short)puVar3[-6],(byte)(in_fpscr >> 0x16) & 3);
          *(float *)(*(int *)(this + 200) + iVar20 + 0x10) = fVar22 * 0.0078125;
          fVar22 = (float)VectorSignedToFloat((int)*(short *)((int)puVar3 + -0x16),
                                              (byte)(in_fpscr >> 0x16) & 3);
          *(float *)(*(int *)(this + 200) + iVar20 + 0x18) = fVar22 * 0.0078125;
          fVar22 = (float)VectorSignedToFloat((int)(short)puVar3[-5],(byte)(in_fpscr >> 0x16) & 3);
          *(float *)(*(int *)(this + 200) + iVar20 + 0x20) = fVar22 * 0.0078125;
          fVar22 = (float)VectorSignedToFloat((int)*(short *)((int)puVar3 + -0x12),
                                              (byte)(in_fpscr >> 0x16) & 3);
          *(float *)(*(int *)(this + 200) + iVar20 + 0x28) = fVar22 * 0.0078125;
          fVar22 = (float)VectorSignedToFloat((int)(short)puVar3[-4],(byte)(in_fpscr >> 0x16) & 3);
          *(float *)(*(int *)(this + 200) + iVar20 + 0x14) = fVar22 * 0.0078125;
          fVar22 = (float)VectorSignedToFloat((int)*(short *)((int)puVar3 + -0xe),
                                              (byte)(in_fpscr >> 0x16) & 3);
          *(float *)(*(int *)(this + 200) + iVar20 + 0x1c) = fVar22 * 0.0078125;
          fVar22 = (float)VectorSignedToFloat((int)(short)puVar3[-3],(byte)(in_fpscr >> 0x16) & 3);
          *(float *)(*(int *)(this + 200) + iVar20 + 0x24) = fVar22 * 0.0078125;
          fVar22 = (float)VectorSignedToFloat((int)*(short *)((int)puVar3 + -10),
                                              (byte)(in_fpscr >> 0x16) & 3);
          *(float *)(*(int *)(this + 200) + iVar20 + 0x2c) = fVar22 * 0.0078125;
          *(short *)(*(int *)(this + 200) + iVar20 + 2) = (short)puVar3[-2];
          *(short *)(*(int *)(this + 200) + iVar20 + 4) = *(short *)((int)puVar3 + -6);
          *(short *)(*(int *)(this + 200) + iVar20 + 6) = (short)puVar3[-1];
          iVar16 = *(int *)(this + 200) + iVar20;
          iVar20 = iVar20 + 0x30;
          *(short *)(iVar16 + 8) = *(short *)((int)puVar3 + -2);
          puVar18 = puVar3 + 8;
        } while (iVar9 < *(int *)(this + 0xc0));
      }
      break;
    case 3:
      puVar18 = puVar18 + 2;
      uVar8 = *puVar3;
      if (0 < (int)uVar8) {
        uVar19 = 0;
        do {
          Rstrcpy(acStack_820 + uVar19 * 0x40,(char *)puVar18);
          sVar7 = _strlen((char *)puVar18);
          uVar19 = uVar19 + 1;
          puVar18 = (uint *)((int)puVar18 + sVar7 + 1);
        } while (uVar19 != uVar8);
      }
      puVar3 = (uint *)((4U - (int)puVar18 & 3) + (int)puVar18);
      goto LAB_00013428;
    case 4:
      if ((*(uint *)this & 0x1000) == 0) {
        uVar4 = RShellMemoryMalloc(*(int *)(this + 0xa0) * 0xc,"Object Vertex List");
        *(undefined4 *)(this + 0xa8) = uVar4;
      }
      else {
        uVar4 = RShellMemoryMalloc(*(int *)(this + 0xa0) * 6,"Object Vertex List");
        *(undefined4 *)(this + 0xa8) = uVar4;
      }
      if ((*(uint *)this & 0x1000) == 0) {
        if (0 < *(int *)(this + 0xa0)) {
          iVar20 = 0;
          iVar9 = 0;
          do {
            iVar20 = iVar20 + 1;
            puVar5 = (undefined4 *)(iVar9 + *(int *)(this + 0xa4));
            puVar17 = (undefined4 *)(iVar9 + *(int *)(this + 0xa8));
            uVar4 = puVar5[1];
            uVar13 = puVar5[2];
            iVar9 = iVar9 + 0xc;
            *puVar17 = *puVar5;
            puVar17[1] = uVar4;
            puVar17[2] = uVar13;
          } while (iVar20 < *(int *)(this + 0xa0));
        }
      }
      else if (0 < *(int *)(this + 0xa0)) {
        iVar9 = 0;
        iVar20 = iVar9;
        do {
          _memcpy((void *)(*(int *)(this + 0xa8) + iVar9),(void *)(*(int *)(this + 0xa4) + iVar9),6)
          ;
          iVar20 = iVar20 + 1;
          iVar9 = iVar9 + 6;
        } while (iVar20 < *(int *)(this + 0xa0));
      }
      puVar6 = (undefined2 *)RShellMemoryMalloc(0x18,"Object Animation");
      *(undefined2 **)(this + 0x104) = puVar6;
      *puVar6 = (short)*puVar3;
      *(uint *)(*(int *)(this + 0x104) + 4) = puVar18[2];
      *(uint *)(*(int *)(this + 0x104) + 8) = puVar18[3];
      *(uint *)(*(int *)(this + 0x104) + 0x10) = puVar18[4];
      *(uint *)(*(int *)(this + 0x104) + 0x14) = puVar18[5];
      iVar20 = *(int *)(this + 0x104);
      *(uint *)(this + 0xd0) = puVar18[6];
      uVar4 = RShellMemoryMalloc(*(int *)(iVar20 + 4) << 2,"Object Animation Frame array");
      *(undefined4 *)(iVar20 + 0xc) = uVar4;
      iVar20 = *(int *)(this + 0x104);
      puVar3 = puVar18 + 7;
      if (0 < *(int *)(iVar20 + 4)) {
        iVar9 = 0;
        puVar18 = puVar18 + 7;
        do {
          iVar16 = *(int *)(iVar20 + 0xc);
          uVar4 = RShellMemoryMalloc(0xc,"Object Animation Frame");
          iVar20 = iVar9 * 4;
          *(undefined4 *)(iVar16 + iVar9 * 4) = uVar4;
          puVar3 = puVar18;
          if ((*(uint *)this & 0x1000) == 0) {
            puVar5 = *(undefined4 **)(*(int *)(*(int *)(this + 0x104) + 0xc) + iVar9 * 4);
            uVar4 = RShellMemoryMalloc(*(int *)(this + 0xa0) * 0xc,"Anim Frame Vertices");
            *puVar5 = uVar4;
            if (0 < *(int *)(this + 0xa0)) {
              iVar16 = 0;
              iVar10 = 0;
              do {
                iVar10 = iVar10 + 1;
                fVar22 = (float)VectorSignedToFloat((int)(short)*puVar3,(byte)(in_fpscr >> 0x16) & 3
                                                   );
                *(float *)(iVar16 + **(int **)(iVar20 + *(int *)(*(int *)(this + 0x104) + 0xc))) =
                     fVar22 * 0.0078125;
                fVar22 = (float)VectorSignedToFloat((int)*(short *)((int)puVar3 + 2),
                                                    (byte)(in_fpscr >> 0x16) & 3);
                *(float *)(iVar16 + **(int **)(iVar20 + *(int *)(*(int *)(this + 0x104) + 0xc)) + 4)
                     = fVar22 * 0.0078125;
                iVar12 = iVar16 + **(int **)(iVar20 + *(int *)(*(int *)(this + 0x104) + 0xc));
                puVar18 = puVar3 + 1;
                iVar16 = iVar16 + 0xc;
                puVar3 = (uint *)((int)puVar3 + 6);
                fVar22 = (float)VectorSignedToFloat((int)(short)*puVar18,
                                                    (byte)(in_fpscr >> 0x16) & 3);
                *(float *)(iVar12 + 8) = fVar22 * 0.0078125;
              } while (iVar10 < *(int *)(this + 0xa0));
            }
          }
          else {
            puVar5 = *(undefined4 **)(*(int *)(*(int *)(this + 0x104) + 0xc) + iVar9 * 4);
            uVar4 = RShellMemoryMalloc(*(int *)(this + 0xa0) * 6,"Anim Frame Vertices");
            *puVar5 = uVar4;
            if (0 < *(int *)(this + 0xa0)) {
              iVar16 = 0;
              puVar11 = puVar18;
              do {
                iVar16 = iVar16 + 1;
                *(short *)((int)puVar11 +
                          (**(int **)(iVar20 + *(int *)(*(int *)(this + 0x104) + 0xc)) -
                          (int)puVar18)) = (short)*puVar11;
                *(short *)((int)puVar11 +
                          (**(int **)(iVar20 + *(int *)(*(int *)(this + 0x104) + 0xc)) -
                          (int)puVar18) + 2) = *(short *)((int)puVar11 + 2);
                puVar3 = (uint *)((int)puVar11 + 6);
                *(short *)((int)puVar11 +
                          (**(int **)(iVar20 + *(int *)(*(int *)(this + 0x104) + 0xc)) -
                          (int)puVar18) + 4) = (short)puVar11[1];
                puVar11 = puVar3;
              } while (iVar16 < *(int *)(this + 0xa0));
            }
          }
          iVar16 = *(int *)(iVar20 + *(int *)(*(int *)(this + 0x104) + 0xc));
          uVar4 = RShellMemoryMalloc(*(int *)(this + 0xd0) << 2,"Anim Facequad Normals");
          *(undefined4 *)(iVar16 + 8) = uVar4;
          puVar2 = PTR__gObjectList_001b61cc;
          if (0 < *(int *)(this + 0xd0)) {
            iVar16 = 0;
            puVar18 = puVar3;
            do {
              puVar3 = puVar18 + 1;
              *(uint *)(*(int *)(*(int *)(iVar20 + *(int *)(*(int *)(this + 0x104) + 0xc)) + 8) +
                       iVar16 * 4) = *(int *)(puVar2 + 0x10) + *puVar18 * 0xc;
              iVar16 = iVar16 + 1;
              puVar18 = puVar3;
            } while (iVar16 < *(int *)(this + 0xd0));
          }
          iVar20 = *(int *)(this + 0x104);
          iVar9 = iVar9 + 1;
          puVar18 = puVar3;
        } while (iVar9 < *(int *)(iVar20 + 4));
      }
      break;
    case 5:
      puVar5 = (undefined4 *)RShellMemoryMalloc(0x5c,"Obj Vertex array");
      *(undefined4 **)(this + 0x10c) = puVar5;
      uVar4 = cRTextures::Add((cRTextures *)PTR__gTextureList_001b61d0,acStack_820,(cTgaHeader *)0x0
                              ,0);
      *puVar5 = uVar4;
      puVar11 = puVar18 + 2;
      *(uint *)(*(int *)(this + 0x10c) + 4) = *puVar3;
      if ((*(uint *)this & 0x1000) == 0) {
        iVar20 = *(int *)(this + 0x10c);
        uVar4 = RShellMemoryMalloc(*(int *)(iVar20 + 4) * 0x14,"Obj VertexUV");
        *(undefined4 *)(iVar20 + 8) = uVar4;
      }
      else {
        iVar20 = *(int *)(this + 0x10c);
        uVar4 = RShellMemoryMalloc(*(int *)(iVar20 + 4) * 10,"Obj VertexUV");
        *(undefined4 *)(iVar20 + 8) = uVar4;
      }
      iVar20 = *(int *)(this + 0x10c);
      if (0 < *(int *)(iVar20 + 4)) {
        iVar16 = 0;
        puVar3 = (uint *)((int)puVar18 + 0x12);
        iVar9 = iVar16;
        do {
          while (puVar11 = puVar3, (*(uint *)this & 0x1000) == 0) {
            iVar10 = iVar16 * 2;
            iVar9 = iVar9 + 1;
            iVar16 = iVar16 + 10;
            fVar22 = (float)VectorSignedToFloat((int)*(short *)((int)puVar11 + -10),
                                                (byte)(in_fpscr >> 0x16) & 3);
            *(float *)(*(int *)(iVar20 + 8) + iVar10) = fVar22 * 0.0078125;
            fVar22 = (float)VectorSignedToFloat((int)(short)puVar11[-2],(byte)(in_fpscr >> 0x16) & 3
                                               );
            *(float *)(*(int *)(*(int *)(this + 0x10c) + 8) + iVar10 + 4) = fVar22 * 0.0078125;
            fVar22 = (float)VectorSignedToFloat((int)*(short *)((int)puVar11 + -6),
                                                (byte)(in_fpscr >> 0x16) & 3);
            *(float *)(*(int *)(*(int *)(this + 0x10c) + 8) + iVar10 + 8) = fVar22 * 0.0078125;
            fVar22 = (float)VectorSignedToFloat((int)(short)puVar11[-1],(byte)(in_fpscr >> 0x16) & 3
                                               );
            *(float *)(*(int *)(*(int *)(this + 0x10c) + 8) + iVar10 + 0xc) = fVar22 * 0.0078125;
            fVar22 = (float)VectorSignedToFloat((int)*(short *)((int)puVar11 + -2),
                                                (byte)(in_fpscr >> 0x16) & 3);
            *(float *)(*(int *)(*(int *)(this + 0x10c) + 8) + iVar10 + 0x10) = fVar22 * 0.0078125;
            iVar20 = *(int *)(this + 0x10c);
            puVar3 = (uint *)((int)puVar11 + 10);
            if (*(int *)(iVar20 + 4) <= iVar9) goto LAB_000139b8;
          }
          iVar9 = iVar9 + 1;
          *(short *)(*(int *)(iVar20 + 8) + iVar16) = *(short *)((int)puVar11 + -10);
          *(short *)(*(int *)(*(int *)(this + 0x10c) + 8) + iVar16 + 2) = (short)puVar11[-2];
          *(short *)(*(int *)(*(int *)(this + 0x10c) + 8) + iVar16 + 4) =
               *(short *)((int)puVar11 + -6);
          *(short *)(*(int *)(*(int *)(this + 0x10c) + 8) + iVar16 + 6) = (short)puVar11[-1];
          iVar20 = *(int *)(*(int *)(this + 0x10c) + 8) + iVar16;
          iVar16 = iVar16 + 10;
          *(short *)(iVar20 + 8) = *(short *)((int)puVar11 + -2);
          iVar20 = *(int *)(this + 0x10c);
          puVar3 = (uint *)((int)puVar11 + 10);
        } while (iVar9 < *(int *)(iVar20 + 4));
      }
LAB_000139b8:
      puVar3 = puVar11 + 1;
      *(uint *)(iVar20 + 0xc) = *puVar11;
      iVar20 = *(int *)(this + 0x10c);
      uVar4 = RShellMemoryMalloc(*(int *)(iVar20 + 0xc) << 3,"Obj UV");
      *(undefined4 *)(iVar20 + 0x10) = uVar4;
      iVar20 = *(int *)(this + 0x10c);
      if (0 < *(int *)(iVar20 + 0xc)) {
        iVar9 = 0;
        puVar18 = puVar11 + 2;
        do {
          while (puVar3 = puVar18, (*(uint *)this & 0x1000) == 0) {
            iVar16 = iVar9 * 8;
            iVar9 = iVar9 + 1;
            fVar22 = (float)VectorSignedToFloat((int)(short)puVar3[-1],(byte)(in_fpscr >> 0x16) & 3)
            ;
            *(float *)(*(int *)(iVar20 + 0x10) + iVar16) = fVar22 * 0.0078125;
            fVar22 = (float)VectorSignedToFloat((int)*(short *)((int)puVar3 + -2),
                                                (byte)(in_fpscr >> 0x16) & 3);
            *(float *)(*(int *)(*(int *)(this + 0x10c) + 0x10) + iVar16 + 4) = fVar22 * 0.0078125;
            iVar20 = *(int *)(this + 0x10c);
            puVar18 = puVar3 + 1;
            if (*(int *)(iVar20 + 0xc) <= iVar9) goto LAB_00013aa4;
          }
          iVar16 = iVar9 * 4;
          iVar9 = iVar9 + 1;
          *(short *)(*(int *)(iVar20 + 0x10) + iVar16) = (short)puVar3[-1];
          *(short *)(*(int *)(*(int *)(this + 0x10c) + 0x10) + iVar16 + 2) =
               *(short *)((int)puVar3 + -2);
          iVar20 = *(int *)(this + 0x10c);
          puVar18 = puVar3 + 1;
        } while (iVar9 < *(int *)(iVar20 + 0xc));
      }
LAB_00013aa4:
      puVar18 = puVar3 + 1;
      *(uint *)(iVar20 + 0x14) = *puVar3;
      iVar20 = *(int *)(this + 0x10c);
      uVar4 = RShellMemoryMalloc(*(int *)(iVar20 + 0x14) << 1,"Vertex Index Array");
      *(undefined4 *)(iVar20 + 0x18) = uVar4;
      iVar20 = *(int *)(this + 0x10c);
      if (0 < *(int *)(iVar20 + 0x14)) {
        iVar9 = 0;
        puVar3 = puVar3 + 2;
        do {
          puVar18 = puVar3;
          iVar16 = iVar9 * 2;
          iVar9 = iVar9 + 1;
          *(short *)(iVar16 + *(int *)(iVar20 + 0x18)) = (short)puVar18[-1];
          iVar20 = *(int *)(this + 0x10c);
          puVar3 = puVar18 + 1;
        } while (iVar9 < *(int *)(iVar20 + 0x14));
      }
      *(uint *)(iVar20 + 0x44) = *puVar18;
      iVar20 = *(int *)(this + 0x10c);
      uVar4 = RShellMemoryMalloc(*(int *)(iVar20 + 0x44) << 1,"Vertex Strip Index Array");
      *(undefined4 *)(iVar20 + 0x48) = uVar4;
      iVar20 = *(int *)(this + 0x10c);
      puVar3 = puVar18 + 1;
      if (0 < *(int *)(iVar20 + 0x44)) {
        iVar9 = 0;
        puVar18 = puVar18 + 2;
        do {
          puVar3 = puVar18;
          iVar16 = iVar9 * 2;
          iVar9 = iVar9 + 1;
          *(short *)(iVar16 + *(int *)(iVar20 + 0x48)) = (short)puVar3[-1];
          iVar20 = *(int *)(this + 0x10c);
          puVar18 = puVar3 + 1;
        } while (iVar9 < *(int *)(iVar20 + 0x44));
      }
      goto LAB_00013428;
    case 6:
      uVar8 = *puVar3;
      *(uint *)(this + 0xe4) = uVar8;
      uVar4 = RShellMemoryMalloc(uVar8 * 10,"Toon Edges");
      *(undefined4 *)(this + 0xe8) = uVar4;
      uVar4 = RShellMemoryMalloc(*(int *)(this + 0xe4) << 2,"Object Edge Index Array");
      *(undefined4 *)(this + 0xe0) = uVar4;
      puVar3 = puVar18 + 2;
      if (0 < *(int *)(this + 0xe4)) {
        iVar20 = 0;
        iVar9 = 0;
        puVar18 = puVar18 + 7;
        do {
          puVar3 = puVar18;
          iVar20 = iVar20 + 1;
          *(short *)(iVar9 + *(int *)(this + 0xe8)) = (short)puVar3[-5];
          *(short *)(iVar9 + *(int *)(this + 0xe8) + 6) = (short)puVar3[-4];
          *(short *)(iVar9 + *(int *)(this + 0xe8) + 8) = (short)puVar3[-3];
          *(short *)(iVar9 + *(int *)(this + 0xe8) + 2) = (short)puVar3[-2];
          iVar16 = iVar9 + *(int *)(this + 0xe8);
          iVar9 = iVar9 + 10;
          *(short *)(iVar16 + 4) = (short)puVar3[-1];
          puVar18 = puVar3 + 5;
        } while (iVar20 < *(int *)(this + 0xe4));
      }
      goto LAB_00013428;
    case 7:
      uVar4 = RShellMemoryMalloc(*(int *)(this + 0xa0) << 4,"Object Vertex Colour List");
      *(undefined4 *)(this + 0xb4) = uVar4;
      if (0 < *(int *)(this + 0xa0)) {
        iVar20 = 0;
        puVar18 = puVar18 + 5;
        do {
          puVar3 = puVar18;
          iVar9 = iVar20 * 0x10;
          iVar20 = iVar20 + 1;
          *(uint *)(*(int *)(this + 0xb4) + iVar9) = puVar3[-4];
          *(uint *)(*(int *)(this + 0xb4) + iVar9 + 4) = puVar3[-3];
          *(uint *)(*(int *)(this + 0xb4) + iVar9 + 8) = puVar3[-2];
          *(uint *)(*(int *)(this + 0xb4) + iVar9 + 0xc) = puVar3[-1];
          puVar18 = puVar3 + 4;
        } while (iVar20 < *(int *)(this + 0xa0));
      }
      goto LAB_00013428;
    }
    if (uVar8 == 8) {
      return;
    }
  } while( true );
}
