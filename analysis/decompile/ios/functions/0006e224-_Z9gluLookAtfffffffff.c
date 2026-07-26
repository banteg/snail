/*
 * mangled: _Z9gluLookAtfffffffff
 * demangled: gluLookAt(float, float, float, float, float, float, float, float, float)
 * address: 0006e224
 * size: 308
 */

/* gluLookAt(float, float, float, float, float, float, float, float, float) */

void gluLookAt(float param_1,float param_2,float param_3,float param_4,float param_5,float param_6,
              float param_7,float param_8,float param_9)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float local_6c;
  float local_68;
  float local_64;
  float local_5c;
  float local_58;
  float local_54;
  float local_4c;
  float local_48;
  float local_44;
  undefined4 local_30;

  fVar3 = param_4 - param_1;
  fVar4 = param_5 - param_2;
  fVar5 = param_6 - param_3;
  fVar1 = SQRT(fVar4 * fVar4 + fVar3 * fVar3 + fVar5 * fVar5);
  fVar2 = SQRT(param_8 * param_8 + param_7 * param_7 + param_9 * param_9);
  if (fVar1 != 0.0) {
    fVar3 = fVar3 / fVar1;
  }
  if (fVar1 != 0.0) {
    fVar4 = fVar4 / fVar1;
    fVar5 = fVar5 / fVar1;
  }
  if (fVar2 != 0.0) {
    param_7 = param_7 / fVar2;
    param_8 = param_8 / fVar2;
  }
  if (fVar2 != 0.0) {
    param_9 = param_9 / fVar2;
  }
  fVar1 = param_8 * fVar3 - param_7 * fVar4;
  fVar6 = param_9 * fVar4 - param_8 * fVar5;
  fVar2 = param_7 * fVar5 - param_9 * fVar3;
  _memset(&local_6c,0,0x40);
  local_30 = 0x3f800000;
  local_68 = fVar2 * fVar5 - fVar1 * fVar4;
  local_64 = -fVar3;
  local_58 = fVar1 * fVar3 - fVar6 * fVar5;
  local_54 = -fVar4;
  local_48 = fVar6 * fVar4 - fVar2 * fVar3;
  local_44 = -fVar5;
  local_6c = fVar6;
  local_5c = fVar2;
  local_4c = fVar1;
  _glMultMatrixf(&local_6c);
  _glTranslatef(-param_1,-param_2,-param_3);
  return;
}
