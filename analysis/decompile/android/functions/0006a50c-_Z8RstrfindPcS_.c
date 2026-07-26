/*
 * mangled: _Z8RstrfindPcS_
 * demangled: Rstrfind(char*, char*)
 * address: 0006a50c
 * size: 156
 */

/* Rstrfind(char*, char*) */

byte * Rstrfind(char *param_1,char *param_2)

{
  byte bVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  byte *pbVar5;
  byte *pbVar6;

  bVar1 = *param_2;
  do {
    if (bVar1 == 0) {
      return (byte *)0x0;
    }
    bVar1 = *param_2;
    pbVar5 = (byte *)param_1;
    pbVar6 = (byte *)param_2;
    while (bVar2 = *pbVar5, ((bVar1 ^ bVar2) & 0xdf) == 0) {
      iVar3 = RstrASC(bVar2);
      iVar4 = RstrASC(*pbVar6);
      if (iVar3 != iVar4) {
        bVar2 = *pbVar5;
        break;
      }
      pbVar6 = pbVar6 + 1;
      bVar1 = *pbVar6;
      pbVar5 = pbVar5 + 1;
      if (bVar1 == 0) {
        if (*pbVar5 != 0) {
          return (byte *)0x0;
        }
        return (byte *)param_2;
      }
    }
    if (bVar2 == 0) {
      return (byte *)param_2;
    }
    param_2 = param_2 + 1;
    bVar1 = *param_2;
  } while( true );
}
