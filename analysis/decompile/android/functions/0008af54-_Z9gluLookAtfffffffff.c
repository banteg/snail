/*
 * mangled: _Z9gluLookAtfffffffff
 * demangled: gluLookAt(float, float, float, float, float, float, float, float, float)
 * address: 0008af54
 * size: 368
 */

/* gluLookAt(float, float, float, float, float, float, float, float, float) */

void gluLookAt(float param_1,float param_2,float param_3,float param_4,float param_5,float param_6,
              float param_7,float param_8,float param_9)

{
  float fVar1;
  float in_r0;
  float in_r1;
  float in_r2;
  float in_r3;
  float extraout_s0;
  float extraout_s1;
  float extraout_s2;
  float extraout_s3;
  float extraout_s4;
  float extraout_s5;
  float *pfVar2;
  float fVar3;
  float fVar4;
  float in_stack_00000000;
  float in_stack_00000004;
  float *local_78;
  undefined4 local_74;
  float local_70;
  undefined4 local_68;
  undefined4 local_64;
  float local_60;
  undefined4 local_58;
  undefined4 local_54;
  float local_50;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  float *local_2c;
  undefined4 local_28;
  undefined4 local_24;

  fVar3 = in_stack_00000000 - in_r1;
  pfVar2 = (float *)(in_r3 - in_r0);
  fVar4 = in_stack_00000004 - in_r2;
  fVar1 = SQRT(fVar3 * fVar3 + (float)pfVar2 * (float)pfVar2 + fVar4 * fVar4);
  if (fVar1 != 0.0) {
    fVar4 = fVar4 / fVar1;
    pfVar2 = (float *)((float)pfVar2 / fVar1);
    fVar3 = fVar3 / fVar1;
  }
  CrossProd(param_1,param_2,param_3,param_4,param_5,param_6,pfVar2);
  CrossProd(extraout_s0,extraout_s1,extraout_s2,extraout_s3,extraout_s4,extraout_s5,local_2c);
  memset(&local_78,0,0x40);
  local_3c = 0x3f800000;
  local_50 = -fVar4;
  local_78 = local_2c;
  local_74 = local_38;
  local_68 = local_28;
  local_64 = local_34;
  local_58 = local_24;
  local_54 = local_30;
  local_70 = -(float)pfVar2;
  local_60 = -fVar3;
  glMultMatrixf(&local_78);
  glTranslatef(-in_r0,-in_r1,-in_r2);
  return;
}
