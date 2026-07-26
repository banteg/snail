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
  int iVar2;
  ushort *puVar3;
  undefined4 uVar4;
  char *pcVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  ushort *puVar9;
  float *pfVar10;
  int iVar11;
  int iVar12;
  float *pfVar13;
  float *pfVar14;
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

  iVar12 = DAT_000302dc;
  RequestFaceQuadNormals(this);
  iVar2 = DAT_000302e0;
  iVar7 = *(int *)(this + 0x10c);
  iVar12 = iVar12 + 0x2ffd4;
  puVar3 = *(ushort **)(iVar7 + 0x18);
  if ((*(uint *)this & 0x200000) == 0) {
    wprintf((char *)(iVar12 + DAT_000302e8),*(int *)(iVar7 + 0x14) % 3);
    iVar2 = DAT_000302e0;
    if (2 < *(int *)(*(int *)(this + 0x10c) + 0x14)) {
      iVar7 = 0;
      do {
        iVar6 = *(int *)(this + 0xa4);
        puVar9 = puVar3 + 2;
        pfVar13 = (float *)(iVar6 + (uint)puVar3[1] * 0xc);
        pfVar14 = (float *)(iVar6 + (uint)*puVar3 * 0xc);
        local_40 = *pfVar13 - *pfVar14;
        puVar3 = puVar3 + 3;
        pfVar10 = (float *)(iVar6 + (uint)*puVar9 * 0xc);
        local_3c = pfVar13[1] - pfVar14[1];
        local_38 = pfVar13[2] - pfVar14[2];
        local_4c = *pfVar10 - *pfVar14;
        local_48 = pfVar10[1] - pfVar14[1];
        local_44 = pfVar10[2] - pfVar14[2];
        tVector::Cross((tVector *)&local_34,(tVector *)&local_40,(tVector *)&local_4c);
        tVector::Normalize((tVector *)&local_34);
        iVar8 = *(int *)(this + 0xcc);
        uVar4 = cRObjects::AddNormal(*(undefined4 *)(iVar12 + iVar2),local_34,uStack_30,uStack_2c);
        iVar6 = *(int *)(*(int *)(this + 0x10c) + 0x14);
        *(undefined4 *)(iVar8 + iVar7 * 4) = uVar4;
        iVar7 = iVar7 + 1;
      } while (iVar7 < iVar6 / 3);
    }
  }
  else {
    iVar6 = *(int *)(this + 0x104);
    if (0 < *(int *)(iVar6 + 4)) {
      pcVar5 = (char *)(iVar12 + DAT_000302e4);
      local_60 = 0;
      do {
        *(undefined4 *)(this + 0xa4) = **(undefined4 **)(*(int *)(iVar6 + 0xc) + local_60 * 4);
        iVar8 = *(int *)(*(int *)(iVar6 + 0xc) + local_60 * 4);
        uVar4 = RShellMemoryMalloc((uint)(*(int *)(iVar7 + 0x14) << 2) / 3,pcVar5);
        iVar7 = *(int *)(this + 0x10c);
        iVar6 = *(int *)(iVar7 + 0x14);
        *(undefined4 *)(iVar8 + 8) = uVar4;
        if (2 < iVar6) {
          iVar6 = 0;
          puVar9 = puVar3;
          do {
            iVar7 = *(int *)(this + 0xa4);
            puVar1 = puVar9 + 2;
            pfVar13 = (float *)(iVar7 + (uint)puVar9[1] * 0xc);
            pfVar14 = (float *)(iVar7 + (uint)*puVar9 * 0xc);
            local_40 = *pfVar13 - *pfVar14;
            puVar9 = puVar9 + 3;
            pfVar10 = (float *)(iVar7 + (uint)*puVar1 * 0xc);
            local_3c = pfVar13[1] - pfVar14[1];
            local_38 = pfVar13[2] - pfVar14[2];
            local_4c = *pfVar10 - *pfVar14;
            local_48 = pfVar10[1] - pfVar14[1];
            local_44 = pfVar10[2] - pfVar14[2];
            tVector::Cross((tVector *)&local_34,(tVector *)&local_40,(tVector *)&local_4c);
            tVector::Normalize((tVector *)&local_34);
            iVar11 = *(int *)(*(int *)(*(int *)(*(int *)(this + 0x104) + 0xc) + local_60 * 4) + 8);
            uVar4 = cRObjects::AddNormal
                              (*(undefined4 *)(iVar12 + iVar2),local_34,uStack_30,uStack_2c);
            iVar7 = *(int *)(this + 0x10c);
            iVar8 = *(int *)(iVar7 + 0x14);
            *(undefined4 *)(iVar11 + iVar6 * 4) = uVar4;
            iVar6 = iVar6 + 1;
          } while (iVar6 < iVar8 / 3);
        }
        iVar6 = *(int *)(this + 0x104);
        local_60 = local_60 + 1;
      } while (local_60 < *(int *)(iVar6 + 4));
    }
  }
  return;
}
