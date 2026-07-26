/*
 * mangled: _ZN12cRInvincible2AIEv
 * demangled: cRInvincible::AI()
 * address: 0001c300
 * size: 568
 */

/* cRInvincible::AI() */

void __thiscall cRInvincible::AI(cRInvincible *this)

{
  undefined *puVar1;
  undefined *puVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  float fVar7;

  puVar1 = PTR__Game_001b60b8;
  switch(*(undefined4 *)(this + 0x74)) {
  case 0:
    iVar3 = *(int *)PTR__Game_001b60b8;
    if ((*(uint *)(iVar3 + 0x822e4) & 0x80) != 0) {
      *(undefined4 *)(this + 0x74) = 1;
      *(undefined4 *)(this + 0x78) = 0;
      *(undefined4 *)(this + 0x80) = 0;
      *(undefined4 *)(this + 0x7c) = 0x3d088889;
      *(undefined4 *)(this + 0x84) = 0x3d088889;
      puVar2 = PTR__gBass_001b61c4;
      *(uint *)(*(int *)puVar1 + 0x85e94) = *(uint *)(*(int *)puVar1 + 0x85e94) | 0x20;
      cRBass::PlaySample((int)puVar2,6.86636e-44);
      return;
    }
    *(uint *)(iVar3 + 0x85e94) = *(uint *)(iVar3 + 0x85e94) & 0xffffffdf;
    return;
  case 1:
    fVar7 = *(float *)(this + 0x80);
    *(float *)(this + 0x80) = fVar7 + *(float *)(this + 0x84);
    if (1.0 < fVar7 + *(float *)(this + 0x84)) {
      *(undefined4 *)(this + 0x74) = 2;
      *(undefined4 *)(this + 0x80) = 0x3f800000;
    }
    break;
  case 2:
    break;
  case 3:
    fVar7 = *(float *)(this + 0x80);
    *(float *)(this + 0x80) = fVar7 - *(float *)(this + 0x84);
    if (fVar7 - *(float *)(this + 0x84) < 0.0) {
      *(undefined4 *)(this + 0x80) = 0;
      puVar1 = PTR__Game_001b60b8;
      *(undefined4 *)(this + 0x74) = 0;
      iVar3 = *(int *)puVar1;
      *(undefined4 *)(iVar3 + 0x85f3c) = 1;
      *(undefined4 *)(iVar3 + 0x85f28) = 0;
      *(undefined4 *)(iVar3 + 0x85f40) = 0;
      *(undefined4 *)(iVar3 + 0x85f44) = 0;
      return;
    }
    if ((*(uint *)(*(int *)PTR__Game_001b60b8 + 0x822e4) & 0x80) != 0) {
      *(undefined4 *)(this + 0x74) = 1;
    }
  default:
    goto switchD_0001c314_default;
  }
  if ((*(uint *)(*(int *)PTR__Game_001b60b8 + 0x822e4) & 0x80) == 0) {
    *(undefined4 *)(this + 0x74) = 3;
  }
switchD_0001c314_default:
  puVar1 = PTR__Game_001b60b8;
  fVar7 = *(float *)(this + 0x78) + *(float *)(this + 0x7c);
  *(float *)(this + 0x78) = fVar7;
  if (1.0 < fVar7) {
    *(float *)(this + 0x78) = fVar7 - 1.0;
  }
  iVar3 = *(int *)puVar1;
  *(undefined4 *)(iVar3 + 0x85f3c) = 1;
  *(undefined4 *)(iVar3 + 0x85f40) = 0;
  *(undefined4 *)(iVar3 + 0x85f44) = 0;
  *(undefined4 *)(iVar3 + 0x85f28) = 2;
  tColourSmall::White((tColourSmall *)(this + 0x28));
  tColourSmall::Alpha((tColourSmall *)(this + 0x28),*(float *)(this + 0x80) * 0.8);
  iVar3 = *(int *)puVar1;
  uVar4 = *(undefined4 *)(iVar3 + 0x847e8);
  uVar5 = *(undefined4 *)(iVar3 + 0x847ec);
  uVar6 = *(undefined4 *)(iVar3 + 0x847f0);
  *(undefined4 *)(this + 0x2c) = *(undefined4 *)(iVar3 + 0x847e4);
  *(undefined4 *)(this + 0x30) = uVar4;
  *(undefined4 *)(this + 0x34) = uVar5;
  *(undefined4 *)(this + 0x38) = uVar6;
  uVar4 = *(undefined4 *)(iVar3 + 0x847f8);
  uVar5 = *(undefined4 *)(iVar3 + 0x847fc);
  uVar6 = *(undefined4 *)(iVar3 + 0x84800);
  *(undefined4 *)(this + 0x3c) = *(undefined4 *)(iVar3 + 0x847f4);
  *(undefined4 *)(this + 0x40) = uVar4;
  *(undefined4 *)(this + 0x44) = uVar5;
  *(undefined4 *)(this + 0x48) = uVar6;
  uVar4 = *(undefined4 *)(iVar3 + 0x84808);
  uVar5 = *(undefined4 *)(iVar3 + 0x8480c);
  uVar6 = *(undefined4 *)(&DAT_00084810 + iVar3);
  *(undefined4 *)(this + 0x4c) = *(undefined4 *)(iVar3 + 0x84804);
  *(undefined4 *)(this + 0x50) = uVar4;
  *(undefined4 *)(this + 0x54) = uVar5;
  *(undefined4 *)(this + 0x58) = uVar6;
  uVar4 = *(undefined4 *)(&DAT_00084818 + iVar3);
  uVar5 = *(undefined4 *)(&DAT_0008481c + iVar3);
  uVar6 = *(undefined4 *)(&DAT_00084820 + iVar3);
  *(undefined4 *)(this + 0x5c) = *(undefined4 *)(&DAT_00084814 + iVar3);
  *(undefined4 *)(this + 0x60) = uVar4;
  *(undefined4 *)(this + 100) = uVar5;
  *(undefined4 *)(this + 0x68) = uVar6;
  tMatrix::RotLocalY((tMatrix *)(this + 0x2c),*(float *)(this + 0x78) * 6.2831855);
  return;
}
