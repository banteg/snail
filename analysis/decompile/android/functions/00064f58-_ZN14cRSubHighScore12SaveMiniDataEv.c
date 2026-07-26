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
  int iVar12;
  char *__dest;
  size_t sVar13;
  cRSubHighScore *pcVar14;
  int iVar15;
  int iVar16;
  char *__format;
  char acStack_22c [512];
  int local_2c;

  iVar12 = DAT_0006506c;
  iVar16 = DAT_00065068 + 0x64f70;
  __format = (char *)(iVar16 + DAT_00065070);
  local_2c = **(int **)(iVar16 + DAT_0006506c);
  __dest = (char *)RShellMemoryScratch();
  iVar15 = 0;
  *__dest = '\0';
  pcVar14 = this;
  do {
    pcVar9 = pcVar14 + 0xc;
    pcVar1 = pcVar14 + 0x28;
    pcVar2 = pcVar14 + 8;
    iVar11 = iVar15 * 0x38;
    iVar15 = iVar15 + 1;
    pcVar3 = pcVar14 + 0x10;
    pcVar4 = pcVar14 + 0x14;
    pcVar5 = pcVar14 + 0x18;
    pcVar6 = pcVar14 + 0x1c;
    pcVar10 = pcVar14 + 0x20;
    pcVar7 = pcVar14 + 0x24;
    pcVar8 = pcVar14 + 0x2c;
    pcVar14 = pcVar14 + 0x38;
    sprintf(acStack_22c,__format,*(undefined4 *)pcVar1,*(undefined4 *)pcVar2,
            (double)*(float *)pcVar9,*(undefined4 *)pcVar3,*(undefined4 *)pcVar4,
            *(undefined4 *)pcVar5,*(undefined4 *)pcVar6,(double)*(float *)pcVar10,
            *(undefined4 *)pcVar7,(uint)(byte)*pcVar8,this + iVar11 + 0x2d);
    strcat(__dest,acStack_22c);
  } while (iVar15 != 0x55);
  sVar13 = strlen(__dest);
  RShellSaveFile((char *)(iVar16 + DAT_00065074),__dest,sVar13 + 1);
  if (local_2c == **(int **)(iVar16 + iVar12)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}
