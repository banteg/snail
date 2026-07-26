/*
 * mangled: _ZN13cRDamageGuage4TakeEfb
 * demangled: cRDamageGuage::Take(float, bool)
 * address: 000710ac
 * size: 392
 */

/* cRDamageGuage::Take(float, bool) */

void cRDamageGuage::Take(float param_1,bool param_2)

{
  char cVar1;
  int *piVar2;
  int iVar3;
  float in_r1;
  int in_r2;
  int iVar4;
  int iVar5;
  int *piVar6;
  int iVar7;
  float fVar8;

  iVar4 = DAT_00071240;
  piVar2 = (int *)(uint)param_2;
  iVar5 = DAT_0007123c + 0x710cc;
  iVar3 = **(int **)(iVar5 + DAT_00071240);
  if ((((*(uint *)(iVar3 + 0x81688) & 0x80) == 0) || (in_r2 != 0)) &&
     ((*piVar2 != 2 ||
      ((in_r1 == 0.0 || 0.0 > in_r1 && ((0.0 <= in_r1 || (*(char *)(iVar3 + 0x81530) == '\0'))))))))
  {
    if (((float)piVar2[9] == 0.0) && (0.0 < in_r1)) {
      cRSnailSkin::Change((cRSnailSkin *)(iVar3 + 0x852d4),1,param_1);
      iVar7 = *(int *)(iVar5 + DAT_00071244);
      iVar3 = cRVoiceManager::Play(iVar7,0,1);
      if (iVar3 == 0) {
        iVar3 = cRVoiceManager::Play(iVar7,9,0);
        piVar6 = *(int **)(iVar5 + iVar4);
        iVar4 = *piVar6;
        cVar1 = *(char *)(iVar4 + 0x81624);
        if (iVar3 != 0) {
          piVar2[9] = piVar2[10];
        }
        if (cVar1 == '\0') {
          cRSnail::SetAnimation((cRSnail *)(iVar4 + 0x83b64),6,true,-1);
          cRSnail::SetAnimation((cRSnail *)(*piVar6 + 0x83b64),1,false,-1);
        }
      }
      else {
        piVar2[9] = piVar2[10];
      }
    }
    fVar8 = in_r1 + (float)piVar2[7];
    if (0.0 <= fVar8) {
      if (DAT_00071238 < fVar8) {
        fVar8 = DAT_00071238;
      }
      piVar2[7] = (int)fVar8;
    }
    else {
      piVar2[7] = DAT_00071234;
    }
  }
  return;
}
