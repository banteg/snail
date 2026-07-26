/*
 * mangled: _ZN9cRSubGame12PlaceParcelsEv
 * demangled: cRSubGame::PlaceParcels()
 * address: 00020124
 * size: 3856
 */

/* WARNING: Type propagation algorithm not settling */
/* cRSubGame::PlaceParcels() */

void __thiscall cRSubGame::PlaceParcels(cRSubGame *this)

{
  int iVar1;
  cRPath *this_00;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  cRSubGame *pcVar10;
  uint uVar11;
  undefined *puVar12;
  int *piVar13;
  undefined *puVar14;
  undefined *puVar15;
  int iVar16;
  bool bVar17;
  uint in_fpscr;
  undefined4 uVar18;
  float fVar19;
  longlong lVar20;
  int local_214;
  int local_210;
  int local_20c;
  int local_208;
  int local_200;
  int local_1fc [100];
  tMatrix atStack_6c [48];
  undefined4 local_3c;
  undefined4 local_38;
  float afStack_2c [3];

  iVar5 = *(int *)(this + 0x58);
  if (iVar5 == 1) {
    PlaceParcelsSurvival(this);
  }
  else if (iVar5 == 0 || iVar5 == 7) {
    DAT_003b6368 = 0;
    DAT_002b0368 = 0;
    iVar5 = 0x20c;
    do {
      *(undefined4 *)((int)&DAT_003b6368 + iVar5) = 0;
      iVar3 = iVar5 + 0x20c;
      *(undefined4 *)((int)&DAT_002b0368 + iVar5) = 0;
      iVar5 = iVar3;
    } while (iVar3 != 0x106000);
    if (0 < *(int *)(this + 0x98)) {
      lVar20 = 0;
      iVar5 = 0;
      local_210 = 0;
      local_20c = 0;
      pcVar10 = this;
LAB_000201bc:
      iVar16 = 0;
      uVar11 = 0;
      iVar3 = iVar5 << 2;
      iVar6 = iVar5 << 7;
      local_1fc[local_20c] = (int)&DAT_00002710;
      iVar1 = *(int *)(pcVar10 + 0xa0);
      local_200 = 0;
      do {
        if (iVar1 <= iVar16) {
          do {
            iVar3 = (iVar3 + iVar6) - iVar5;
            iVar6 = (&DAT_002b0368)[iVar3];
            if (0 < iVar6) {
              iVar5 = iVar5 + 1;
              if (iVar6 < local_1fc[(&DAT_002b0370)[iVar3]]) {
                local_1fc[(&DAT_002b0370)[iVar3]] = iVar6;
              }
              if (local_200 < iVar6) {
                local_200 = iVar6;
              }
            }
            uVar11 = uVar11 + 1;
            if (9 < (int)uVar11) {
              pcVar10 = pcVar10 + 0x2c;
              local_20c = local_20c + 1;
              iVar3 = *(int *)(this + 0x98);
              if (local_20c < iVar3) goto LAB_000201bc;
              iVar1 = *(int *)(this + 0x12fc);
              local_208 = (iVar1 * 0x50) / 100 - local_200;
              iVar6 = local_210;
              if (0 < iVar3) {
                iVar16 = 0;
                do {
                  piVar13 = local_1fc + iVar16;
                  iVar16 = iVar16 + 1;
                  if ((undefined *)*piVar13 != &DAT_00002710) {
                    iVar6 = iVar6 + *piVar13;
                  }
                } while (iVar16 != iVar3);
              }
              goto LAB_0002078c;
            }
            iVar16 = 0;
            iVar3 = iVar5 << 2;
            iVar6 = iVar5 << 7;
          } while (iVar1 < 1);
        }
        iVar1 = iVar16 * 8;
        iVar2 = iVar16 * 10;
        if (((*(ushort *)(iVar2 + *(int *)(pcVar10 + 0xb4)) & 1) != 0) &&
           (*(byte *)(iVar2 + *(int *)(pcVar10 + 0xb4) + 2) == uVar11)) {
          if (uVar11 == 0) {
            iVar8 = (int)((ulonglong)lVar20 >> 0x20);
            iVar7 = iVar8 * 0x20c;
            (&DAT_003b6370)[iVar8 * 0x83] = local_20c;
            *(int *)(&_gGroup0 + (&DAT_003b6368)[iVar8 * 0x83] * 0x10 + iVar7) = iVar16;
            *(undefined4 *)(&DAT_003b616c + (&DAT_003b6368)[iVar8 * 0x83] * 0x10 + iVar7) = 0;
            *(undefined4 *)(&DAT_003b6170 + (&DAT_003b6368)[iVar8 * 0x83] * 0x10 + iVar7) = 0;
            uVar18 = VectorUnsignedToFloat
                               ((uint)*(byte *)(iVar2 + *(int *)(pcVar10 + 0xb4) + 5),
                                (byte)(in_fpscr >> 0x16) & 3);
            *(undefined4 *)(&DAT_003b6174 + (&DAT_003b6368)[iVar8 * 0x83] * 0x10 + iVar7) = uVar18;
            (&DAT_003b636c)[iVar8 * 0x83] = 0;
            (&DAT_003b6368)[iVar8 * 0x83] = (&DAT_003b6368)[iVar8 * 0x83] + 1;
            lVar20 = (ulonglong)(iVar8 + 1) << 0x20;
            local_210 = local_210 + 1;
          }
          else {
            iVar8 = (iVar3 + iVar6) - iVar5;
            iVar7 = iVar8 * 4;
            (&DAT_002b0370)[iVar8] = local_20c;
            *(int *)(&_gGroup + (&DAT_002b0368)[iVar8] * 0x10 + iVar7) = iVar16;
            *(undefined4 *)((&DAT_002b0368)[iVar8] * 0x10 + iVar7 + 0x2b016c) = 0;
            *(undefined4 *)((&DAT_002b0368)[iVar8] * 0x10 + iVar7 + 0x2b0170) = 0;
            uVar18 = VectorUnsignedToFloat
                               ((uint)*(byte *)(iVar2 + *(int *)(pcVar10 + 0xb4) + 5),
                                (byte)(in_fpscr >> 0x16) & 3);
            *(undefined4 *)((&DAT_002b0368)[iVar8] * 0x10 + iVar7 + 0x2b0174) = uVar18;
            *(uint *)(iVar7 + 0x2b036c) = uVar11;
            (&DAT_002b0368)[iVar8] = (&DAT_002b0368)[iVar8] + 1;
          }
        }
        iVar2 = uVar11 + 0x30;
        if (uVar11 == 0) {
          iVar2 = 0;
          do {
            if (*(char *)(iVar1 + iVar2 + *(int *)(pcVar10 + 0xb0)) == '0') {
              iVar8 = (int)((ulonglong)lVar20 >> 0x20);
              fVar19 = (float)VectorSignedToFloat(iVar2,(byte)(in_fpscr >> 0x16) & 3);
              (&DAT_003b6370)[iVar8 * 0x83] = local_20c;
              *(int *)(&_gGroup0 + (&DAT_003b6368)[iVar8 * 0x83] * 0x10 + iVar8 * 0x20c) = iVar16;
              iVar7 = (&DAT_003b6368)[iVar8 * 0x83] * 0x10 + iVar8 * 0x20c;
              *(float *)(&DAT_003b616c + iVar7) = (fVar19 - 4.0) + 0.5;
              *(undefined4 *)(&DAT_003b6174 + iVar7) = 0;
              *(undefined4 *)(&DAT_003b6170 + iVar7) = 0;
              (&DAT_003b636c)[iVar8 * 0x83] = 0;
              (&DAT_003b6368)[iVar8 * 0x83] = (&DAT_003b6368)[iVar8 * 0x83] + 1;
              local_210 = local_210 + 1;
              lVar20 = (ulonglong)(iVar8 + 1) << 0x20;
            }
            iVar2 = iVar2 + 1;
          } while (iVar2 != 8);
        }
        else {
          iVar7 = *(int *)(pcVar10 + 0xb0);
          if (*(char *)(iVar7 + iVar16 * 8) == iVar2) {
            iVar8 = (iVar3 + iVar6) - iVar5;
            iVar7 = iVar8 * 4;
            (&DAT_002b0370)[iVar8] = local_20c;
            *(int *)(&_gGroup + (&DAT_002b0368)[iVar8] * 0x10 + iVar7) = iVar16;
            iVar9 = (&DAT_002b0368)[iVar8] * 0x10 + iVar7;
            *(undefined4 *)(iVar9 + 0x2b0174) = 0;
            *(undefined4 *)(iVar9 + 0x2b0170) = 0;
            *(undefined4 *)(iVar9 + 0x2b016c) = 0xc0600000;
            iVar9 = (&DAT_002b0368)[iVar8];
            *(uint *)(iVar7 + 0x2b036c) = uVar11;
            (&DAT_002b0368)[iVar8] = iVar9 + 1;
            iVar7 = *(int *)(pcVar10 + 0xb0);
          }
          if (*(char *)(iVar1 + iVar7 + 1) == iVar2) {
            iVar8 = (iVar3 + iVar6) - iVar5;
            iVar7 = iVar8 * 4;
            (&DAT_002b0370)[iVar8] = local_20c;
            *(int *)(&_gGroup + (&DAT_002b0368)[iVar8] * 0x10 + iVar7) = iVar16;
            iVar9 = (&DAT_002b0368)[iVar8] * 0x10 + iVar7;
            *(undefined4 *)(iVar9 + 0x2b0174) = 0;
            *(undefined4 *)(iVar9 + 0x2b0170) = 0;
            *(undefined4 *)(iVar9 + 0x2b016c) = 0xc0200000;
            iVar9 = (&DAT_002b0368)[iVar8];
            *(uint *)(iVar7 + 0x2b036c) = uVar11;
            (&DAT_002b0368)[iVar8] = iVar9 + 1;
            iVar7 = *(int *)(pcVar10 + 0xb0);
          }
          if (*(char *)(iVar1 + iVar7 + 2) == iVar2) {
            iVar8 = (iVar3 + iVar6) - iVar5;
            iVar7 = iVar8 * 4;
            (&DAT_002b0370)[iVar8] = local_20c;
            *(int *)(&_gGroup + (&DAT_002b0368)[iVar8] * 0x10 + iVar7) = iVar16;
            iVar9 = (&DAT_002b0368)[iVar8] * 0x10 + iVar7;
            *(undefined4 *)(iVar9 + 0x2b0174) = 0;
            *(undefined4 *)(iVar9 + 0x2b0170) = 0;
            *(undefined4 *)(iVar9 + 0x2b016c) = 0xbfc00000;
            iVar9 = (&DAT_002b0368)[iVar8];
            *(uint *)(iVar7 + 0x2b036c) = uVar11;
            (&DAT_002b0368)[iVar8] = iVar9 + 1;
            iVar7 = *(int *)(pcVar10 + 0xb0);
          }
          if (*(char *)(iVar1 + iVar7 + 3) == iVar2) {
            iVar8 = (iVar3 + iVar6) - iVar5;
            iVar7 = iVar8 * 4;
            (&DAT_002b0370)[iVar8] = local_20c;
            *(int *)(&_gGroup + (&DAT_002b0368)[iVar8] * 0x10 + iVar7) = iVar16;
            iVar9 = (&DAT_002b0368)[iVar8] * 0x10 + iVar7;
            *(undefined4 *)(iVar9 + 0x2b0174) = 0;
            *(undefined4 *)(iVar9 + 0x2b0170) = 0;
            *(undefined4 *)(iVar9 + 0x2b016c) = 0xbf000000;
            iVar9 = (&DAT_002b0368)[iVar8];
            *(uint *)(iVar7 + 0x2b036c) = uVar11;
            (&DAT_002b0368)[iVar8] = iVar9 + 1;
            iVar7 = *(int *)(pcVar10 + 0xb0);
          }
          if (*(char *)(iVar1 + iVar7 + 4) == iVar2) {
            iVar8 = (iVar3 + iVar6) - iVar5;
            iVar7 = iVar8 * 4;
            (&DAT_002b0370)[iVar8] = local_20c;
            *(int *)(&_gGroup + (&DAT_002b0368)[iVar8] * 0x10 + iVar7) = iVar16;
            iVar9 = (&DAT_002b0368)[iVar8] * 0x10 + iVar7;
            *(undefined4 *)(iVar9 + 0x2b0174) = 0;
            *(undefined4 *)(iVar9 + 0x2b0170) = 0;
            *(undefined4 *)(iVar9 + 0x2b016c) = 0x3f000000;
            iVar9 = (&DAT_002b0368)[iVar8];
            *(uint *)(iVar7 + 0x2b036c) = uVar11;
            (&DAT_002b0368)[iVar8] = iVar9 + 1;
            iVar7 = *(int *)(pcVar10 + 0xb0);
          }
          if (*(char *)(iVar1 + iVar7 + 5) == iVar2) {
            iVar8 = (iVar3 + iVar6) - iVar5;
            iVar7 = iVar8 * 4;
            (&DAT_002b0370)[iVar8] = local_20c;
            *(int *)(&_gGroup + (&DAT_002b0368)[iVar8] * 0x10 + iVar7) = iVar16;
            iVar9 = (&DAT_002b0368)[iVar8] * 0x10 + iVar7;
            *(undefined4 *)(iVar9 + 0x2b0174) = 0;
            *(undefined4 *)(iVar9 + 0x2b0170) = 0;
            *(undefined4 *)(iVar9 + 0x2b016c) = 0x3fc00000;
            iVar9 = (&DAT_002b0368)[iVar8];
            *(uint *)(iVar7 + 0x2b036c) = uVar11;
            (&DAT_002b0368)[iVar8] = iVar9 + 1;
            iVar7 = *(int *)(pcVar10 + 0xb0);
          }
          if (*(char *)(iVar1 + iVar7 + 6) == iVar2) {
            iVar8 = (iVar3 + iVar6) - iVar5;
            iVar7 = iVar8 * 4;
            (&DAT_002b0370)[iVar8] = local_20c;
            *(int *)(&_gGroup + (&DAT_002b0368)[iVar8] * 0x10 + iVar7) = iVar16;
            iVar9 = (&DAT_002b0368)[iVar8] * 0x10 + iVar7;
            *(undefined4 *)(iVar9 + 0x2b0174) = 0;
            *(undefined4 *)(iVar9 + 0x2b0170) = 0;
            *(undefined4 *)(iVar9 + 0x2b016c) = 0x40200000;
            iVar9 = (&DAT_002b0368)[iVar8];
            *(uint *)(iVar7 + 0x2b036c) = uVar11;
            (&DAT_002b0368)[iVar8] = iVar9 + 1;
            iVar7 = *(int *)(pcVar10 + 0xb0);
          }
          if (*(char *)(iVar1 + iVar7 + 7) == iVar2) {
            iVar2 = (iVar3 + iVar6) - iVar5;
            iVar1 = iVar2 * 4;
            (&DAT_002b0370)[iVar2] = local_20c;
            *(int *)(&_gGroup + (&DAT_002b0368)[iVar2] * 0x10 + iVar1) = iVar16;
            iVar7 = (&DAT_002b0368)[iVar2] * 0x10 + iVar1;
            *(undefined4 *)(iVar7 + 0x2b0174) = 0;
            *(undefined4 *)(iVar7 + 0x2b0170) = 0;
            *(undefined4 *)(iVar7 + 0x2b016c) = 0x40600000;
            iVar7 = (&DAT_002b0368)[iVar2];
            *(uint *)(iVar1 + 0x2b036c) = uVar11;
            (&DAT_002b0368)[iVar2] = iVar7 + 1;
          }
        }
        iVar1 = *(int *)(pcVar10 + 0xa0);
        iVar16 = iVar16 + 1;
      } while( true );
    }
    lVar20 = 0;
    iVar1 = *(int *)(this + 0x12fc);
    iVar5 = 0;
    local_210 = 0;
    local_208 = 0;
    iVar6 = iVar5;
LAB_0002078c:
    if (iVar6 < iVar1) {
      RShellError("Parcel Allocation could fail in %s.  Add more parcel Sets",this + 0x1268);
      iVar3 = *(int *)(this + 0x12fc) - local_208;
    }
    else {
      iVar3 = *(int *)(this + 0x12fc) - local_208;
    }
    if (local_210 < iVar3) {
      RShellError("Parcel Allocation could fail in %s. Add more 0 parcels ",this + 0x1268);
    }
    local_214 = 0;
    while( true ) {
      uVar18 = (undefined4)((ulonglong)lVar20 >> 0x20);
      if (local_208 <= local_214 || 0 >= iVar5) break;
      fVar19 = (float)VectorSignedToFloat(iVar5,(byte)(in_fpscr >> 0x16) & 3);
      fVar19 = (float)RAND(fVar19,"P1");
      iVar6 = (int)fVar19;
      lVar20 = CONCAT44(uVar18,iVar6);
      piVar13 = (int *)(&_gGroup + iVar6 * 0x20c);
      iVar3 = (&DAT_002b0368)[iVar6 * 0x83];
      if (0 < iVar3) {
        iVar1 = 0;
        do {
          iVar16 = *piVar13 + *(int *)(this + (&DAT_002b0370)[iVar6 * 0x83] * 0x2c + 0x9c);
          uVar11 = *(uint *)(this + iVar16 * 0xdc + 0x1e41d8);
          if ((uVar11 & 0x10) != 0) {
            RShellError("Duplicate Parcel Request in %s.",this + 0x1268);
            uVar11 = *(uint *)(this + iVar16 * 0xdc + 0x1e41d8);
          }
          *(uint *)(this + iVar16 * 0xdc + 0x1e41d8) = uVar11 | 0x11;
          _memcpy(this + iVar16 * 0xdc + 0x1e425c,piVar13 + 1,0xc);
          iVar1 = iVar1 + 1;
          piVar13 = piVar13 + 4;
          fVar19 = (float)VectorSignedToFloat(iVar16,(byte)(in_fpscr >> 0x16) & 3);
          *(float *)(this + iVar16 * 0xdc + 0x1e4264) =
               *(float *)(this + iVar16 * 0xdc + 0x1e4264) + fVar19 + 0.5;
          *(float *)(this + iVar16 * 0xdc + 0x1e4260) =
               *(float *)(this + iVar16 * 0xdc + 0x1e4260) + 1.0;
          if ((*(uint *)(this + iVar16 * 0xdc + 0x1e41d8) & 0x20) != 0) {
            *(float *)(this + iVar16 * 0xdc + 0x1e425c) =
                 -*(float *)(this + iVar16 * 0xdc + 0x1e425c);
          }
        } while (iVar1 < (int)(&DAT_002b0368)[iVar6 * 0x83]);
      }
      iVar6 = (&DAT_002b0370)[iVar6 * 0x84 - (int)lVar20];
      if (0 < iVar5) {
        iVar1 = 0;
        do {
          while (puVar15 = &_gGroup + iVar1 * 0x20c, (&DAT_002b0370)[iVar1 * 0x83] == iVar6) {
            iVar5 = iVar5 + -1;
            iVar16 = iVar1;
            while (iVar16 < iVar5) {
              iVar2 = *(int *)(puVar15 + 0x40c);
              if (0 < iVar2) {
                iVar7 = 0;
                puVar14 = &_gGroup + (iVar16 + 1) * 0x20c;
                puVar12 = &_gGroup + iVar16 * 0x20c;
                do {
                  _memcpy(puVar12,puVar14,0x10);
                  iVar2 = *(int *)(puVar15 + 0x40c);
                  iVar7 = iVar7 + 1;
                  puVar14 = puVar14 + 0x10;
                  puVar12 = puVar12 + 0x10;
                } while (iVar7 < iVar2);
              }
              *(int *)(puVar15 + 0x200) = iVar2;
              *(undefined4 *)(puVar15 + 0x208) = *(undefined4 *)(puVar15 + 0x414);
              *(undefined4 *)(puVar15 + 0x204) = *(undefined4 *)(puVar15 + 0x410);
              puVar15 = puVar15 + 0x20c;
              iVar16 = iVar16 + 1;
            }
            if (iVar5 <= iVar1) goto LAB_00020970;
          }
          iVar1 = iVar1 + 1;
        } while (iVar1 < iVar5);
      }
LAB_00020970:
      local_214 = local_214 + iVar3;
    }
    while( true ) {
      iVar6 = (int)((ulonglong)lVar20 >> 0x20);
      iVar3 = *(int *)(this + 0x12fc);
      bVar17 = iVar3 == local_214;
      iVar5 = iVar3 - local_214;
      if (iVar3 > local_214) {
        bVar17 = iVar6 == 0;
        iVar5 = iVar6;
      }
      if (bVar17 || iVar5 < 0 != (iVar3 <= local_214 && SBORROW4(iVar3,local_214))) break;
      fVar19 = (float)VectorSignedToFloat(iVar6,(byte)(in_fpscr >> 0x16) & 3);
      fVar19 = (float)RAND(fVar19,"P2");
      iVar1 = (int)fVar19;
      iVar5 = iVar1 * 0x20c;
      iVar16 = (&DAT_003b6368)[iVar1 * 0x83];
      iVar3 = *(int *)(&_gGroup0 + iVar5) +
              *(int *)(this + (&DAT_003b6370)[iVar1 * 0x83] * 0x2c + 0x9c);
      uVar11 = *(uint *)(this + iVar3 * 0xdc + 0x1e41d8);
      if ((uVar11 & 0x10) != 0) {
        RShellError("Duplicate Parcel Request in %s.",this + 0x1268);
        uVar11 = *(uint *)(this + iVar3 * 0xdc + 0x1e41d8);
      }
      *(uint *)(this + iVar3 * 0xdc + 0x1e41d8) = uVar11 | 0x11;
      fVar19 = (float)VectorSignedToFloat(iVar3,(byte)(in_fpscr >> 0x16) & 3);
      uVar18 = *(undefined4 *)(&DAT_003b6170 + iVar5);
      uVar4 = *(undefined4 *)(&DAT_003b6174 + iVar5);
      *(undefined4 *)(this + iVar3 * 0xdc + 0x1e425c) = *(undefined4 *)(&DAT_003b616c + iVar5);
      *(undefined4 *)(this + iVar3 * 0xdc + 0x1e4260) = uVar18;
      *(undefined4 *)(this + iVar3 * 0xdc + 0x1e4264) = uVar4;
      lVar20 = (ulonglong)(iVar6 - 1U) << 0x20;
      *(float *)(this + iVar3 * 0xdc + 0x1e4264) =
           *(float *)(this + iVar3 * 0xdc + 0x1e4264) + fVar19 + 0.5;
      *(float *)(this + iVar3 * 0xdc + 0x1e4260) = *(float *)(this + iVar3 * 0xdc + 0x1e4260) + 1.0;
      if ((uVar11 & 0x20) != 0) {
        *(float *)(this + iVar3 * 0xdc + 0x1e425c) = -*(float *)(this + iVar3 * 0xdc + 0x1e425c);
      }
      if (iVar1 < (int)(iVar6 - 1U)) {
        puVar15 = &_gGroup0 + (iVar1 + 1) * 0x20c;
        do {
          _memcpy(puVar15 + -0x20c,puVar15,0x10);
          iVar1 = iVar1 + 1;
          *(undefined4 *)(puVar15 + -0xc) = *(undefined4 *)(puVar15 + 0x200);
          *(undefined4 *)(puVar15 + -4) = *(undefined4 *)(puVar15 + 0x208);
          *(undefined4 *)(puVar15 + -8) = 0;
          puVar15 = puVar15 + 0x20c;
        } while (iVar1 < (int)((ulonglong)lVar20 >> 0x20));
      }
      local_214 = local_214 + iVar16;
    }
    if ((local_214 != iVar3) &&
       (RShellError("Did not generate required Parcels(%i) in %s",iVar3,this + 0x1268),
       *(int *)(this + 0x1304) != 0)) {
      uVar18 = ___divsi3(*(int *)(this + 0x12fc) * local_214);
      *(undefined4 *)(this + 0x1304) = uVar18;
    }
    *(int *)(this + 0x12fc) = local_214;
    iVar5 = *(int *)(this + 0x6c);
    if (0 < iVar5) {
      pcVar10 = this + 0x1e41d8;
      iVar3 = 0;
      do {
        if (((*(uint *)pcVar10 & 1) != 0) && ((*(uint *)pcVar10 & 0x40) != 0)) {
          iVar5 = *(int *)(pcVar10 + 0x98);
          this_00 = *(cRPath **)(iVar5 + 0x2c);
          iVar6 = ((int)(iVar5 - ((*(byte *)(iVar5 + 0x32) & 7) * 0x44 + 0x85fd0 +
                                 *(int *)PTR__Game_001b60b8)) >> 2) * -0xf0f0f0f;
          iVar5 = iVar6 + 7;
          if (-1 < iVar6) {
            iVar5 = iVar6;
          }
          uVar11 = (int)*(float *)(pcVar10 + 0x8c) - (iVar5 >> 3);
          uVar11 = uVar11 & ~((int)uVar11 >> 0x1f);
          if (*(int *)(this_00 + 0x2c) == 0x39) {
            cRPath::HalfPipePos(this_00,*(float *)(uVar11 * 0xa8 + *(int *)(this_00 + 0x4c) + 0xa0),
                                *(float *)(pcVar10 + 0x84),*(float *)(pcVar10 + 0x88),atStack_6c,
                                afStack_2c);
            *(undefined4 *)(pcVar10 + 0x84) = local_3c;
            *(undefined4 *)(pcVar10 + 0x88) = local_38;
            iVar5 = *(int *)(this + 0x6c);
          }
          else if (*(int *)(this_00 + 0x2c) == 0x3a) {
            cRPath::HalfPolePos(this_00,*(float *)(uVar11 * 0xa8 + *(int *)(this_00 + 0x4c) + 0xa0),
                                *(float *)(pcVar10 + 0x84),*(float *)(pcVar10 + 0x88),atStack_6c,
                                afStack_2c);
            *(undefined4 *)(pcVar10 + 0x84) = local_3c;
            *(undefined4 *)(pcVar10 + 0x88) = local_38;
            iVar5 = *(int *)(this + 0x6c);
          }
          else {
            cRPath::GetPos(this_00,(tVector *)(this + iVar3 * 0xdc + 0x1e425c),uVar11,iVar5 >> 3,
                           (tVector *)(this + iVar3 * 0xdc + 0x1e425c));
            iVar5 = *(int *)(this + 0x6c);
          }
        }
        iVar3 = iVar3 + 1;
        pcVar10 = pcVar10 + 0xdc;
      } while (iVar3 < iVar5);
    }
  }
  return;
}
