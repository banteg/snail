/*
 * mangled: _ZN8cRParcel2AIEv
 * demangled: cRParcel::AI()
 * address: 00074a98
 * size: 1248
 */

/* cRParcel::AI() */

void cRParcel::AI(void)

{
  char cVar1;
  int in_r0;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  uint in_fpscr;
  float in_s0;
  float extraout_s0;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float local_34;
  float local_30;
  float local_2c;

  iVar5 = *(int *)(in_r0 + 0x30);
  if (*(char *)(iVar5 + 0x19) != '\0') {
    return;
  }
  switch(*(undefined4 *)(in_r0 + 0x2c)) {
  case 1:
    if (*(float *)(in_r0 + 0x18) < *(float *)((int)DWORD_ARRAY_000110f8 + iVar5 + 0x11c8) - 10.0) {
      in_s0 = (float)cRSprite::Kill(*(cRSprite **)(in_r0 + 0x48));
      *(undefined4 *)(in_r0 + 0x2c) = 0;
    }
    fVar7 = *(float *)(in_r0 + 0x50) + *(float *)(in_r0 + 0x54);
    iVar5 = *(int *)(in_r0 + 0x48);
    uVar2 = *(undefined4 *)(in_r0 + 0x14);
    uVar3 = *(undefined4 *)(in_r0 + 0x18);
    *(float *)(in_r0 + 0x50) = fVar7;
    if (1.0 < fVar7) {
      *(float *)(in_r0 + 0x50) = fVar7 - 1.0;
    }
    *(undefined4 *)(iVar5 + 0x48) = *(undefined4 *)(in_r0 + 0x10);
    *(undefined4 *)(iVar5 + 0x4c) = uVar2;
    *(undefined4 *)(iVar5 + 0x50) = uVar3;
    fVar8 = *(float *)(iVar5 + 0x4c);
    fVar7 = (float)Sin(in_s0);
    iVar4 = *(int *)(in_r0 + 0x58);
    iVar6 = *(int *)(in_r0 + 0x48);
    cVar1 = *(char *)(iVar4 + 0x374);
    *(float *)(iVar5 + 0x4c) = fVar8 + fVar7 * 0.3;
    fVar7 = *(float *)(iVar4 + 0x360) + *(float *)(iVar4 + 0x34c);
    *(float *)(iVar6 + 0x7c) = fVar7;
    if (cVar1 != '\0') {
      *(float *)(iVar6 + 0x7c) = fVar7 + *(float *)(iVar4 + 0x390) + *(float *)(iVar4 + 0x38c);
    }
    break;
  case 2:
    break;
  case 3:
    break;
  case 4:
    fVar8 = *(float *)(in_r0 + 0x14);
    fVar7 = (float)Sin(in_s0);
    iVar5 = *(int *)(in_r0 + 0x30);
    *(undefined4 *)(in_r0 + 0x5c) = 0;
    *(undefined4 *)(in_r0 + 0x60) = 0x3d2aaaab;
    local_2c = *(float *)((int)&__DT_SYMTAB[0x10a].st_size + iVar5) - *(float *)(in_r0 + 0x18);
    local_34 = *(float *)((int)&__DT_SYMTAB[0x10a].st_name + iVar5) - *(float *)(in_r0 + 0x10);
    fVar8 = fVar8 + fVar7 * 0.3;
    *(float *)(in_r0 + 0x14) = fVar8;
    local_30 = *(float *)((int)&__DT_SYMTAB[0x10a].st_value + iVar5) - fVar8;
    uVar2 = tVector::Magnitude((tVector *)&local_34);
    iVar5 = *(int *)(in_r0 + 0x30);
    *(undefined4 *)(in_r0 + 0x2c) = 5;
    *(undefined4 *)(in_r0 + 100) = uVar2;
    fVar8 = *(float *)((int)&__DT_SYMTAB[0x10a].st_value + iVar5);
    fVar7 = *(float *)((int)&__DT_SYMTAB[0x10a].st_name + iVar5);
    *(float *)(in_r0 + 0x70) =
         *(float *)(in_r0 + 0x18) - *(float *)((int)&__DT_SYMTAB[0x10a].st_size + iVar5);
    *(float *)(in_r0 + 0x68) = *(float *)(in_r0 + 0x10) - fVar7;
    *(float *)(in_r0 + 0x6c) = *(float *)(in_r0 + 0x14) - fVar8;
    in_s0 = (float)tVector::Normalize((tVector *)(in_r0 + 0x68));
    iVar5 = *(int *)(in_r0 + 0x30);
    goto LAB_00074cb8;
  case 5:
LAB_00074cb8:
    fVar7 = 1.0 - *(float *)(in_r0 + 0x5c);
    fVar10 = *(float *)((int)&__DT_SYMTAB[0x10a].st_name + iVar5);
    fVar8 = *(float *)((int)&__DT_SYMTAB[0x10a].st_size + iVar5);
    iVar6 = *(int *)(in_r0 + 0x48);
    fVar9 = fVar7 * *(float *)(in_r0 + 100);
    fVar7 = fVar7 * 0.6 + 0.4;
    *(float *)(in_r0 + 0x14) =
         *(float *)((int)&__DT_SYMTAB[0x10a].st_value + iVar5) + fVar9 * *(float *)(in_r0 + 0x6c);
    *(float *)(in_r0 + 0x18) = fVar8 + fVar9 * *(float *)(in_r0 + 0x70);
    *(float *)(in_r0 + 0x10) = fVar10 + fVar9 * *(float *)(in_r0 + 0x68);
    *(float *)(iVar6 + 0x60) = fVar7;
    *(float *)(iVar6 + 100) = fVar7;
    fVar7 = (float)Sin(in_s0);
    fVar11 = *(float *)(in_r0 + 0x14);
    fVar8 = *(float *)((int)DWORD_ARRAY_000110f8 + iVar5 + 0x1210);
    fVar10 = *(float *)(in_r0 + 0x18);
    fVar9 = *(float *)((int)DWORD_ARRAY_000110f8 + iVar5 + 0x120c);
    fVar7 = fVar7 * 0.5;
    *(float *)(iVar6 + 0x48) =
         *(float *)(in_r0 + 0x10) + fVar7 * *(float *)((int)DWORD_ARRAY_000110f8 + iVar5 + 0x1208);
    *(float *)(iVar6 + 0x4c) = fVar11 + fVar7 * fVar9;
    *(float *)(iVar6 + 0x50) = fVar10 + fVar7 * fVar8;
    fVar7 = *(float *)(in_r0 + 0x5c) + *(float *)(in_r0 + 0x60);
    *(float *)(in_r0 + 0x5c) = fVar7;
    if (1.0 < fVar7) {
LAB_00074f84:
      *(undefined4 *)(in_r0 + 0x2c) = 0;
      cRSprite::Kill(*(cRSprite **)(in_r0 + 0x48));
    }
    break;
  case 6:
    *(undefined4 *)(in_r0 + 0x2c) = 7;
    *(undefined4 *)(in_r0 + 0x60) = 0x3c888889;
    *(undefined4 *)(in_r0 + 0x5c) = 0;
    uVar2 = gRMathRand2();
    fVar7 = (float)VectorSignedToFloat(uVar2,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(in_r0 + 0x74) = (fVar7 - 16384.0) * 6.1035156e-05;
    uVar2 = gRMathRand2();
    iVar5 = *(int *)(in_r0 + 0x30);
    *(undefined4 *)(in_r0 + 0x7c) = 0;
    fVar7 = (float)VectorSignedToFloat(uVar2,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(in_r0 + 0x78) = (fVar7 - 16384.0) * 6.1035156e-05 * 1.5 + 1.0;
    in_s0 = extraout_s0;
    goto LAB_00074e60;
  case 7:
LAB_00074e60:
    fVar11 = *(float *)(in_r0 + 0x5c);
    fVar9 = *(float *)((int)&__DT_SYMTAB[0x10a].st_name + iVar5);
    fVar10 = fVar11 * 0.6 + 0.4;
    fVar7 = *(float *)((int)&__DT_SYMTAB[0x10a].st_size + iVar5);
    local_2c = *(float *)(gGroup0 + iVar5 + 0xc1f3c);
    fVar8 = *(float *)((int)&__DT_SYMTAB[0x10a].st_value + iVar5);
    iVar6 = *(int *)(in_r0 + 0x48);
    local_34 = *(float *)(gGroup0 + iVar5 + 0xc1f34) - fVar9;
    local_30 = *(float *)(gGroup0 + iVar5 + 0xc1f38) - fVar8;
    *(float *)(iVar6 + 0x48) = fVar9 + fVar11 * local_34;
    local_2c = local_2c - fVar7;
    *(float *)(iVar6 + 0x60) = fVar10;
    *(float *)(iVar6 + 100) = fVar10;
    *(float *)(iVar6 + 0x4c) = fVar8 + fVar11 * local_30;
    *(float *)(iVar6 + 0x50) = fVar7 + fVar11 * local_2c;
    fVar7 = (float)Sin(in_s0);
    fVar9 = *(float *)(in_r0 + 0x78);
    fVar8 = *(float *)(in_r0 + 0x7c);
    *(float *)(iVar6 + 0x48) = *(float *)(iVar6 + 0x48) + fVar7 * *(float *)(in_r0 + 0x74);
    *(float *)(iVar6 + 0x4c) = *(float *)(iVar6 + 0x4c) + fVar7 * fVar9;
    *(float *)(iVar6 + 0x50) = *(float *)(iVar6 + 0x50) + fVar7 * fVar8;
    fVar7 = *(float *)(in_r0 + 0x5c) + *(float *)(in_r0 + 0x60);
    *(float *)(in_r0 + 0x5c) = fVar7;
    if (fVar7 <= 1.0) {
      return;
    }
    cRCompletion::RegisterParcel((cRCompletion *)(gGroup0 + *(int *)(in_r0 + 0x30) + 0xc1f04));
    goto LAB_00074f84;
  }
  return;
}
