/*
 * mangled: _ZN10cRBackdrop2AIEv
 * demangled: cRBackdrop::AI()
 * address: 00041994
 * size: 452
 */

/* cRBackdrop::AI() */

void __thiscall cRBackdrop::AI(cRBackdrop *this)

{
  cRBackdrop *pcVar1;
  int iVar2;
  int iVar3;
  float fVar4;
  float fVar5;
  float fVar6;

  fVar4 = *(float *)(*(int *)PTR__Game_001b60b8 + 0x3c);
  if (((((fVar4 == 0.0) || (fVar4 == 180.0)) &&
       ((*(float *)(this + 0x38) == 90.0 || (*(float *)(this + 0x38) == 270.0)))) ||
      (((fVar4 == 90.0 || (fVar4 == 270.0)) &&
       ((*(float *)(this + 0x38) == 0.0 || (*(float *)(this + 0x38) == 180.0)))))) &&
     ((&DAT_003594e4)[*(int *)(this + 0x54) * 0x1ac + *(int *)PTR__Game_001b60b8] != '\0')) {
    this[0x58] = (cRBackdrop)0x1;
    *(undefined4 *)(this + 0x50) = 0xffffffff;
  }
  *(undefined4 *)(this + 0x38) = *(undefined4 *)(*(int *)PTR__Game_001b60b8 + 0x3c);
  *(float *)(this + 0x13c8) =
       *(float *)(this + 0x13c8) + (*(float *)(this + 0x13cc) - *(float *)(this + 0x13c8)) * 0.3;
  if (this[0x58] != (cRBackdrop)0x0) {
    ChangeReal(this);
    this[0x58] = (cRBackdrop)0x0;
  }
  iVar3 = 0;
  do {
    pcVar1 = this + iVar3 * 0x28 + 0x74;
    iVar2 = 0;
    do {
      fVar5 = *(float *)(pcVar1 + 4);
      iVar2 = iVar2 + 1;
      fVar4 = *(float *)(pcVar1 + -4) + *(float *)pcVar1;
      *(float *)(pcVar1 + -4) = fVar4;
      if (6.2831855 < fVar4) {
        fVar4 = fVar4 - 6.2831855;
        *(float *)(pcVar1 + -4) = fVar4;
      }
      fVar4 = (float)Sin(fVar4);
      fVar6 = *(float *)(pcVar1 + 8);
      *(float *)(pcVar1 + 0xc) = fVar5 * fVar4;
      fVar4 = (float)Cos(*(float *)(pcVar1 + -4));
      *(float *)(pcVar1 + 0x10) = fVar6 * fVar4;
      pcVar1 = pcVar1 + 0x1b8;
    } while (iVar2 != 0xb);
    iVar3 = iVar3 + 1;
  } while (iVar3 != 0xb);
  return;
}
