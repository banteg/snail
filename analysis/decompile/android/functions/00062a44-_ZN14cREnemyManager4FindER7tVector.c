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
  int iVar2;
  cREnemyManager *pcVar3;
  int iVar4;
  int iVar5;
  cREnemyManager *pcVar6;
  float fVar7;
  float local_34;
  float local_30;
  float local_2c;

  iVar2 = *(int *)this;
  if (iVar2 < 1) {
    pcVar6 = (cREnemyManager *)0x0;
  }
  else {
    pcVar6 = (cREnemyManager *)0x0;
    fVar7 = 1e+09;
    pcVar3 = this;
    iVar4 = 0;
    do {
      while( true ) {
        local_2c = *(float *)(pcVar3 + 0x10) - *(float *)(param_1 + 8);
        local_34 = *(float *)(pcVar3 + 8) - *(float *)param_1;
        local_30 = *(float *)(pcVar3 + 0xc) - *(float *)(param_1 + 4);
        if ((local_2c <= 0.0) || (30.0 <= local_2c)) break;
        pcVar3 = pcVar3 + 0x18;
        fVar1 = (float)tVector::Magnitude((tVector *)&local_34);
        iVar5 = iVar4 + 1;
        if (fVar7 <= fVar1) {
          iVar2 = *(int *)this;
        }
        else {
          iVar2 = *(int *)this;
          pcVar6 = this + iVar4 * 0x18 + 4;
          fVar7 = fVar1;
        }
        iVar4 = iVar5;
        if (iVar2 <= iVar5) {
          return pcVar6;
        }
      }
      iVar4 = iVar4 + 1;
      pcVar3 = pcVar3 + 0x18;
    } while (iVar4 < iVar2);
  }
  return pcVar6;
}
