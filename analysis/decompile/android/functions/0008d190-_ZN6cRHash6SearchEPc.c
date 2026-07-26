/*
 * mangled: _ZN6cRHash6SearchEPc
 * demangled: cRHash::Search(char*)
 * address: 0008d190
 * size: 232
 */

/* cRHash::Search(char*) */

undefined4 __thiscall cRHash::Search(cRHash *this,char *param_1)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  char *pcVar4;
  char cVar5;
  cRHash *pcVar6;
  char cVar7;

  iVar2 = Calc(this,param_1);
  if (*(int *)(this + iVar2 * 8) == -1) {
    return 0xffffffff;
  }
  pcVar6 = this + iVar2 * 8;
  do {
    pcVar3 = (char *)(**(code **)(this + 0x808))(*(undefined4 *)pcVar6);
    cVar1 = *pcVar3;
    pcVar4 = param_1;
    if (cVar1 == '\0') {
LAB_0008d250:
      if (*pcVar4 == '\0') {
        return *(undefined4 *)pcVar6;
      }
    }
    else {
      cVar5 = *param_1;
      while (cVar5 != '\0') {
        if (cVar5 != cVar1) {
          if ((byte)(cVar5 + 0x9fU) < 0x1a) {
            cVar5 = cVar5 + -0x20;
          }
          cVar7 = cVar1;
          if ((byte)(cVar1 + 0x9fU) < 0x1a) {
            cVar7 = cVar1 + -0x20;
          }
          if (cVar5 != cVar7) {
            if (cVar1 == '\0') goto LAB_0008d250;
            break;
          }
        }
        cVar1 = pcVar3[1];
        pcVar4 = pcVar4 + 1;
        pcVar3 = pcVar3 + 1;
        if (cVar1 == '\0') goto LAB_0008d250;
        cVar5 = *pcVar4;
      }
    }
    pcVar6 = *(cRHash **)(pcVar6 + 4);
    if (pcVar6 == (cRHash *)0x0) {
      return 0xffffffff;
    }
  } while( true );
}
