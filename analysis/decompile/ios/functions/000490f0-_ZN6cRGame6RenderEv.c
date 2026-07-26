/*
 * mangled: _ZN6cRGame6RenderEv
 * demangled: cRGame::Render()
 * address: 000490f0
 * size: 1896
 */

/* cRGame::Render() */

void __thiscall cRGame::Render(cRGame *this)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  uint uVar4;
  cRObject *pcVar5;
  undefined4 *puVar6;
  float fVar7;
  cRSprite *this_00;
  int iVar8;
  cRBod *pcVar9;
  int *piVar10;
  int iVar11;
  undefined4 *puVar12;
  undefined *puVar13;
  int iVar14;
  float fVar15;
  int iVar16;
  cRGame *pcVar17;
  bool bVar18;
  uint local_8c;
  uint local_88;
  int local_84;
  tMatrix atStack_78 [48];
  undefined4 local_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  float local_38;
  undefined4 uStack_34;
  float local_30;
  int local_2c [3];

  if (*(int *)(this + 0x328) < 1) {
    iVar11 = 0;
    iVar8 = 0;
    *PTR__G0SwapBufferRequest_001b60e4 = 1;
    G0RenderStart();
    cRBackdrop::Render((cRBackdrop *)(this + 0x4d2e0));
    tMatrix::Identity(atStack_78);
    local_8c = *(uint *)(this + 0x36c) & 1;
    if ((*(uint *)(this + 0x39c) & 1) != 0) {
      local_8c = local_8c + 1;
    }
    local_2c[0] = -1;
    local_2c[1] = 0xffffffff;
    bVar18 = (*(uint *)(this + 0x3cc) & 1) != 0;
    local_2c[2] = 0xffffffff;
    uVar4 = 0xffffffff;
    if (bVar18) {
      uVar4 = local_8c;
    }
    if (bVar18) {
      uVar4 = uVar4 + 1;
    }
    if (bVar18) {
      local_8c = uVar4;
    }
    *(uint *)(this + 0x39c) = *(uint *)(this + 0x39c) & 0xffffff | 0x2000000;
    puVar13 = PTR__Game_001b60b8;
    pcVar17 = this;
    do {
      if ((*(uint *)(pcVar17 + 0x36c) & 1) != 0) {
        if (iVar8 == 0) {
          local_2c[0] = iVar11;
          iVar8 = 1;
        }
        else if (0 < iVar8) {
          iVar14 = *(int *)(pcVar17 + 0x368);
          iVar16 = 0;
          do {
            if (*(int *)(this + local_2c[iVar16] * 0x30 + 0x368) < iVar14) {
              if (iVar16 < 2) {
                piVar10 = local_2c;
                iVar2 = 1;
                do {
                  iVar2 = iVar2 + -1;
                  piVar10[2] = piVar10[1];
                  piVar10 = piVar10 + -1;
                } while (iVar2 != iVar16 + -1);
              }
              iVar8 = iVar8 + 1;
              local_2c[iVar16] = iVar11;
              iVar16 = iVar8;
            }
            iVar16 = iVar16 + 1;
          } while (iVar16 < iVar8);
        }
      }
      iVar11 = iVar11 + 1;
      pcVar17 = pcVar17 + 0x30;
    } while (iVar11 != 3);
    *(float *)(this + 0x3bc) =
         *(float *)(*(int *)PTR__Game_001b60b8 + 0x3c) -
         *(float *)(*(int *)PTR__Game_001b60b8 + 0x48);
    *(undefined4 *)(this + 0x3c0) = *(undefined4 *)(*(int *)puVar13 + 0x4c);
    if (0 < (int)local_8c) {
      local_88 = 0;
      local_84 = 0;
      do {
        iVar8 = local_2c[local_88];
        uVar4 = *(uint *)(this + iVar8 * 0x30 + 0x36c);
        if ((uVar4 & 1) != 0) {
          if (((uVar4 & 2) == 0) || ((uVar4 & 4) == 0)) {
            iVar11 = *(int *)(this + iVar8 * 0x30 + 900);
            if ((uVar4 & 0x10) != 0) {
              *(undefined4 *)(this + iVar8 * 0x30 + 0x374) = 0;
              *(undefined4 *)(this + iVar8 * 0x30 + 0x37c) = 0x3f000000;
            }
            G0RenderCamera(*(float *)(this + iVar8 * 0x30 + 0x370),
                           *(float *)(this + iVar8 * 0x30 + 0x374),
                           *(float *)(this + iVar8 * 0x30 + 0x378),
                           *(float *)(this + iVar8 * 0x30 + 0x37c),*(float *)(iVar11 + 0xb4),
                           (tMatrix *)(iVar11 + 0x2c),(tMatrix *)(iVar11 + 0x74),
                           (bool)this[iVar8 * 0x30 + 0x388],false,
                           *(float *)(this + iVar8 * 0x30 + 0x38c),
                           *(float *)(this + iVar8 * 0x30 + 0x390));
            uVar4 = *(uint *)(this + iVar8 * 0x30 + 0x36c);
            if ((uVar4 & 2) == 0) {
              pcVar9 = *(cRBod **)(this + 0x35c);
              if (pcVar9 == (cRBod *)0x0) {
                local_84 = 0;
              }
              else {
                local_84 = 0;
                do {
                  while( true ) {
                    if ((*(uint *)(pcVar9 + 4) & 0x10) == 0) {
                      uVar4 = *(uint *)(pcVar9 + 4);
                    }
                    else {
                      wprintf("DEBUG RENDER\n");
                      uVar4 = *(uint *)(pcVar9 + 4);
                    }
                    if (((uVar4 & 0x22) == 0x22) &&
                       ((uVar4 & *(uint *)(this + iVar8 * 0x30 + 0x36c) & 0xff000000) != 0)) break;
LAB_00049354:
                    pcVar9 = *(cRBod **)(pcVar9 + 0xc);
                    if (pcVar9 == (cRBod *)0x0) goto LAB_0004942c;
                  }
                  if ((uVar4 & 0x80) != 0) {
                    *(cRBod **)(&_gBodZList + local_84 * 4) = pcVar9;
                    local_84 = local_84 + 1;
                    uVar4 = *(uint *)(pcVar9 + 4);
                  }
                  if ((uVar4 & 0x800) != 0) {
                    *(undefined4 *)(*(int *)(*(int *)(pcVar9 + 0x24) + 0x104) + 0x10) =
                         *(undefined4 *)(*(int *)(pcVar9 + 0x6c) + 4);
                    uVar4 = *(uint *)(pcVar9 + 4);
                  }
                  if ((uVar4 & 0x400) == 0) {
                    local_48 = *(undefined4 *)(pcVar9 + 0x10);
                    uStack_44 = *(undefined4 *)(pcVar9 + 0x14);
                    uStack_40 = *(undefined4 *)(pcVar9 + 0x18);
                    fVar7 = *(float *)(pcVar9 + 0x1c);
                    pcVar5 = *(cRObject **)(pcVar9 + 0x24);
                    fVar15 = *(float *)(pcVar9 + 0x20);
                    bVar18 = (bool)cRBod::IsAfterSprites(pcVar9);
                    G0RenderObject(pcVar5,atStack_78,fVar7,fVar15,(tColourSmall *)(pcVar9 + 0x28),
                                   bVar18);
                    goto LAB_00049354;
                  }
                  pcVar5 = *(cRObject **)(pcVar9 + 0x24);
                  fVar7 = *(float *)(pcVar9 + 0x1c);
                  fVar15 = *(float *)(pcVar9 + 0x20);
                  bVar18 = (bool)cRBod::IsAfterSprites(pcVar9);
                  G0RenderObject(pcVar5,(tMatrix *)(pcVar9 + 0x2c),fVar7,fVar15,
                                 (tColourSmall *)(pcVar9 + 0x28),bVar18);
                  pcVar9 = *(cRBod **)(pcVar9 + 0xc);
                } while (pcVar9 != (cRBod *)0x0);
LAB_0004942c:
                uVar4 = *(uint *)(this + iVar8 * 0x30 + 0x36c);
              }
            }
            if ((uVar4 & 4) == 0) {
              iVar11 = *(int *)(PTR__gRSpriteManager_001b61e4 + iVar8 * 4 + 0x2af84);
              G0RenderSprite3DStart();
              if (iVar11 != 0) {
                puVar12 = &_ZBuffer;
                do {
                  while (uVar4 = *(uint *)(iVar11 + 4),
                        (uVar4 & *(uint *)(this + iVar8 * 0x30 + 0x36c) & 0xff000000) == 0) {
                    RShellError("Loose Sprite scene viewport");
                    iVar11 = *(int *)(iVar11 + 0xc);
                    if (iVar11 == 0) goto LAB_000494c4;
                  }
                  if (((uVar4 & 1) != 0) && ((uVar4 & 0x240) == 0x40)) {
                    local_38 = *(float *)(iVar11 + 0x48);
                    uStack_34 = *(undefined4 *)(iVar11 + 0x4c);
                    local_30 = *(float *)(iVar11 + 0x50);
                    iVar16 = *(int *)(this + iVar8 * 0x30 + 900);
                    tVector::operator*=((tVector *)&local_38,*(undefined4 *)(iVar16 + 0x74),
                                        *(undefined4 *)(iVar16 + 0x78),
                                        *(undefined4 *)(iVar16 + 0x7c),
                                        *(undefined4 *)(iVar16 + 0x80),
                                        *(undefined4 *)(iVar16 + 0x84),
                                        *(undefined4 *)(iVar16 + 0x88),
                                        *(undefined4 *)(iVar16 + 0x8c),
                                        *(undefined4 *)(iVar16 + 0x90),
                                        *(undefined4 *)(iVar16 + 0x94),
                                        *(undefined4 *)(iVar16 + 0x98),
                                        *(undefined4 *)(iVar16 + 0x9c),
                                        *(undefined4 *)(iVar16 + 0xa0),
                                        *(undefined4 *)(iVar16 + 0xa4),
                                        *(undefined4 *)(iVar16 + 0xa8),
                                        *(undefined4 *)(iVar16 + 0xac),
                                        *(undefined4 *)(iVar16 + 0xb0));
                    local_38 = -local_38;
                    local_30 = -local_30;
                    fVar7 = (local_30 * -256.0) / 61.0 + *(float *)(iVar11 + 0x94);
                    iVar16 = (int)fVar7;
                    if (iVar16 < 0x100) {
                      if (iVar16 < 0) goto LAB_0004948c;
                    }
                    else {
                      iVar16 = 0xff;
                    }
                    if ((undefined4 *)(&_ZBufferIndex)[iVar16] == (undefined4 *)0x0) {
                      (&_ZBufferIndex)[iVar16] = puVar12;
                      *puVar12 = 0;
                    }
                    else {
                      puVar3 = (undefined4 *)0x0;
                      puVar1 = (undefined4 *)(&_ZBufferIndex)[iVar16];
                      do {
                        puVar6 = puVar1;
                        if ((float)puVar6[4] <= fVar7) {
                          if (puVar3 == (undefined4 *)0x0) {
                            *puVar12 = puVar6;
                            (&_ZBufferIndex)[iVar16] = puVar12;
                          }
                          else {
                            *puVar3 = puVar12;
                            *puVar12 = puVar6;
                          }
                          goto LAB_000497fc;
                        }
                        puVar3 = puVar6;
                        puVar1 = (undefined4 *)*puVar6;
                      } while ((undefined4 *)*puVar6 != (undefined4 *)0x0);
                      *puVar6 = puVar12;
                      *puVar12 = 0;
                    }
LAB_000497fc:
                    puVar12[5] = iVar11;
                    puVar12[4] = fVar7;
                    puVar12[1] = local_38;
                    puVar12[2] = uStack_34;
                    puVar12[3] = local_30;
                    *(float *)(iVar11 + 0x18) = fVar7;
                    *(int *)(iVar11 + 0x14) = iVar16;
                    puVar12 = puVar12 + 6;
                  }
LAB_0004948c:
                  iVar11 = *(int *)(iVar11 + 0xc);
                } while (iVar11 != 0);
              }
LAB_000494c4:
              puVar12 = &_ZBufferIndex;
              do {
                piVar10 = (int *)puVar12[0xff];
                if (piVar10 != (int *)0x0) {
                  do {
                    while (this_00 = (cRSprite *)piVar10[5], (*(uint *)(this_00 + 4) & 2) == 0) {
                      G0RenderSprite3D((tVector *)(piVar10 + 1),this_00);
                      piVar10 = (int *)*piVar10;
                      if (piVar10 == (int *)0x0) goto LAB_00049538;
                    }
                    cRSprite::BuildTail(this_00,(tMatrix *)
                                                (*(int *)(this + iVar8 * 0x30 + 900) + 0x74));
                    G0RenderSprite3D((tVector *)(piVar10 + 1),(cRSprite *)piVar10[5]);
                    piVar10 = (int *)*piVar10;
                  } while (piVar10 != (int *)0x0);
LAB_00049538:
                  puVar12[0xff] = 0;
                }
                puVar12 = puVar12 + -1;
              } while (puVar12 != (undefined4 *)0x4d1c6c);
              G0RenderSprite3DEnd();
              uVar4 = *(uint *)(this + iVar8 * 0x30 + 0x36c);
            }
          }
          if ((uVar4 & 8) == 0) {
            G0FontRenderStart();
            FontPrintRender(*(int *)(this + iVar8 * 0x30 + 0x36c));
            G0FontRenderEnd();
            uVar4 = *(uint *)(this + iVar8 * 0x30 + 0x36c);
          }
          if (((uVar4 & 2) == 0) && (local_84 != 0)) {
            iVar11 = *(int *)(this + iVar8 * 0x30 + 900);
            G0RenderCamera(*(float *)(this + iVar8 * 0x30 + 0x370),
                           *(float *)(this + iVar8 * 0x30 + 0x374),
                           *(float *)(this + iVar8 * 0x30 + 0x378),
                           *(float *)(this + iVar8 * 0x30 + 0x37c),*(float *)(iVar11 + 0xb4),
                           (tMatrix *)(iVar11 + 0x2c),(tMatrix *)(iVar11 + 0x74),
                           (bool)this[iVar8 * 0x30 + 0x388],true,
                           *(float *)(this + iVar8 * 0x30 + 0x38c),
                           *(float *)(this + iVar8 * 0x30 + 0x390));
            puVar13 = &_gBodZList + local_84 * 4;
            do {
              while( true ) {
                pcVar9 = *(cRBod **)(puVar13 + -4);
                local_84 = local_84 + -1;
                if ((*(uint *)(pcVar9 + 4) & 0x400) != 0) break;
                local_48 = *(undefined4 *)(pcVar9 + 0x10);
                uStack_44 = *(undefined4 *)(pcVar9 + 0x14);
                uStack_40 = *(undefined4 *)(pcVar9 + 0x18);
                puVar13 = puVar13 + -4;
                pcVar5 = *(cRObject **)(pcVar9 + 0x24);
                fVar7 = *(float *)(pcVar9 + 0x1c);
                fVar15 = *(float *)(pcVar9 + 0x20);
                bVar18 = (bool)cRBod::IsAfterSprites(pcVar9);
                G0RenderObject(pcVar5,atStack_78,fVar7,fVar15,(tColourSmall *)(pcVar9 + 0x28),bVar18
                              );
                if (local_84 == 0) goto LAB_00049694;
              }
              pcVar5 = *(cRObject **)(pcVar9 + 0x24);
              fVar15 = *(float *)(pcVar9 + 0x1c);
              fVar7 = *(float *)(pcVar9 + 0x20);
              bVar18 = (bool)cRBod::IsAfterSprites(pcVar9);
              puVar13 = puVar13 + -4;
              G0RenderObject(pcVar5,(tMatrix *)(pcVar9 + 0x2c),fVar15,fVar7,
                             (tColourSmall *)(pcVar9 + 0x28),bVar18);
            } while (local_84 != 0);
          }
        }
LAB_00049694:
        local_88 = local_88 + 1;
      } while (local_88 != local_8c);
    }
    G0RenderEnd();
  }
  else {
    *(int *)(this + 0x328) = *(int *)(this + 0x328) + -1;
  }
  return;
}
