/*
 * mangled: _ZN14cRSubHighScore12LoadMiniDataEv
 * demangled: cRSubHighScore::LoadMiniData()
 * address: 0003d154
 * size: 472
 */

/* cRSubHighScore::LoadMiniData() */

void __thiscall cRSubHighScore::LoadMiniData(cRSubHighScore *this)

{
  cRSubHighScore cVar1;
  cRSubHighScore *pcVar2;
  char *pcVar3;
  int iVar4;
  char *pcVar5;
  cRSubHighScore *pcVar6;
  cRSubHighScore *pcVar7;
  int iVar8;
  double dVar9;
  int local_20;

  pcVar3 = (char *)RShellLoadFile("HighScores.txt",&local_20);
  if (pcVar3 != (char *)0x0) {
    iVar8 = 0;
    pcVar3[local_20 + -1] = '\0';
    pcVar5 = pcVar3;
    pcVar7 = this;
    if (pcVar3 < pcVar3 + local_20 + -8) {
      do {
        iVar4 = _atoi(pcVar5);
        *(int *)(pcVar7 + 0x28) = iVar4;
        pcVar5 = (char *)Rstrscan(pcVar5,' ');
        iVar4 = _atoi(pcVar5);
        *(int *)(pcVar7 + 8) = iVar4;
        pcVar5 = (char *)Rstrscan(pcVar5,' ');
        dVar9 = _atof(pcVar5);
        *(float *)(pcVar7 + 0xc) =
             (float)(double)(((ulonglong)dVar9 & 0xffffffff00000000) +
                            ((ulonglong)dVar9 & 0xffffffff));
        pcVar5 = (char *)Rstrscan(pcVar5,' ');
        iVar4 = _atoi(pcVar5);
        *(int *)(pcVar7 + 0x10) = iVar4;
        pcVar5 = (char *)Rstrscan(pcVar5,' ');
        iVar4 = _atoi(pcVar5);
        *(int *)(pcVar7 + 0x14) = iVar4;
        pcVar5 = (char *)Rstrscan(pcVar5,' ');
        iVar4 = _atoi(pcVar5);
        *(int *)(pcVar7 + 0x18) = iVar4;
        pcVar5 = (char *)Rstrscan(pcVar5,' ');
        iVar4 = _atoi(pcVar5);
        *(int *)(pcVar7 + 0x1c) = iVar4;
        pcVar5 = (char *)Rstrscan(pcVar5,' ');
        dVar9 = _atof(pcVar5);
        *(float *)(pcVar7 + 0x20) =
             (float)(double)(((ulonglong)dVar9 & 0xffffffff00000000) +
                            ((ulonglong)dVar9 & 0xffffffff));
        pcVar5 = (char *)Rstrscan(pcVar5,' ');
        iVar4 = _atoi(pcVar5);
        *(int *)(pcVar7 + 0x24) = iVar4;
        pcVar5 = (char *)Rstrscan(pcVar5,' ');
        iVar4 = _atoi(pcVar5);
        pcVar7[0x2c] = (cRSubHighScore)(iVar4 != 0);
        pcVar6 = (cRSubHighScore *)Rstrscan(pcVar5,'\"');
        cVar1 = *pcVar6;
        pcVar2 = this + iVar8 * 0x38 + 0x2d;
        while (cVar1 != (cRSubHighScore)0x22) {
          *pcVar2 = cVar1;
          pcVar6 = pcVar6 + 1;
          pcVar2 = pcVar2 + 1;
          cVar1 = *pcVar6;
        }
        *pcVar2 = (cRSubHighScore)0x0;
        pcVar5 = (char *)Rstrnewline((char *)pcVar6);
        iVar8 = iVar8 + 1;
      } while (((iVar8 != 0x55) && (pcVar5 != (char *)0x0)) &&
              (pcVar7 = pcVar7 + 0x38, pcVar5 < pcVar3 + local_20 + -8));
    }
    RShellMemoryFree(pcVar3);
  }
  return;
}
