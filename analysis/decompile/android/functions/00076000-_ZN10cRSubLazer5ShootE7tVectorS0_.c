/*
 * mangled: _ZN10cRSubLazer5ShootE7tVectorS0_
 * demangled: cRSubLazer::Shoot(tVector, tVector)
 * address: 00076000
 * size: 156
 */

/* cRSubLazer::Shoot(tVector, tVector) */

void cRSubLazer::Shoot(cRBod *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                      undefined4 param_5,undefined4 param_6,undefined4 param_7)

{
  float fVar1;
  int *piVar2;
  int iVar3;

  *(undefined4 *)(param_1 + 0x74) = 1;
  tMatrix::Identity((tMatrix *)(param_1 + 0x2c));
  *(undefined4 *)(param_1 + 0x8c) = DAT_0007609c;
  iVar3 = DAT_000760a4;
  fVar1 = DAT_000760a0;
  *(undefined4 *)(param_1 + 0x5c) = param_2;
  *(undefined4 *)(param_1 + 0x60) = param_3;
  *(undefined4 *)(param_1 + 100) = param_4;
  piVar2 = *(int **)(iVar3 + 0x76058 + DAT_000760a8);
  *(undefined4 *)(param_1 + 0x80) = param_5;
  *(undefined4 *)(param_1 + 0x84) = param_6;
  *(undefined4 *)(param_1 + 0x88) = param_7;
  iVar3 = *piVar2;
  *(float *)(param_1 + 0x90) = *(float *)(*(int *)(param_1 + 0x7c) + 0x54) * fVar1;
  cLinkedList<cRBod>::AddAfter
            ((cLinkedList<cRBod> *)(iVar3 + 0x358),param_1,
             (cRBod *)(*(int *)(param_1 + 0x7c) + 0x2ca0));
  tMatrix::SetZDir((tMatrix *)(param_1 + 0x2c),(tVector *)(param_1 + 0x80));
  return;
}
