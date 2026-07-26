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
  undefined4 *puVar5;
  float in_s0;
  float fVar6;

  iVar1 = Game;
  switch(*(undefined4 *)(in_r0 + 0x74)) {
  case 0:
    if ((*(uint *)(Game + 0x81688) & 0x80) == 0) {
      *(uint *)(Game + 0x85240) = *(uint *)(Game + 0x85240) & 0xffffffdf;
      return;
    }
    Start(in_r0);
    return;
  case 1:
    fVar6 = *(float *)(in_r0 + 0x80);
    *(float *)(in_r0 + 0x80) = fVar6 + *(float *)(in_r0 + 0x84);
    if (1.0 < fVar6 + *(float *)(in_r0 + 0x84)) {
      *(undefined4 *)(in_r0 + 0x80) = 0x3f800000;
      *(undefined4 *)(in_r0 + 0x74) = 2;
    }
    break;
  case 2:
    break;
  case 3:
    fVar6 = *(float *)(in_r0 + 0x80);
    *(float *)(in_r0 + 0x80) = fVar6 - *(float *)(in_r0 + 0x84);
    iVar1 = Game;
    if (fVar6 - *(float *)(in_r0 + 0x84) < 0.0) {
      *(undefined4 *)(in_r0 + 0x80) = 0;
      *(undefined4 *)(in_r0 + 0x74) = 0;
      cRSnailSkin::Change((cRSnailSkin *)(Game + 0x852d4),0,in_s0);
      return;
    }
    if ((*(uint *)(Game + 0x81688) & 0x80) != 0) {
      *(undefined4 *)(in_r0 + 0x74) = 1;
    }
  default:
    goto switchD_0007241c_default;
  }
  iVar1 = Game;
  if ((*(uint *)(Game + 0x81688) & 0x80) == 0) {
    *(undefined4 *)(in_r0 + 0x74) = 3;
  }
switchD_0007241c_default:
  fVar6 = *(float *)(in_r0 + 0x78) + *(float *)(in_r0 + 0x7c);
  *(float *)(in_r0 + 0x78) = fVar6;
  if (1.0 < fVar6) {
    *(float *)(in_r0 + 0x78) = fVar6 - 1.0;
  }
  cRSnailSkin::Change((cRSnailSkin *)(iVar1 + 0x852d4),2,in_s0);
  fVar6 = (float)tColourSmall::White((tColourSmall *)(in_r0 + 0x28));
  fVar6 = (float)tColourSmall::Alpha((tColourSmall *)(in_r0 + 0x28),fVar6);
  iVar1 = Game;
  uVar2 = *(undefined4 *)(Game + 0x83b94);
  uVar3 = *(undefined4 *)(Game + 0x83b98);
  uVar4 = *(undefined4 *)(Game + 0x83b9c);
  puVar5 = (undefined4 *)(Game + 0x83ba0);
  *(undefined4 *)(in_r0 + 0x2c) = *(undefined4 *)(Game + 0x83b90);
  *(undefined4 *)(in_r0 + 0x30) = uVar2;
  *(undefined4 *)(in_r0 + 0x34) = uVar3;
  *(undefined4 *)(in_r0 + 0x38) = uVar4;
  uVar2 = *(undefined4 *)(iVar1 + 0x83ba4);
  uVar3 = *(undefined4 *)(iVar1 + 0x83ba8);
  uVar4 = *(undefined4 *)(iVar1 + 0x83bac);
  *(undefined4 *)(in_r0 + 0x3c) = *puVar5;
  *(undefined4 *)(in_r0 + 0x40) = uVar2;
  *(undefined4 *)(in_r0 + 0x44) = uVar3;
  *(undefined4 *)(in_r0 + 0x48) = uVar4;
  uVar2 = *(undefined4 *)(iVar1 + 0x83bb4);
  uVar3 = *(undefined4 *)(iVar1 + 0x83bb8);
  uVar4 = *(undefined4 *)(iVar1 + 0x83bbc);
  *(undefined4 *)(in_r0 + 0x4c) = *(undefined4 *)(iVar1 + 0x83bb0);
  *(undefined4 *)(in_r0 + 0x50) = uVar2;
  *(undefined4 *)(in_r0 + 0x54) = uVar3;
  *(undefined4 *)(in_r0 + 0x58) = uVar4;
  uVar2 = *(undefined4 *)(iVar1 + 0x83bc4);
  uVar3 = *(undefined4 *)(iVar1 + 0x83bc8);
  uVar4 = *(undefined4 *)(iVar1 + 0x83bcc);
  *(undefined4 *)(in_r0 + 0x5c) = *(undefined4 *)(iVar1 + 0x83bc0);
  *(undefined4 *)(in_r0 + 0x60) = uVar2;
  *(undefined4 *)(in_r0 + 100) = uVar3;
  *(undefined4 *)(in_r0 + 0x68) = uVar4;
  tMatrix::RotLocalY((tMatrix *)(in_r0 + 0x2c),fVar6);
  return;
}
