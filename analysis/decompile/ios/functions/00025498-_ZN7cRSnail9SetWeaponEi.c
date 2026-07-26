/*
 * mangled: _ZN7cRSnail9SetWeaponEi
 * demangled: cRSnail::SetWeapon(int)
 * address: 00025498
 * size: 2640
 */

/* cRSnail::SetWeapon(int) */

void __thiscall cRSnail::SetWeapon(cRSnail *this,int param_1)

{
  bool bVar1;
  ushort *puVar2;
  int iVar3;
  undefined4 uVar4;
  undefined2 *puVar5;
  int unaff_r9;
  int in_lr;
  float fVar6;

  if (param_1 == 0x10) {
LAB_000259d0:
    param_1 = 0;
    unaff_r9 = 2;
    in_lr = 2;
  }
  else if (param_1 < 0x11) {
    if (param_1 == 2) {
      param_1 = 0;
      unaff_r9 = 1;
      in_lr = 1;
    }
    else if (param_1 < 3) {
      if (param_1 == 1) {
        unaff_r9 = 0;
        in_lr = unaff_r9;
      }
    }
    else if (param_1 == 4) {
      param_1 = 1;
      unaff_r9 = param_1;
      in_lr = param_1;
    }
    else if (param_1 == 8) {
      param_1 = 0;
      unaff_r9 = 2;
      in_lr = param_1;
    }
  }
  else if (param_1 == 0x40) {
LAB_000255e4:
    param_1 = 3;
    unaff_r9 = 0;
    in_lr = 0;
  }
  else if (param_1 < 0x41) {
    if (param_1 == 0x20) goto LAB_000255e4;
  }
  else {
    if (param_1 == 0x90) goto LAB_000259d0;
    if (param_1 == 0xc0) goto LAB_000255e4;
  }
  iVar3 = *(int *)(this + 0x6c0);
  if (iVar3 == in_lr) {
    bVar1 = false;
  }
  else {
    if (iVar3 == 1) {
      puVar5 = *(undefined2 **)(*(int *)(this + 0x7a4) + 0x104);
      *(undefined2 **)(this + 0x6d0) = puVar5;
      *puVar5 = 8;
      puVar2 = *(ushort **)(this + 0x6d0);
      if ((*puVar2 & 8) == 0) {
        *(undefined4 *)(this + 0x6c8) = 0;
        *(float *)(this + 0x6cc) = ABS(*(float *)(puVar2 + 10));
      }
      else {
        fVar6 = *(float *)(puVar2 + 10);
        *(float *)(this + 0x6cc) = -ABS(fVar6);
        *(float *)(this + 0x6c8) = -ABS(fVar6) + 1.0;
      }
      uVar4 = *(undefined4 *)(this + 0x7a4);
LAB_000257f8:
      bVar1 = false;
      *(undefined4 *)(this + 0x700) = 0;
      *(undefined4 *)(this + 0x5ec) = uVar4;
      *(uint *)(*(int *)(this + 0x704) + 4) = *(uint *)(*(int *)(this + 0x704) + 4) | 0x20;
      if (in_lr == 1) goto LAB_0002581c;
LAB_000254f4:
      if (in_lr == 2) {
        if (bVar1) {
          puVar5 = *(undefined2 **)(*(int *)(this + 0x900) + 0x104);
          *(undefined2 **)(this + 0x6d0) = puVar5;
          *puVar5 = 4;
          puVar2 = *(ushort **)(this + 0x6d0);
          if ((*puVar2 & 8) == 0) {
            *(undefined4 *)(this + 0x6c8) = 0;
            *(float *)(this + 0x6cc) = ABS(*(float *)(puVar2 + 10));
          }
          else {
            fVar6 = *(float *)(puVar2 + 10);
            *(float *)(this + 0x6cc) = -ABS(fVar6);
            *(float *)(this + 0x6c8) = -ABS(fVar6) + 1.0;
          }
          *(undefined4 *)(this + 0x700) = 0;
          *(undefined4 *)(this + 0x5ec) = *(undefined4 *)(this + 0x900);
          *(uint *)(*(int *)(this + 0x704) + 4) = *(uint *)(*(int *)(this + 0x704) + 4) | 0x20;
          iVar3 = *(int *)(this + 0x700);
        }
        else {
          iVar3 = *(int *)(this + 0x700) + 1;
          *(undefined4 *)(this + *(int *)(this + 0x700) * 4 + 0x6d8) = 4;
          *(int *)(this + 0x700) = iVar3;
        }
        *(undefined4 *)(this + iVar3 * 4 + 0x6d8) = 3;
        *(int *)(this + 0x700) = iVar3 + 1;
      }
      else if (in_lr == 0) {
        iVar3 = *(int *)(this + 0x700);
        *(undefined4 *)(this + iVar3 * 4 + 0x6d8) = 0xffffffff;
        *(int *)(this + 0x700) = iVar3 + 1;
      }
    }
    else {
      if (iVar3 == 2) {
        puVar5 = *(undefined2 **)(*(int *)(this + 0x900) + 0x104);
        *(undefined2 **)(this + 0x6d0) = puVar5;
        *puVar5 = 8;
        puVar2 = *(ushort **)(this + 0x6d0);
        if ((*puVar2 & 8) == 0) {
          *(undefined4 *)(this + 0x6c8) = 0;
          *(float *)(this + 0x6cc) = ABS(*(float *)(puVar2 + 10));
          uVar4 = *(undefined4 *)(this + 0x900);
        }
        else {
          fVar6 = *(float *)(puVar2 + 10);
          *(float *)(this + 0x6cc) = -ABS(fVar6);
          *(float *)(this + 0x6c8) = -ABS(fVar6) + 1.0;
          uVar4 = *(undefined4 *)(this + 0x900);
        }
        goto LAB_000257f8;
      }
      bVar1 = true;
      if (in_lr != 1) goto LAB_000254f4;
LAB_0002581c:
      if (bVar1) {
        puVar5 = *(undefined2 **)(*(int *)(this + 0x7a4) + 0x104);
        *(undefined2 **)(this + 0x6d0) = puVar5;
        *puVar5 = 4;
        puVar2 = *(ushort **)(this + 0x6d0);
        if ((*puVar2 & 8) == 0) {
          *(undefined4 *)(this + 0x6c8) = 0;
          *(float *)(this + 0x6cc) = ABS(*(float *)(puVar2 + 10));
        }
        else {
          fVar6 = *(float *)(puVar2 + 10);
          *(float *)(this + 0x6cc) = -ABS(fVar6);
          *(float *)(this + 0x6c8) = -ABS(fVar6) + 1.0;
        }
        *(undefined4 *)(this + 0x700) = 0;
        *(undefined4 *)(this + 0x5ec) = *(undefined4 *)(this + 0x7a4);
        *(uint *)(*(int *)(this + 0x704) + 4) = *(uint *)(*(int *)(this + 0x704) + 4) | 0x20;
        iVar3 = *(int *)(this + 0x700);
      }
      else {
        iVar3 = *(int *)(this + 0x700) + 1;
        *(int *)(this + *(int *)(this + 0x700) * 4 + 0x6d8) = in_lr;
        *(int *)(this + 0x700) = iVar3;
      }
      *(undefined4 *)(this + iVar3 * 4 + 0x6d8) = 0;
      *(int *)(this + 0x700) = iVar3 + 1;
    }
    bVar1 = true;
    *(int *)(this + 0x6c0) = in_lr;
  }
  iVar3 = *(int *)(this + 0xa54);
  if (iVar3 != unaff_r9) {
    if (iVar3 == 1) {
      puVar5 = *(undefined2 **)(*(int *)(this + 0xb38) + 0x104);
      *(undefined2 **)(this + 0xa64) = puVar5;
      *puVar5 = 8;
      puVar2 = *(ushort **)(this + 0xa64);
      if ((*puVar2 & 8) == 0) {
        *(undefined4 *)(this + 0xa5c) = 0;
        *(float *)(this + 0xa60) = ABS(*(float *)(puVar2 + 10));
      }
      else {
        fVar6 = *(float *)(puVar2 + 10);
        *(float *)(this + 0xa60) = -ABS(fVar6);
        *(float *)(this + 0xa5c) = -ABS(fVar6) + 1.0;
      }
      uVar4 = *(undefined4 *)(this + 0xb38);
LAB_00025938:
      bVar1 = false;
      *(undefined4 *)(this + 0xa94) = 0;
      *(undefined4 *)(this + 0x980) = uVar4;
      *(uint *)(*(int *)(this + 0xa98) + 4) = *(uint *)(*(int *)(this + 0xa98) + 4) | 0x20;
      if (unaff_r9 == 1) goto LAB_0002595c;
LAB_00025534:
      if (unaff_r9 == 2) {
        if (bVar1) {
          puVar5 = *(undefined2 **)(*(int *)(this + 0xc94) + 0x104);
          *(undefined2 **)(this + 0xa64) = puVar5;
          *puVar5 = 4;
          puVar2 = *(ushort **)(this + 0xa64);
          if ((*puVar2 & 8) == 0) {
            *(undefined4 *)(this + 0xa5c) = 0;
            *(float *)(this + 0xa60) = ABS(*(float *)(puVar2 + 10));
          }
          else {
            fVar6 = *(float *)(puVar2 + 10);
            *(float *)(this + 0xa60) = -ABS(fVar6);
            *(float *)(this + 0xa5c) = -ABS(fVar6) + 1.0;
          }
          *(undefined4 *)(this + 0xa94) = 0;
          *(undefined4 *)(this + 0x980) = *(undefined4 *)(this + 0xc94);
          *(uint *)(*(int *)(this + 0xa98) + 4) = *(uint *)(*(int *)(this + 0xa98) + 4) | 0x20;
          iVar3 = *(int *)(this + 0xa94);
        }
        else {
          iVar3 = *(int *)(this + 0xa94) + 1;
          *(undefined4 *)(this + *(int *)(this + 0xa94) * 4 + 0xa6c) = 4;
          *(int *)(this + 0xa94) = iVar3;
        }
        *(undefined4 *)(this + iVar3 * 4 + 0xa6c) = 3;
        *(int *)(this + 0xa94) = iVar3 + 1;
      }
      else if (unaff_r9 == 0) {
        iVar3 = *(int *)(this + 0xa94);
        *(undefined4 *)(this + iVar3 * 4 + 0xa6c) = 0xffffffff;
        *(int *)(this + 0xa94) = iVar3 + 1;
      }
    }
    else {
      if (iVar3 == 2) {
        puVar5 = *(undefined2 **)(*(int *)(this + 0xc94) + 0x104);
        *(undefined2 **)(this + 0xa64) = puVar5;
        *puVar5 = 8;
        puVar2 = *(ushort **)(this + 0xa64);
        if ((*puVar2 & 8) == 0) {
          *(undefined4 *)(this + 0xa5c) = 0;
          *(float *)(this + 0xa60) = ABS(*(float *)(puVar2 + 10));
          uVar4 = *(undefined4 *)(this + 0xc94);
        }
        else {
          fVar6 = *(float *)(puVar2 + 10);
          *(float *)(this + 0xa60) = -ABS(fVar6);
          *(float *)(this + 0xa5c) = -ABS(fVar6) + 1.0;
          uVar4 = *(undefined4 *)(this + 0xc94);
        }
        goto LAB_00025938;
      }
      bVar1 = true;
      if (unaff_r9 != 1) goto LAB_00025534;
LAB_0002595c:
      if (bVar1) {
        puVar5 = *(undefined2 **)(*(int *)(this + 0xb38) + 0x104);
        *(undefined2 **)(this + 0xa64) = puVar5;
        *puVar5 = 4;
        puVar2 = *(ushort **)(this + 0xa64);
        if ((*puVar2 & 8) == 0) {
          *(undefined4 *)(this + 0xa5c) = 0;
          *(float *)(this + 0xa60) = ABS(*(float *)(puVar2 + 10));
        }
        else {
          fVar6 = *(float *)(puVar2 + 10);
          *(float *)(this + 0xa60) = -ABS(fVar6);
          *(float *)(this + 0xa5c) = -ABS(fVar6) + 1.0;
        }
        *(undefined4 *)(this + 0xa94) = 0;
        *(undefined4 *)(this + 0x980) = *(undefined4 *)(this + 0xb38);
        *(uint *)(*(int *)(this + 0xa98) + 4) = *(uint *)(*(int *)(this + 0xa98) + 4) | 0x20;
        iVar3 = *(int *)(this + 0xa94);
      }
      else {
        iVar3 = *(int *)(this + 0xa94) + 1;
        *(int *)(this + *(int *)(this + 0xa94) * 4 + 0xa6c) = unaff_r9;
        *(int *)(this + 0xa94) = iVar3;
      }
      *(undefined4 *)(this + iVar3 * 4 + 0xa6c) = 0;
      *(int *)(this + 0xa94) = iVar3 + 1;
    }
    bVar1 = true;
    *(int *)(this + 0xa54) = unaff_r9;
  }
  iVar3 = *(int *)(this + 0xde8);
  if (iVar3 == param_1) {
    if (bVar1) {
      cRSound::Play((cRSound *)PTR__gRSound_001b61e0,0x19);
      return;
    }
    return;
  }
  if (iVar3 == 1) {
    puVar5 = *(undefined2 **)(*(int *)(this + 0xecc) + 0x104);
    *(undefined2 **)(this + 0xdf8) = puVar5;
    *puVar5 = 8;
    puVar2 = *(ushort **)(this + 0xdf8);
    if ((*puVar2 & 8) == 0) {
      *(undefined4 *)(this + 0xdf0) = 0;
      *(float *)(this + 0xdf4) = ABS(*(float *)(puVar2 + 10));
    }
    else {
      fVar6 = *(float *)(puVar2 + 10);
      *(float *)(this + 0xdf4) = -ABS(fVar6);
      *(float *)(this + 0xdf0) = -ABS(fVar6) + 1.0;
    }
    uVar4 = *(undefined4 *)(this + 0xecc);
  }
  else {
    if (iVar3 != 3) {
      bVar1 = true;
      goto joined_r0x00025570;
    }
    puVar5 = *(undefined2 **)(*(int *)(this + 0x1028) + 0x104);
    *(undefined2 **)(this + 0xdf8) = puVar5;
    *puVar5 = 8;
    puVar2 = *(ushort **)(this + 0xdf8);
    if ((*puVar2 & 8) == 0) {
      *(undefined4 *)(this + 0xdf0) = 0;
      *(float *)(this + 0xdf4) = ABS(*(float *)(puVar2 + 10));
      uVar4 = *(undefined4 *)(this + 0x1028);
    }
    else {
      fVar6 = *(float *)(puVar2 + 10);
      *(float *)(this + 0xdf4) = -ABS(fVar6);
      *(float *)(this + 0xdf0) = -ABS(fVar6) + 1.0;
      uVar4 = *(undefined4 *)(this + 0x1028);
    }
  }
  bVar1 = false;
  *(undefined4 *)(this + 0xe28) = 0;
  *(undefined4 *)(this + 0xd14) = uVar4;
  *(uint *)(*(int *)(this + 0xe2c) + 4) = *(uint *)(*(int *)(this + 0xe2c) + 4) | 0x20;
joined_r0x00025570:
  if (param_1 == 1) {
    if (bVar1) {
      puVar5 = *(undefined2 **)(*(int *)(this + 0xecc) + 0x104);
      *(undefined2 **)(this + 0xdf8) = puVar5;
      *puVar5 = 4;
      puVar2 = *(ushort **)(this + 0xdf8);
      if ((*puVar2 & 8) == 0) {
        *(undefined4 *)(this + 0xdf0) = 0;
        *(float *)(this + 0xdf4) = ABS(*(float *)(puVar2 + 10));
      }
      else {
        fVar6 = *(float *)(puVar2 + 10);
        *(float *)(this + 0xdf4) = -ABS(fVar6);
        *(float *)(this + 0xdf0) = -ABS(fVar6) + 1.0;
      }
      *(undefined4 *)(this + 0xe28) = 0;
      *(undefined4 *)(this + 0xd14) = *(undefined4 *)(this + 0xecc);
      *(uint *)(*(int *)(this + 0xe2c) + 4) = *(uint *)(*(int *)(this + 0xe2c) + 4) | 0x20;
      iVar3 = *(int *)(this + 0xe28);
    }
    else {
      iVar3 = *(int *)(this + 0xe28) + 1;
      *(undefined4 *)(this + *(int *)(this + 0xe28) * 4 + 0xe00) = 1;
      *(int *)(this + 0xe28) = iVar3;
    }
    *(undefined4 *)(this + iVar3 * 4 + 0xe00) = 0;
    *(int *)(this + 0xe28) = iVar3 + 1;
  }
  else if (param_1 == 3) {
    if (bVar1) {
      puVar5 = *(undefined2 **)(*(int *)(this + 0x1028) + 0x104);
      *(undefined2 **)(this + 0xdf8) = puVar5;
      *puVar5 = 4;
      puVar2 = *(ushort **)(this + 0xdf8);
      if ((*puVar2 & 8) == 0) {
        *(undefined4 *)(this + 0xdf0) = 0;
        *(float *)(this + 0xdf4) = ABS(*(float *)(puVar2 + 10));
      }
      else {
        fVar6 = *(float *)(puVar2 + 10);
        *(float *)(this + 0xdf4) = -ABS(fVar6);
        *(float *)(this + 0xdf0) = -ABS(fVar6) + 1.0;
      }
      *(undefined4 *)(this + 0xe28) = 0;
      *(undefined4 *)(this + 0xd14) = *(undefined4 *)(this + 0x1028);
      *(uint *)(*(int *)(this + 0xe2c) + 4) = *(uint *)(*(int *)(this + 0xe2c) + 4) | 0x20;
      iVar3 = *(int *)(this + 0xe28);
    }
    else {
      iVar3 = *(int *)(this + 0xe28) + 1;
      *(undefined4 *)(this + *(int *)(this + 0xe28) * 4 + 0xe00) = 4;
      *(int *)(this + 0xe28) = iVar3;
    }
    *(undefined4 *)(this + iVar3 * 4 + 0xe00) = 3;
    *(int *)(this + 0xe28) = iVar3 + 1;
  }
  else if (param_1 == 0) {
    iVar3 = *(int *)(this + 0xe28);
    *(undefined4 *)(this + iVar3 * 4 + 0xe00) = 0xffffffff;
    *(int *)(this + 0xe28) = iVar3 + 1;
  }
  *(int *)(this + 0xde8) = param_1;
  cRSound::Play((cRSound *)PTR__gRSound_001b61e0,0x19);
  return;
}
