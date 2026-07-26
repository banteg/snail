/*
 * mangled: _ZN8cRObject19CalcFaceQuadNormalsEv
 * demangled: cRObject::CalcFaceQuadNormals()
 * address: 0002ffb0
 * size: 812
 */

/* cRObject::CalcFaceQuadNormals() */

void __thiscall cRObject::CalcFaceQuadNormals(cRObject *this)

{
  ushort *puVar1;
  ushort *puVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  ushort *puVar7;
  float *pfVar8;
  int iVar9;
  float *pfVar10;
  float *pfVar11;
  int local_60;
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  undefined4 local_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;

  RequestFaceQuadNormals(this);
  iVar5 = *(int *)(this + 0x10c);
  puVar2 = *(ushort **)(iVar5 + 0x18);
  if ((*(uint *)this & 0x200000) == 0) {
    wprintf("CFQN GLVertexArray->IndexArrayCount/3=%i\n",*(int *)(iVar5 + 0x14) % 3);
    if (2 < *(int *)(*(int *)(this + 0x10c) + 0x14)) {
      iVar5 = 0;
      do {
        iVar4 = *(int *)(this + 0xa4);
        puVar7 = puVar2 + 2;
        pfVar10 = (float *)(iVar4 + (uint)puVar2[1] * 0xc);
        pfVar11 = (float *)(iVar4 + (uint)*puVar2 * 0xc);
        local_40 = *pfVar10 - *pfVar11;
        puVar2 = puVar2 + 3;
        pfVar8 = (float *)(iVar4 + (uint)*puVar7 * 0xc);
        local_3c = pfVar10[1] - pfVar11[1];
        local_38 = pfVar10[2] - pfVar11[2];
        local_4c = *pfVar8 - *pfVar11;
        local_48 = pfVar8[1] - pfVar11[1];
        local_44 = pfVar8[2] - pfVar11[2];
        tVector::Cross((tVector *)&local_34,(tVector *)&local_40,(tVector *)&local_4c);
        tVector::Normalize((tVector *)&local_34);
        iVar6 = *(int *)(this + 0xcc);
        uVar3 = cRObjects::AddNormal(gObjectList,local_34,uStack_30,uStack_2c);
        iVar4 = *(int *)(*(int *)(this + 0x10c) + 0x14);
        *(undefined4 *)(iVar6 + iVar5 * 4) = uVar3;
        iVar5 = iVar5 + 1;
      } while (iVar5 < iVar4 / 3);
    }
  }
  else {
    iVar4 = *(int *)(this + 0x104);
    if (0 < *(int *)(iVar4 + 4)) {
      local_60 = 0;
      do {
        *(undefined4 *)(this + 0xa4) = **(undefined4 **)(*(int *)(iVar4 + 0xc) + local_60 * 4);
        iVar6 = *(int *)(*(int *)(iVar4 + 0xc) + local_60 * 4);
        uVar3 = RShellMemoryMalloc((uint)(*(int *)(iVar5 + 0x14) << 2) / 3,"Anim Face Quand Normals"
                                  );
        iVar5 = *(int *)(this + 0x10c);
        iVar4 = *(int *)(iVar5 + 0x14);
        *(undefined4 *)(iVar6 + 8) = uVar3;
        if (2 < iVar4) {
          iVar4 = 0;
          puVar7 = puVar2;
          do {
            iVar5 = *(int *)(this + 0xa4);
            puVar1 = puVar7 + 2;
            pfVar10 = (float *)(iVar5 + (uint)puVar7[1] * 0xc);
            pfVar11 = (float *)(iVar5 + (uint)*puVar7 * 0xc);
            local_40 = *pfVar10 - *pfVar11;
            puVar7 = puVar7 + 3;
            pfVar8 = (float *)(iVar5 + (uint)*puVar1 * 0xc);
            local_3c = pfVar10[1] - pfVar11[1];
            local_38 = pfVar10[2] - pfVar11[2];
            local_4c = *pfVar8 - *pfVar11;
            local_48 = pfVar8[1] - pfVar11[1];
            local_44 = pfVar8[2] - pfVar11[2];
            tVector::Cross((tVector *)&local_34,(tVector *)&local_40,(tVector *)&local_4c);
            tVector::Normalize((tVector *)&local_34);
            iVar9 = *(int *)(*(int *)(*(int *)(*(int *)(this + 0x104) + 0xc) + local_60 * 4) + 8);
            uVar3 = cRObjects::AddNormal(gObjectList,local_34,uStack_30,uStack_2c);
            iVar5 = *(int *)(this + 0x10c);
            iVar6 = *(int *)(iVar5 + 0x14);
            *(undefined4 *)(iVar9 + iVar4 * 4) = uVar3;
            iVar4 = iVar4 + 1;
          } while (iVar4 < iVar6 / 3);
        }
        iVar4 = *(int *)(this + 0x104);
        local_60 = local_60 + 1;
      } while (local_60 < *(int *)(iVar4 + 4));
    }
  }
  return;
}
