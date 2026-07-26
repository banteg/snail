/*
 * mangled: _ZN11cRSubTracks6ExportEP12cRSubSegment
 * demangled: cRSubTracks::Export(cRSubSegment*)
 * address: 00084a98
 * size: 420
 */

/* cRSubTracks::Export(cRSubSegment*) */

void __thiscall cRSubTracks::Export(cRSubTracks *this,cRSubSegment *param_1)

{
  int iVar1;
  int iVar2;
  FILE *__s;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  void *__ptr;
  int iVar7;
  char acStack_42c [1024];
  int local_2c;

  iVar1 = DAT_00084c40;
  iVar6 = DAT_00084c3c + 0x84ab0;
  local_2c = **(int **)(iVar6 + DAT_00084c40);
  sprintf(acStack_42c,(char *)(iVar6 + DAT_00084c44),*(undefined4 *)(param_1 + 0x10));
  __s = fopen(acStack_42c,(char *)(iVar6 + DAT_00084c48));
  iVar2 = DAT_00084c4c;
  if (__s == (FILE *)0x0) {
    wprintf((char *)(iVar6 + DAT_00084c64),acStack_42c);
    uVar3 = 0;
  }
  else {
    fwrite((void *)(iVar6 + DAT_00084c50),1,0x10,__s);
    fprintf(__s,(char *)(iVar6 + DAT_00084c54),*(undefined4 *)(param_1 + 0xc));
    fprintf(__s,(char *)(iVar6 + DAT_00084c58),*(undefined4 *)(param_1 + 0x10));
    fwrite((void *)(iVar6 + DAT_00084c5c),1,6,__s);
    fwrite((void *)(iVar6 + iVar2),1,0xb,__s);
    if (0 < *(int *)(param_1 + 4)) {
      iVar5 = 0;
      __ptr = (void *)(iVar6 + DAT_00084c60);
      do {
        fputc(0x40,__s);
        iVar7 = 0;
        do {
          iVar4 = iVar5 * 8 + iVar7;
          iVar7 = iVar7 + 1;
          fputc((uint)*(byte *)(*(int *)(param_1 + 0x14) + iVar4),__s);
        } while (iVar7 != 8);
        fwrite(__ptr,1,2,__s);
        iVar5 = iVar5 + 1;
      } while (iVar5 < *(int *)(param_1 + 4));
    }
    fwrite((void *)(iVar6 + iVar2),1,0xb,__s);
    fclose(__s);
    uVar3 = 1;
  }
  if (local_2c == **(int **)(iVar6 + iVar1)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(uVar3);
}
