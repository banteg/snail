/*
 * mangled: _Z7OFGetIDPcS_S_
 * demangled: OFGetID(char*, char*, char*)
 * address: 0008e714
 * size: 220
 */

/* OFGetID(char*, char*, char*) */

void OFGetID(char *param_1,char *param_2,char *param_3)

{
  char *pcVar1;
  char cVar2;
  char *pcVar3;
  int iVar4;
  char acStack_124 [256];
  int local_24;

  local_24 = __stack_chk_guard;
  sprintf(acStack_124,"<name>%s</name>",param_1);
  iVar4 = Rstrfind(acStack_124,param_2);
  if (iVar4 == 0) {
    RShellError("Can\'t find %s in OF Xml",param_1);
  }
  else {
    iVar4 = Rstrfind("<id>",(char *)(iVar4 + -100));
    cVar2 = *(char *)(iVar4 + 4);
    pcVar3 = param_3;
    while (cVar2 != '<') {
      *pcVar3 = cVar2;
      pcVar1 = (char *)(iVar4 + 5);
      iVar4 = iVar4 + 1;
      pcVar3 = pcVar3 + 1;
      cVar2 = *pcVar1;
    }
    *pcVar3 = '\0';
    wprintf("Found %s",param_3);
  }
  if (local_24 != __stack_chk_guard) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}
