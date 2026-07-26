/*
 * mangled: _ZN10cRSMTracks7ReplaceEv
 * demangled: cRSMTracks::Replace()
 * address: 00083cd0
 * size: 644
 */

/* cRSMTracks::Replace() */

void __thiscall cRSMTracks::Replace(cRSMTracks *this)

{
  int iVar1;
  int iVar2;
  int iVar3;
  char *pcVar4;
  char cVar5;
  int *piVar6;
  char *pcVar7;
  int iVar8;
  char *pcVar9;
  int iVar10;
  int local_523c;
  char acStack_5230 [16384];
  int iStack_1230;
  char acStack_122c [4096];
  char acStack_22c [512];
  int local_2c;

  iVar1 = DAT_00083f58;
  iVar10 = DAT_00083f54 + 0x83ce8;
  piVar6 = *(int **)(iVar10 + DAT_00083f58);
  pcVar9 = (char *)(iVar10 + DAT_00083f5c);
  *(undefined4 *)this = 0;
  local_2c = *piVar6;
  iVar3 = RShellFindFile(pcVar9,false);
  if (iVar3 == 0) {
    RShellReadDirectory((char *)(iVar10 + DAT_00083f6c),(char *)(iVar10 + DAT_00083f70),(int *)this,
                        acStack_5230);
    RShellSaveDirectory(pcVar9,*(int *)this,acStack_5230);
  }
  else {
    RShellLoadDirectory(pcVar9,(int *)this,acStack_5230);
  }
  iVar2 = DAT_00083f64;
  iVar3 = DAT_00083f60;
  if (0 < *(int *)this) {
    local_523c = 0;
    while( true ) {
      pcVar7 = acStack_5230 + local_523c * 0x80;
      sprintf(acStack_22c,(char *)(iVar10 + iVar3),pcVar7,acStack_122c);
      RShellLoadFile(acStack_22c,acStack_122c,&iStack_1230);
      pcVar9 = (char *)Rstrfind((char *)(iVar10 + iVar2),acStack_122c);
      if (pcVar9 == (char *)0x0) {
        RShellError((char *)(iVar10 + DAT_00083f78),pcVar7);
        goto LAB_00083ea4;
      }
      pcVar9 = (char *)Rstrnewline(pcVar9);
      if ((pcVar9 == (char *)0x0) || (pcVar9 = (char *)Rstrnewline(pcVar9), pcVar9 == (char *)0x0))
      break;
      if (*pcVar9 != '@') {
        RShellError((char *)(iVar10 + DAT_00083f7c),pcVar7);
        goto LAB_00083ea4;
      }
      while( true ) {
        cVar5 = pcVar9[1];
        pcVar4 = pcVar9 + 1;
        if ((cVar5 == '@') && (pcVar9[2] == '@')) break;
        while( true ) {
          iVar8 = 0;
          while( true ) {
            if (cVar5 == 'F') {
              pcVar4[iVar8] = '_';
            }
            iVar8 = iVar8 + 1;
            if (iVar8 == 8) break;
            cVar5 = pcVar4[iVar8];
          }
          if (pcVar4[8] != '@') {
            RShellError((char *)(iVar10 + DAT_00083f74),pcVar7);
            goto LAB_00083ea4;
          }
          pcVar9 = (char *)Rstrnewline(pcVar4 + 8);
          if (pcVar9 == (char *)0x0) goto LAB_00083ec8;
          if (*pcVar9 == '@') break;
          cVar5 = pcVar9[1];
          pcVar4 = pcVar9 + 1;
        }
      }
      local_523c = local_523c + 1;
      RShellSaveFile(acStack_22c,acStack_122c,iStack_1230);
      if (*(int *)this <= local_523c) goto LAB_00083ea4;
    }
LAB_00083ec8:
    RShellError((char *)(iVar10 + DAT_00083f68),pcVar7);
  }
LAB_00083ea4:
  if (local_2c == **(int **)(iVar10 + iVar1)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}
