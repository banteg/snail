
/* tQuaternian::tQuaternian(tMatrix const&) */

tQuaternian * __thiscall tQuaternian::tQuaternian(tQuaternian *this,tMatrix *param_1)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  char *pcVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  float extraout_s0;
  float extraout_s0_00;
  float fVar8;
  float extraout_s0_01;
  float extraout_s0_02;
  undefined8 uVar9;
  
  uVar6 = *(undefined4 *)param_1;
  uVar3 = *(undefined4 *)(param_1 + 0x14);
  uVar7 = *(undefined4 *)(param_1 + 0x28);
  uVar1 = __addsf3(uVar6,uVar3);
  uVar1 = __addsf3(uVar1,uVar7);
  uVar1 = __addsf3(uVar1,0x3f800000);
  iVar2 = __aeabi_fcmpgt(uVar1,DAT_00029fac);
  iVar4 = DAT_00029fb0 + 0x29c74;
  if (iVar2 != 0) {
    uVar1 = Sqrt(extraout_s0);
    uVar1 = __aeabi_fdiv(0x3f000000,uVar1);
    uVar3 = __aeabi_fdiv(0x3e800000,uVar1);
    *(undefined4 *)(this + 0xc) = uVar3;
    uVar3 = __aeabi_fsub(*(undefined4 *)(param_1 + 0x18),*(undefined4 *)(param_1 + 0x24));
    uVar3 = __aeabi_fmul(uVar3,uVar1);
    *(undefined4 *)this = uVar3;
    uVar3 = __aeabi_fsub(*(undefined4 *)(param_1 + 0x20),*(undefined4 *)(param_1 + 8));
    uVar3 = __aeabi_fmul(uVar3,uVar1);
    *(undefined4 *)(this + 4) = uVar3;
    uVar3 = __aeabi_fsub(*(undefined4 *)(param_1 + 4),*(undefined4 *)(param_1 + 0x10));
    uVar1 = __aeabi_fmul(uVar3,uVar1);
    *(undefined4 *)(this + 8) = uVar1;
    return this;
  }
  iVar2 = __aeabi_fcmpge(uVar6,uVar3);
  if (iVar2 == 0) {
    iVar2 = __aeabi_fcmpge(uVar3,uVar7);
    if (iVar2 == 0) {
      iVar2 = __aeabi_fcmpgt(uVar6,uVar7);
      if (iVar2 == 0) goto LAB_00029da0;
      goto LAB_00029e44;
    }
  }
  else {
    iVar2 = __aeabi_fcmpgt(uVar6,uVar7);
    if (iVar2 != 0) {
LAB_00029e44:
      uVar1 = __addsf3(uVar6,0x3f800000);
      uVar1 = __aeabi_fsub(uVar1,uVar3);
      uVar1 = __aeabi_fsub(uVar1,uVar7);
      iVar2 = __aeabi_fcmplt(uVar1,0);
      fVar8 = extraout_s0_02;
      if (iVar2 != 0) {
        pcVar5 = (char *)(iVar4 + DAT_00029fb8);
        uVar9 = __aeabi_f2d(uVar1);
        uVar1 = (undefined4)((ulonglong)uVar9 >> 0x20);
        fVar8 = (float)wprintf(pcVar5,uVar1,(int)uVar9,uVar1);
      }
      uVar1 = Sqrt(fVar8);
      uVar1 = __addsf3(uVar1,uVar1);
      uVar3 = __aeabi_fmul(uVar1,0x3e800000);
      *(undefined4 *)this = uVar3;
      uVar3 = __addsf3(*(undefined4 *)(param_1 + 0x10),*(undefined4 *)(param_1 + 4));
      uVar3 = __aeabi_fdiv(uVar3,uVar1);
      *(undefined4 *)(this + 4) = uVar3;
      uVar3 = __addsf3(*(undefined4 *)(param_1 + 0x20),*(undefined4 *)(param_1 + 8));
      uVar3 = __aeabi_fdiv(uVar3,uVar1);
      *(undefined4 *)(this + 8) = uVar3;
      uVar3 = __addsf3(*(undefined4 *)(param_1 + 0x24),*(undefined4 *)(param_1 + 0x18));
      uVar1 = __aeabi_fdiv(uVar3,uVar1);
      *(undefined4 *)(this + 0xc) = uVar1;
      return this;
    }
    iVar2 = __aeabi_fcmpgt(uVar3,uVar7);
    if (iVar2 == 0) {
LAB_00029da0:
      uVar1 = __addsf3(uVar7,0x3f800000);
      uVar1 = __aeabi_fsub(uVar1,uVar6);
      uVar1 = __aeabi_fsub(uVar1,uVar3);
      iVar2 = __aeabi_fcmplt(uVar1,0);
      fVar8 = extraout_s0_01;
      if (iVar2 != 0) {
        pcVar5 = (char *)(iVar4 + DAT_00029fb4);
        uVar9 = __aeabi_f2d(uVar1);
        uVar1 = (undefined4)((ulonglong)uVar9 >> 0x20);
        fVar8 = (float)wprintf(pcVar5,uVar1,(int)uVar9,uVar1);
      }
      uVar1 = Sqrt(fVar8);
      uVar1 = __addsf3(uVar1,uVar1);
      uVar3 = __addsf3(*(undefined4 *)(param_1 + 0x20),*(undefined4 *)(param_1 + 8));
      uVar3 = __aeabi_fdiv(uVar3,uVar1);
      *(undefined4 *)this = uVar3;
      uVar3 = __addsf3(*(undefined4 *)(param_1 + 0x24),*(undefined4 *)(param_1 + 0x18));
      uVar3 = __aeabi_fdiv(uVar3,uVar1);
      *(undefined4 *)(this + 4) = uVar3;
      uVar3 = __aeabi_fmul(uVar1,0x3e800000);
      *(undefined4 *)(this + 8) = uVar3;
      uVar3 = __addsf3(*(undefined4 *)(param_1 + 0x10),*(undefined4 *)(param_1 + 4));
      uVar1 = __aeabi_fdiv(uVar3,uVar1);
      *(undefined4 *)(this + 0xc) = uVar1;
      return this;
    }
  }
  uVar1 = __addsf3(uVar3,0x3f800000);
  uVar1 = __aeabi_fsub(uVar1,uVar6);
  uVar1 = __aeabi_fsub(uVar1,uVar7);
  iVar2 = __aeabi_fcmplt(uVar1,0);
  fVar8 = extraout_s0_00;
  if (iVar2 != 0) {
    pcVar5 = (char *)(iVar4 + DAT_00029fb4);
    uVar9 = __aeabi_f2d(uVar1);
    uVar1 = (undefined4)((ulonglong)uVar9 >> 0x20);
    fVar8 = (float)wprintf(pcVar5,uVar1,(int)uVar9,uVar1);
  }
  uVar1 = Sqrt(fVar8);
  uVar1 = __addsf3(uVar1,uVar1);
  uVar3 = __addsf3(*(undefined4 *)(param_1 + 0x10),*(undefined4 *)(param_1 + 4));
  uVar3 = __aeabi_fdiv(uVar3,uVar1);
  *(undefined4 *)this = uVar3;
  uVar3 = __aeabi_fmul(uVar1,0x3e800000);
  *(undefined4 *)(this + 4) = uVar3;
  uVar3 = __addsf3(*(undefined4 *)(param_1 + 0x24),*(undefined4 *)(param_1 + 0x18));
  uVar3 = __aeabi_fdiv(uVar3,uVar1);
  *(undefined4 *)(this + 8) = uVar3;
  uVar3 = __addsf3(*(undefined4 *)(param_1 + 0x20),*(undefined4 *)(param_1 + 8));
  uVar1 = __aeabi_fdiv(uVar3,uVar1);
  *(undefined4 *)(this + 0xc) = uVar1;
  return this;
}

