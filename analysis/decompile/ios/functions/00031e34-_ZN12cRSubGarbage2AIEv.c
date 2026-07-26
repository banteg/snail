/*
 * mangled: _ZN12cRSubGarbage2AIEv
 * demangled: cRSubGarbage::AI()
 * address: 00031e34
 * size: 1500
 */

/* cRSubGarbage::AI() */

void __thiscall cRSubGarbage::AI(cRSubGarbage *this)

{
  cRSubGarbage *pcVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  cRSubGarbage *pcVar6;
  int iVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  undefined4 local_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;

  if (*(char *)(*(int *)(this + 0x80) + 0x12) != '\0') {
    return;
  }
  switch(*(undefined4 *)(this + 0x78)) {
  case 0:
    goto switchD_00031e64_caseD_0;
  case 1:
    iVar3 = *(int *)(this + 0xa8);
    uVar2 = *(undefined4 *)(this + 0x60);
    uVar4 = *(undefined4 *)(this + 100);
    *(undefined4 *)(iVar3 + 0x48) = *(undefined4 *)(this + 0x5c);
    *(undefined4 *)(iVar3 + 0x4c) = uVar2;
    *(undefined4 *)(iVar3 + 0x50) = uVar4;
    iVar3 = *(int *)(this + 0xb4);
    if (*(float *)(&DAT_000027f4 + iVar3) <= *(float *)(this + 100)) {
      if (0.0 < *(float *)(iVar3 + 0x364)) {
        *(undefined4 *)(this + 0x78) = 2;
        if (0.0 < *(float *)(this + 0x5c)) {
          *(undefined4 *)(this + 0x7c) = 1;
        }
        else {
          *(undefined4 *)(this + 0x7c) = 2;
        }
        *(int *)(iVar3 + 0x2f8) = *(int *)(iVar3 + 0x2f8) + 10;
        iVar7 = *(int *)(iVar3 + 0x2cc);
        iVar5 = iVar7 + 10;
        *(int *)(iVar3 + 0x2cc) = iVar5;
        if ((iVar7 / 50000 != iVar5 / 50000) &&
           (*(int *)(::__static_initialization_and_destruction_0 + iVar3 + 4) < 9)) {
          *(int *)(::__static_initialization_and_destruction_0 + iVar3 + 4) =
               *(int *)(::__static_initialization_and_destruction_0 + iVar3 + 4) + 1;
          if ((*(int *)(*(int *)PTR__Game_001b60b8 + 0x72bd0) == 0) &&
             (*(int *)(*(int *)PTR__Game_001b60b8 + 0x24) == 0)) {
            cRSound::Play((cRSound *)PTR__gRSound_001b61e0,0x2d);
          }
        }
      }
      cREnemyManager::Register
                ((cREnemyManager *)(&DAT_00303ab4 + *(int *)(this + 0x80)),(tVector *)(this + 0x5c),
                 *(float *)(this + 0x90),0,(cRBodPos *)this);
      iVar3 = *(int *)(this + 0xb4);
      goto LAB_00031e80;
    }
    *(undefined4 *)(this + 0x78) = 0;
    iVar3 = *(int *)PTR__Game_001b60b8;
    if ((*(uint *)(this + 4) & 0x200) == 0) {
      RShellError("List remove");
    }
    else if ((*(uint *)(this + 4) & 0x40) == 0) {
      iVar5 = *(int *)(this + 0xc);
      if (iVar5 != 0) {
        *(undefined4 *)(iVar5 + 8) = *(undefined4 *)(this + 8);
      }
      if (*(int *)(this + 8) == 0) {
        *(int *)(iVar3 + 0x35c) = iVar5;
      }
      else {
        *(int *)(*(int *)(this + 8) + 0xc) = iVar5;
      }
      *(undefined4 *)(this + 0xc) = *(undefined4 *)(iVar3 + 0x360);
      *(cRSubGarbage **)(iVar3 + 0x360) = this;
      *(uint *)(this + 4) = *(uint *)(this + 4) & 0xfffffdff;
    }
    else {
      RShellError("List remove NEXTBOD");
    }
    cRSprite::Kill(*(cRSprite **)(this + 0xa8));
    iVar3 = *(int *)(this + 0x80);
    pcVar6 = *(cRSubGarbage **)(iVar3 + 0x5e88);
    if (this == pcVar6) goto LAB_00032440;
    if (pcVar6 == (cRSubGarbage *)0x0) {
      return;
    }
    for (pcVar1 = *(cRSubGarbage **)(pcVar6 + 0x74); this != pcVar1;
        pcVar1 = *(cRSubGarbage **)(pcVar1 + 0x74)) {
      if (pcVar1 == (cRSubGarbage *)0x0) {
        return;
      }
      pcVar6 = pcVar1;
    }
    goto LAB_00032200;
  case 2:
    fVar12 = 0.1;
    *(undefined4 *)(this + 0x78) = 3;
    fVar8 = (float)SRAND(0.1,"GDI");
    fVar11 = (float)RAND(0.2,(char *)0x0);
    fVar9 = (float)RAND(0.3,(char *)0x0);
    iVar3 = *(int *)(this + 0x80);
    iVar5 = *(int *)(this + 0x7c);
    fVar10 = *(float *)(iVar3 + 0x4c);
    fVar8 = fVar8 * fVar10;
    *(float *)(this + 0x84) = fVar8;
    if (iVar5 == 1) {
      fVar8 = ABS(fVar8);
      *(float *)(this + 0x84) = fVar8;
    }
    *(float *)(this + 0x8c) = fVar9 * fVar10;
    *(float *)(this + 0x88) = (fVar11 + fVar12) * fVar10;
    if ((iVar5 != 1) && (iVar5 == 2)) {
      *(float *)(this + 0x84) = -ABS(fVar8);
    }
    fVar8 = *(float *)(this + 0x84);
    if (fVar8 < 0.0) {
      fVar11 = -0.2;
    }
    else if (fVar8 == 0.0) {
      fVar11 = 0.0;
    }
    else {
      fVar11 = 0.2;
    }
    fVar9 = *(float *)(iVar3 + 0x4c);
    *(undefined4 *)(this + 0x98) = 0;
    *(float *)(this + 0x84) = fVar8 + fVar11 * fVar9;
    fVar8 = *(float *)(iVar3 + 0x4c);
    *(undefined4 *)(this + 0xa0) = 0;
    *(float *)(this + 0x9c) = fVar8 * 0.008333334;
    *(float *)(this + 0xa4) = *(float *)(iVar3 + 0x4c) * 0.2777778;
switchD_00031e64_caseD_3:
    iVar3 = *(int *)(this + 0xa8);
    *(float *)(this + 0x5c) = *(float *)(this + 0x5c) + *(float *)(this + 0x84);
    *(float *)(this + 0x60) = *(float *)(this + 0x60) + *(float *)(this + 0x88);
    *(float *)(this + 100) = *(float *)(this + 100) + *(float *)(this + 0x8c);
    uVar2 = *(undefined4 *)(this + 0x60);
    uVar4 = *(undefined4 *)(this + 100);
    *(undefined4 *)(iVar3 + 0x48) = *(undefined4 *)(this + 0x5c);
    *(undefined4 *)(iVar3 + 0x4c) = uVar2;
    *(undefined4 *)(iVar3 + 0x50) = uVar4;
    *(float *)(this + 0x88) =
         *(float *)(this + 0x88) +
         *(float *)(*(int *)(this + 0x80) + 0x4c) * *(float *)(*(int *)(this + 0x80) + 0x4c) * -0.01
    ;
    if ((*(float *)(this + 0x60) < -10.0) ||
       (iVar3 = *(int *)(this + 0xb4), *(float *)(this + 100) < *(float *)(&DAT_000027f4 + iVar3)))
    {
      *(undefined4 *)(this + 0x78) = 0;
      iVar3 = *(int *)PTR__Game_001b60b8;
      if ((*(uint *)(this + 4) & 0x200) == 0) {
        RShellError("List remove");
      }
      else if ((*(uint *)(this + 4) & 0x40) == 0) {
        iVar5 = *(int *)(this + 0xc);
        if (iVar5 != 0) {
          *(undefined4 *)(iVar5 + 8) = *(undefined4 *)(this + 8);
        }
        if (*(int *)(this + 8) == 0) {
          *(int *)(iVar3 + 0x35c) = iVar5;
        }
        else {
          *(int *)(*(int *)(this + 8) + 0xc) = iVar5;
        }
        *(undefined4 *)(this + 0xc) = *(undefined4 *)(iVar3 + 0x360);
        *(cRSubGarbage **)(iVar3 + 0x360) = this;
        *(uint *)(this + 4) = *(uint *)(this + 4) & 0xfffffdff;
      }
      else {
        RShellError("List remove NEXTBOD");
      }
      cRSprite::Kill(*(cRSprite **)(this + 0xa8));
      iVar3 = *(int *)(this + 0x80);
      pcVar6 = *(cRSubGarbage **)(iVar3 + 0x5e88);
      if (this == pcVar6) {
LAB_00032440:
        *(undefined4 *)(iVar3 + 0x5e88) = *(undefined4 *)(this + 0x74);
      }
      else if (pcVar6 != (cRSubGarbage *)0x0) {
        for (pcVar1 = *(cRSubGarbage **)(pcVar6 + 0x74); this != pcVar1;
            pcVar1 = *(cRSubGarbage **)(pcVar1 + 0x74)) {
          if (pcVar1 == (cRSubGarbage *)0x0) {
            return;
          }
          pcVar6 = pcVar1;
        }
LAB_00032200:
        *(undefined4 *)(pcVar6 + 0x74) = *(undefined4 *)(this + 0x74);
        *(undefined4 *)(this + 0x74) = 0;
      }
    }
    else {
      fVar8 = *(float *)(this + 0xa0);
      fVar11 = 1.0;
      *(float *)(this + 0xa0) = fVar8 + *(float *)(this + 0xa4);
      if ((1.0 < fVar8 + *(float *)(this + 0xa4)) &&
         (*(undefined4 *)(this + 0xa0) = 0, (*(uint *)(*(int *)PTR__Game_001b60b8 + 0x2d8) & 3) == 0
         )) {
        iVar3 = cRSpriteManager::New
                          ((int)PTR__gRSpriteManager_001b61e4,*(int *)(iVar3 + 0x370),0x13,-1);
        *(undefined4 *)(iVar3 + 0x68) = 0;
        *(uint *)(iVar3 + 4) = *(uint *)(iVar3 + 4) | 0x800;
        fVar8 = *(float *)(*(int *)(this + 0x80) + 0x4c);
        *(undefined4 *)(iVar3 + 0x70) = 0;
        *(float *)(iVar3 + 0x6c) = fVar8 * 0.033333335;
        *(float *)(iVar3 + 0x74) = *(float *)(*(int *)(this + 0x80) + 0x4c) * 0.4166667;
        tColour::tColour((tColour *)&local_3c,fVar11,fVar11,fVar11,fVar11);
        *(undefined4 *)(iVar3 + 0x2c) = local_3c;
        *(undefined4 *)(iVar3 + 0x30) = uStack_38;
        *(undefined4 *)(iVar3 + 0x34) = uStack_34;
        *(undefined4 *)(iVar3 + 0x38) = uStack_30;
        *(undefined4 *)(iVar3 + 0x60) = 0x3e99999a;
        *(undefined4 *)(iVar3 + 100) = 0x3fa66666;
        fVar8 = *(float *)(this + 0x84);
        fVar11 = *(float *)(this + 0x88);
        fVar9 = *(float *)(this + 0x8c);
        *(undefined4 *)(iVar3 + 0x78) = 0;
        *(float *)(iVar3 + 0x54) = fVar8 * 0.2;
        *(float *)(iVar3 + 0x58) = fVar11 * 0.2;
        *(float *)(iVar3 + 0x5c) = fVar9 * 0.2;
        uVar2 = *(undefined4 *)(this + 0x60);
        uVar4 = *(undefined4 *)(this + 100);
        *(undefined4 *)(iVar3 + 0x48) = *(undefined4 *)(this + 0x5c);
        *(undefined4 *)(iVar3 + 0x4c) = uVar2;
        *(undefined4 *)(iVar3 + 0x50) = uVar4;
        iVar3 = *(int *)(this + 0xb4);
      }
LAB_00031e80:
      *(float *)(*(int *)(this + 0xa8) + 0x7c) = *(float *)(iVar3 + 0x360) + *(float *)(this + 0x94)
      ;
      iVar3 = *(int *)(this + 0xb4);
      if (*(char *)(iVar3 + 0x374) != '\0') {
        *(float *)(*(int *)(this + 0xa8) + 0x7c) =
             *(float *)(*(int *)(this + 0xa8) + 0x7c) +
             *(float *)(iVar3 + 0x390) + *(float *)(iVar3 + 0x38c);
      }
    }
switchD_00031e64_caseD_0:
    return;
  case 3:
    goto switchD_00031e64_caseD_3;
  default:
    iVar3 = *(int *)(this + 0xb4);
    goto LAB_00031e80;
  }
}
