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
  cRBorder cVar2;
  int iVar3;
  cRBorder *pcVar4;
  cRBorder cVar5;
  cRBorder cVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  cRBorder *pcVar10;
  int iVar11;
  bool bVar12;
  float fVar13;

  iVar3 = RShellInkeyInput();
  if (((((*(uint *)(this + 0x704) & 0xc) != 0) &&
       (cRInputOK::AI((cRInputOK *)(this + 0x2a0)),
       (*(uint *)(*(int *)(this + 0x2c0) + 0x194) & 0x20) != 0)) || (iVar3 == 5)) ||
     ((*(uint *)(this + 0x194) & 0x8000000) != 0)) {
    if (this[*(int *)(this + 0x6f4) + 0x2c4] != (cRBorder)0x0) {
      pcVar4 = this + *(int *)(this + 0x6f4) + 0x2c4;
      do {
        pcVar10 = pcVar4 + 1;
        *pcVar4 = *pcVar10;
        pcVar4 = pcVar4 + 1;
      } while (*pcVar10 != (cRBorder)0x0);
    }
    uVar7 = *(uint *)(this + 0x194);
    *(uint *)(this + 0x194) = uVar7 & 0xffffdfff;
    *(int *)(this + 0x708) = *(int *)(this + 0x708) + -1;
    *(uint *)(this + 0x194) = uVar7 & 0xffffdfff | 0x4000;
    RePosition(this);
    if ((*(uint *)(this + 0x704) & 0xc) == 0) {
      return;
    }
    cRBorderManager::Kill((cRBorderManager *)(Game + 0xd14),*(cRBorder **)(this + 0x2c0));
    return;
  }
  if (iVar3 == 6) {
    if ((*(uint *)(this + 0x704) & 1) != 0) {
LAB_0005d9e8:
      if (*(int *)(this + 0x708) < *(int *)(this + 0x70c)) {
        if (iVar3 == 0x20) {
          uVar7 = *(uint *)(this + 0x704);
          if ((uVar7 & 1) != 0) {
            iVar3 = *(int *)(this + 0x6f4);
            goto LAB_0005d700;
          }
        }
        else {
          uVar7 = *(uint *)(this + 0x704);
        }
        if (((uVar7 & 2) != 0) && (iVar3 == 0x2c || iVar3 == 0x2e)) goto LAB_0005d864;
        iVar8 = *(int *)(this + 0x6f4);
        *(int *)(this + 0x6f4) = iVar8 + 1;
        this[iVar8 + 0x2c4] = SUB41(iVar3,0);
        pcVar4 = this + iVar8 + 0x2c5;
        cVar5 = (cRBorder)0x20;
        while( true ) {
          cVar6 = *pcVar4;
          if (cVar6 == (cRBorder)0x0) break;
          *pcVar4 = cVar5;
          pcVar4 = pcVar4 + 1;
          cVar5 = cVar6;
        }
        pcVar4[1] = (cRBorder)0x0;
        *pcVar4 = cVar5;
        iVar3 = *(int *)(this + 0x6f4);
        uVar7 = *(uint *)(this + 0x704);
        *(int *)(this + 0x708) = *(int *)(this + 0x708) + 1;
        goto LAB_0005d700;
      }
LAB_0005d69c:
      iVar3 = *(int *)(this + 0x6f4);
      uVar7 = *(uint *)(this + 0x704);
      goto LAB_0005d700;
    }
    if ((*(uint *)(this + 0x704) & 2) == 0) {
      iVar3 = *(int *)(this + 0x6f4);
      *(int *)(this + 0x6f4) = iVar3 + 1;
      this[iVar3 + 0x2c4] = (cRBorder)0x3e;
      pcVar4 = this + iVar3 + 0x2c5;
      if (this[iVar3 + 0x2c5] == (cRBorder)0x0) {
        cVar5 = (cRBorder)0x20;
      }
      else {
        cVar6 = (cRBorder)0x20;
        cVar2 = this[iVar3 + 0x2c5];
        do {
          cVar5 = cVar2;
          *pcVar4 = cVar6;
          pcVar4 = pcVar4 + 1;
          cVar6 = cVar5;
          cVar2 = *pcVar4;
        } while (*pcVar4 != (cRBorder)0x0);
      }
      *pcVar4 = cVar5;
      pcVar4[1] = (cRBorder)0x0;
      iVar3 = *(int *)(this + 0x6f4);
      *(int *)(this + 0x708) = *(int *)(this + 0x708) + 1;
      uVar7 = *(uint *)(this + 0x704);
      goto LAB_0005d700;
    }
LAB_0005d864:
    iVar3 = *(int *)(this + 0x6f4);
LAB_0005d868:
    cVar5 = this[0x2c4];
    if (cVar5 != (cRBorder)0x0) {
      iVar8 = 0;
      pcVar4 = this;
      do {
        if (cVar5 == (cRBorder)0x20) {
          if (iVar3 != iVar8) {
            if (this[iVar8 + 0x2c4] != (cRBorder)0x0) {
              pcVar10 = this + iVar8 + 0x2c4;
              do {
                pcVar1 = pcVar10 + 1;
                *pcVar10 = *pcVar1;
                pcVar10 = pcVar10 + 1;
              } while (*pcVar1 != (cRBorder)0x0);
              iVar3 = *(int *)(this + 0x6f4);
            }
            if (iVar8 <= iVar3) {
              iVar3 = iVar3 + -1;
              *(int *)(this + 0x6f4) = iVar3;
            }
            *(int *)(this + 0x708) = *(int *)(this + 0x708) + -1;
          }
        }
        else if (iVar3 != iVar8) break;
        cVar5 = pcVar4[0x2c5];
        iVar8 = iVar8 + 1;
        pcVar4 = pcVar4 + 1;
      } while (cVar5 != (cRBorder)0x0);
    }
  }
  else {
    if (iVar3 == 3) {
      iVar3 = *(int *)(this + 0x6f4);
      if (0 < iVar3) {
        cVar5 = this[iVar3 + 0x2c4];
        this[iVar3 + 0x2c4] = this[iVar3 + 0x2c3];
        this[iVar3 + 0x2c3] = cVar5;
        uVar7 = *(uint *)(this + 0x704);
        iVar3 = *(int *)(this + 0x6f4) + -1;
        *(int *)(this + 0x6f4) = iVar3;
        goto LAB_0005d700;
      }
    }
    else {
      if (iVar3 == 4) {
        iVar3 = *(int *)(this + 0x6f4);
        if (*(int *)(this + 0x708) <= iVar3) goto LAB_0005d9d4;
        cVar5 = this[iVar3 + 0x2c4];
        this[iVar3 + 0x2c4] = this[iVar3 + 0x2c5];
        this[iVar3 + 0x2c5] = cVar5;
        uVar7 = *(uint *)(this + 0x704);
        iVar3 = *(int *)(this + 0x6f4) + 1;
        *(int *)(this + 0x6f4) = iVar3;
        goto LAB_0005d700;
      }
      if (iVar3 != 7) {
        if (iVar3 != 8) {
          if (iVar3 != 9) {
            if (iVar3 != 10) {
              if (iVar3 == 1) {
                wprintf("BORDER BACKSPACE");
                iVar3 = *(int *)(this + 0x6f4);
                if (0 < iVar3) {
                  *(int *)(this + 0x6f4) = iVar3 + -1;
                  cVar5 = this[iVar3 + 0x2c3];
                  pcVar4 = this + iVar3 + 0x2c3;
                  while (cVar5 != (cRBorder)0x0) {
                    cVar5 = pcVar4[1];
                    *pcVar4 = cVar5;
                    pcVar4 = pcVar4 + 1;
                  }
LAB_0005dc74:
                  iVar3 = *(int *)(this + 0x6f4);
                  *(int *)(this + 0x708) = *(int *)(this + 0x708) + -1;
                  uVar7 = *(uint *)(this + 0x704);
                  goto LAB_0005d700;
                }
              }
              else {
                if (iVar3 != 2) {
                  if (iVar3 != 0) goto LAB_0005d9e8;
                  goto LAB_0005d69c;
                }
                iVar3 = *(int *)(this + 0x6f4);
                if (iVar3 < *(int *)(this + 0x708)) {
                  cVar5 = this[iVar3 + 0x2c4];
                  pcVar4 = this + iVar3 + 0x2c4;
                  while (cVar5 != (cRBorder)0x0) {
                    cVar5 = pcVar4[1];
                    *pcVar4 = cVar5;
                    pcVar4 = pcVar4 + 1;
                  }
                  goto LAB_0005dc74;
                }
              }
              goto LAB_0005d9d4;
            }
            iVar8 = *(int *)(this + 0x6f4);
            iVar3 = iVar8;
            if (iVar8 < 1) {
LAB_0005de34:
              pcVar4 = this + iVar3;
              if (pcVar4[0x2c4] == (cRBorder)0x3e) goto LAB_0005ddd8;
            }
            else {
              if (this[iVar8 + 0x2c4] != (cRBorder)0x3e) {
                pcVar4 = this + iVar8 + 0x2c4;
                do {
                  iVar3 = iVar3 + -1;
                  if (iVar3 == 0) goto LAB_0005de34;
                  pcVar4 = pcVar4 + -1;
                } while (*pcVar4 != (cRBorder)0x3e);
              }
LAB_0005ddd8:
              iVar3 = iVar3 + 1;
              pcVar4 = this + iVar3;
            }
            if (this[iVar8 + 0x2c4] != (cRBorder)0x0) {
              pcVar10 = this + iVar8 + 0x2c4;
              do {
                pcVar1 = pcVar10 + 1;
                *pcVar10 = *pcVar1;
                pcVar10 = pcVar10 + 1;
              } while (*pcVar1 != (cRBorder)0x0);
            }
            cVar5 = pcVar4[0x2c4];
            pcVar4 = this + iVar3 + 0x2c4;
            *(int *)(this + 0x6f4) = iVar3;
            do {
              cVar6 = pcVar4[1];
              bVar12 = cVar5 != (cRBorder)0x0;
              pcVar4 = pcVar4 + 1;
              *pcVar4 = cVar5;
              cVar5 = cVar6;
            } while (bVar12);
            goto LAB_0005d69c;
          }
          iVar8 = *(int *)(this + 0x6f4);
          cVar5 = this[iVar8 + 0x2c4];
          iVar3 = iVar8;
          if (cVar5 == (cRBorder)0x3e || cVar5 == (cRBorder)0x0) {
            if (cVar5 != (cRBorder)0x0) goto LAB_0005dce0;
          }
          else {
            pcVar4 = this + iVar8 + 0x2c4;
            do {
              pcVar4 = pcVar4 + 1;
              iVar3 = iVar3 + 1;
            } while (*pcVar4 != (cRBorder)0x3e && *pcVar4 != (cRBorder)0x0);
LAB_0005dce0:
            pcVar4 = this + iVar8 + 0x2c4;
            do {
              pcVar10 = pcVar4 + 1;
              *pcVar4 = *pcVar10;
              iVar8 = iVar3;
              pcVar4 = pcVar4 + 1;
            } while (*pcVar10 != (cRBorder)0x0);
          }
          *(int *)(this + 0x6f4) = iVar8 + -1;
          pcVar4 = this + iVar8 + 0x2c3;
          cVar5 = this[iVar8 + 0x2c3];
          do {
            cVar6 = pcVar4[1];
            bVar12 = cVar5 != (cRBorder)0x0;
            pcVar4 = pcVar4 + 1;
            *pcVar4 = cVar5;
            cVar5 = cVar6;
          } while (bVar12);
          goto LAB_0005d69c;
        }
        iVar3 = *(int *)(this + 0x6f4);
        iVar11 = 0;
        iVar8 = iVar3;
        if (iVar3 < 1) {
LAB_0005dd74:
          pcVar4 = this + iVar8;
          if (pcVar4[0x2c4] == (cRBorder)0x3e) goto LAB_0005d900;
        }
        else {
          if (this[iVar3 + 0x2c4] != (cRBorder)0x3e) {
            pcVar4 = this + iVar3 + 0x2c4;
            iVar11 = 1;
            while (iVar8 = iVar8 + -1, iVar8 != 0) {
              pcVar4 = pcVar4 + -1;
              if (*pcVar4 == (cRBorder)0x3e) goto LAB_0005d900;
              iVar11 = iVar11 + 1;
            }
            goto LAB_0005dd74;
          }
LAB_0005d900:
          iVar8 = iVar8 + 1;
          iVar11 = iVar11 + -1;
          pcVar4 = this + iVar8;
        }
        cVar5 = pcVar4[0x2c4];
        if (cVar5 != (cRBorder)0x0 && cVar5 != (cRBorder)0x3e) {
          pcVar4 = this + iVar8 + 0x2c4;
          do {
            pcVar4 = pcVar4 + 1;
            cVar5 = *pcVar4;
            iVar8 = iVar8 + 1;
          } while (cVar5 != (cRBorder)0x3e && cVar5 != (cRBorder)0x0);
        }
        if (cVar5 == (cRBorder)0x3e) {
          if (this[iVar8 + 0x2c5] == (cRBorder)0x3e || this[iVar8 + 0x2c5] == (cRBorder)0x0) {
            iVar9 = 0;
          }
          else {
            iVar9 = 0;
            pcVar4 = this + iVar8 + 0x2c4;
            do {
              pcVar10 = pcVar4 + 2;
              iVar9 = iVar9 + 1;
              pcVar4 = pcVar4 + 1;
            } while (*pcVar10 != (cRBorder)0x3e && *pcVar10 != (cRBorder)0x0);
          }
          if (iVar11 <= iVar9) {
            iVar9 = iVar11;
          }
          cVar5 = this[iVar3 + 0x2c4];
          pcVar4 = this + iVar3 + 0x2c4;
          while (cVar5 != (cRBorder)0x0) {
            cVar5 = pcVar4[1];
            *pcVar4 = cVar5;
            pcVar4 = pcVar4 + 1;
          }
          iVar9 = iVar9 + iVar8;
          *(int *)(this + 0x6f4) = iVar9;
          pcVar4 = this + iVar9 + 0x2c4;
          cVar5 = this[iVar9 + 0x2c4];
          do {
            cVar6 = pcVar4[1];
            bVar12 = cVar5 != (cRBorder)0x0;
            pcVar4 = pcVar4 + 1;
            *pcVar4 = cVar5;
            cVar5 = cVar6;
          } while (bVar12);
          iVar3 = *(int *)(this + 0x6f4);
        }
        goto LAB_0005d9d4;
      }
      iVar3 = *(int *)(this + 0x6f4);
      iVar8 = iVar3;
      if (iVar3 < 1) {
        iVar11 = -1;
LAB_0005dc8c:
        if (this[iVar8 + 0x2c4] == (cRBorder)0x3e) goto LAB_0005db20;
      }
      else {
        if (this[iVar3 + 0x2c4] == (cRBorder)0x3e) {
          iVar11 = -1;
        }
        else {
          pcVar4 = this + iVar3 + 0x2c4;
          iVar11 = -1;
          do {
            iVar8 = iVar8 + -1;
            iVar11 = iVar11 + 1;
            if (iVar8 == 0) goto LAB_0005dc8c;
            pcVar4 = pcVar4 + -1;
          } while (*pcVar4 != (cRBorder)0x3e);
        }
LAB_0005db20:
        iVar8 = iVar8 + -1;
      }
      if (iVar8 != 0) {
        if (iVar8 < 1) {
          iVar9 = 0;
LAB_0005de8c:
          if (this[iVar8 + 0x2c4] == (cRBorder)0x3e) goto LAB_0005db68;
        }
        else {
          if (this[iVar8 + 0x2c4] == (cRBorder)0x3e) {
            iVar9 = 0;
          }
          else {
            iVar9 = 0;
            pcVar4 = this + iVar8 + 0x2c4;
            do {
              iVar8 = iVar8 + -1;
              iVar9 = iVar9 + 1;
              if (iVar8 == 0) goto LAB_0005de8c;
              pcVar4 = pcVar4 + -1;
            } while (*pcVar4 != (cRBorder)0x3e);
          }
LAB_0005db68:
          iVar8 = iVar8 + 1;
        }
        if (iVar11 <= iVar9) {
          iVar9 = iVar11;
        }
        if (this[iVar3 + 0x2c4] != (cRBorder)0x0) {
          pcVar4 = this + iVar3 + 0x2c4;
          do {
            pcVar10 = pcVar4 + 1;
            *pcVar4 = *pcVar10;
            pcVar4 = pcVar4 + 1;
          } while (*pcVar10 != (cRBorder)0x0);
        }
        iVar9 = iVar9 + iVar8;
        *(int *)(this + 0x6f4) = iVar9;
        pcVar4 = this + iVar9 + 0x2c4;
        cVar5 = this[iVar9 + 0x2c4];
        do {
          cVar6 = pcVar4[1];
          bVar12 = cVar5 != (cRBorder)0x0;
          pcVar4 = pcVar4 + 1;
          *pcVar4 = cVar5;
          cVar5 = cVar6;
        } while (bVar12);
        iVar3 = *(int *)(this + 0x6f4);
      }
    }
LAB_0005d9d4:
    uVar7 = *(uint *)(this + 0x704);
LAB_0005d700:
    if ((uVar7 & 2) != 0) goto LAB_0005d868;
  }
  fVar13 = *(float *)(this + 0x6fc);
  *(float *)(this + 0x6fc) = fVar13 + *(float *)(this + 0x700);
  if (fVar13 + *(float *)(this + 0x700) <= 1.0) {
    if (*(int *)(this + 0x6f8) == 1) goto LAB_0005d760;
  }
  else {
    *(undefined4 *)(this + 0x6fc) = 0;
    if (*(int *)(this + 0x6f8) == 0) {
      *(undefined4 *)(this + 0x6f8) = 1;
LAB_0005d760:
      this[iVar3 + 0x2c4] = (cRBorder)0x7c;
      goto LAB_0005d76c;
    }
    *(undefined4 *)(this + 0x6f8) = 0;
  }
  this[iVar3 + 0x2c4] = (cRBorder)0x20;
