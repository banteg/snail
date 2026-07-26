/*
 * mangled: _ZN8cRObject19CalcFaceQuadNormalsEv
 * demangled: cRObject::CalcFaceQuadNormals()
 * address: 00014400
 * size: 1316
 */

/* cRObject::CalcFaceQuadNormals() */

void __thiscall cRObject::CalcFaceQuadNormals(cRObject *this)

{
  undefined *puVar1;
  undefined4 uVar2;
  float fVar3;
  int iVar4;
  float *pfVar5;
  ushort *puVar6;
  int iVar7;
  float *pfVar8;
  undefined4 *puVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  ushort *puVar13;
  int local_58;
  int local_54;
  undefined4 local_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  undefined4 local_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;

  if (*(int *)(this + 0xcc) == 0) {
    *(int *)(this + 0xd0) = *(int *)(*(int *)(this + 0x10c) + 0x14) / 3;
    uVar2 = RShellMemoryMalloc((*(int *)(*(int *)(this + 0x10c) + 0x14) / 3) * 4,
                               "Object FaceQuad Normals List");
    *(undefined4 *)(this + 0xcc) = uVar2;
  }
  iVar4 = *(int *)(this + 0x10c);
  puVar6 = *(ushort **)(iVar4 + 0x18);
  if ((*(uint *)this & 0x200000) == 0) {
    wprintf("CFQN GLVertexArray->IndexArrayCount/3=%i\n",*(int *)(iVar4 + 0x14) % 3);
    if (0 < *(int *)(*(int *)(this + 0x10c) + 0x14) / 3) {
      iVar4 = 0;
      do {
        iVar7 = *(int *)(this + 0xa4);
        pfVar5 = (float *)(iVar7 + (uint)puVar6[1] * 0xc);
        pfVar8 = (float *)(iVar7 + (uint)*puVar6 * 0xc);
        local_38 = *pfVar5 - *pfVar8;
        local_34 = pfVar5[1] - pfVar8[1];
        local_30 = pfVar5[2] - pfVar8[2];
        pfVar5 = (float *)(iVar7 + (uint)puVar6[2] * 0xc);
        pfVar8 = (float *)(iVar7 + (uint)*puVar6 * 0xc);
        local_44 = *pfVar5 - *pfVar8;
        local_40 = pfVar5[1] - pfVar8[1];
        local_3c = pfVar5[2] - pfVar8[2];
        tVector::Cross((tVector *)&local_2c,(tVector *)&local_38,(tVector *)&local_44);
        tVector::Normalize((tVector *)&local_2c);
        puVar1 = PTR__gObjectList_001b61cc;
        iVar7 = *(int *)(this + 0xcc);
        local_50 = local_2c;
        uStack_4c = uStack_28;
        uStack_48 = uStack_24;
        iVar12 = *(int *)(PTR__gObjectList_001b61cc + 0xc);
        if (0 < iVar12) {
          iVar11 = 0;
          iVar10 = 0;
          do {
            fVar3 = (float)tVector::Dot((tVector *)&local_50,
                                        (tVector *)(iVar10 + *(int *)(puVar1 + 0x10)));
            if (0.99 < fVar3) {
              iVar10 = iVar10 + *(int *)(puVar1 + 0x10);
              goto LAB_00014850;
            }
            iVar12 = *(int *)(puVar1 + 0xc);
            iVar11 = iVar11 + 1;
            iVar10 = iVar10 + 0xc;
          } while (iVar11 < iVar12);
        }
        puVar1 = PTR__gObjectList_001b61cc;
        puVar9 = (undefined4 *)(iVar12 * 0xc + *(int *)(PTR__gObjectList_001b61cc + 0x10));
        *puVar9 = local_50;
        puVar9[1] = uStack_4c;
        puVar9[2] = uStack_48;
        iVar12 = *(int *)(puVar1 + 0xc) + 1;
        *(int *)(puVar1 + 0xc) = iVar12;
        if (0x7ff < iVar12) {
          RShellError("Too Many Normals, increase ROBJECTS_NORMALTABLE_SIZE NormalNumber=%i (%i) \n"
                      ,iVar12,0x800);
        }
        iVar10 = *(int *)(puVar1 + 0x10) + -0xc + *(int *)(puVar1 + 0xc) * 0xc;
LAB_00014850:
        puVar6 = puVar6 + 3;
        *(int *)(iVar7 + iVar4 * 4) = iVar10;
        iVar4 = iVar4 + 1;
      } while (iVar4 < *(int *)(*(int *)(this + 0x10c) + 0x14) / 3);
    }
  }
  else {
    iVar7 = *(int *)(this + 0x104);
    if (0 < *(int *)(iVar7 + 4)) {
      local_58 = 0;
      do {
        *(undefined4 *)(this + 0xa4) = **(undefined4 **)(*(int *)(iVar7 + 0xc) + local_58 * 4);
        iVar7 = *(int *)(*(int *)(iVar7 + 0xc) + local_58 * 4);
        uVar2 = RShellMemoryMalloc((uint)(*(int *)(iVar4 + 0x14) << 2) / 3,"Anim Face Quand Normals"
                                  );
        *(undefined4 *)(iVar7 + 8) = uVar2;
        iVar4 = *(int *)(this + 0x10c);
        if (0 < *(int *)(iVar4 + 0x14) / 3) {
          local_54 = 0;
          puVar13 = puVar6;
          do {
            iVar4 = *(int *)(this + 0xa4);
            pfVar5 = (float *)(iVar4 + (uint)puVar13[1] * 0xc);
            pfVar8 = (float *)(iVar4 + (uint)*puVar13 * 0xc);
            local_38 = *pfVar5 - *pfVar8;
            local_34 = pfVar5[1] - pfVar8[1];
            local_30 = pfVar5[2] - pfVar8[2];
            pfVar5 = (float *)(iVar4 + (uint)puVar13[2] * 0xc);
            pfVar8 = (float *)(iVar4 + (uint)*puVar13 * 0xc);
            local_44 = *pfVar5 - *pfVar8;
            local_40 = pfVar5[1] - pfVar8[1];
            local_3c = pfVar5[2] - pfVar8[2];
            tVector::Cross((tVector *)&local_2c,(tVector *)&local_38,(tVector *)&local_44);
            tVector::Normalize((tVector *)&local_2c);
            puVar1 = PTR__gObjectList_001b61cc;
            iVar7 = *(int *)(*(int *)(*(int *)(*(int *)(this + 0x104) + 0xc) + local_58 * 4) + 8);
            local_50 = local_2c;
            uStack_4c = uStack_28;
            uStack_48 = uStack_24;
            iVar4 = *(int *)(PTR__gObjectList_001b61cc + 0xc);
            if (0 < iVar4) {
              iVar10 = 0;
              iVar12 = 0;
              do {
                fVar3 = (float)tVector::Dot((tVector *)&local_50,
                                            (tVector *)(iVar12 + *(int *)(puVar1 + 0x10)));
                if (0.99 < fVar3) {
                  iVar12 = iVar12 + *(int *)(puVar1 + 0x10);
                  goto LAB_00014610;
                }
                iVar4 = *(int *)(puVar1 + 0xc);
                iVar10 = iVar10 + 1;
                iVar12 = iVar12 + 0xc;
              } while (iVar10 < iVar4);
            }
            puVar1 = PTR__gObjectList_001b61cc;
            puVar9 = (undefined4 *)(iVar4 * 0xc + *(int *)(PTR__gObjectList_001b61cc + 0x10));
            *puVar9 = local_50;
            puVar9[1] = uStack_4c;
            puVar9[2] = uStack_48;
            iVar4 = *(int *)(puVar1 + 0xc) + 1;
            *(int *)(puVar1 + 0xc) = iVar4;
            if (0x7ff < iVar4) {
              RShellError("Too Many Normals, increase ROBJECTS_NORMALTABLE_SIZE NormalNumber=%i (%i) \n"
                          ,iVar4,0x800);
            }
            iVar12 = *(int *)(puVar1 + 0x10) + -0xc + *(int *)(puVar1 + 0xc) * 0xc;
LAB_00014610:
            puVar13 = puVar13 + 3;
            *(int *)(iVar7 + local_54 * 4) = iVar12;
            iVar4 = *(int *)(this + 0x10c);
            local_54 = local_54 + 1;
          } while (local_54 < *(int *)(iVar4 + 0x14) / 3);
        }
        iVar7 = *(int *)(this + 0x104);
        local_58 = local_58 + 1;
      } while (local_58 < *(int *)(iVar7 + 4));
    }
  }
  return;
}
