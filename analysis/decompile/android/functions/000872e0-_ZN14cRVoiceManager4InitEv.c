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
  char *pcVar2;
  char *pcVar3;
  char *pcVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  int iVar8;
  int iVar9;
  cRVoiceManager *pcVar10;
  int iVar11;
  int iVar12;
  int iVar13;
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

  local_2c = __stack_chk_guard;
  local_12c[0] = '\0';
  local_260 = 0;
  pcVar2 = (char *)RShellMemoryScratch();
  RShellLoadFile("Voice/_Voice.txt",pcVar2,&local_234);
  pcVar2[local_234 + -1] = '\0';
  pcVar10 = this;
  do {
    Rstrcpy(local_12c,"Set:");
    switch(local_260) {
    case 1:
      strcat(local_12c,"Dying");
      break;
    case 2:
      strcat(local_12c,"Enemies");
      break;
    case 3:
      strcat(local_12c,"Fall");
      break;
    case 4:
      strcat(local_12c,"Misc");
      break;
    case 5:
      strcat(local_12c,"PowerUp");
      break;
    case 6:
      strcat(local_12c,"Slow");
      break;
    case 7:
      strcat(local_12c,"Start");
      break;
    case 8:
      strcat(local_12c,"Victory");
      break;
    case 9:
      strcat(local_12c,"Ouch");
      break;
    case 10:
      strcat(local_12c,"Package");
      break;
    case 0xb:
      strcat(local_12c,"Slugged");
      break;
    case 0xc:
      strcat(local_12c,"WormTunnel");
      break;
    case 0xd:
      strcat(local_12c,"Tutorial");
      break;
    case 0xe:
      strcat(local_12c,"Postal");
      break;
    case 0xf:
      strcat(local_12c,"SuperTramp");
      break;
    default:
      strcat(local_12c,"Damage");
    }
    local_230 = (char *)Rstrfind(local_12c,pcVar2);
    if (local_230 == (char *)0x0) {
      RShellError("Cannot find %s in _Voice.txt",local_12c);
      goto LAB_0008766c;
    }
    local_230 = (char *)Rstrfind("{",local_230);
    pcVar3 = (char *)Rstrfind("}",local_230);
    pcVar4 = (char *)Rstrnewline(local_230);
    local_230 = pcVar4;
    if (pcVar4 < pcVar3) {
      iVar11 = 0;
      do {
        pcVar4 = (char *)Rstrnewline(pcVar4);
        iVar11 = iVar11 + 1;
      } while (pcVar4 < pcVar3);
      iVar9 = 0;
      iVar12 = 0;
      cRVoiceSet::Init((cRVoiceSet *)(this + local_260 * 0x18),iVar11);
      do {
        cVar1 = *local_230;
        if (cVar1 == '\t' || cVar1 == ' ') {
          do {
            local_230 = local_230 + 1;
            cVar1 = *local_230;
          } while (cVar1 == '\t' || cVar1 == ' ');
        }
        pcVar3 = &local_22c;
        pcVar4 = local_22b;
        if (cVar1 != '\r') {
          while (cVar1 != ' ') {
            local_230 = local_230 + 1;
            pcVar4[-1] = cVar1;
            cVar1 = *local_230;
            pcVar3 = pcVar4;
            if (cVar1 == '\t' || cVar1 == '\r') break;
            pcVar4 = pcVar4 + 1;
          }
        }
        *pcVar3 = '\0';
        iVar12 = iVar12 + 1;
        local_230 = (char *)Rstrnewline(local_230);
        cRResourceManager::Add
                  ((cRResourceManager *)&gResourceManager,2,*(int *)(pcVar10 + 0xc) + iVar9,
                   &local_22c);
        iVar13 = *(int *)(pcVar10 + 0xc);
        uVar5 = RShellSoundRegister(&local_22c,1);
        iVar8 = *(int *)(pcVar10 + 0xc);
        *(undefined4 *)(iVar13 + iVar9) = uVar5;
        strcpy((char *)(iVar8 + iVar9 + 4),&local_22c);
        iVar9 = iVar9 + 0x8c;
      } while (iVar12 < iVar11);
    }
    else {
      cRVoiceSet::Init((cRVoiceSet *)(this + local_260 * 0x18),0);
    }
    pcVar10 = pcVar10 + 0x18;
    local_260 = local_260 + 1;
  } while (local_260 != 0x10);
  local_230 = (char *)Rstrfind("NormalizeMusic:",pcVar2);
  local_230 = (char *)Rstrfind(":",local_230);
  uVar5 = Rstrint(&local_230);
  local_230 = (char *)Rstrfind("NormalizeSfx:",pcVar2);
  local_230 = (char *)Rstrfind(":",local_230);
  uVar6 = Rstrint(&local_230);
  local_230 = (char *)Rstrfind("NormalizeVoice:",pcVar2);
  local_230 = (char *)Rstrfind(":",local_230);
  uVar7 = Rstrint(&local_230);
  VectorSignedToFloat(uVar5,(byte)(in_fpscr >> 0x16) & 3);
  VectorSignedToFloat(uVar6,(byte)(in_fpscr >> 0x16) & 3);
  VectorSignedToFloat(uVar7,(byte)(in_fpscr >> 0x16) & 3);
  PfmAudioNormalize(extraout_s0,extraout_s1,extraout_s2);
  local_230 = (char *)Rstrfind("Frequency:",pcVar2);
  local_230 = (char *)Rstrfind(":",local_230);
  uVar5 = Rstrfloat(&local_230);
  *(undefined4 *)(this + 0x184) = uVar5;
  ReSet(this);
LAB_0008766c:
  if (local_2c != __stack_chk_guard) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}
