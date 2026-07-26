/*
 * mangled: _ZN14cREnemyManager4FindER7tVector
 * demangled: cREnemyManager::Find(tVector&)
 * address: 00062a44
 * size: 228
 */

/* cREnemyManager::Find(tVector&) */

cREnemyManager * __thiscall cREnemyManager::Find(cREnemyManager *this,tVector *param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  cREnemyManager *pcVar4;
  int iVar5;
  int iVar6;
  cREnemyManager *pcVar7;
  float fVar8;
  float local_34;
  float local_30;
  float local_2c;

  fVar1 = DAT_00062b2c;
  iVar3 = *(int *)this;
  if (iVar3 < 1) {
    pcVar7 = (cREnemyManager *)0x0;
  }
  else {
    pcVar7 = (cREnemyManager *)0x0;
    pcVar4 = this;
    iVar5 = 0;
    fVar8 = DAT_00062b28;
    do {
      while( true ) {
        local_2c = *(float *)(pcVar4 + 0x10) - *(float *)(param_1 + 8);
        local_34 = *(float *)(pcVar4 + 8) - *(float *)param_1;
        local_30 = *(float *)(pcVar4 + 0xc) - *(float *)(param_1 + 4);
        if ((local_2c <= 0.0) || (fVar1 <= local_2c)) break;
        pcVar4 = pcVar4 + 0x18;
        fVar2 = (float)tVector::Magnitude((tVector *)&local_34);
        iVar6 = iVar5 + 1;
        if (fVar8 <= fVar2) {
          iVar3 = *(int *)this;
        }
        else {
          iVar3 = *(int *)this;
          pcVar7 = this + iVar5 * 0x18 + 4;
          fVar8 = fVar2;
        }
        iVar5 = iVar6;
        if (iVar3 <= iVar6) {
          return pcVar7;
        }
      }
      iVar5 = iVar5 + 1;
      pcVar4 = pcVar4 + 0x18;
    } while (iVar5 < iVar3);
  }
  return pcVar7;
}
