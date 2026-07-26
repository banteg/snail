/*
 * mangled: _ZN12cRInvincible2AIEv
 * demangled: cRInvincible::AI()
 * address: 00072404
 * size: 488
 */

/* cRInvincible::AI() */

void cRInvincible::AI(void)

{
  cRInvincible *in_r0;
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  float in_s0;
  float fVar7;
  float fVar8;

  fVar7 = DAT_000725ec;
  iVar5 = DAT_000725f8 + 0x7241c;
  switch(*(undefined4 *)(in_r0 + 0x74)) {
  case 0:
    iVar5 = **(int **)(iVar5 + DAT_000725fc);
    if ((*(uint *)(iVar5 + 0x81688) & 0x80) == 0) {
      *(uint *)(iVar5 + 0x85240) = *(uint *)(iVar5 + 0x85240) & 0xffffffdf;
      return;
    }
    Start(in_r0);
    return;
  case 1:
    fVar8 = *(float *)(in_r0 + 0x80);
    *(float *)(in_r0 + 0x80) = fVar8 + *(float *)(in_r0 + 0x84);
    if (fVar7 < fVar8 + *(float *)(in_r0 + 0x84)) {
      *(float *)(in_r0 + 0x80) = fVar7;
      *(undefined4 *)(in_r0 + 0x74) = 2;
    }
    break;
  case 2:
    break;
  case 3:
    fVar7 = *(float *)(in_r0 + 0x80);
    *(float *)(in_r0 + 0x80) = fVar7 - *(float *)(in_r0 + 0x84);
    iVar6 = DAT_000725fc;
    if (fVar7 - *(float *)(in_r0 + 0x84) < 0.0) {
      *(undefined4 *)(in_r0 + 0x80) = 0;
      *(undefined4 *)(in_r0 + 0x74) = 0;
      cRSnailSkin::Change((cRSnailSkin *)(**(int **)(iVar5 + iVar6) + 0x852d4),0,in_s0);
      return;
    }
    iVar1 = **(int **)(iVar5 + DAT_000725fc);
    if ((*(uint *)(iVar1 + 0x81688) & 0x80) != 0) {
      *(undefined4 *)(in_r0 + 0x74) = 1;
    }
    goto switchD_0007241c_default;
  default:
    iVar1 = **(int **)(iVar5 + DAT_000725fc);
    iVar6 = DAT_000725fc;
    goto switchD_0007241c_default;
  }
  iVar6 = DAT_000725fc;
  iVar1 = **(int **)(iVar5 + DAT_000725fc);
  if ((*(uint *)(iVar1 + 0x81688) & 0x80) == 0) {
    *(undefined4 *)(in_r0 + 0x74) = 3;
  }
switchD_0007241c_default:
  fVar7 = DAT_000725ec;
  fVar8 = *(float *)(in_r0 + 0x78) + *(float *)(in_r0 + 0x7c);
  *(float *)(in_r0 + 0x78) = fVar8;
  if (fVar7 < fVar8) {
    *(float *)(in_r0 + 0x78) = fVar8 - fVar7;
  }
  cRSnailSkin::Change((cRSnailSkin *)(iVar1 + 0x852d4),2,in_s0);
  fVar7 = (float)tColourSmall::White((tColourSmall *)(in_r0 + 0x28));
  fVar7 = (float)tColourSmall::Alpha((tColourSmall *)(in_r0 + 0x28),fVar7);
  iVar5 = **(int **)(iVar5 + iVar6);
  uVar2 = *(undefined4 *)(iVar5 + 0x83b94);
  uVar3 = *(undefined4 *)(iVar5 + 0x83b98);
  uVar4 = *(undefined4 *)(iVar5 + 0x83b9c);
  *(undefined4 *)(in_r0 + 0x2c) = *(undefined4 *)(iVar5 + 0x83b90);
  *(undefined4 *)(in_r0 + 0x30) = uVar2;
  *(undefined4 *)(in_r0 + 0x34) = uVar3;
  *(undefined4 *)(in_r0 + 0x38) = uVar4;
  uVar2 = *(undefined4 *)(iVar5 + 0x83ba4);
  uVar3 = *(undefined4 *)(iVar5 + 0x83ba8);
  uVar4 = *(undefined4 *)(iVar5 + 0x83bac);
  *(undefined4 *)(in_r0 + 0x3c) = *(undefined4 *)(iVar5 + 0x83ba0);
  *(undefined4 *)(in_r0 + 0x40) = uVar2;
  *(undefined4 *)(in_r0 + 0x44) = uVar3;
  *(undefined4 *)(in_r0 + 0x48) = uVar4;
  uVar2 = *(undefined4 *)(iVar5 + 0x83bb4);
  uVar3 = *(undefined4 *)(iVar5 + 0x83bb8);
  uVar4 = *(undefined4 *)(iVar5 + 0x83bbc);
  *(undefined4 *)(in_r0 + 0x4c) = *(undefined4 *)(iVar5 + 0x83bb0);
  *(undefined4 *)(in_r0 + 0x50) = uVar2;
  *(undefined4 *)(in_r0 + 0x54) = uVar3;
  *(undefined4 *)(in_r0 + 0x58) = uVar4;
  uVar2 = *(undefined4 *)(iVar5 + 0x83bc4);
  uVar3 = *(undefined4 *)(iVar5 + 0x83bc8);
  uVar4 = *(undefined4 *)(iVar5 + 0x83bcc);
  *(undefined4 *)(in_r0 + 0x5c) = *(undefined4 *)(iVar5 + 0x83bc0);
  *(undefined4 *)(in_r0 + 0x60) = uVar2;
  *(undefined4 *)(in_r0 + 100) = uVar3;
  *(undefined4 *)(in_r0 + 0x68) = uVar4;
  tMatrix::RotLocalY((tMatrix *)(in_r0 + 0x2c),fVar7);
  return;
}