LAB_0005d76c:
  cVar5 = this[0x2c4];
  if (cVar5 != (cRBorder)0x0) {
    pcVar10 = this + 0x2c4;
    iVar3 = 1;
    iVar8 = 0;
    pcVar4 = this;
    do {
      if (iVar8 == 0) {
        if ((byte)((char)cVar5 + 0x9fU) < 0x1a) {
          *pcVar10 = (cRBorder)((char)cVar5 + -0x20);
        }
LAB_0005d7a0:
        cVar5 = pcVar10[iVar3];
      }
      else {
        if (*(int *)(this + 0x6f4) == iVar8 + -1) {
          if (iVar8 == 1) {
            if ((byte)((char)cVar5 + 0x9fU) < 0x1a) {
              this[0x2c5] = (cRBorder)((char)cVar5 + -0x20);
            }
          }
          else if (pcVar4[0x2c2] == (cRBorder)0x20) goto LAB_0005d7dc;
          goto LAB_0005d7a0;
        }
        if (pcVar4[0x2c3] != (cRBorder)0x20) goto LAB_0005d7a0;
LAB_0005d7dc:
        if ((byte)((char)cVar5 + 0x9fU) < 0x1a) {
          pcVar10[iVar8] = (cRBorder)((char)cVar5 + -0x20);
        }
        cVar5 = pcVar10[iVar3];
      }
      if (cVar5 == (cRBorder)0x0) break;
      iVar3 = iVar3 + 1;
      pcVar4 = pcVar4 + 1;
      iVar8 = iVar8 + 1;
    } while( true );
  }
  RePosition(this);
  return;
}
