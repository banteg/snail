/*
 * mangled: _ZN11cRSubTracks6ExportEP12cRSubSegment
 * demangled: cRSubTracks::Export(cRSubSegment*)
 * address: 00084a98
 * size: 420
 */

/* cRSubTracks::Export(cRSubSegment*) */

void __thiscall cRSubTracks::Export(cRSubTracks *this,cRSubSegment *param_1)

{
  FILE *__s;
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  char acStack_42c [1024];
  int local_2c;

  local_2c = __stack_chk_guard;
  sprintf(acStack_42c,"Segments/%s.txt",*(undefined4 *)(param_1 + 0x10));
  __s = fopen(acStack_42c,"w");
  if (__s == (FILE *)0x0) {
    wprintf("Cannot open %s",acStack_42c);
    uVar1 = 0;
  }
  else {
    fwrite("// Segment data\n",1,0x10,__s);
    fprintf(__s,"ID:%i\n",*(undefined4 *)(param_1 + 0xc));
    fprintf(__s,"Name:\'%s\'\n",*(undefined4 *)(param_1 + 0x10));
    fwrite("Data:\n",1,6,__s);
    fwrite("@@@@@@@@@@\n",1,0xb,__s);
    if (0 < *(int *)(param_1 + 4)) {
      iVar3 = 0;
      do {
        fputc(0x40,__s);
        iVar4 = 0;
        do {
          iVar2 = iVar3 * 8 + iVar4;
          iVar4 = iVar4 + 1;
          fputc((uint)*(byte *)(*(int *)(param_1 + 0x14) + iVar2),__s);
        } while (iVar4 != 8);
        fwrite(&DAT_000943f8,1,2,__s);
        iVar3 = iVar3 + 1;
      } while (iVar3 < *(int *)(param_1 + 4));
    }
    fwrite("@@@@@@@@@@\n",1,0xb,__s);
    fclose(__s);
    uVar1 = 1;
  }
  if (local_2c == __stack_chk_guard) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(uVar1);
}
