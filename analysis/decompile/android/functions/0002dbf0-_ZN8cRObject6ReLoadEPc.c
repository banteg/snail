/*
 * mangled: _ZN8cRObject6ReLoadEPc
 * demangled: cRObject::ReLoad(char*)
 * address: 0002dbf0
 * size: 1004
 */

/* cRObject::ReLoad(char*) */

void __thiscall cRObject::ReLoad(cRObject *this,char *param_1)

{
  int iVar1;
  float *pfVar2;
  float fVar3;
  undefined4 uVar4;
  float *pfVar5;
  float fVar6;
  char *pcVar7;
  char *pcVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  char *pcVar12;
  char *pcVar13;
  int iVar14;
  float *local_2c [2];

  pfVar2 = (float *)RShellMemoryScratch();
  iVar9 = DAT_0002dfdc + 0x2dc18;
  pcVar12 = (char *)(iVar9 + DAT_0002dfe0);
  pcVar13 = (char *)(iVar9 + DAT_0002dfe4);
  RShellLoadFile(param_1,pfVar2,(int *)0x0);
  sprintf((char *)(this + 0x20),param_1);
  pcVar7 = (char *)(iVar9 + DAT_0002dfe8);
  fVar3 = pfVar2[1];
  pcVar8 = (char *)(iVar9 + DAT_0002dfec);
  fVar6 = *pfVar2;
  pfVar5 = pfVar2 + 2;
  local_2c[0] = pfVar2;
  if (fVar6 == 7.00649e-45) goto LAB_0002dcac;
  do {
    if (fVar6 == 1.12104e-44) {
      return;
    }
    local_2c[0] = (float *)((int)pfVar5 + (int)fVar3 + -8);
    while( true ) {
      fVar3 = local_2c[0][1];
      fVar6 = *local_2c[0];
      pfVar5 = local_2c[0] + 2;
      if (fVar6 != 7.00649e-45) break;
LAB_0002dcac:
      fVar3 = local_2c[0][2];
      local_2c[0] = pfVar5 + 1;
      iVar9 = *(int *)(this + 0x10c);
      *(float *)(iVar9 + 4) = fVar3;
      if ((*(uint *)this & 0x1000) == 0) {
        uVar4 = RShellMemoryMalloc((int)fVar3 * 0x14,pcVar7);
        *(undefined4 *)(iVar9 + 8) = uVar4;
      }
      else {
        uVar4 = RShellMemoryMalloc((int)fVar3 * 10,pcVar7);
        *(undefined4 *)(iVar9 + 8) = uVar4;
      }
      iVar9 = *(int *)(this + 0x10c);
      if (0 < *(int *)(iVar9 + 4)) {
        iVar10 = 0;
        iVar11 = 0;
        do {
          while (iVar14 = iVar10 * 2, (*(uint *)this & 0x1000) == 0) {
            iVar11 = iVar11 + 1;
            iVar10 = iVar10 + 10;
            SmoGetFixed(this,local_2c,(float *)(*(int *)(iVar9 + 8) + iVar14));
            SmoGetFixed(this,local_2c,(float *)(*(int *)(*(int *)(this + 0x10c) + 8) + iVar14 + 4));
            SmoGetFixed(this,local_2c,(float *)(*(int *)(*(int *)(this + 0x10c) + 8) + iVar14 + 8));
            SmoGetFixed(this,local_2c,(float *)(*(int *)(*(int *)(this + 0x10c) + 8) + iVar14 + 0xc)
                       );
            SmoGetFixed(this,local_2c,
                        (float *)(*(int *)(*(int *)(this + 0x10c) + 8) + iVar14 + 0x10));
            iVar9 = *(int *)(this + 0x10c);
            if (*(int *)(iVar9 + 4) <= iVar11) goto LAB_0002de3c;
          }
          iVar11 = iVar11 + 1;
          SmoGetFixedShort(this,local_2c,(short *)(*(int *)(iVar9 + 8) + iVar10));
          SmoGetFixedShort(this,local_2c,
                           (short *)(*(int *)(*(int *)(this + 0x10c) + 8) + iVar10 + 2));
          SmoGetFixedShort(this,local_2c,
                           (short *)(*(int *)(*(int *)(this + 0x10c) + 8) + iVar10 + 4));
          SmoGetFixedShort(this,local_2c,
                           (short *)(*(int *)(*(int *)(this + 0x10c) + 8) + iVar10 + 6));
          iVar9 = *(int *)(*(int *)(this + 0x10c) + 8) + iVar10;
          iVar10 = iVar10 + 10;
          SmoGetFixedShort(this,local_2c,(short *)(iVar9 + 8));
          iVar9 = *(int *)(this + 0x10c);
        } while (iVar11 < *(int *)(iVar9 + 4));
      }
LAB_0002de3c:
      fVar3 = *local_2c[0];
      *(float *)(iVar9 + 0xc) = fVar3;
      local_2c[0] = local_2c[0] + 1;
      uVar4 = RShellMemoryMalloc((int)fVar3 << 3,pcVar12);
      *(undefined4 *)(iVar9 + 0x10) = uVar4;
      iVar9 = *(int *)(this + 0x10c);
      if (0 < *(int *)(iVar9 + 0xc)) {
        iVar10 = 0;
        do {
          while( true ) {
            iVar11 = iVar10 * 8;
            iVar14 = iVar10 * 4;
            if ((*(uint *)this & 0x1000) != 0) break;
            iVar10 = iVar10 + 1;
            SmoGetFixed(this,local_2c,(float *)(*(int *)(iVar9 + 0x10) + iVar11));
            SmoGetFixed(this,local_2c,
                        (float *)(*(int *)(*(int *)(this + 0x10c) + 0x10) + iVar11 + 4));
            iVar9 = *(int *)(this + 0x10c);
            if (*(int *)(iVar9 + 0xc) <= iVar10) goto LAB_0002df08;
          }
          iVar10 = iVar10 + 1;
          SmoGetFixedShort(this,local_2c,(short *)(*(int *)(iVar9 + 0x10) + iVar14));
          SmoGetFixedShort(this,local_2c,
                           (short *)(*(int *)(*(int *)(this + 0x10c) + 0x10) + iVar14 + 2));
          iVar9 = *(int *)(this + 0x10c);
        } while (iVar10 < *(int *)(iVar9 + 0xc));
      }
LAB_0002df08:
      fVar3 = *local_2c[0];
      *(float *)(iVar9 + 0x14) = fVar3;
      local_2c[0] = local_2c[0] + 1;
      uVar4 = RShellMemoryMalloc((int)fVar3 << 1,pcVar13);
      *(undefined4 *)(iVar9 + 0x18) = uVar4;
      iVar10 = *(int *)(this + 0x10c);
      iVar9 = *(int *)(iVar10 + 0x14);
      if (0 < iVar9) {
        iVar11 = 0;
        iVar14 = *(int *)(iVar10 + 0x18);
        pfVar2 = local_2c[0];
        do {
          iVar1 = iVar11 * 2;
          local_2c[0] = pfVar2 + 1;
          iVar11 = iVar11 + 1;
          *(undefined2 *)(iVar14 + iVar1) = *(undefined2 *)pfVar2;
          pfVar2 = local_2c[0];
        } while (iVar11 < iVar9);
      }
      fVar3 = *local_2c[0];
      *(float *)(iVar10 + 0x44) = fVar3;
      local_2c[0] = local_2c[0] + 1;
      uVar4 = RShellMemoryMalloc((int)fVar3 << 1,pcVar8);
      iVar9 = *(int *)(this + 0x10c);
      iVar11 = *(int *)(iVar9 + 0x44);
      *(undefined4 *)(iVar10 + 0x48) = uVar4;
      if (0 < iVar11) {
        iVar10 = *(int *)(iVar9 + 0x48);
        iVar9 = 0;
        pfVar2 = local_2c[0];
        do {
          iVar14 = iVar9 * 2;
          local_2c[0] = pfVar2 + 1;
          iVar9 = iVar9 + 1;
          *(undefined2 *)(iVar10 + iVar14) = *(undefined2 *)pfVar2;
          pfVar2 = local_2c[0];
        } while (iVar9 < iVar11);
      }
    }
  } while( true );
}
