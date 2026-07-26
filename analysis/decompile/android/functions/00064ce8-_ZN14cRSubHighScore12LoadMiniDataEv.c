/*
 * mangled: _ZN14cRSubHighScore12LoadMiniDataEv
 * demangled: cRSubHighScore::LoadMiniData()
 * address: 00064ce8
 * size: 480
 */

/* cRSubHighScore::LoadMiniData() */

void __thiscall cRSubHighScore::LoadMiniData(cRSubHighScore *this)

{
  cRSubHighScore cVar1;
  cRSubHighScore *pcVar2;
  char *pcVar3;
  int iVar4;
  char *pcVar5;
  undefined4 extraout_r0;
  undefined4 extraout_r0_00;
  cRSubHighScore *pcVar6;
  undefined4 extraout_r1;
  undefined4 extraout_r1_00;
  int iVar7;
  cRSubHighScore *pcVar8;
  int local_24 [2];

  pcVar3 = (char *)RShellLoadFile((char *)(DAT_00064ec8 + 0x64d00 + DAT_00064ecc),local_24);
  if (pcVar3 != (char *)0x0) {
    iVar7 = 0;
    pcVar3[local_24[0] + -1] = '\0';
    pcVar8 = this;
    pcVar5 = pcVar3;
    if (pcVar3 < pcVar3 + local_24[0] + -8) {
      do {
        iVar4 = atoi(pcVar5);
        *(int *)(pcVar8 + 0x28) = iVar4;
        pcVar5 = (char *)Rstrscan(pcVar5,' ');
        iVar4 = atoi(pcVar5);
        *(int *)(pcVar8 + 8) = iVar4;
        pcVar5 = (char *)Rstrscan(pcVar5,' ');
        strtod(pcVar5,(char **)0x0);
        *(float *)(pcVar8 + 0xc) = (float)(double)CONCAT44(extraout_r1,extraout_r0);
        pcVar5 = (char *)Rstrscan(pcVar5,' ');
        iVar4 = atoi(pcVar5);
        *(int *)(pcVar8 + 0x10) = iVar4;
        pcVar5 = (char *)Rstrscan(pcVar5,' ');
        iVar4 = atoi(pcVar5);
        *(int *)(pcVar8 + 0x14) = iVar4;
        pcVar5 = (char *)Rstrscan(pcVar5,' ');
        iVar4 = atoi(pcVar5);
        *(int *)(pcVar8 + 0x18) = iVar4;
        pcVar5 = (char *)Rstrscan(pcVar5,' ');
        iVar4 = atoi(pcVar5);
        *(int *)(pcVar8 + 0x1c) = iVar4;
        pcVar5 = (char *)Rstrscan(pcVar5,' ');
        strtod(pcVar5,(char **)0x0);
        *(float *)(pcVar8 + 0x20) = (float)(double)CONCAT44(extraout_r1_00,extraout_r0_00);
        pcVar5 = (char *)Rstrscan(pcVar5,' ');
        iVar4 = atoi(pcVar5);
        *(int *)(pcVar8 + 0x24) = iVar4;
        pcVar5 = (char *)Rstrscan(pcVar5,' ');
        iVar4 = atoi(pcVar5);
        pcVar8[0x2c] = (cRSubHighScore)(iVar4 != 0);
        pcVar6 = (cRSubHighScore *)Rstrscan(pcVar5,'\"');
        cVar1 = *pcVar6;
        pcVar2 = this + iVar7 * 0x38 + 0x2d;
        while (cVar1 != (cRSubHighScore)0x22) {
          *pcVar2 = cVar1;
          pcVar6 = pcVar6 + 1;
          pcVar2 = pcVar2 + 1;
          cVar1 = *pcVar6;
        }
        *pcVar2 = (cRSubHighScore)0x0;
        iVar7 = iVar7 + 1;
        pcVar5 = (char *)Rstrnewline((char *)pcVar6);
      } while (((iVar7 != 0x55) && (pcVar5 != (char *)0x0)) &&
              (pcVar8 = pcVar8 + 0x38, pcVar5 < pcVar3 + local_24[0] + -8));
    }
    RShellMemoryFree(pcVar3);
  }
  return;
}
