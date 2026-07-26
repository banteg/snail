/*
 * mangled: _ZN9cRDirectX6ExportEP8cRObjectPc
 * demangled: cRDirectX::Export(cRObject*, char*)
 * address: 00089538
 * size: 736
 */

/* cRDirectX::Export(cRObject*, char*) */

undefined4 __thiscall cRDirectX::Export(cRDirectX *this,cRObject *param_1,char *param_2)

{
  int iVar1;
  FILE *__s;
  undefined4 uVar2;
  float *pfVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  char *pcVar7;
  void *pvVar8;
  int iVar9;
  void *pvVar10;

  iVar9 = DAT_00089818 + 0x89550;
  __s = fopen(param_2,(char *)(iVar9 + DAT_0008981c));
  iVar1 = DAT_00089820;
  if (__s == (FILE *)0x0) {
    wprintf((char *)(iVar9 + DAT_00089850),param_2);
    uVar2 = 0;
  }
  else {
    fwrite((void *)(iVar9 + DAT_00089824),1,0x11,__s);
    fwrite((void *)(iVar9 + DAT_00089828),1,8,__s);
    fwrite((void *)(iVar9 + DAT_0008982c),1,0x18,__s);
    fwrite((void *)(iVar9 + DAT_00089830),1,0x94,__s);
    iVar5 = DAT_00089834;
    fwrite((void *)(iVar9 + iVar1),1,3,__s);
    fwrite((void *)(iVar9 + DAT_00089838),1,8,__s);
    fprintf(__s,(char *)(iVar9 + iVar5),*(undefined4 *)(param_1 + 0xa0));
    if (0 < *(int *)(param_1 + 0xa0)) {
      iVar4 = 0;
      iVar6 = 0;
      pcVar7 = (char *)(iVar9 + DAT_0008983c);
      pvVar8 = (void *)(iVar9 + DAT_00089840);
      pvVar10 = (void *)(iVar9 + DAT_00089844);
      do {
        while( true ) {
          pfVar3 = (float *)(*(int *)(param_1 + 0xa4) + iVar4);
          fprintf(__s,pcVar7,SUB84((double)*pfVar3,0),(int)((ulonglong)(double)*pfVar3 >> 0x20),
                  (double)pfVar3[1],(double)pfVar3[2]);
          if (*(int *)(param_1 + 0xa0) + -1 != iVar6) break;
          iVar6 = iVar6 + 1;
          fwrite(pvVar10,1,2,__s);
          iVar4 = iVar4 + 0xc;
          if (*(int *)(param_1 + 0xa0) <= iVar6) goto LAB_000896d8;
        }
        fwrite(pvVar8,1,2,__s);
        iVar6 = iVar6 + 1;
        iVar4 = iVar4 + 0xc;
      } while (iVar6 < *(int *)(param_1 + 0xa0));
    }
LAB_000896d8:
    fprintf(__s,(char *)(iVar9 + iVar5),*(int *)(param_1 + 0xc0) << 1);
    if (0 < *(int *)(param_1 + 0xc0)) {
      iVar5 = 0;
      iVar4 = 0;
      pcVar7 = (char *)(iVar9 + DAT_00089848);
      pvVar8 = (void *)(iVar9 + DAT_00089840);
      pvVar10 = (void *)(iVar9 + DAT_00089844);
      do {
        while( true ) {
          iVar6 = *(int *)(param_1 + 200) + iVar5;
          fprintf(__s,pcVar7,(uint)*(ushort *)(iVar6 + 2),(uint)*(ushort *)(iVar6 + 4),
                  (uint)*(ushort *)(iVar6 + 6));
          iVar6 = *(int *)(param_1 + 200) + iVar5;
          fprintf(__s,pcVar7,(uint)*(ushort *)(iVar6 + 2),(uint)*(ushort *)(iVar6 + 6),
                  (uint)*(ushort *)(iVar6 + 8));
          if (*(int *)(param_1 + 0xc0) + -1 != iVar4) break;
          iVar4 = iVar4 + 1;
          fwrite(pvVar10,1,2,__s);
          iVar5 = iVar5 + 0x30;
          if (*(int *)(param_1 + 0xc0) <= iVar4) goto LAB_000897bc;
        }
        fwrite(pvVar8,1,2,__s);
        iVar4 = iVar4 + 1;
        iVar5 = iVar5 + 0x30;
      } while (iVar4 < *(int *)(param_1 + 0xc0));
    }
LAB_000897bc:
    fwrite((void *)(iVar9 + iVar1),1,3,__s);
    fwrite((void *)(iVar9 + DAT_0008984c),1,2,__s);
    fclose(__s);
    uVar2 = 1;
  }
  return uVar2;
}
