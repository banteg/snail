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
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  float *local_2c [2];

  pfVar2 = (float *)RShellMemoryScratch();
  RShellLoadFile(param_1,pfVar2,(int *)0x0);
  sprintf((char *)(this + 0x20),param_1);
  fVar3 = pfVar2[1];
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
      iVar7 = *(int *)(this + 0x10c);
      *(float *)(iVar7 + 4) = fVar3;
      if ((*(uint *)this & 0x1000) == 0) {
        uVar4 = RShellMemoryMalloc((int)fVar3 * 0x14,"Obj VertexUV");
        *(undefined4 *)(iVar7 + 8) = uVar4;
      }
      else {
        uVar4 = RShellMemoryMalloc((int)fVar3 * 10,"Obj VertexUV");
        *(undefined4 *)(iVar7 + 8) = uVar4;
      }
      iVar7 = *(int *)(this + 0x10c);
      if (0 < *(int *)(iVar7 + 4)) {
        iVar8 = 0;
        iVar9 = 0;
        do {
          while (iVar10 = iVar8 * 2, (*(uint *)this & 0x1000) == 0) {
            iVar9 = iVar9 + 1;
            iVar8 = iVar8 + 10;
            SmoGetFixed(this,local_2c,(float *)(*(int *)(iVar7 + 8) + iVar10));
            SmoGetFixed(this,local_2c,(float *)(*(int *)(*(int *)(this + 0x10c) + 8) + iVar10 + 4));
            SmoGetFixed(this,local_2c,(float *)(*(int *)(*(int *)(this + 0x10c) + 8) + iVar10 + 8));
            SmoGetFixed(this,local_2c,(float *)(*(int *)(*(int *)(this + 0x10c) + 8) + iVar10 + 0xc)
                       );
            SmoGetFixed(this,local_2c,
                        (float *)(*(int *)(*(int *)(this + 0x10c) + 8) + iVar10 + 0x10));
            iVar7 = *(int *)(this + 0x10c);
            if (*(int *)(iVar7 + 4) <= iVar9) goto LAB_0002de3c;
          }
          iVar9 = iVar9 + 1;
          SmoGetFixedShort(this,local_2c,(short *)(*(int *)(iVar7 + 8) + iVar8));
          SmoGetFixedShort(this,local_2c,(short *)(*(int *)(*(int *)(this + 0x10c) + 8) + iVar8 + 2)
                          );
          SmoGetFixedShort(this,local_2c,(short *)(*(int *)(*(int *)(this + 0x10c) + 8) + iVar8 + 4)
                          );
          SmoGetFixedShort(this,local_2c,(short *)(*(int *)(*(int *)(this + 0x10c) + 8) + iVar8 + 6)
                          );
          iVar7 = *(int *)(*(int *)(this + 0x10c) + 8) + iVar8;
          iVar8 = iVar8 + 10;
          SmoGetFixedShort(this,local_2c,(short *)(iVar7 + 8));
          iVar7 = *(int *)(this + 0x10c);
        } while (iVar9 < *(int *)(iVar7 + 4));
      }
LAB_0002de3c:
      fVar3 = *local_2c[0];
      *(float *)(iVar7 + 0xc) = fVar3;
      local_2c[0] = local_2c[0] + 1;
      uVar4 = RShellMemoryMalloc((int)fVar3 << 3,"Obj UV");
      *(undefined4 *)(iVar7 + 0x10) = uVar4;
      iVar7 = *(int *)(this + 0x10c);
      if (0 < *(int *)(iVar7 + 0xc)) {
        iVar8 = 0;
        do {
          while( true ) {
            iVar9 = iVar8 * 8;
            iVar10 = iVar8 * 4;
            if ((*(uint *)this & 0x1000) != 0) break;
            iVar8 = iVar8 + 1;
            SmoGetFixed(this,local_2c,(float *)(*(int *)(iVar7 + 0x10) + iVar9));
            SmoGetFixed(this,local_2c,(float *)(*(int *)(*(int *)(this + 0x10c) + 0x10) + iVar9 + 4)
                       );
            iVar7 = *(int *)(this + 0x10c);
            if (*(int *)(iVar7 + 0xc) <= iVar8) goto LAB_0002df08;
          }
          iVar8 = iVar8 + 1;
          SmoGetFixedShort(this,local_2c,(short *)(*(int *)(iVar7 + 0x10) + iVar10));
          SmoGetFixedShort(this,local_2c,
                           (short *)(*(int *)(*(int *)(this + 0x10c) + 0x10) + iVar10 + 2));
          iVar7 = *(int *)(this + 0x10c);
        } while (iVar8 < *(int *)(iVar7 + 0xc));
      }
LAB_0002df08:
      fVar3 = *local_2c[0];
      *(float *)(iVar7 + 0x14) = fVar3;
      local_2c[0] = local_2c[0] + 1;
      uVar4 = RShellMemoryMalloc((int)fVar3 << 1,"Vertex Index Array");
      *(undefined4 *)(iVar7 + 0x18) = uVar4;
      iVar8 = *(int *)(this + 0x10c);
      iVar7 = *(int *)(iVar8 + 0x14);
      if (0 < iVar7) {
        iVar9 = 0;
        iVar10 = *(int *)(iVar8 + 0x18);
        pfVar2 = local_2c[0];
        do {
          iVar1 = iVar9 * 2;
          local_2c[0] = pfVar2 + 1;
          iVar9 = iVar9 + 1;
          *(undefined2 *)(iVar10 + iVar1) = *(undefined2 *)pfVar2;
          pfVar2 = local_2c[0];
        } while (iVar9 < iVar7);
      }
      fVar3 = *local_2c[0];
      *(float *)(iVar8 + 0x44) = fVar3;
      local_2c[0] = local_2c[0] + 1;
      uVar4 = RShellMemoryMalloc((int)fVar3 << 1,"Vertex Strip Index Array");
      iVar7 = *(int *)(this + 0x10c);
      iVar9 = *(int *)(iVar7 + 0x44);
      *(undefined4 *)(iVar8 + 0x48) = uVar4;
      if (0 < iVar9) {
        iVar8 = *(int *)(iVar7 + 0x48);
        iVar7 = 0;
        pfVar2 = local_2c[0];
        do {
          iVar10 = iVar7 * 2;
          local_2c[0] = pfVar2 + 1;
          iVar7 = iVar7 + 1;
          *(undefined2 *)(iVar8 + iVar10) = *(undefined2 *)pfVar2;
          pfVar2 = local_2c[0];
        } while (iVar7 < iVar9);
      }
    }
  } while( true );
}
