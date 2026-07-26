/*
 * mangled: _ZN8cRObject4LoadEPc
 * demangled: cRObject::Load(char*)
 * address: 0002eae4
 * size: 2408
 */

/* cRObject::Load(char*) */

void __thiscall cRObject::Load(cRObject *this,char *param_1)

{
  float *pfVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  size_t sVar5;
  undefined2 *puVar6;
  uint uVar7;
  int iVar8;
  uint uVar9;
  float *extraout_r3;
  float fVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  float fVar14;
  float fVar15;
  char acStack_82c [2048];
  float *local_2c [2];

  uVar9 = *(uint *)this;
  pfVar1 = (float *)RShellMemoryScratch();
  RShellLoadFile(param_1,pfVar1,(int *)0x0);
  sprintf((char *)(this + 0x20),param_1);
  local_2c[0] = pfVar1;
  do {
    fVar10 = *local_2c[0];
    pfVar1 = local_2c[0] + 2;
    switch(fVar10) {
    case 0.0:
      fVar10 = local_2c[0][2];
      *(uint *)this = (uint)fVar10 | 0x2000000;
      fVar14 = local_2c[0][3];
      if ((uVar9 & 0x1000) != 0) {
        *(uint *)this = (uint)fVar10 | 0x2001000;
      }
      *(float *)(this + 0xa0) = fVar14;
      local_2c[0] = local_2c[0] + 4;
      break;
    case 1.4013e-45:
      if ((*(uint *)this & 0x1000) == 0) {
        local_2c[0] = pfVar1;
        uVar3 = RShellMemoryMalloc(*(int *)(this + 0xa0) * 0xc,"Object Vertex List");
        *(undefined4 *)(this + 0xa4) = uVar3;
      }
      else {
        local_2c[0] = pfVar1;
        uVar3 = RShellMemoryMalloc(*(int *)(this + 0xa0) * 6,"Object Vertex List");
        *(undefined4 *)(this + 0xa4) = uVar3;
      }
      if (0 < *(int *)(this + 0xa0)) {
        iVar2 = 0;
        iVar8 = 0;
        do {
          iVar11 = iVar2 * 2;
          if ((*(uint *)this & 0x1000) == 0) {
            SmoGetFixed(this,local_2c,(float *)(*(int *)(this + 0xa4) + iVar11));
            SmoGetFixed(this,local_2c,(float *)(*(int *)(this + 0xa4) + iVar11 + 4));
            SmoGetFixed(this,local_2c,(float *)(*(int *)(this + 0xa4) + iVar11 + 8));
          }
          else {
            SmoGetFixedShort(this,local_2c,(short *)(*(int *)(this + 0xa4) + iVar2));
            SmoGetFixedShort(this,local_2c,(short *)(*(int *)(this + 0xa4) + iVar2 + 2));
            SmoGetFixedShort(this,local_2c,(short *)(*(int *)(this + 0xa4) + iVar2 + 4));
          }
          iVar8 = iVar8 + 1;
          iVar2 = iVar2 + 6;
        } while (iVar8 < *(int *)(this + 0xa0));
      }
      break;
    case 2.8026e-45:
      pfVar1 = local_2c[0] + 2;
      local_2c[0] = local_2c[0] + 3;
      RequestFaceQuads(this,(int)*pfVar1);
      if (0 < *(int *)(this + 0xc0)) {
        iVar2 = 0;
        iVar8 = 0;
        pfVar1 = local_2c[0];
        do {
          fVar10 = pfVar1[1];
          iVar12 = *(int *)(this + 200);
          local_2c[0] = pfVar1 + 2;
          *(undefined2 *)(iVar12 + iVar2) = SUB42(*pfVar1,0);
          iVar8 = iVar8 + 1;
          uVar3 = cRTextures::Add((cRTextures *)gTextureList,acStack_82c + (int)fVar10 * 0x40,
                                  (cTgaHeader *)0x0,0);
          iVar11 = *(int *)(this + 200);
          *(undefined4 *)((undefined2 *)(iVar12 + iVar2) + 6) = uVar3;
          SmoGetFixed(this,local_2c,(float *)(iVar11 + iVar2 + 0x10));
          SmoGetFixed(this,local_2c,(float *)(*(int *)(this + 200) + iVar2 + 0x18));
          SmoGetFixed(this,local_2c,(float *)(*(int *)(this + 200) + iVar2 + 0x20));
          SmoGetFixed(this,local_2c,(float *)(*(int *)(this + 200) + iVar2 + 0x28));
          SmoGetFixed(this,local_2c,(float *)(*(int *)(this + 200) + iVar2 + 0x14));
          SmoGetFixed(this,local_2c,(float *)(*(int *)(this + 200) + iVar2 + 0x1c));
          SmoGetFixed(this,local_2c,(float *)(*(int *)(this + 200) + iVar2 + 0x24));
          SmoGetFixed(this,local_2c,(float *)(*(int *)(this + 200) + iVar2 + 0x2c));
          *(undefined2 *)(*(int *)(this + 200) + iVar2 + 2) = *(undefined2 *)local_2c[0];
          pfVar1 = local_2c[0] + 2;
          *(undefined2 *)(*(int *)(this + 200) + iVar2 + 4) = *(undefined2 *)((int)local_2c[0] + 2);
          *(undefined2 *)(*(int *)(this + 200) + iVar2 + 6) = *(undefined2 *)(local_2c[0] + 1);
          iVar11 = *(int *)(this + 200) + iVar2;
          iVar2 = iVar2 + 0x30;
          *(undefined2 *)(iVar11 + 8) = *(undefined2 *)((int)local_2c[0] + 6);
          local_2c[0] = pfVar1;
        } while (iVar8 < *(int *)(this + 0xc0));
      }
      break;
    case 4.2039e-45:
      fVar10 = local_2c[0][2];
      pfVar1 = local_2c[0] + 3;
      if (0 < (int)fVar10) {
        iVar2 = 0;
        local_2c[0] = pfVar1;
        do {
          Rstrcpy(acStack_82c + iVar2 * 0x40,(char *)pfVar1);
          sVar5 = strlen((char *)pfVar1);
          iVar2 = iVar2 + 1;
          pfVar1 = (float *)((int)pfVar1 + sVar5 + 1);
        } while (iVar2 < (int)fVar10);
      }
      local_2c[0] = (float *)((int)pfVar1 + (4U - (int)pfVar1 & 3));
      break;
    case 5.60519e-45:
      local_2c[0] = pfVar1;
      RequestVerticesCopy(this);
      puVar6 = (undefined2 *)RShellMemoryMalloc(0x18,"Object Animation");
      fVar10 = local_2c[0][1];
      fVar14 = *local_2c[0];
      *(undefined2 **)(this + 0x104) = puVar6;
      fVar15 = local_2c[0][3];
      *(float *)(puVar6 + 2) = fVar10;
      fVar10 = local_2c[0][2];
      *(float *)(puVar6 + 8) = fVar15;
      fVar15 = local_2c[0][4];
      *puVar6 = SUB42(fVar14,0);
      *(float *)(puVar6 + 10) = fVar15;
      *(float *)(puVar6 + 4) = fVar10;
      pfVar1 = local_2c[0] + 5;
      local_2c[0] = local_2c[0] + 6;
      *(float *)(this + 0xd0) = *pfVar1;
      uVar3 = RShellMemoryMalloc(*(int *)(puVar6 + 2) << 2,"Object Animation Frame array");
      iVar8 = *(int *)(this + 0x104);
      iVar2 = *(int *)(iVar8 + 4);
      *(undefined4 *)(puVar6 + 6) = uVar3;
      if (0 < iVar2) {
        iVar2 = 0;
        do {
          iVar11 = *(int *)(iVar8 + 0xc);
          uVar3 = RShellMemoryMalloc(0xc,"Object Animation Frame");
          uVar7 = *(uint *)this;
          *(undefined4 *)(iVar11 + iVar2 * 4) = uVar3;
          if ((uVar7 & 0x1000) == 0) {
            puVar4 = *(undefined4 **)(*(int *)(*(int *)(this + 0x104) + 0xc) + iVar2 * 4);
            uVar3 = RShellMemoryMalloc(*(int *)(this + 0xa0) * 0xc,"Anim Frame Vertices");
            *puVar4 = uVar3;
            SmoGetFixedArray(this,local_2c,
                             (float *)**(undefined4 **)
                                        (*(int *)(*(int *)(this + 0x104) + 0xc) + iVar2 * 4),
                             *(int *)(this + 0xa0) * 3);
          }
          else {
            puVar4 = *(undefined4 **)(*(int *)(*(int *)(this + 0x104) + 0xc) + iVar2 * 4);
            uVar3 = RShellMemoryMalloc(*(int *)(this + 0xa0) * 6,"Anim Frame Vertices");
            *puVar4 = uVar3;
            SmoGetFixedShortArray
                      (this,local_2c,
                       (short *)**(undefined4 **)
                                  (*(int *)(*(int *)(this + 0x104) + 0xc) + iVar2 * 4),
                       *(int *)(this + 0xa0) * 3);
          }
          iVar12 = *(int *)(*(int *)(*(int *)(this + 0x104) + 0xc) + iVar2 * 4);
          uVar3 = RShellMemoryMalloc(*(int *)(this + 0xd0) << 2,"Anim Facequad Normals");
          iVar11 = *(int *)(this + 0xd0);
          if (iVar11 < 1) {
            iVar8 = *(int *)(this + 0x104);
          }
          *(undefined4 *)(iVar12 + 8) = uVar3;
          if (0 < iVar11) {
            iVar8 = *(int *)(this + 0x104);
            iVar12 = 0;
            iVar13 = *(int *)(*(int *)(*(int *)(iVar8 + 0xc) + iVar2 * 4) + 8);
            pfVar1 = local_2c[0];
            do {
              local_2c[0] = pfVar1 + 1;
              *(int *)(iVar13 + iVar12 * 4) = gObjectList._16_4_ + (int)*pfVar1 * 0xc;
              iVar12 = iVar12 + 1;
              pfVar1 = local_2c[0];
            } while (iVar12 < iVar11);
          }
          iVar2 = iVar2 + 1;
        } while (iVar2 < *(int *)(iVar8 + 4));
      }
      break;
    case 7.00649e-45:
      local_2c[0] = pfVar1;
      puVar4 = (undefined4 *)RShellMemoryMalloc(0x5c,"Obj Vertex array");
      *(undefined4 **)(this + 0x10c) = puVar4;
      uVar3 = cRTextures::Add((cRTextures *)gTextureList,acStack_82c,(cTgaHeader *)0x0,0);
      iVar2 = *(int *)(this + 0x10c);
      fVar10 = *local_2c[0];
      *(float *)(iVar2 + 4) = fVar10;
      uVar7 = *(uint *)this;
      *puVar4 = uVar3;
      if ((uVar7 & 0x1000) == 0) {
        local_2c[0] = local_2c[0] + 1;
        uVar3 = RShellMemoryMalloc((int)fVar10 * 0x14,"Obj VertexUV");
        *(undefined4 *)(iVar2 + 8) = uVar3;
        if ((*(uint *)this & 0x1000) == 0) goto LAB_0002f404;
LAB_0002ed74:
        SmoGetFixedShortArray
                  (this,local_2c,*(short **)(*(int *)(this + 0x10c) + 8),
                   *(int *)(*(int *)(this + 0x10c) + 4) * 5);
      }
      else {
        local_2c[0] = local_2c[0] + 1;
        uVar3 = RShellMemoryMalloc((int)fVar10 * 10,"Obj VertexUV");
        *(undefined4 *)(iVar2 + 8) = uVar3;
        if ((*(uint *)this & 0x1000) != 0) goto LAB_0002ed74;
LAB_0002f404:
        SmoGetFixedArray(this,local_2c,*(float **)(*(int *)(this + 0x10c) + 8),
                         *(int *)(*(int *)(this + 0x10c) + 4) * 5);
      }
      iVar2 = *(int *)(this + 0x10c);
      fVar10 = *local_2c[0];
      *(float *)(iVar2 + 0xc) = fVar10;
      local_2c[0] = local_2c[0] + 1;
      uVar3 = RShellMemoryMalloc((int)fVar10 << 3,"Obj UV");
      *(undefined4 *)(iVar2 + 0x10) = uVar3;
      if ((*(uint *)this & 0x1000) == 0) {
        SmoGetFixedArray(this,local_2c,*(float **)(*(int *)(this + 0x10c) + 0x10),
                         *(int *)(*(int *)(this + 0x10c) + 0xc) << 1);
      }
      else {
        SmoGetFixedShortArray
                  (this,local_2c,*(short **)(*(int *)(this + 0x10c) + 0x10),
                   *(int *)(*(int *)(this + 0x10c) + 0xc) << 1);
      }
      iVar11 = *(int *)(this + 0x10c);
      fVar10 = *local_2c[0];
      *(float *)(iVar11 + 0x14) = fVar10;
      local_2c[0] = local_2c[0] + 1;
      uVar3 = RShellMemoryMalloc((int)fVar10 << 1,"Vertex Index Array");
      iVar8 = *(int *)(this + 0x10c);
      iVar2 = *(int *)(iVar8 + 0x14);
      pfVar1 = extraout_r3;
      if (iVar2 < 1) {
        pfVar1 = local_2c[0];
      }
      *(undefined4 *)(iVar11 + 0x18) = uVar3;
      if (0 < iVar2) {
        iVar11 = 0;
        iVar12 = *(int *)(iVar8 + 0x18);
        do {
          iVar13 = iVar11 * 2;
          pfVar1 = local_2c[0] + 1;
          iVar11 = iVar11 + 1;
          *(undefined2 *)(iVar12 + iVar13) = *(undefined2 *)local_2c[0];
          local_2c[0] = pfVar1;
        } while (iVar11 < iVar2);
      }
      local_2c[0] = pfVar1 + 1;
      fVar10 = *pfVar1;
      *(float *)(iVar8 + 0x44) = fVar10;
      uVar3 = RShellMemoryMalloc((int)fVar10 << 1,"Vertex Strip Index Array");
      iVar2 = *(int *)(this + 0x10c);
      iVar11 = *(int *)(iVar2 + 0x44);
      *(undefined4 *)(iVar8 + 0x48) = uVar3;
      if (0 < iVar11) {
        iVar8 = *(int *)(iVar2 + 0x48);
        iVar2 = 0;
        do {
          iVar12 = iVar2 * 2;
          pfVar1 = local_2c[0] + 1;
          iVar2 = iVar2 + 1;
          *(undefined2 *)(iVar8 + iVar12) = *(undefined2 *)local_2c[0];
          local_2c[0] = pfVar1;
        } while (iVar2 < iVar11);
      }
      break;
    case 8.40779e-45:
      fVar10 = local_2c[0][2];
      local_2c[0] = local_2c[0] + 3;
      *(float *)(this + 0xe4) = fVar10;
      uVar3 = RShellMemoryMalloc((int)fVar10 * 10,"Toon Edges");
      *(undefined4 *)(this + 0xe8) = uVar3;
      uVar3 = RShellMemoryMalloc(*(int *)(this + 0xe4) << 2,"Object Edge Index Array");
      iVar2 = *(int *)(this + 0xe4);
      *(undefined4 *)(this + 0xe0) = uVar3;
      if (0 < iVar2) {
        iVar12 = *(int *)(this + 0xe8);
        iVar11 = 0;
        iVar13 = 0;
        iVar8 = iVar12;
        do {
          iVar13 = iVar13 + 1;
          puVar6 = (undefined2 *)(iVar12 + iVar11);
          *puVar6 = *(undefined2 *)local_2c[0];
          iVar11 = iVar11 + 10;
          puVar6[3] = *(undefined2 *)(local_2c[0] + 1);
          *(undefined2 *)(iVar8 + 8) = *(undefined2 *)(local_2c[0] + 2);
          iVar8 = iVar8 + 10;
          puVar6[1] = *(undefined2 *)(local_2c[0] + 3);
          pfVar1 = local_2c[0] + 4;
          local_2c[0] = local_2c[0] + 5;
          puVar6[2] = *(undefined2 *)pfVar1;
        } while (iVar13 < iVar2);
      }
      break;
    case 9.80909e-45:
      local_2c[0] = pfVar1;
      iVar2 = RShellMemoryMalloc(*(int *)(this + 0xa0) << 4,"Object Vertex Colour List");
      *(int *)(this + 0xb4) = iVar2;
      if (0 < *(int *)(this + 0xa0)) {
        iVar8 = 0;
        do {
          *(float *)(iVar2 + iVar8 * 0x10) = *local_2c[0];
          iVar11 = iVar8 * 0x10;
          iVar8 = iVar8 + 1;
          *(float *)(*(int *)(this + 0xb4) + iVar11 + 4) = local_2c[0][1];
          *(float *)(*(int *)(this + 0xb4) + iVar11 + 8) = local_2c[0][2];
          iVar12 = *(int *)(this + 0xa0);
          pfVar1 = local_2c[0] + 3;
          iVar2 = *(int *)(this + 0xb4);
          local_2c[0] = local_2c[0] + 4;
          *(float *)(iVar2 + iVar11 + 0xc) = *pfVar1;
        } while (iVar8 < iVar12);
      }
      break;
    case 1.12104e-44:
      return;
    default:
      local_2c[0] = pfVar1;
      wprintf("*** ERROR: Unknown SMO Packet %i",fVar10);
      if (fVar10 == 1.12104e-44) {
        return;
      }
    }
  } while( true );
}
