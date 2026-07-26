/*
 * mangled: _Z8RstrfindPcS_
 * demangled: Rstrfind(char*, char*)
 * address: 0000e068
 * size: 196
 */

/* Rstrfind(char*, char*) */

byte * Rstrfind(char *param_1,char *param_2)

{
  byte bVar1;
  byte bVar2;
  byte *pbVar3;
  byte *pbVar4;
  byte bVar5;

  bVar5 = *param_2;
  pbVar4 = (byte *)param_1;
  pbVar3 = (byte *)param_2;
  if (bVar5 == 0) {
    return (byte *)0x0;
  }
  do {
    while (bVar1 = *pbVar4, (bVar1 & 0xdf) != (bVar5 & 0xdf)) {
LAB_0000e108:
      if (bVar1 == 0) {
        return pbVar3;
      }
      param_2 = (char *)(pbVar3 + 1);
      bVar5 = *param_2;
      pbVar4 = (byte *)param_1;
      pbVar3 = (byte *)param_2;
      if (bVar5 == 0) {
        return (byte *)0x0;
      }
    }
    bVar2 = bVar1;
    if ((byte)(bVar1 + 0x9f) < 0x1a) {
      bVar2 = bVar1 - 0x20;
    }
    if ((byte)(bVar5 + 0x9f) < 0x1a) {
      bVar5 = bVar5 - 0x20;
    }
    if (bVar2 != bVar5) goto LAB_0000e108;
    param_2 = param_2 + 1;
    bVar5 = *param_2;
    pbVar4 = pbVar4 + 1;
    if (bVar5 == 0) {
      if (*pbVar4 != 0) {
        return (byte *)0x0;
      }
      return pbVar3;
    }
  } while( true );
}
