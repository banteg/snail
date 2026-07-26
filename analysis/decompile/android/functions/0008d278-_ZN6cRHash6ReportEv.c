/*
 * mangled: _ZN6cRHash6ReportEv
 * demangled: cRHash::Report()
 * address: 0008d278
 * size: 172
 */

/* cRHash::Report() */

void __thiscall cRHash::Report(cRHash *this)

{
  int iVar1;
  int iVar2;
  cRHash *pcVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;

  iVar2 = DAT_0008d330;
  iVar1 = DAT_0008d32c;
  iVar7 = DAT_0008d324 + 0x8d290;
  wprintf((char *)(iVar7 + DAT_0008d328));
  iVar5 = 0;
  iVar6 = 0;
  do {
    if (*(int *)(this + iVar5 * 8) == -1) {
      wprintf((char *)(iVar7 + iVar2),iVar5);
    }
    else {
      pcVar3 = this + iVar5 * 8;
      if (pcVar3 == (cRHash *)0x0) {
        iVar4 = 0;
      }
      else {
        iVar4 = 0;
        do {
          pcVar3 = *(cRHash **)(pcVar3 + 4);
          iVar4 = iVar4 + 1;
        } while (pcVar3 != (cRHash *)0x0);
      }
      if (iVar6 < iVar4) {
        iVar6 = iVar4;
      }
      wprintf((char *)(iVar7 + iVar1),iVar5,iVar4);
    }
    iVar5 = iVar5 + 1;
  } while (iVar5 != 0x100);
  wprintf((char *)(iVar7 + DAT_0008d334),iVar6);
  return;
}
