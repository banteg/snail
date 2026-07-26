/*
 * mangled: _Z14PfmLoadFileDatPviiiitt
 * demangled: PfmLoadFileDat(void*, int, int, int, int, unsigned short, unsigned short)
 * address: 00024c74
 * size: 552
 */

/* PfmLoadFileDat(void*, int, int, int, int, unsigned short, unsigned short) */

void PfmLoadFileDat(void *param_1,int param_2,int param_3,int param_4,int param_5,ushort param_6,
                   ushort param_7)

{
  void *local_2c;

  if (gDatFP == (FILE *)0x0) {
    wprintf("ERROR: Cannot open File\n");
    return;
  }
  switch(param_5) {
  case 0:
    fseek(gDatFP,param_2 + gJavaAssetStart,0);
    fread(param_1,1,param_3,gDatFP);
    return;
  case 1:
    local_2c = malloc(param_4);
    fseek(gDatFP,param_2 + gJavaAssetStart,0);
    fread(local_2c,1,param_4,gDatFP);
    JAVAC_UnZip(param_1,param_3,local_2c,param_4);
    goto LAB_00023ac4;
  case 2:
    local_2c = malloc(param_4);
    fseek(gDatFP,param_2 + gJavaAssetStart,0);
    fread(local_2c,1,param_4,gDatFP);
    JAVAC_UnJpg((void *)((int)param_1 + 0x12),param_3,local_2c,param_4,(uint)param_6,(uint)param_7);
    break;
  case 3:
    local_2c = malloc(param_4);
    fseek(gDatFP,param_2 + gJavaAssetStart,0);
    fread(local_2c,1,param_4,gDatFP);
    JAVAC_UnPng((void *)((int)param_1 + 0x12),param_3,local_2c,param_4,(uint)param_6,(uint)param_7);
    break;
  default:
    return;
  }
  *(ushort *)((int)param_1 + 0xe) = param_7;
  *(undefined1 *)((int)param_1 + 0x11) = 8;
  *(ushort *)((int)param_1 + 0xc) = param_6;
  *(undefined1 *)((int)param_1 + 2) = 2;
  *(undefined2 *)((int)param_1 + 10) = 0;
  *(undefined1 *)((int)param_1 + 0x10) = 0x20;
  *(undefined1 *)((int)param_1 + 7) = 0;
  *(undefined1 *)((int)param_1 + 6) = 0;
  *(undefined1 *)((int)param_1 + 5) = 0;
  *(undefined1 *)((int)param_1 + 4) = 0;
  *(undefined1 *)((int)param_1 + 3) = 0;
  *(undefined1 *)((int)param_1 + 1) = 0;
  *(undefined1 *)param_1 = 0;
  *(undefined2 *)((int)param_1 + 8) = 0;
LAB_00023ac4:
  free(local_2c);
  return;
}
