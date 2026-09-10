
/* tQuaternian::tQuaternian(tMatrix const&) */

tQuaternian * __thiscall tQuaternian::tQuaternian(tQuaternian *this,tMatrix *param_1)

{
  undefined4 uVar1;
  float fVar2;
  int iVar3;
  float fVar4;
  undefined4 uVar5;
  int iVar6;
  char *pcVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined8 uVar10;
  
  uVar8 = *(undefined4 *)param_1;
  uVar5 = *(undefined4 *)(param_1 + 0x14);
  uVar9 = *(undefined4 *)(param_1 + 0x28);
  uVar1 = __addsf3(uVar8,uVar5);
  uVar1 = __addsf3(uVar1,uVar9);
  fVar2 = (float)__addsf3(uVar1,0x3f800000);
  iVar3 = __aeabi_fcmpgt(fVar2,DAT_00029fac);
  iVar6 = DAT_00029fb0 + 0x29c74;
  if (iVar3 != 0) {
    fVar2 = Sqrt(fVar2);
    uVar1 = __aeabi_fdiv(0x3f000000,fVar2);
    uVar5 = __aeabi_fdiv(0x3e800000,uVar1);
    *(undefined4 *)(this + 0xc) = uVar5;
    uVar5 = __aeabi_fsub(*(undefined4 *)(param_1 + 0x18),*(undefined4 *)(param_1 + 0x24));
    uVar5 = __aeabi_fmul(uVar5,uVar1);
    *(undefined4 *)this = uVar5;
    uVar5 = __aeabi_fsub(*(undefined4 *)(param_1 + 0x20),*(undefined4 *)(param_1 + 8));
    uVar5 = __aeabi_fmul(uVar5,uVar1);
    *(undefined4 *)(this + 4) = uVar5;
    uVar5 = __aeabi_fsub(*(undefined4 *)(param_1 + 4),*(undefined4 *)(param_1 + 0x10));
    uVar1 = __aeabi_fmul(uVar5,uVar1);
    *(undefined4 *)(this + 8) = uVar1;
    return this;
  }
  iVar3 = __aeabi_fcmpge(uVar8,uVar5);
  if (iVar3 == 0) {
    iVar3 = __aeabi_fcmpge(uVar5,uVar9);
    if (iVar3 == 0) {
      iVar3 = __aeabi_fcmpgt(uVar8,uVar9);
      if (iVar3 == 0) goto LAB_00029da0;
      goto LAB_00029e44;
    }
  }
  else {
    iVar3 = __aeabi_fcmpgt(uVar8,uVar9);
    if (iVar3 != 0) {
LAB_00029e44:
      uVar1 = __addsf3(uVar8,0x3f800000);
      uVar1 = __aeabi_fsub(uVar1,uVar5);
      fVar4 = (float)__aeabi_fsub(uVar1,uVar9);
      iVar3 = __aeabi_fcmplt(fVar4,0);
      fVar2 = fVar4;
      if (iVar3 != 0) {
        fVar2 = 0.0;
        pcVar7 = (char *)(iVar6 + DAT_00029fb8);
        uVar10 = __aeabi_f2d(fVar4);
        uVar1 = (undefined4)((ulonglong)uVar10 >> 0x20);
        wprintf(pcVar7,uVar1,(int)uVar10,uVar1);
      }
      fVar2 = Sqrt(fVar2);
      uVar1 = __addsf3(fVar2,fVar2);
      uVar5 = __aeabi_fmul(uVar1,0x3e800000);
      *(undefined4 *)this = uVar5;
      uVar5 = __addsf3(*(undefined4 *)(param_1 + 0x10),*(undefined4 *)(param_1 + 4));
      uVar5 = __aeabi_fdiv(uVar5,uVar1);
      *(undefined4 *)(this + 4) = uVar5;
      uVar5 = __addsf3(*(undefined4 *)(param_1 + 0x20),*(undefined4 *)(param_1 + 8));
      uVar5 = __aeabi_fdiv(uVar5,uVar1);
      *(undefined4 *)(this + 8) = uVar5;
      uVar5 = __addsf3(*(undefined4 *)(param_1 + 0x24),*(undefined4 *)(param_1 + 0x18));
      uVar1 = __aeabi_fdiv(uVar5,uVar1);
      *(undefined4 *)(this + 0xc) = uVar1;
      return this;
    }
    iVar3 = __aeabi_fcmpgt(uVar5,uVar9);
    if (iVar3 == 0) {
LAB_00029da0:
      uVar1 = __addsf3(uVar9,0x3f800000);
      uVar1 = __aeabi_fsub(uVar1,uVar8);
      fVar4 = (float)__aeabi_fsub(uVar1,uVar5);
      iVar3 = __aeabi_fcmplt(fVar4,0);
      fVar2 = fVar4;
      if (iVar3 != 0) {
        fVar2 = 0.0;
        pcVar7 = (char *)(iVar6 + DAT_00029fb4);
        uVar10 = __aeabi_f2d(fVar4);
        uVar1 = (undefined4)((ulonglong)uVar10 >> 0x20);
        wprintf(pcVar7,uVar1,(int)uVar10,uVar1);
      }
      fVar2 = Sqrt(fVar2);
      uVar1 = __addsf3(fVar2,fVar2);
      uVar5 = __addsf3(*(undefined4 *)(param_1 + 0x20),*(undefined4 *)(param_1 + 8));
      uVar5 = __aeabi_fdiv(uVar5,uVar1);
      *(undefined4 *)this = uVar5;
      uVar5 = __addsf3(*(undefined4 *)(param_1 + 0x24),*(undefined4 *)(param_1 + 0x18));
      uVar5 = __aeabi_fdiv(uVar5,uVar1);
      *(undefined4 *)(this + 4) = uVar5;
      uVar5 = __aeabi_fmul(uVar1,0x3e800000);
      *(undefined4 *)(this + 8) = uVar5;
      uVar5 = __addsf3(*(undefined4 *)(param_1 + 0x10),*(undefined4 *)(param_1 + 4));
      uVar1 = __aeabi_fdiv(uVar5,uVar1);
      *(undefined4 *)(this + 0xc) = uVar1;
      return this;
    }
  }
  uVar1 = __addsf3(uVar5,0x3f800000);
  uVar1 = __aeabi_fsub(uVar1,uVar8);
  fVar4 = (float)__aeabi_fsub(uVar1,uVar9);
  iVar3 = __aeabi_fcmplt(fVar4,0);
  fVar2 = fVar4;
  if (iVar3 != 0) {
    fVar2 = 0.0;
    pcVar7 = (char *)(iVar6 + DAT_00029fb4);
    uVar10 = __aeabi_f2d(fVar4);
    uVar1 = (undefined4)((ulonglong)uVar10 >> 0x20);
    wprintf(pcVar7,uVar1,(int)uVar10,uVar1);
  }
  fVar2 = Sqrt(fVar2);
  uVar1 = __addsf3(fVar2,fVar2);
  uVar5 = __addsf3(*(undefined4 *)(param_1 + 0x10),*(undefined4 *)(param_1 + 4));
  uVar5 = __aeabi_fdiv(uVar5,uVar1);
  *(undefined4 *)this = uVar5;
  uVar5 = __aeabi_fmul(uVar1,0x3e800000);
  *(undefined4 *)(this + 4) = uVar5;
  uVar5 = __addsf3(*(undefined4 *)(param_1 + 0x24),*(undefined4 *)(param_1 + 0x18));
  uVar5 = __aeabi_fdiv(uVar5,uVar1);
  *(undefined4 *)(this + 8) = uVar5;
  uVar5 = __addsf3(*(undefined4 *)(param_1 + 0x20),*(undefined4 *)(param_1 + 8));
  uVar1 = __aeabi_fdiv(uVar5,uVar1);
  *(undefined4 *)(this + 0xc) = uVar1;
  return this;
}

