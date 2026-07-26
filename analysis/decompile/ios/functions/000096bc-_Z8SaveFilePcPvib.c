/*
 * mangled: _Z8SaveFilePcPvib
 * demangled: SaveFile(char*, void*, int, bool)
 * address: 000096bc
 * size: 200
 */

/* SaveFile(char*, void*, int, bool) */

void SaveFile(char *param_1,void *param_2,int param_3,bool param_4)

{
  byte bVar1;
  FILE *pFVar2;
  int iVar3;
  char acStack_218 [512];

  if ((param_4) && (0 < param_3)) {
    iVar3 = 0;
    bVar1 = 0;
    do {
      *(byte *)(iVar3 + (int)param_2) =
           *(byte *)(iVar3 + (int)param_2) ^ (char)iVar3 * (char)iVar3 ^ bVar1;
      iVar3 = iVar3 + 1;
      bVar1 = bVar1 + 3;
    } while (iVar3 != param_3);
  }
  pFVar2 = _fopen(param_1,"wb");
  if (pFVar2 == (FILE *)0x0) {
    _getcwd(acStack_218,0x200);
    _printf("ERROR:Cannot save file : %s (from %s)\n",param_1,acStack_218);
  }
  else {
    _printf("Saving file :%s %i bytes\n",param_1,param_3);
    _fwrite(param_2,1,param_3,pFVar2);
    _fclose(pFVar2);
  }
  return;
}
