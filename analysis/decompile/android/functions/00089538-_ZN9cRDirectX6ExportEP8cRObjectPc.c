/*
 * mangled: _ZN9cRDirectX6ExportEP8cRObjectPc
 * demangled: cRDirectX::Export(cRObject*, char*)
 * address: 00089538
 * size: 736
 */

/* cRDirectX::Export(cRObject*, char*) */

undefined4 __thiscall cRDirectX::Export(cRDirectX *this,cRObject *param_1,char *param_2)

{
  FILE *__s;
  undefined4 uVar1;
  float *pfVar2;
  int iVar3;
  int iVar4;
  int iVar5;

  __s = fopen(param_2,"w");
  if (__s == (FILE *)0x0) {
    wprintf("Cannot open %s",param_2);
    uVar1 = 0;
  }
  else {
    fwrite("xof 0303txt 0032\n",1,0x11,__s);
    fwrite("Frame {\n",1,8,__s);
    fwrite("\tFrameTransformMatrix {\n",1,0x18,__s);
    fwrite("\t\t1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000;;\n"
           ,1,0x94,__s);
    fwrite(&DAT_000964c4,1,3,__s);
    fwrite("\tMesh {\n",1,8,__s);
    fprintf(__s,"\t\t%i;\n",*(undefined4 *)(param_1 + 0xa0));
    if (0 < *(int *)(param_1 + 0xa0)) {
      iVar4 = 0;
      iVar5 = 0;
      do {
        while( true ) {
          pfVar2 = (float *)(*(int *)(param_1 + 0xa4) + iVar4);
          fprintf(__s,"\t\t%f;%f;%f;",SUB84((double)*pfVar2,0),
                  (int)((ulonglong)(double)*pfVar2 >> 0x20),(double)pfVar2[1],(double)pfVar2[2]);
          if (*(int *)(param_1 + 0xa0) + -1 != iVar5) break;
          iVar5 = iVar5 + 1;
          fwrite(&DAT_000964d8,1,2,__s);
          iVar4 = iVar4 + 0xc;
          if (*(int *)(param_1 + 0xa0) <= iVar5) goto LAB_000896d8;
        }
        fwrite(&DAT_000964e8,1,2,__s);
        iVar5 = iVar5 + 1;
        iVar4 = iVar4 + 0xc;
      } while (iVar5 < *(int *)(param_1 + 0xa0));
    }
LAB_000896d8:
    fprintf(__s,"\t\t%i;\n",*(int *)(param_1 + 0xc0) << 1);
    if (0 < *(int *)(param_1 + 0xc0)) {
      iVar4 = 0;
      iVar5 = 0;
      do {
        while( true ) {
          iVar3 = *(int *)(param_1 + 200) + iVar4;
          fprintf(__s,"\t\t3;%i;%i;%i;",(uint)*(ushort *)(iVar3 + 2),(uint)*(ushort *)(iVar3 + 4),
                  (uint)*(ushort *)(iVar3 + 6));
          iVar3 = *(int *)(param_1 + 200) + iVar4;
          fprintf(__s,"\t\t3;%i;%i;%i;",(uint)*(ushort *)(iVar3 + 2),(uint)*(ushort *)(iVar3 + 6),
                  (uint)*(ushort *)(iVar3 + 8));
          if (*(int *)(param_1 + 0xc0) + -1 != iVar5) break;
          iVar5 = iVar5 + 1;
          fwrite(&DAT_000964d8,1,2,__s);
          iVar4 = iVar4 + 0x30;
          if (*(int *)(param_1 + 0xc0) <= iVar5) goto LAB_000897bc;
        }
        fwrite(&DAT_000964e8,1,2,__s);
        iVar5 = iVar5 + 1;
        iVar4 = iVar4 + 0x30;
      } while (iVar5 < *(int *)(param_1 + 0xc0));
    }
LAB_000897bc:
    fwrite(&DAT_000964c4,1,3,__s);
    fwrite(&DAT_000964fc,1,2,__s);
    fclose(__s);
    uVar1 = 1;
  }
  return uVar1;
}
