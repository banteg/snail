/*
 * mangled: _ZN14cRVoiceManager4InitEv
 * demangled: cRVoiceManager::Init()
 * address: 000872e0
 * size: 1316
 */

/* cRVoiceManager::Init() */

void __thiscall cRVoiceManager::Init(cRVoiceManager *this)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  char *pcVar5;
  char *pcVar6;
  char *pcVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  char *pcVar11;
  char *pcVar12;
  int iVar13;
  int iVar14;
  cRVoiceManager *pcVar15;
  int iVar16;
  int iVar17;
  int iVar18;
  int iVar19;
  uint in_fpscr;
  float extraout_s0;
  float extraout_s1;
  float extraout_s2;
  int local_260;
  int local_234;
  char *local_230;
  char local_22c;
  char local_22b [255];
  char local_12c [256];
  int local_2c;

  iVar3 = DAT_00087810;
  iVar2 = DAT_0008780c;
  iVar18 = DAT_00087808 + 0x872f8;
  local_2c = **(int **)(iVar18 + DAT_0008780c);
  local_12c[0] = '\0';
  local_260 = 0;
  pcVar5 = (char *)RShellMemoryScratch();
  RShellLoadFile((char *)(iVar18 + DAT_00087814),pcVar5,&local_234);
  pcVar11 = (char *)(iVar18 + DAT_00087818);
  pcVar12 = (char *)(iVar18 + DAT_0008781c);
  pcVar5[local_234 + -1] = '\0';
  pcVar15 = this;
  do {
    Rstrcpy(local_12c,(char *)(iVar18 + iVar3));
    switch(local_260) {
    case 1:
      strcat(local_12c,(char *)(iVar18 + DAT_0008786c));
      break;
    case 2:
      strcat(local_12c,(char *)(iVar18 + DAT_00087868));
      break;
    case 3:
      strcat(local_12c,(char *)(iVar18 + DAT_00087864));
      break;
    case 4:
      strcat(local_12c,(char *)(iVar18 + DAT_00087860));
      break;
    case 5:
      strcat(local_12c,(char *)(iVar18 + DAT_0008785c));
      break;
    case 6:
      strcat(local_12c,(char *)(iVar18 + DAT_00087858));
      break;
    case 7:
      strcat(local_12c,(char *)(iVar18 + DAT_00087854));
      break;
    case 8:
      strcat(local_12c,(char *)(iVar18 + DAT_00087850));
      break;
    case 9:
      strcat(local_12c,(char *)(iVar18 + DAT_0008784c));
      break;
    case 10:
      strcat(local_12c,(char *)(iVar18 + DAT_00087848));
      break;
    case 0xb:
      strcat(local_12c,(char *)(iVar18 + DAT_00087844));
      break;
    case 0xc:
      strcat(local_12c,(char *)(iVar18 + DAT_00087840));
      break;
    case 0xd:
      strcat(local_12c,(char *)(iVar18 + DAT_0008783c));
      break;
    case 0xe:
      strcat(local_12c,(char *)(iVar18 + DAT_00087820));
      break;
    case 0xf:
      strcat(local_12c,(char *)(iVar18 + DAT_00087874));
      break;
    default:
      strcat(local_12c,(char *)(iVar18 + DAT_00087870));
    }
    local_230 = (char *)Rstrfind(local_12c,pcVar5);
    if (local_230 == (char *)0x0) {
      RShellError((char *)(iVar18 + DAT_00087878),local_12c);
      goto LAB_0008766c;
    }
    local_230 = (char *)Rstrfind(pcVar11,local_230);
    pcVar6 = (char *)Rstrfind(pcVar12,local_230);
    pcVar7 = (char *)Rstrnewline(local_230);
    local_230 = pcVar7;
    if (pcVar7 < pcVar6) {
      iVar16 = 0;
      do {
        pcVar7 = (char *)Rstrnewline(pcVar7);
        iVar4 = DAT_00087824;
        iVar16 = iVar16 + 1;
      } while (pcVar7 < pcVar6);
      iVar14 = 0;
      iVar17 = 0;
      cRVoiceSet::Init((cRVoiceSet *)(this + local_260 * 0x18),iVar16);
      do {
        cVar1 = *local_230;
        if (cVar1 == '\t' || cVar1 == ' ') {
          do {
            local_230 = local_230 + 1;
            cVar1 = *local_230;
          } while (cVar1 == '\t' || cVar1 == ' ');
        }
        pcVar6 = &local_22c;
        pcVar7 = local_22b;
        if (cVar1 != '\r') {
          while (cVar1 != ' ') {
            local_230 = local_230 + 1;
            pcVar7[-1] = cVar1;
            cVar1 = *local_230;
            pcVar6 = pcVar7;
            if (cVar1 == '\t' || cVar1 == '\r') break;
            pcVar7 = pcVar7 + 1;
          }
        }
        *pcVar6 = '\0';
        iVar17 = iVar17 + 1;
        local_230 = (char *)Rstrnewline(local_230);
        cRResourceManager::Add
                  (*(cRResourceManager **)(iVar18 + iVar4),2,*(int *)(pcVar15 + 0xc) + iVar14,
                   &local_22c);
        iVar19 = *(int *)(pcVar15 + 0xc);
        uVar8 = RShellSoundRegister(&local_22c,1);
        iVar13 = *(int *)(pcVar15 + 0xc);
        *(undefined4 *)(iVar19 + iVar14) = uVar8;
        strcpy((char *)(iVar13 + iVar14 + 4),&local_22c);
        iVar14 = iVar14 + 0x8c;
      } while (iVar17 < iVar16);
    }
    else {
      cRVoiceSet::Init((cRVoiceSet *)(this + local_260 * 0x18),0);
    }
    iVar16 = DAT_0008782c;
    pcVar15 = pcVar15 + 0x18;
    local_260 = local_260 + 1;
  } while (local_260 != 0x10);
  local_230 = (char *)Rstrfind((char *)(iVar18 + DAT_00087828),pcVar5);
  pcVar11 = (char *)(iVar18 + iVar16);
  local_230 = (char *)Rstrfind(pcVar11,local_230);
  uVar8 = Rstrint(&local_230);
  local_230 = (char *)Rstrfind((char *)(iVar18 + DAT_00087830),pcVar5);
  local_230 = (char *)Rstrfind(pcVar11,local_230);
  uVar9 = Rstrint(&local_230);
  local_230 = (char *)Rstrfind((char *)(iVar18 + DAT_00087834),pcVar5);
  local_230 = (char *)Rstrfind(pcVar11,local_230);
  uVar10 = Rstrint(&local_230);
  VectorSignedToFloat(uVar8,(byte)(in_fpscr >> 0x16) & 3);
  VectorSignedToFloat(uVar9,(byte)(in_fpscr >> 0x16) & 3);
  VectorSignedToFloat(uVar10,(byte)(in_fpscr >> 0x16) & 3);
  PfmAudioNormalize(extraout_s0,extraout_s1,extraout_s2);
  local_230 = (char *)Rstrfind((char *)(iVar18 + DAT_00087838),pcVar5);
  local_230 = (char *)Rstrfind(pcVar11,local_230);
  uVar8 = Rstrfloat(&local_230);
  *(undefined4 *)(this + 0x184) = uVar8;
  ReSet(this);
LAB_0008766c:
  if (local_2c != **(int **)(iVar18 + iVar2)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}
