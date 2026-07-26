/*
 * mangled: _ZN14cRVoiceManager4InitEv
 * demangled: cRVoiceManager::Init()
 * address: 0006c4a4
 * size: 1304
 */

/* cRVoiceManager::Init() */

void __thiscall cRVoiceManager::Init(cRVoiceManager *this)

{
  char *pcVar1;
  char *pcVar2;
  char *pcVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  char cVar7;
  int iVar8;
  cRVoiceManager *pcVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  uint in_fpscr;
  float fVar13;
  float fVar14;
  int iVar15;
  int iVar16;
  float fVar17;
  char local_230 [256];
  char local_130 [256];
  int local_30;
  char *local_2c [3];

  local_130[0] = '\0';
  pcVar1 = (char *)RShellMemoryScratch();
  iVar12 = 0;
  RShellLoadFile("Voice/_Voice.txt",pcVar1,&local_30);
  pcVar1[local_30 + -1] = '\0';
  pcVar9 = this;
  do {
    Rstrcpy(local_130,"Set:");
    switch(iVar12) {
    case 0:
      _strcat(local_130,"Damage");
      break;
    case 1:
      _strcat(local_130,"Dying");
      break;
    case 2:
      _strcat(local_130,"Enemies");
      break;
    case 3:
      _strcat(local_130,"Fall");
      break;
    case 4:
      _strcat(local_130,"Misc");
      break;
    case 5:
      _strcat(local_130,"PowerUp");
      break;
    case 6:
      _strcat(local_130,"Slow");
      break;
    case 7:
      _strcat(local_130,"Start");
      break;
    case 8:
      _strcat(local_130,"Victory");
      break;
    case 9:
      _strcat(local_130,"Ouch");
      break;
    case 10:
      _strcat(local_130,"Package");
      break;
    case 0xb:
      _strcat(local_130,"Slugged");
      break;
    case 0xc:
      _strcat(local_130,"WormTunnel");
      break;
    case 0xd:
      _strcat(local_130,"Tutorial");
      break;
    case 0xe:
      _strcat(local_130,"Postal");
      local_2c[0] = (char *)Rstrfind(local_130,pcVar1);
      goto joined_r0x0006c900;
    case 0xf:
      _strcat(local_130,"SuperTramp");
    }
    local_2c[0] = (char *)Rstrfind(local_130,pcVar1);
joined_r0x0006c900:
    if (local_2c[0] == (char *)0x0) {
      RShellError("Cannot find %s in _Voice.txt",local_130);
      return;
    }
    local_2c[0] = (char *)Rstrfind("{",local_2c[0]);
    pcVar2 = (char *)Rstrfind("}",local_2c[0]);
    pcVar3 = (char *)Rstrnewline(local_2c[0]);
    local_2c[0] = pcVar3;
    if (pcVar3 < pcVar2) {
      iVar11 = 0;
      do {
        pcVar3 = (char *)Rstrnewline(pcVar3);
        iVar11 = iVar11 + 1;
      } while (pcVar3 < pcVar2);
      iVar10 = iVar11 * 4;
    }
    else {
      iVar10 = 0;
      iVar11 = iVar10;
    }
    *(undefined4 *)(pcVar9 + 4) = 0;
    *(int *)pcVar9 = iVar11;
    uVar4 = RShellMemoryMalloc(iVar10,"Playlist");
    *(undefined4 *)(pcVar9 + 8) = uVar4;
    uVar4 = RShellMemoryMalloc(*(int *)pcVar9 << 2,"VoiceBite");
    *(undefined4 *)(pcVar9 + 0x10) = 0;
    *(undefined4 *)(pcVar9 + 0x14) = 0x3b888889;
    *(undefined4 *)(pcVar9 + 0xc) = uVar4;
    if (0 < *(int *)pcVar9) {
      iVar10 = 0;
      do {
        *(int *)(*(int *)(pcVar9 + 8) + iVar10 * 4) = iVar10;
        iVar10 = iVar10 + 1;
      } while (iVar10 < *(int *)pcVar9);
    }
    iVar10 = 0;
    do {
      uVar4 = gRMathRand2();
      fVar17 = 3.0517578e-05;
      fVar13 = (float)VectorSignedToFloat(uVar4,(byte)(in_fpscr >> 0x16) & 3);
      fVar14 = (float)VectorSignedToFloat(*(undefined4 *)pcVar9,(byte)(in_fpscr >> 0x16) & 3);
      iVar15 = (int)(fVar13 * 3.0517578e-05 * fVar14);
      uVar4 = gRMathRand2();
      iVar8 = *(int *)pcVar9;
      fVar13 = (float)VectorSignedToFloat(uVar4,(byte)(in_fpscr >> 0x16) & 3);
      fVar14 = (float)VectorSignedToFloat(iVar8,(byte)(in_fpscr >> 0x16) & 3);
      iVar16 = (int)(fVar13 * fVar17 * fVar14);
      if ((iVar8 <= iVar15) || (iVar8 <= iVar16)) {
        wprintf("RANDOM ERORR\n");
      }
      iVar8 = *(int *)(pcVar9 + 8);
      iVar10 = iVar10 + 1;
      uVar4 = *(undefined4 *)(iVar8 + iVar15 * 4);
      *(undefined4 *)(iVar8 + iVar15 * 4) = *(undefined4 *)(iVar8 + iVar16 * 4);
      *(undefined4 *)(*(int *)(pcVar9 + 8) + iVar16 * 4) = uVar4;
    } while (iVar10 != 100);
    if (0 < iVar11) {
      iVar10 = 0;
      do {
        if (*local_2c[0] == ' ' || *local_2c[0] == '\t') {
          do {
            local_2c[0] = local_2c[0] + 1;
          } while (*local_2c[0] == ' ' || *local_2c[0] == '\t');
        }
        cVar7 = *local_2c[0];
        pcVar2 = local_230;
        if ((cVar7 != '\r' && cVar7 != '\t') && (cVar7 != ' ')) {
          pcVar2 = local_230;
          pcVar3 = local_2c[0];
          do {
            pcVar2 = pcVar2 + 1;
            pcVar3 = pcVar3 + 1;
            pcVar2[-1] = cVar7;
            cVar7 = *pcVar3;
            local_2c[0] = pcVar3;
            if (cVar7 == '\r' || cVar7 == '\t') break;
          } while (cVar7 != ' ');
        }
        pcVar3 = local_2c[0];
        *pcVar2 = '\0';
        local_2c[0] = (char *)Rstrnewline(pcVar3);
        iVar8 = *(int *)(pcVar9 + 0xc);
        uVar4 = RShellSoundRegister(local_230,1);
        *(undefined4 *)(iVar8 + iVar10 * 4) = uVar4;
        iVar10 = iVar10 + 1;
      } while (iVar10 != iVar11);
    }
    iVar12 = iVar12 + 1;
    pcVar9 = pcVar9 + 0x18;
    if (iVar12 == 0x10) {
      local_2c[0] = (char *)Rstrfind("NormalizeMusic:",pcVar1);
      local_2c[0] = (char *)Rstrfind(":",local_2c[0]);
      uVar4 = Rstrint(local_2c);
      local_2c[0] = (char *)Rstrfind("NormalizeSfx:",pcVar1);
      local_2c[0] = (char *)Rstrfind(":",local_2c[0]);
      uVar5 = Rstrint(local_2c);
      local_2c[0] = (char *)Rstrfind("NormalizeVoice:",pcVar1);
      local_2c[0] = (char *)Rstrfind(":",local_2c[0]);
      uVar6 = Rstrint(local_2c);
      fVar17 = (float)VectorSignedToFloat(uVar5,(byte)(in_fpscr >> 0x16) & 3);
      fVar13 = (float)VectorSignedToFloat(uVar4,(byte)(in_fpscr >> 0x16) & 3);
      fVar14 = (float)VectorSignedToFloat(uVar6,(byte)(in_fpscr >> 0x16) & 3);
      MacAudioNormalize(fVar13 / 100.0,fVar17 / 100.0,fVar14 / 100.0);
      local_2c[0] = (char *)Rstrfind("Frequency:",pcVar1);
      local_2c[0] = (char *)Rstrfind(":",local_2c[0]);
      uVar4 = Rstrfloat(local_2c);
      *(undefined4 *)(this + 0x180) = 0;
      *(undefined4 *)(this + 0x10) = 0;
      *(undefined4 *)(this + 0x28) = 0;
      *(undefined4 *)(this + 0x40) = 0;
      *(undefined4 *)(this + 0x58) = 0;
      *(undefined4 *)(this + 0x70) = 0;
      *(undefined4 *)(this + 0x88) = 0;
      *(undefined4 *)(this + 0xa0) = 0;
      *(undefined4 *)(this + 0xb8) = 0;
      *(undefined4 *)(this + 0xd0) = 0;
      *(undefined4 *)(this + 0xe8) = 0;
      *(undefined4 *)(this + 0x100) = 0;
      *(undefined4 *)(this + 0x118) = 0;
      *(undefined4 *)(this + 0x130) = 0;
      *(undefined4 *)(this + 0x148) = 0;
      *(undefined4 *)(this + 0x160) = 0;
      *(undefined4 *)(this + 0x178) = 0;
      *(undefined4 *)(this + 0x184) = uVar4;
      return;
    }
  } while( true );
}
