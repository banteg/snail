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
  char *pcVar6;
  undefined2 *puVar7;
  uint uVar8;
  int iVar9;
  uint uVar10;
  char *pcVar11;
  char *pcVar12;
  char *pcVar13;
  float *extraout_r3;
  float fVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  int iVar18;
  cRTextures *this_00;
  int iVar19;
  int iVar20;
  float fVar21;
  float fVar22;
  char acStack_82c [2048];
  float *local_2c [2];

  iVar18 = DAT_0002f44c;
  uVar10 = *(uint *)this;
  pfVar1 = (float *)RShellMemoryScratch();
  iVar18 = iVar18 + 0x2eb1c;
  RShellLoadFile(param_1,pfVar1,(int *)0x0);
  sprintf((char *)(this + 0x20),param_1);
  pcVar11 = (char *)(iVar18 + DAT_0002f450);
  pcVar12 = (char *)(iVar18 + DAT_0002f454);
  pcVar13 = (char *)(iVar18 + DAT_0002f458);
  local_2c[0] = pfVar1;
  do {
    fVar14 = *local_2c[0];
    pfVar1 = local_2c[0] + 2;
    switch(fVar14) {
    case 0.0:
      fVar14 = local_2c[0][2];
      *(uint *)this = (uint)fVar14 | 0x2000000;
      fVar21 = local_2c[0][3];
      if ((uVar10 & 0x1000) != 0) {
        *(uint *)this = (uint)fVar14 | 0x2001000;
      }
      *(float *)(this + 0xa0) = fVar21;
      local_2c[0] = local_2c[0] + 4;
      break;
    case 1.4013e-45:
      if ((*(uint *)this & 0x1000) == 0) {
        local_2c[0] = pfVar1;
        uVar3 = RShellMemoryMalloc(*(int *)(this + 0xa0) * 0xc,(char *)(iVar18 + DAT_0002f484));
        *(undefined4 *)(this + 0xa4) = uVar3;
      }
      else {
        local_2c[0] = pfVar1;
        uVar3 = RShellMemoryMalloc(*(int *)(this + 0xa0) * 6,(char *)(iVar18 + DAT_0002f484));
        *(undefined4 *)(this + 0xa4) = uVar3;
      }
      if (0 < *(int *)(this + 0xa0)) {
        iVar2 = 0;
        iVar9 = 0;
        do {
          iVar15 = iVar2 * 2;
          if ((*(uint *)this & 0x1000) == 0) {
            SmoGetFixed(this,local_2c,(float *)(*(int *)(this + 0xa4) + iVar15));
            SmoGetFixed(this,local_2c,(float *)(*(int *)(this + 0xa4) + iVar15 + 4));
            SmoGetFixed(this,local_2c,(float *)(*(int *)(this + 0xa4) + iVar15 + 8));
          }
          else {
            SmoGetFixedShort(this,local_2c,(short *)(*(int *)(this + 0xa4) + iVar2));
            SmoGetFixedShort(this,local_2c,(short *)(*(int *)(this + 0xa4) + iVar2 + 2));
            SmoGetFixedShort(this,local_2c,(short *)(*(int *)(this + 0xa4) + iVar2 + 4));
          }
          iVar9 = iVar9 + 1;
          iVar2 = iVar2 + 6;
        } while (iVar9 < *(int *)(this + 0xa0));
      }
      break;
    case 2.8026e-45:
      pfVar1 = local_2c[0] + 2;
      local_2c[0] = local_2c[0] + 3;
      RequestFaceQuads(this,(int)*pfVar1);
      if (0 < *(int *)(this + 0xc0)) {
        iVar2 = 0;
        iVar9 = 0;
        this_00 = *(cRTextures **)(iVar18 + DAT_0002f470);
        pfVar1 = local_2c[0];
        do {
          fVar14 = pfVar1[1];
          iVar19 = *(int *)(this + 200);
          local_2c[0] = pfVar1 + 2;
          *(undefined2 *)(iVar19 + iVar2) = SUB42(*pfVar1,0);
          iVar9 = iVar9 + 1;
          uVar3 = cRTextures::Add(this_00,acStack_82c + (int)fVar14 * 0x40,(cTgaHeader *)0x0,0);
          iVar15 = *(int *)(this + 200);
          *(undefined4 *)((undefined2 *)(iVar19 + iVar2) + 6) = uVar3;
          SmoGetFixed(this,local_2c,(float *)(iVar15 + iVar2 + 0x10));
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
          iVar15 = *(int *)(this + 200) + iVar2;
          iVar2 = iVar2 + 0x30;
          *(undefined2 *)(iVar15 + 8) = *(undefined2 *)((int)local_2c[0] + 6);
          local_2c[0] = pfVar1;
        } while (iVar9 < *(int *)(this + 0xc0));
      }
      break;
    case 4.2039e-45:
      fVar14 = local_2c[0][2];
      pfVar1 = local_2c[0] + 3;
      if (0 < (int)fVar14) {
        iVar2 = 0;
        local_2c[0] = pfVar1;
        do {
          Rstrcpy(acStack_82c + iVar2 * 0x40,(char *)pfVar1);
          sVar5 = strlen((char *)pfVar1);
          iVar2 = iVar2 + 1;
          pfVar1 = (float *)((int)pfVar1 + sVar5 + 1);
        } while (iVar2 < (int)fVar14);
      }
      local_2c[0] = (float *)((int)pfVar1 + (4U - (int)pfVar1 & 3));
      break;
    case 5.60519e-45:
      local_2c[0] = pfVar1;
      RequestVerticesCopy(this);
      puVar7 = (undefined2 *)RShellMemoryMalloc(0x18,(char *)(iVar18 + DAT_0002f488));
      fVar14 = local_2c[0][1];
      pcVar6 = (char *)(iVar18 + DAT_0002f48c);
      fVar21 = *local_2c[0];
      *(undefined2 **)(this + 0x104) = puVar7;
      fVar22 = local_2c[0][3];
      *(float *)(puVar7 + 2) = fVar14;
      fVar14 = local_2c[0][2];
      *(float *)(puVar7 + 8) = fVar22;
      fVar22 = local_2c[0][4];
      *puVar7 = SUB42(fVar21,0);
      *(float *)(puVar7 + 10) = fVar22;
      *(float *)(puVar7 + 4) = fVar14;
      pfVar1 = local_2c[0] + 5;
      local_2c[0] = local_2c[0] + 6;
      *(float *)(this + 0xd0) = *pfVar1;
      uVar3 = RShellMemoryMalloc(*(int *)(puVar7 + 2) << 2,pcVar6);
      iVar15 = *(int *)(this + 0x104);
      iVar9 = *(int *)(iVar15 + 4);
      *(undefined4 *)(puVar7 + 6) = uVar3;
      iVar2 = DAT_0002f490;
      if (0 < iVar9) {
        iVar9 = 0;
        do {
          iVar19 = *(int *)(iVar15 + 0xc);
          uVar3 = RShellMemoryMalloc(0xc,pcVar11);
          uVar8 = *(uint *)this;
          *(undefined4 *)(iVar19 + iVar9 * 4) = uVar3;
          if ((uVar8 & 0x1000) == 0) {
            puVar4 = *(undefined4 **)(*(int *)(*(int *)(this + 0x104) + 0xc) + iVar9 * 4);
            uVar3 = RShellMemoryMalloc(*(int *)(this + 0xa0) * 0xc,pcVar12);
            *puVar4 = uVar3;
            SmoGetFixedArray(this,local_2c,
                             (float *)**(undefined4 **)
                                        (*(int *)(*(int *)(this + 0x104) + 0xc) + iVar9 * 4),
                             *(int *)(this + 0xa0) * 3);
          }
          else {
            puVar4 = *(undefined4 **)(*(int *)(*(int *)(this + 0x104) + 0xc) + iVar9 * 4);
            uVar3 = RShellMemoryMalloc(*(int *)(this + 0xa0) * 6,pcVar12);
            *puVar4 = uVar3;
            SmoGetFixedShortArray
                      (this,local_2c,
                       (short *)**(undefined4 **)
                                  (*(int *)(*(int *)(this + 0x104) + 0xc) + iVar9 * 4),
                       *(int *)(this + 0xa0) * 3);
          }
          iVar20 = *(int *)(*(int *)(*(int *)(this + 0x104) + 0xc) + iVar9 * 4);
          uVar3 = RShellMemoryMalloc(*(int *)(this + 0xd0) << 2,pcVar13);
          iVar19 = *(int *)(this + 0xd0);
          if (iVar19 < 1) {
            iVar15 = *(int *)(this + 0x104);
          }
          *(undefined4 *)(iVar20 + 8) = uVar3;
          if (0 < iVar19) {
            iVar15 = *(int *)(this + 0x104);
            iVar20 = 0;
            iVar17 = *(int *)(iVar18 + iVar2);
            iVar16 = *(int *)(*(int *)(*(int *)(iVar15 + 0xc) + iVar9 * 4) + 8);
            pfVar1 = local_2c[0];
            do {
              local_2c[0] = pfVar1 + 1;
              *(int *)(iVar16 + iVar20 * 4) = *(int *)(iVar17 + 0x10) + (int)*pfVar1 * 0xc;
              iVar20 = iVar20 + 1;
              pfVar1 = local_2c[0];
            } while (iVar20 < iVar19);
          }
          iVar9 = iVar9 + 1;
        } while (iVar9 < *(int *)(iVar15 + 4));
      }
      break;
    case 7.00649e-45:
      local_2c[0] = pfVar1;
      puVar4 = (undefined4 *)RShellMemoryMalloc(0x5c,(char *)(iVar18 + DAT_0002f46c));
      iVar2 = DAT_0002f470;
      *(undefined4 **)(this + 0x10c) = puVar4;
      uVar3 = cRTextures::Add(*(cRTextures **)(iVar18 + iVar2),acStack_82c,(cTgaHeader *)0x0,0);
      iVar2 = *(int *)(this + 0x10c);
      fVar14 = *local_2c[0];
      *(float *)(iVar2 + 4) = fVar14;
      uVar8 = *(uint *)this;
      *puVar4 = uVar3;
      if ((uVar8 & 0x1000) == 0) {
        local_2c[0] = local_2c[0] + 1;
        uVar3 = RShellMemoryMalloc((int)fVar14 * 0x14,(char *)(iVar18 + DAT_0002f474));
        *(undefined4 *)(iVar2 + 8) = uVar3;
        if ((*(uint *)this & 0x1000) == 0) goto LAB_0002f404;
LAB_0002ed74:
        SmoGetFixedShortArray
                  (this,local_2c,*(short **)(*(int *)(this + 0x10c) + 8),
                   *(int *)(*(int *)(this + 0x10c) + 4) * 5);
      }
      else {
        local_2c[0] = local_2c[0] + 1;
        uVar3 = RShellMemoryMalloc((int)fVar14 * 10,(char *)(iVar18 + DAT_0002f474));
        *(undefined4 *)(iVar2 + 8) = uVar3;
        if ((*(uint *)this & 0x1000) != 0) goto LAB_0002ed74;
LAB_0002f404:
        SmoGetFixedArray(this,local_2c,*(float **)(*(int *)(this + 0x10c) + 8),
                         *(int *)(*(int *)(this + 0x10c) + 4) * 5);
      }
      iVar2 = *(int *)(this + 0x10c);
      fVar14 = *local_2c[0];
      pcVar6 = (char *)(iVar18 + DAT_0002f478);
      *(float *)(iVar2 + 0xc) = fVar14;
      local_2c[0] = local_2c[0] + 1;
      uVar3 = RShellMemoryMalloc((int)fVar14 << 3,pcVar6);
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
      iVar15 = *(int *)(this + 0x10c);
      fVar14 = *local_2c[0];
      pcVar6 = (char *)(iVar18 + DAT_0002f47c);
      *(float *)(iVar15 + 0x14) = fVar14;
      local_2c[0] = local_2c[0] + 1;
      uVar3 = RShellMemoryMalloc((int)fVar14 << 1,pcVar6);
      iVar9 = *(int *)(this + 0x10c);
      iVar2 = *(int *)(iVar9 + 0x14);
      pfVar1 = extraout_r3;
      if (iVar2 < 1) {
        pfVar1 = local_2c[0];
      }
      *(undefined4 *)(iVar15 + 0x18) = uVar3;
      if (0 < iVar2) {
        iVar15 = 0;
        iVar19 = *(int *)(iVar9 + 0x18);
        do {
          iVar20 = iVar15 * 2;
          pfVar1 = local_2c[0] + 1;
          iVar15 = iVar15 + 1;
          *(undefined2 *)(iVar19 + iVar20) = *(undefined2 *)local_2c[0];
          local_2c[0] = pfVar1;
        } while (iVar15 < iVar2);
      }
      iVar2 = DAT_0002f480;
      local_2c[0] = pfVar1 + 1;
      fVar14 = *pfVar1;
      *(float *)(iVar9 + 0x44) = fVar14;
      uVar3 = RShellMemoryMalloc((int)fVar14 << 1,(char *)(iVar18 + iVar2));
      iVar2 = *(int *)(this + 0x10c);
      iVar15 = *(int *)(iVar2 + 0x44);
      *(undefined4 *)(iVar9 + 0x48) = uVar3;
      if (0 < iVar15) {
        iVar9 = *(int *)(iVar2 + 0x48);
        iVar2 = 0;
        do {
          iVar19 = iVar2 * 2;
          pfVar1 = local_2c[0] + 1;
          iVar2 = iVar2 + 1;
          *(undefined2 *)(iVar9 + iVar19) = *(undefined2 *)local_2c[0];
          local_2c[0] = pfVar1;
        } while (iVar2 < iVar15);
      }
      break;
    case 8.40779e-45:
      fVar14 = local_2c[0][2];
      local_2c[0] = local_2c[0] + 3;
      pcVar6 = (char *)(iVar18 + DAT_0002f464);
      *(float *)(this + 0xe4) = fVar14;
      uVar3 = RShellMemoryMalloc((int)fVar14 * 10,pcVar6);
      pcVar6 = (char *)(iVar18 + DAT_0002f468);
      *(undefined4 *)(this + 0xe8) = uVar3;
      uVar3 = RShellMemoryMalloc(*(int *)(this + 0xe4) << 2,pcVar6);
      iVar2 = *(int *)(this + 0xe4);
      *(undefined4 *)(this + 0xe0) = uVar3;
      if (0 < iVar2) {
        iVar19 = *(int *)(this + 0xe8);
        iVar15 = 0;
        iVar20 = 0;
        iVar9 = iVar19;
        do {
          iVar20 = iVar20 + 1;
          puVar7 = (undefined2 *)(iVar19 + iVar15);
          *puVar7 = *(undefined2 *)local_2c[0];
          iVar15 = iVar15 + 10;
          puVar7[3] = *(undefined2 *)(local_2c[0] + 1);
          *(undefined2 *)(iVar9 + 8) = *(undefined2 *)(local_2c[0] + 2);
          iVar9 = iVar9 + 10;
          puVar7[1] = *(undefined2 *)(local_2c[0] + 3);
          pfVar1 = local_2c[0] + 4;
          local_2c[0] = local_2c[0] + 5;
          puVar7[2] = *(undefined2 *)pfVar1;
        } while (iVar20 < iVar2);
      }
      break;
    case 9.80909e-45:
      local_2c[0] = pfVar1;
      iVar2 = RShellMemoryMalloc(*(int *)(this + 0xa0) << 4,(char *)(iVar18 + DAT_0002f460));
      *(int *)(this + 0xb4) = iVar2;
      if (0 < *(int *)(this + 0xa0)) {
        iVar9 = 0;
        do {
          *(float *)(iVar2 + iVar9 * 0x10) = *local_2c[0];
          iVar15 = iVar9 * 0x10;
          iVar9 = iVar9 + 1;
          *(float *)(*(int *)(this + 0xb4) + iVar15 + 4) = local_2c[0][1];
          *(float *)(*(int *)(this + 0xb4) + iVar15 + 8) = local_2c[0][2];
          iVar19 = *(int *)(this + 0xa0);
          pfVar1 = local_2c[0] + 3;
          iVar2 = *(int *)(this + 0xb4);
          local_2c[0] = local_2c[0] + 4;
          *(float *)(iVar2 + iVar15 + 0xc) = *pfVar1;
        } while (iVar9 < iVar19);
      }
      break;
    case 1.12104e-44:
      return;
    default:
      local_2c[0] = pfVar1;
      wprintf((char *)(iVar18 + DAT_0002f45c),fVar14);
      if (fVar14 == 1.12104e-44) {
        return;
      }
    }
  } while( true );
}
