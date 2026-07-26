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
  float fVar12;
  float local_34;
  float local_30;
  float local_2c;

  uVar2 = DAT_00074dd8;
  iVar5 = *(int *)(in_r0 + 0x30);
  if (*(char *)(iVar5 + 0x19) != '\0') {
    return;
  }
  switch(*(undefined4 *)(in_r0 + 0x2c)) {
  case 1:
    if (*(float *)(in_r0 + 0x18) <
        *(float *)((int)DWORD_ARRAY_000110f8 + iVar5 + 0x11c8) - DAT_00074dc8) {
      in_s0 = (float)cRSprite::Kill(*(cRSprite **)(in_r0 + 0x48));
      *(undefined4 *)(in_r0 + 0x2c) = 0;
    }
    fVar7 = DAT_00074df8;
    fVar8 = *(float *)(in_r0 + 0x50) + *(float *)(in_r0 + 0x54);
    iVar5 = *(int *)(in_r0 + 0x48);
    uVar2 = *(undefined4 *)(in_r0 + 0x14);
    uVar3 = *(undefined4 *)(in_r0 + 0x18);
    *(float *)(in_r0 + 0x50) = fVar8;
    if (fVar7 < fVar8) {
      *(float *)(in_r0 + 0x50) = fVar8 - fVar7;
    }
    *(undefined4 *)(iVar5 + 0x48) = *(undefined4 *)(in_r0 + 0x10);
    *(undefined4 *)(iVar5 + 0x4c) = uVar2;
    *(undefined4 *)(iVar5 + 0x50) = uVar3;
    fVar8 = *(float *)(iVar5 + 0x4c);
    fVar7 = (float)Sin(in_s0);
    iVar4 = *(int *)(in_r0 + 0x58);
    iVar6 = *(int *)(in_r0 + 0x48);
    cVar1 = *(char *)(iVar4 + 0x374);
    *(float *)(iVar5 + 0x4c) = fVar8 + fVar7 * DAT_00074dcc;
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
    *(undefined4 *)(in_r0 + 0x5c) = DAT_00074ddc;
    *(undefined4 *)(in_r0 + 0x60) = DAT_00074dd0;
    local_2c = *(float *)((int)&__DT_SYMTAB[0x10a].st_size + iVar5) - *(float *)(in_r0 + 0x18);
    local_34 = *(float *)((int)&__DT_SYMTAB[0x10a].st_name + iVar5) - *(float *)(in_r0 + 0x10);
    fVar8 = fVar8 + fVar7 * DAT_00074dcc;
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
    fVar7 = DAT_00074df8;
    fVar8 = DAT_00074df8 - *(float *)(in_r0 + 0x5c);
    fVar12 = *(float *)((int)&__DT_SYMTAB[0x10a].st_name + iVar5);
    fVar9 = *(float *)((int)&__DT_SYMTAB[0x10a].st_size + iVar5);
    iVar6 = *(int *)(in_r0 + 0x48);
    fVar10 = fVar8 * *(float *)(in_r0 + 100);
    fVar8 = DAT_00074df0 + fVar8 * DAT_00074dec;
    *(float *)(in_r0 + 0x14) =
         *(float *)((int)&__DT_SYMTAB[0x10a].st_value + iVar5) + fVar10 * *(float *)(in_r0 + 0x6c);
    *(float *)(in_r0 + 0x18) = fVar9 + fVar10 * *(float *)(in_r0 + 0x70);
    *(float *)(in_r0 + 0x10) = fVar12 + fVar10 * *(float *)(in_r0 + 0x68);
    *(float *)(iVar6 + 0x60) = fVar8;
    *(float *)(iVar6 + 100) = fVar8;
    fVar8 = (float)Sin(in_s0);
    fVar11 = *(float *)(in_r0 + 0x14);
    fVar9 = *(float *)((int)DWORD_ARRAY_000110f8 + iVar5 + 0x1210);
    fVar12 = *(float *)(in_r0 + 0x18);
    fVar10 = *(float *)((int)DWORD_ARRAY_000110f8 + iVar5 + 0x120c);
    fVar8 = fVar8 * DAT_00074dd4;
    *(float *)(iVar6 + 0x48) =
         *(float *)(in_r0 + 0x10) + fVar8 * *(float *)((int)DWORD_ARRAY_000110f8 + iVar5 + 0x1208);
    *(float *)(iVar6 + 0x4c) = fVar11 + fVar8 * fVar10;
    *(float *)(iVar6 + 0x50) = fVar12 + fVar8 * fVar9;
    fVar8 = *(float *)(in_r0 + 0x5c) + *(float *)(in_r0 + 0x60);
    *(float *)(in_r0 + 0x5c) = fVar8;
    if (fVar7 < fVar8) {
LAB_00074f84:
      *(undefined4 *)(in_r0 + 0x2c) = 0;
      cRSprite::Kill(*(cRSprite **)(in_r0 + 0x48));
    }
    break;
  case 6:
    *(undefined4 *)(in_r0 + 0x2c) = 7;
    uVar3 = DAT_00074ddc;
    *(undefined4 *)(in_r0 + 0x60) = uVar2;
    *(undefined4 *)(in_r0 + 0x5c) = uVar3;
    uVar2 = gRMathRand2();
    fVar8 = DAT_00074de4;
    fVar7 = DAT_00074de0;
    fVar9 = (float)VectorSignedToFloat(uVar2,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(in_r0 + 0x74) = (fVar9 - DAT_00074de0) * DAT_00074de4;
    uVar2 = gRMathRand2();
    fVar9 = DAT_00074df8;
    iVar5 = *(int *)(in_r0 + 0x30);
    *(undefined4 *)(in_r0 + 0x7c) = uVar3;
    fVar10 = (float)VectorSignedToFloat(uVar2,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(in_r0 + 0x78) = fVar9 + (fVar10 - fVar7) * fVar8 * DAT_00074de8;
    in_s0 = extraout_s0;
    goto LAB_00074e60;
  case 7:
LAB_00074e60:
    fVar12 = *(float *)(in_r0 + 0x5c);
    fVar9 = *(float *)((int)&__DT_SYMTAB[0x10a].st_name + iVar5);
    fVar10 = DAT_00074df0 + fVar12 * DAT_00074dec;
    fVar7 = *(float *)((int)&__DT_SYMTAB[0x10a].st_size + iVar5);
    local_2c = *(float *)(gGroup0 + iVar5 + 0xc1f3c);
    fVar8 = *(float *)((int)&__DT_SYMTAB[0x10a].st_value + iVar5);
    iVar6 = *(int *)(in_r0 + 0x48);
    local_34 = *(float *)(gGroup0 + iVar5 + 0xc1f34) - fVar9;
    local_30 = *(float *)(gGroup0 + iVar5 + 0xc1f38) - fVar8;
    *(float *)(iVar6 + 0x48) = fVar9 + fVar12 * local_34;
    local_2c = local_2c - fVar7;
    *(float *)(iVar6 + 0x60) = fVar10;
    *(float *)(iVar6 + 100) = fVar10;
    *(float *)(iVar6 + 0x4c) = fVar8 + fVar12 * local_30;
    *(float *)(iVar6 + 0x50) = fVar7 + fVar12 * local_2c;
    fVar7 = (float)Sin(in_s0);
    fVar9 = *(float *)(in_r0 + 0x78);
    fVar8 = *(float *)(in_r0 + 0x7c);
    *(float *)(iVar6 + 0x48) = *(float *)(iVar6 + 0x48) + fVar7 * *(float *)(in_r0 + 0x74);
    *(float *)(iVar6 + 0x4c) = *(float *)(iVar6 + 0x4c) + fVar7 * fVar9;
    *(float *)(iVar6 + 0x50) = *(float *)(iVar6 + 0x50) + fVar7 * fVar8;
    fVar7 = DAT_00074df8;
    fVar8 = *(float *)(in_r0 + 0x5c) + *(float *)(in_r0 + 0x60);
    *(float *)(in_r0 + 0x5c) = fVar8;
    if (fVar8 <= fVar7) {
      return;
    }
    cRCompletion::RegisterParcel((cRCompletion *)(gGroup0 + *(int *)(in_r0 + 0x30) + 0xc1f04));
    goto LAB_00074f84;
  }
  return;
}
