/*
 * mangled: _ZN8cRSubLoc2AIEv
 * demangled: cRSubLoc::AI()
 * address: 00035a80
 * size: 1532
 */

/* cRSubLoc::AI() */

void __thiscall cRSubLoc::AI(cRSubLoc *this)

{
  cRSubLoc cVar1;
  byte bVar2;
  undefined *puVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  uint in_fpscr;
  uint uVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;

  puVar3 = PTR__Game_001b60b8;
  if (((byte)this[0x33] & 0x20) == 0) {
    return;
  }
  iVar4 = *(int *)PTR__Game_001b60b8;
  if (*(char *)(iVar4 + 0x72b8a) != '\0') {
    return;
  }
  fVar9 = *(float *)(this + 0x18);
  fVar10 = *(float *)(iVar4 + 0x82024);
  cVar1 = this[0x30];
  if (cVar1 == (cRSubLoc)0xe) {
    fVar11 = (float)VectorSignedToFloat(*(undefined4 *)(iVar4 + 0x72be0),
                                        (byte)(in_fpscr >> 0x16) & 3);
    uVar7 = in_fpscr & 0xfffffff | (uint)(fVar10 < fVar11) << 0x1f |
            (uint)(fVar10 == fVar11) << 0x1e;
    uVar8 = uVar7 | (uint)(NAN(fVar10) || NAN(fVar11)) << 0x1c;
    bVar2 = (byte)(uVar7 >> 0x18);
    if (!(bool)(bVar2 >> 6 & 1) && bVar2 >> 7 == ((byte)(uVar8 >> 0x1c) & 1)) {
      fVar9 = (float)RAND(100.0,"W");
      iVar4 = *(int *)puVar3;
      uVar7 = uVar8 & 0xfffffff |
              (uint)(fVar9 < (1.0 - *(float *)(&DAT_003648f8 + iVar4)) * -3.5 + 4.0) << 0x1f;
      if (SUB41(uVar7 >> 0x1f,0)) {
        fVar12 = 8.0;
        fVar10 = 0.0;
        fVar13 = *(float *)(this + 0x14) + 8.0;
        fVar14 = *(float *)(this + 0x18) + 0.0;
        fVar9 = (float)VectorUnsignedToFloat((byte)this[0x33] & 0xf,(byte)(uVar7 >> 0x16) & 3);
        fVar11 = *(float *)(this + 0x10) + 0.0 + fVar9 * 0.5;
        fVar9 = (float)SRAND(3.0,"Wall2");
        local_44 = (*(float *)(iVar4 + 0x8201c) + fVar10) - fVar11;
        local_40 = (*(float *)(iVar4 + 0x82020) + fVar10) - fVar13;
        local_3c = (fVar9 + fVar12 + *(float *)(iVar4 + 0x82024)) - fVar14;
        if (local_3c < -4.0) {
          tVector::Normalize((tVector *)&local_44);
          local_44 = local_44 * 0.4;
          local_40 = local_40 * 0.4;
          local_3c = local_3c * 0.4;
          local_38 = fVar11;
          local_34 = fVar13;
          local_30 = fVar14;
          cRSubLazerManager::Shoot
                    (*(int *)puVar3 + 0x766a8,fVar11,fVar13,fVar14,local_44,local_40,local_3c);
          fVar9 = *(float *)(this + 0x18);
          goto LAB_00035ba0;
        }
      }
      fVar9 = *(float *)(this + 0x18);
    }
LAB_00035ba0:
    iVar4 = *(int *)PTR__Game_001b60b8;
    if (*(float *)(iVar4 + 0x847b4) <= fVar9) {
      return;
    }
    if ((byte)((char)this[0x30] - 0x1dU) < 2) {
      uVar7 = ((int)((int)this - (iVar4 + ((byte)this[0x32] & 7) * 0x44 + 0x85fd0)) >> 2) *
              -0xf0f0f0f;
      if ((int)uVar7 < 0) {
        uVar7 = uVar7 + 7;
      }
      iVar6 = (((int)uVar7 >> 3) * 0x3f - (uVar7 & 0xfffffff8)) * 4 + iVar4;
      if (((*(uint *)(&DAT_00256d50 + iVar6) & 8) != 0) &&
         ((*(uint *)(&DAT_00256df8 + iVar6) & 0x200) != 0)) {
        if ((*(uint *)(&DAT_00256df8 + iVar6) & 0x40) == 0) {
          iVar5 = *(int *)(&DAT_00256e00 + iVar6);
          if (iVar5 != 0) {
            *(undefined4 *)(iVar5 + 8) = *(undefined4 *)(&DAT_00256dfc + iVar6);
          }
          iVar6 = *(int *)(&DAT_00256dfc + iVar6);
          if (iVar6 != 0) {
            *(int *)(iVar6 + 0xc) = iVar5;
          }
          if (iVar6 == 0) {
            *(int *)(iVar4 + 0x35c) = iVar5;
          }
          iVar6 = (((int)uVar7 >> 3) * 0x3f - (uVar7 & 0xfffffff8)) * 4;
          iVar5 = iVar6 + iVar4;
          *(undefined4 *)(&DAT_00256e00 + iVar5) = *(undefined4 *)(iVar4 + 0x360);
          *(int *)(iVar4 + 0x360) = iVar4 + iVar6 + 0x256df4;
          *(uint *)(&DAT_00256df8 + iVar5) = *(uint *)(&DAT_00256df8 + iVar5) & 0xfffffdff;
        }
        else {
          RShellError("List remove NEXTBOD");
        }
      }
    }
    uVar7 = *(uint *)(this + 4);
    if ((uVar7 & 0x200) == 0) {
      return;
    }
    iVar4 = *(int *)PTR__Game_001b60b8;
joined_r0x00035bfc:
    if ((uVar7 & 0x40) == 0) {
      iVar6 = *(int *)(this + 0xc);
      if (iVar6 != 0) {
        *(undefined4 *)(iVar6 + 8) = *(undefined4 *)(this + 8);
      }
      if (*(int *)(this + 8) == 0) {
        *(int *)(iVar4 + 0x35c) = iVar6;
      }
      else {
        *(int *)(*(int *)(this + 8) + 0xc) = iVar6;
      }
      *(undefined4 *)(this + 0xc) = *(undefined4 *)(iVar4 + 0x360);
      *(cRSubLoc **)(iVar4 + 0x360) = this;
      *(uint *)(this + 4) = *(uint *)(this + 4) & 0xfffffdff;
      return;
    }
  }
  else {
    if (cVar1 == (cRSubLoc)0x16) {
      fVar10 = *(float *)(iVar4 + 0x847b4);
    }
    else {
      if ((byte)((char)cVar1 - 0x1dU) < 2) {
        iVar6 = *(int *)(this + 0x2c);
        if (*(int *)(iVar6 + 0x2c) == 0x1c) {
          fVar9 = *(float *)(this + 0x20) + *(float *)(iVar4 + 0x72bc4) * -0.033333335;
          in_fpscr = in_fpscr & 0xfffffff | (uint)(fVar9 < -1.0) << 0x1f;
          *(float *)(this + 0x20) = fVar9;
          if (SUB41(in_fpscr >> 0x1f,0)) {
            *(float *)(this + 0x20) = fVar9 + 1.0;
          }
          tColourSmall::Alpha((tColourSmall *)(this + 0x28),0.8);
          iVar6 = *(int *)(this + 0x2c);
        }
        puVar3 = PTR__Game_001b60b8;
        iVar4 = *(int *)PTR__Game_001b60b8;
        tColourSmall::Set((tColourSmall *)(iVar6 + 0x7c),*(float *)(iVar4 + 0x73dd0),
                          *(float *)(iVar4 + 0x73dd4),*(float *)(iVar4 + 0x73dd8),0.5);
        iVar4 = *(int *)puVar3;
        fVar9 = (float)VectorSignedToFloat(*(undefined4 *)(*(int *)(this + 0x2c) + 0x3c),
                                           (byte)(in_fpscr >> 0x16) & 3);
        if (*(float *)(iVar4 + 0x847b4) - (fVar9 + 5.0) <= *(float *)(this + 0x18)) {
          return;
        }
        if ((byte)((char)this[0x30] - 0x1dU) < 2) {
          uVar7 = ((int)((int)this - (iVar4 + ((byte)this[0x32] & 7) * 0x44 + 0x85fd0)) >> 2) *
                  -0xf0f0f0f;
          if ((int)uVar7 < 0) {
            uVar7 = uVar7 + 7;
          }
          iVar6 = (((int)uVar7 >> 3) * 0x3f - (uVar7 & 0xfffffff8)) * 4 + iVar4;
          if (((*(uint *)(&DAT_00256d50 + iVar6) & 8) != 0) &&
             ((*(uint *)(&DAT_00256df8 + iVar6) & 0x200) != 0)) {
            if ((*(uint *)(&DAT_00256df8 + iVar6) & 0x40) == 0) {
              iVar5 = *(int *)(&DAT_00256e00 + iVar6);
              if (iVar5 != 0) {
                *(undefined4 *)(iVar5 + 8) = *(undefined4 *)(&DAT_00256dfc + iVar6);
              }
              iVar6 = *(int *)(&DAT_00256dfc + iVar6);
              if (iVar6 != 0) {
                *(int *)(iVar6 + 0xc) = iVar5;
              }
              if (iVar6 == 0) {
                *(int *)(iVar4 + 0x35c) = iVar5;
              }
              iVar6 = (((int)uVar7 >> 3) * 0x3f - (uVar7 & 0xfffffff8)) * 4;
              iVar5 = iVar6 + iVar4;
              *(undefined4 *)(&DAT_00256e00 + iVar5) = *(undefined4 *)(iVar4 + 0x360);
              *(int *)(iVar4 + 0x360) = iVar4 + iVar6 + 0x256df4;
              *(uint *)(&DAT_00256df8 + iVar5) = *(uint *)(&DAT_00256df8 + iVar5) & 0xfffffdff;
            }
            else {
              RShellError("List remove NEXTBOD");
            }
          }
        }
        uVar7 = *(uint *)(this + 4);
        if ((uVar7 & 0x200) == 0) {
          return;
        }
        iVar4 = *(int *)PTR__Game_001b60b8;
        goto joined_r0x00035bfc;
      }
      uVar7 = in_fpscr & 0xfffffff | (uint)(fVar9 < *(float *)(iVar4 + 0x847b4)) << 0x1f;
      if (!SUB41(uVar7 >> 0x1f,0)) {
        return;
      }
      fVar10 = (float)VectorSignedToFloat(*(int *)(iVar4 + 0x72be8) + -5,(byte)(uVar7 >> 0x16) & 3);
    }
    if (fVar10 <= fVar9) {
      return;
    }
    if ((*(uint *)(this + 4) & 0x200) == 0) {
      return;
    }
    if ((*(uint *)(this + 4) & 0x40) == 0) {
      iVar6 = *(int *)(this + 0xc);
      if (iVar6 != 0) {
        *(undefined4 *)(iVar6 + 8) = *(undefined4 *)(this + 8);
      }
      if (*(int *)(this + 8) == 0) {
        *(int *)(iVar4 + 0x35c) = iVar6;
      }
      else {
        *(int *)(*(int *)(this + 8) + 0xc) = iVar6;
      }
      *(undefined4 *)(this + 0xc) = *(undefined4 *)(iVar4 + 0x360);
      *(cRSubLoc **)(iVar4 + 0x360) = this;
      *(uint *)(this + 4) = *(uint *)(this + 4) & 0xfffffdff;
      return;
    }
  }
  RShellError("List remove NEXTBOD");
  return;
}
