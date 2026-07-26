/*
 * mangled: _ZN14cRSubHighScore12SaveMiniDataEv
 * demangled: cRSubHighScore::SaveMiniData()
 * address: 0003d330
 * size: 216
 */

/* cRSubHighScore::SaveMiniData() */

void __thiscall cRSubHighScore::SaveMiniData(cRSubHighScore *this)

{
  cRSubHighScore *pcVar1;
  cRSubHighScore *pcVar2;
  cRSubHighScore *pcVar3;
  cRSubHighScore *pcVar4;
  cRSubHighScore *pcVar5;
  cRSubHighScore *pcVar6;
  cRSubHighScore *pcVar7;
  cRSubHighScore *pcVar8;
  cRSubHighScore *pcVar9;
  cRSubHighScore *pcVar10;
  char *pcVar11;
  size_t sVar12;
  cRSubHighScore *pcVar13;
  int iVar14;
  char acStack_218 [512];

  pcVar11 = (char *)RShellMemoryScratch();
  iVar14 = 0;
  *pcVar11 = '\0';
  pcVar13 = this;
  do {
    pcVar9 = pcVar13 + 0xc;
    pcVar1 = pcVar13 + 0x28;
    pcVar2 = pcVar13 + 8;
    pcVar3 = pcVar13 + 0x10;
    pcVar4 = pcVar13 + 0x14;
    pcVar5 = pcVar13 + 0x18;
    pcVar6 = pcVar13 + 0x1c;
    pcVar10 = pcVar13 + 0x20;
    pcVar7 = pcVar13 + 0x24;
    pcVar8 = pcVar13 + 0x2c;
    pcVar13 = pcVar13 + 0x38;
    _sprintf(acStack_218,"%i %i %f %i %i %i %i %f %i %i \"%s\"\r\n",*(undefined4 *)pcVar1,
             *(undefined4 *)pcVar2,(double)*(float *)pcVar9,*(undefined4 *)pcVar3,
             *(undefined4 *)pcVar4,*(undefined4 *)pcVar5,*(undefined4 *)pcVar6,
             (double)*(float *)pcVar10,*(undefined4 *)pcVar7,(uint)(byte)*pcVar8,
             this + iVar14 * 0x38 + 0x2d);
    iVar14 = iVar14 + 1;
    _strcat(pcVar11,acStack_218);
  } while (iVar14 != 0x55);
  sVar12 = _strlen(pcVar11);
  RShellSaveFile("HighScores.txt",pcVar11,sVar12 + 1);
  return;
}
