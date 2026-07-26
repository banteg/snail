/*
 * mangled: _ZN6cRHash6ReportEv
 * demangled: cRHash::Report()
 * address: 0008d278
 * size: 172
 */

/* cRHash::Report() */

void __thiscall cRHash::Report(cRHash *this)

{
  cRHash *pcVar1;
  int iVar2;
  int iVar3;
  int iVar4;

  wprintf("Hash Table Report:");
  iVar3 = 0;
  iVar4 = 0;
  do {
    if (*(int *)(this + iVar3 * 8) == -1) {
      wprintf("%i -1\n",iVar3);
    }
    else {
      pcVar1 = this + iVar3 * 8;
      if (pcVar1 == (cRHash *)0x0) {
        iVar2 = 0;
      }
      else {
        iVar2 = 0;
        do {
          pcVar1 = *(cRHash **)(pcVar1 + 4);
          iVar2 = iVar2 + 1;
        } while (pcVar1 != (cRHash *)0x0);
      }
      if (iVar4 < iVar2) {
        iVar4 = iVar2;
      }
      wprintf("%i %i\n",iVar3,iVar2);
    }
    iVar3 = iVar3 + 1;
  } while (iVar3 != 0x100);
  wprintf("MaxListLength=%i\n",iVar4);
  return;
}
