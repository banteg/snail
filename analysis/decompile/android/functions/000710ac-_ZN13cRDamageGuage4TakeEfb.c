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
  int iVar4;
  float in_r1;
  int in_r2;
  float fVar5;

  piVar2 = (int *)(uint)param_2;
  if ((((*(uint *)(Game + 0x81688) & 0x80) == 0) || (in_r2 != 0)) &&
     ((*piVar2 != 2 ||
      ((in_r1 == 0.0 || 0.0 > in_r1 && ((0.0 <= in_r1 || (*(char *)(Game + 0x81530) == '\0'))))))))
  {
    if (((float)piVar2[9] == 0.0) && (0.0 < in_r1)) {
      cRSnailSkin::Change((cRSnailSkin *)(Game + 0x852d4),1,param_1);
      iVar3 = cRVoiceManager::Play((int)&gVoiceManager,0,1);
      if (iVar3 == 0) {
        iVar4 = cRVoiceManager::Play((int)&gVoiceManager,9,0);
        iVar3 = Game;
        cVar1 = *(char *)(Game + 0x81624);
        if (iVar4 != 0) {
          piVar2[9] = piVar2[10];
        }
        if (cVar1 == '\0') {
          cRSnail::SetAnimation((cRSnail *)(iVar3 + 0x83b64),6,true,-1);
          cRSnail::SetAnimation((cRSnail *)(Game + 0x83b64),1,false,-1);
        }
      }
      else {
        piVar2[9] = piVar2[10];
      }
    }
    fVar5 = in_r1 + (float)piVar2[7];
    if (0.0 <= fVar5) {
      if (1.0 < fVar5) {
        fVar5 = 1.0;
      }
      piVar2[7] = (int)fVar5;
    }
    else {
      piVar2[7] = 0;
    }
  }
  return;
}
