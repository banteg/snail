/*
 * mangled: _ZN14cRSubHighScore12SaveMiniDataEv
 * demangled: cRSubHighScore::SaveMiniData()
 * address: 00064f58
 * size: 272
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
  int iVar11;
  char *__dest;
  size_t sVar12;
  cRSubHighScore *pcVar13;
  int iVar14;
  char acStack_22c [512];
  int local_2c;

  local_2c = __stack_chk_guard;
  __dest = (char *)RShellMemoryScratch();
  iVar14 = 0;
  *__dest = '\0';
  pcVar13 = this;
  do {
    pcVar9 = pcVar13 + 0xc;
    pcVar1 = pcVar13 + 0x28;
    pcVar2 = pcVar13 + 8;
    iVar11 = iVar14 * 0x38;
    iVar14 = iVar14 + 1;
    pcVar3 = pcVar13 + 0x10;
    pcVar4 = pcVar13 + 0x14;
    pcVar5 = pcVar13 + 0x18;
    pcVar6 = pcVar13 + 0x1c;
    pcVar10 = pcVar13 + 0x20;
    pcVar7 = pcVar13 + 0x24;
    pcVar8 = pcVar13 + 0x2c;
    pcVar13 = pcVar13 + 0x38;
    sprintf(acStack_22c,"%i %i %f %i %i %i %i %f %i %i \"%s\"\r\n",*(undefined4 *)pcVar1,
            *(undefined4 *)pcVar2,(double)*(float *)pcVar9,*(undefined4 *)pcVar3,
            *(undefined4 *)pcVar4,*(undefined4 *)pcVar5,*(undefined4 *)pcVar6,
            (double)*(float *)pcVar10,*(undefined4 *)pcVar7,(uint)(byte)*pcVar8,this + iVar11 + 0x2d
           );
    strcat(__dest,acStack_22c);
  } while (iVar14 != 0x55);
  sVar12 = strlen(__dest);
  RShellSaveFile("highscores.txt",__dest,sVar12 + 1);
  if (local_2c == __stack_chk_guard) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}
