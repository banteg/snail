/*
 * mangled: _ZN8cRBorder9InputTextEv
 * demangled: cRBorder::InputText()
 * address: 0005d594
 * size: 2340
 */

/* cRBorder::InputText() */

void __thiscall cRBorder::InputText(cRBorder *this)

{
  cRBorder *pcVar1;
  float fVar2;
  cRBorder cVar3;
  int iVar4;
  cRBorder *pcVar5;
  cRBorder cVar6;
  cRBorder cVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  cRBorder *pcVar11;
  int iVar12;
  bool bVar13;
  float fVar14;

  iVar4 = RShellInkeyInput();
  iVar9 = DAT_0005dac8 + 0x5d5b0;
  if (((((*(uint *)(this + 0x704) & 0xc) != 0) &&
       (cRInputOK::AI((cRInputOK *)(this + 0x2a0)),
       (*(uint *)(*(int *)(this + 0x2c0) + 0x194) & 0x20) != 0)) || (iVar4 == 5)) ||
     ((*(uint *)(this + 0x194) & 0x8000000) != 0)) {
    if (this[*(int *)(this + 0x6f4) + 0x2c4] != (cRBorder)0x0) {
      pcVar5 = this + *(int *)(this + 0x6f4) + 0x2c4;
      do {
        pcVar11 = pcVar5 + 1;
        *pcVar5 = *pcVar11;
        pcVar5 = pcVar5 + 1;
      } while (*pcVar11 != (cRBorder)0x0);
    }
    uVar8 = *(uint *)(this + 0x194);
    *(uint *)(this + 0x194) = uVar8 & 0xffffdfff;
    *(int *)(this + 0x708) = *(int *)(this + 0x708) + -1;
    *(uint *)(this + 0x194) = uVar8 & 0xffffdfff | 0x4000;
    RePosition(this);
    if ((*(uint *)(this + 0x704) & 0xc) == 0) {
      return;
    }
    cRBorderManager::Kill
              ((cRBorderManager *)(**(int **)(iVar9 + DAT_0005dacc) + 0xd14),
               *(cRBorder **)(this + 0x2c0));
    return;
  }
  if (iVar4 == 6) {
    if ((*(uint *)(this + 0x704) & 1) != 0) {
LAB_0005d9e8:
      if (*(int *)(this + 0x708) < *(int *)(this + 0x70c)) {
        if (iVar4 == 0x20) {
          uVar8 = *(uint *)(this + 0x704);
          if ((uVar8 & 1) != 0) {
            iVar4 = *(int *)(this + 0x6f4);
            goto LAB_0005d700;
          }
        }
        else {
          uVar8 = *(uint *)(this + 0x704);
        }
        if (((uVar8 & 2) != 0) && (iVar4 == 0x2c || iVar4 == 0x2e)) goto LAB_0005d864;
        iVar9 = *(int *)(this + 0x6f4);
        *(int *)(this + 0x6f4) = iVar9 + 1;
        this[iVar9 + 0x2c4] = SUB41(iVar4,0);
        pcVar5 = this + iVar9 + 0x2c5;
        cVar6 = (cRBorder)0x20;
        while( true ) {
          cVar7 = *pcVar5;
          if (cVar7 == (cRBorder)0x0) break;
          *pcVar5 = cVar6;
          pcVar5 = pcVar5 + 1;
          cVar6 = cVar7;
        }
        pcVar5[1] = (cRBorder)0x0;
        *pcVar5 = cVar6;
        iVar4 = *(int *)(this + 0x6f4);
        uVar8 = *(uint *)(this + 0x704);
        *(int *)(this + 0x708) = *(int *)(this + 0x708) + 1;
        goto LAB_0005d700;
      }
LAB_0005d69c:
      iVar4 = *(int *)(this + 0x6f4);
      uVar8 = *(uint *)(this + 0x704);
      goto LAB_0005d700;
    }
    if ((*(uint *)(this + 0x704) & 2) == 0) {
      iVar4 = *(int *)(this + 0x6f4);
      *(int *)(this + 0x6f4) = iVar4 + 1;
      this[iVar4 + 0x2c4] = (cRBorder)0x3e;
      pcVar5 = this + iVar4 + 0x2c5;
      if (this[iVar4 + 0x2c5] == (cRBorder)0x0) {
        cVar6 = (cRBorder)0x20;
      }
      else {
        cVar7 = (cRBorder)0x20;
        cVar3 = this[iVar4 + 0x2c5];
        do {
          cVar6 = cVar3;
          *pcVar5 = cVar7;
          pcVar5 = pcVar5 + 1;
          cVar7 = cVar6;
          cVar3 = *pcVar5;
        } while (*pcVar5 != (cRBorder)0x0);
      }
      *pcVar5 = cVar6;
      pcVar5[1] = (cRBorder)0x0;
      iVar4 = *(int *)(this + 0x6f4);
      *(int *)(this + 0x708) = *(int *)(this + 0x708) + 1;
      uVar8 = *(uint *)(this + 0x704);
      goto LAB_0005d700;
    }
LAB_0005d864:
    iVar4 = *(int *)(this + 0x6f4);
LAB_0005d868:
    cVar6 = this[0x2c4];
    if (cVar6 != (cRBorder)0x0) {
      iVar9 = 0;
      pcVar5 = this;
      do {
        if (cVar6 == (cRBorder)0x20) {
          if (iVar4 != iVar9) {
            if (this[iVar9 + 0x2c4] != (cRBorder)0x0) {
              pcVar11 = this + iVar9 + 0x2c4;
              do {
                pcVar1 = pcVar11 + 1;
                *pcVar11 = *pcVar1;
                pcVar11 = pcVar11 + 1;
              } while (*pcVar1 != (cRBorder)0x0);
              iVar4 = *(int *)(this + 0x6f4);
            }
            if (iVar9 <= iVar4) {
              iVar4 = iVar4 + -1;
              *(int *)(this + 0x6f4) = iVar4;
            }
            *(int *)(this + 0x708) = *(int *)(this + 0x708) + -1;
          }
        }
        else if (iVar4 != iVar9) break;
        cVar6 = pcVar5[0x2c5];
        iVar9 = iVar9 + 1;
        pcVar5 = pcVar5 + 1;
      } while (cVar6 != (cRBorder)0x0);
    }
  }
  else {
    if (iVar4 == 3) {
      iVar4 = *(int *)(this + 0x6f4);
      if (0 < iVar4) {
        cVar6 = this[iVar4 + 0x2c4];
        this[iVar4 + 0x2c4] = this[iVar4 + 0x2c3];
        this[iVar4 + 0x2c3] = cVar6;
        uVar8 = *(uint *)(this + 0x704);
        iVar4 = *(int *)(this + 0x6f4) + -1;
        *(int *)(this + 0x6f4) = iVar4;
        goto LAB_0005d700;
      }
    }
    else {
      if (iVar4 == 4) {
        iVar4 = *(int *)(this + 0x6f4);
        if (*(int *)(this + 0x708) <= iVar4) goto LAB_0005d9d4;
        cVar6 = this[iVar4 + 0x2c4];
        this[iVar4 + 0x2c4] = this[iVar4 + 0x2c5];
        this[iVar4 + 0x2c5] = cVar6;
        uVar8 = *(uint *)(this + 0x704);
        iVar4 = *(int *)(this + 0x6f4) + 1;
        *(int *)(this + 0x6f4) = iVar4;
        goto LAB_0005d700;
      }
      if (iVar4 != 7) {
        if (iVar4 != 8) {
          if (iVar4 != 9) {
            if (iVar4 != 10) {
              if (iVar4 == 1) {
                wprintf((char *)(iVar9 + DAT_0005dad0));
                iVar4 = *(int *)(this + 0x6f4);
                if (0 < iVar4) {
                  *(int *)(this + 0x6f4) = iVar4 + -1;
                  cVar6 = this[iVar4 + 0x2c3];
                  pcVar5 = this + iVar4 + 0x2c3;
                  while (cVar6 != (cRBorder)0x0) {
                    cVar6 = pcVar5[1];
                    *pcVar5 = cVar6;
                    pcVar5 = pcVar5 + 1;
                  }
LAB_0005dc74:
                  iVar4 = *(int *)(this + 0x6f4);
                  *(int *)(this + 0x708) = *(int *)(this + 0x708) + -1;
                  uVar8 = *(uint *)(this + 0x704);
                  goto LAB_0005d700;
                }
              }
              else {
                if (iVar4 != 2) {
                  if (iVar4 != 0) goto LAB_0005d9e8;
                  goto LAB_0005d69c;
                }
                iVar4 = *(int *)(this + 0x6f4);
                if (iVar4 < *(int *)(this + 0x708)) {
                  cVar6 = this[iVar4 + 0x2c4];
                  pcVar5 = this + iVar4 + 0x2c4;
                  while (cVar6 != (cRBorder)0x0) {
                    cVar6 = pcVar5[1];
                    *pcVar5 = cVar6;
                    pcVar5 = pcVar5 + 1;
                  }
                  goto LAB_0005dc74;
                }
              }
              goto LAB_0005d9d4;
            }
            iVar9 = *(int *)(this + 0x6f4);
            iVar4 = iVar9;
            if (iVar9 < 1) {
LAB_0005de34:
              pcVar5 = this + iVar4;
              if (pcVar5[0x2c4] == (cRBorder)0x3e) goto LAB_0005ddd8;
            }
            else {
              if (this[iVar9 + 0x2c4] != (cRBorder)0x3e) {
                pcVar5 = this + iVar9 + 0x2c4;
                do {
                  iVar4 = iVar4 + -1;
                  if (iVar4 == 0) goto LAB_0005de34;
                  pcVar5 = pcVar5 + -1;
                } while (*pcVar5 != (cRBorder)0x3e);
              }
LAB_0005ddd8:
              iVar4 = iVar4 + 1;
              pcVar5 = this + iVar4;
            }
            if (this[iVar9 + 0x2c4] != (cRBorder)0x0) {
              pcVar11 = this + iVar9 + 0x2c4;
              do {
                pcVar1 = pcVar11 + 1;
                *pcVar11 = *pcVar1;
                pcVar11 = pcVar11 + 1;
              } while (*pcVar1 != (cRBorder)0x0);
            }
            cVar6 = pcVar5[0x2c4];
            pcVar5 = this + iVar4 + 0x2c4;
            *(int *)(this + 0x6f4) = iVar4;
            do {
              cVar7 = pcVar5[1];
              bVar13 = cVar6 != (cRBorder)0x0;
              pcVar5 = pcVar5 + 1;
              *pcVar5 = cVar6;
              cVar6 = cVar7;
            } while (bVar13);
            goto LAB_0005d69c;
          }
          iVar9 = *(int *)(this + 0x6f4);
          cVar6 = this[iVar9 + 0x2c4];
          iVar4 = iVar9;
          if (cVar6 == (cRBorder)0x3e || cVar6 == (cRBorder)0x0) {
            if (cVar6 != (cRBorder)0x0) goto LAB_0005dce0;
          }
          else {
            pcVar5 = this + iVar9 + 0x2c4;
            do {
              pcVar5 = pcVar5 + 1;
              iVar4 = iVar4 + 1;
            } while (*pcVar5 != (cRBorder)0x3e && *pcVar5 != (cRBorder)0x0);
LAB_0005dce0:
            pcVar5 = this + iVar9 + 0x2c4;
            do {
              pcVar11 = pcVar5 + 1;
              *pcVar5 = *pcVar11;
              iVar9 = iVar4;
              pcVar5 = pcVar5 + 1;
            } while (*pcVar11 != (cRBorder)0x0);
          }
          *(int *)(this + 0x6f4) = iVar9 + -1;
          pcVar5 = this + iVar9 + 0x2c3;
          cVar6 = this[iVar9 + 0x2c3];
          do {
            cVar7 = pcVar5[1];
            bVar13 = cVar6 != (cRBorder)0x0;
            pcVar5 = pcVar5 + 1;
            *pcVar5 = cVar6;
            cVar6 = cVar7;
          } while (bVar13);
          goto LAB_0005d69c;
        }
        iVar4 = *(int *)(this + 0x6f4);
        iVar12 = 0;
        iVar9 = iVar4;
        if (iVar4 < 1) {
LAB_0005dd74:
          pcVar5 = this + iVar9;
          if (pcVar5[0x2c4] == (cRBorder)0x3e) goto LAB_0005d900;
        }
        else {
          if (this[iVar4 + 0x2c4] != (cRBorder)0x3e) {
            pcVar5 = this + iVar4 + 0x2c4;
            iVar12 = 1;
            while (iVar9 = iVar9 + -1, iVar9 != 0) {
              pcVar5 = pcVar5 + -1;
              if (*pcVar5 == (cRBorder)0x3e) goto LAB_0005d900;
              iVar12 = iVar12 + 1;
            }
            goto LAB_0005dd74;
          }
LAB_0005d900:
          iVar9 = iVar9 + 1;
          iVar12 = iVar12 + -1;
          pcVar5 = this + iVar9;
        }
        cVar6 = pcVar5[0x2c4];
        if (cVar6 != (cRBorder)0x0 && cVar6 != (cRBorder)0x3e) {
          pcVar5 = this + iVar9 + 0x2c4;
          do {
            pcVar5 = pcVar5 + 1;
            cVar6 = *pcVar5;
            iVar9 = iVar9 + 1;
          } while (cVar6 != (cRBorder)0x3e && cVar6 != (cRBorder)0x0);
        }
        if (cVar6 == (cRBorder)0x3e) {
          if (this[iVar9 + 0x2c5] == (cRBorder)0x3e || this[iVar9 + 0x2c5] == (cRBorder)0x0) {
            iVar10 = 0;
          }
          else {
            iVar10 = 0;
            pcVar5 = this + iVar9 + 0x2c4;
            do {
              pcVar11 = pcVar5 + 2;
              iVar10 = iVar10 + 1;
              pcVar5 = pcVar5 + 1;
            } while (*pcVar11 != (cRBorder)0x3e && *pcVar11 != (cRBorder)0x0);
          }
          if (iVar12 <= iVar10) {
            iVar10 = iVar12;
          }
          cVar6 = this[iVar4 + 0x2c4];
          pcVar5 = this + iVar4 + 0x2c4;
          while (cVar6 != (cRBorder)0x0) {
            cVar6 = pcVar5[1];
            *pcVar5 = cVar6;
            pcVar5 = pcVar5 + 1;
          }
          iVar10 = iVar10 + iVar9;
          *(int *)(this + 0x6f4) = iVar10;
          pcVar5 = this + iVar10 + 0x2c4;
          cVar6 = this[iVar10 + 0x2c4];
          do {
            cVar7 = pcVar5[1];
            bVar13 = cVar6 != (cRBorder)0x0;
            pcVar5 = pcVar5 + 1;
            *pcVar5 = cVar6;
            cVar6 = cVar7;
          } while (bVar13);
          iVar4 = *(int *)(this + 0x6f4);
        }
        goto LAB_0005d9d4;
      }
      iVar4 = *(int *)(this + 0x6f4);
      iVar9 = iVar4;
      if (iVar4 < 1) {
        iVar12 = -1;
LAB_0005dc8c:
        if (this[iVar9 + 0x2c4] == (cRBorder)0x3e) goto LAB_0005db20;
      }
      else {
        if (this[iVar4 + 0x2c4] == (cRBorder)0x3e) {
          iVar12 = -1;
        }
        else {
          pcVar5 = this + iVar4 + 0x2c4;
          iVar12 = -1;
          do {
            iVar9 = iVar9 + -1;
            iVar12 = iVar12 + 1;
            if (iVar9 == 0) goto LAB_0005dc8c;
            pcVar5 = pcVar5 + -1;
          } while (*pcVar5 != (cRBorder)0x3e);
        }
LAB_0005db20:
        iVar9 = iVar9 + -1;
      }
      if (iVar9 != 0) {
        if (iVar9 < 1) {
          iVar10 = 0;
LAB_0005de8c:
          if (this[iVar9 + 0x2c4] == (cRBorder)0x3e) goto LAB_0005db68;
        }
        else {
          if (this[iVar9 + 0x2c4] == (cRBorder)0x3e) {
            iVar10 = 0;
          }
          else {
            iVar10 = 0;
            pcVar5 = this + iVar9 + 0x2c4;
            do {
              iVar9 = iVar9 + -1;
              iVar10 = iVar10 + 1;
              if (iVar9 == 0) goto LAB_0005de8c;
              pcVar5 = pcVar5 + -1;
            } while (*pcVar5 != (cRBorder)0x3e);
          }
LAB_0005db68:
          iVar9 = iVar9 + 1;
        }
        if (iVar12 <= iVar10) {
          iVar10 = iVar12;
        }
        if (this[iVar4 + 0x2c4] != (cRBorder)0x0) {
          pcVar5 = this + iVar4 + 0x2c4;
          do {
            pcVar11 = pcVar5 + 1;
            *pcVar5 = *pcVar11;
            pcVar5 = pcVar5 + 1;
          } while (*pcVar11 != (cRBorder)0x0);
        }
        iVar10 = iVar10 + iVar9;
        *(int *)(this + 0x6f4) = iVar10;
        pcVar5 = this + iVar10 + 0x2c4;
        cVar6 = this[iVar10 + 0x2c4];
        do {
          cVar7 = pcVar5[1];
          bVar13 = cVar6 != (cRBorder)0x0;
          pcVar5 = pcVar5 + 1;
          *pcVar5 = cVar6;
          cVar6 = cVar7;
        } while (bVar13);
        iVar4 = *(int *)(this + 0x6f4);
      }
    }
LAB_0005d9d4:
    uVar8 = *(uint *)(this + 0x704);
LAB_0005d700:
    if ((uVar8 & 2) != 0) goto LAB_0005d868;
  }
  fVar2 = DAT_0005dac0;
  fVar14 = *(float *)(this + 0x6fc);
  *(float *)(this + 0x6fc) = fVar14 + *(float *)(this + 0x700);
  if (fVar14 + *(float *)(this + 0x700) <= fVar2) {
    if (*(int *)(this + 0x6f8) == 1) goto LAB_0005d760;
  }
  else {
    *(undefined4 *)(this + 0x6fc) = DAT_0005dac4;
    if (*(int *)(this + 0x6f8) == 0) {
      *(undefined4 *)(this + 0x6f8) = 1;
LAB_0005d760:
      this[iVar4 + 0x2c4] = (cRBorder)0x7c;
      goto LAB_0005d76c;
    }
    *(undefined4 *)(this + 0x6f8) = 0;
  }
  this[iVar4 + 0x2c4] = (cRBorder)0x20;
LAB_0005d76c:
  cVar6 = this[0x2c4];
  if (cVar6 != (cRBorder)0x0) {
    pcVar11 = this + 0x2c4;
    iVar4 = 1;
    iVar9 = 0;
    pcVar5 = this;
    do {
      if (iVar9 == 0) {
        if ((byte)((char)cVar6 + 0x9fU) < 0x1a) {
          *pcVar11 = (cRBorder)((char)cVar6 + -0x20);
        }
LAB_0005d7a0:
        cVar6 = pcVar11[iVar4];
      }
      else {
        if (*(int *)(this + 0x6f4) == iVar9 + -1) {
          if (iVar9 == 1) {
            if ((byte)((char)cVar6 + 0x9fU) < 0x1a) {
              this[0x2c5] = (cRBorder)((char)cVar6 + -0x20);
            }
          }
          else if (pcVar5[0x2c2] == (cRBorder)0x20) goto LAB_0005d7dc;
          goto LAB_0005d7a0;
        }
        if (pcVar5[0x2c3] != (cRBorder)0x20) goto LAB_0005d7a0;
LAB_0005d7dc:
        if ((byte)((char)cVar6 + 0x9fU) < 0x1a) {
          pcVar11[iVar9] = (cRBorder)((char)cVar6 + -0x20);
        }
        cVar6 = pcVar11[iVar4];
      }
      if (cVar6 == (cRBorder)0x0) break;
      iVar4 = iVar4 + 1;
      pcVar5 = pcVar5 + 1;
      iVar9 = iVar9 + 1;
    } while( true );
  }
  RePosition(this);
  return;
}
