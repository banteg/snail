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
  char *pcVar2;
  char *pcVar3;
  char cVar4;
  char *pcVar5;
  int local_523c;
  char acStack_5230 [16384];
  int iStack_1230;
  char acStack_122c [4096];
  char acStack_22c [512];
  int local_2c;

  *(undefined4 *)this = 0;
  local_2c = __stack_chk_guard;
  iVar1 = RShellFindFile("Data/SegmentsDir.txt",false);
  if (iVar1 == 0) {
    RShellReadDirectory("Segments","*.txt",(int *)this,acStack_5230);
    RShellSaveDirectory("Data/SegmentsDir.txt",*(int *)this,acStack_5230);
  }
  else {
    RShellLoadDirectory("Data/SegmentsDir.txt",(int *)this,acStack_5230);
  }
  if (0 < *(int *)this) {
    local_523c = 0;
    while( true ) {
      pcVar5 = acStack_5230 + local_523c * 0x80;
      sprintf(acStack_22c,"Segments/%s",pcVar5,acStack_122c);
      RShellLoadFile(acStack_22c,acStack_122c,&iStack_1230);
      pcVar2 = (char *)Rstrfind("Data:",acStack_122c);
      if (pcVar2 == (char *)0x0) {
        RShellError("Cannot find Data: in Segment %s\n",pcVar5);
        goto LAB_00083ea4;
      }
      pcVar2 = (char *)Rstrnewline(pcVar2);
      if ((pcVar2 == (char *)0x0) || (pcVar2 = (char *)Rstrnewline(pcVar2), pcVar2 == (char *)0x0))
      break;
      if (*pcVar2 != '@') {
        RShellError("Data line must start with \'@\' in Segment %s\n",pcVar5);
        goto LAB_00083ea4;
      }
      while( true ) {
        cVar4 = pcVar2[1];
        pcVar3 = pcVar2 + 1;
        if ((cVar4 == '@') && (pcVar2[2] == '@')) break;
        while( true ) {
          iVar1 = 0;
          while( true ) {
            if (cVar4 == 'F') {
              pcVar3[iVar1] = '_';
            }
            iVar1 = iVar1 + 1;
            if (iVar1 == 8) break;
            cVar4 = pcVar3[iVar1];
          }
          if (pcVar3[8] != '@') {
            RShellError("Data line must end with \'@\' in Segment %s\n",pcVar5);
            goto LAB_00083ea4;
          }
          pcVar2 = (char *)Rstrnewline(pcVar3 + 8);
          if (pcVar2 == (char *)0x0) goto LAB_00083ec8;
          if (*pcVar2 == '@') break;
          cVar4 = pcVar2[1];
          pcVar3 = pcVar2 + 1;
        }
      }
      local_523c = local_523c + 1;
      RShellSaveFile(acStack_22c,acStack_122c,iStack_1230);
      if (*(int *)this <= local_523c) goto LAB_00083ea4;
    }
LAB_00083ec8:
    RShellError("Unexpected end of file in Segment %s\n",pcVar5);
  }
LAB_00083ea4:
  if (local_2c == __stack_chk_guard) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}
