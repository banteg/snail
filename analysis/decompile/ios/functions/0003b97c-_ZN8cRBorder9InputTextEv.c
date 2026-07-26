/*
 * mangled: _ZN8cRBorder9InputTextEv
 * demangled: cRBorder::InputText()
 * address: 0003b97c
 * size: 2696
 */

/* cRBorder::InputText() */

void __thiscall cRBorder::InputText(cRBorder *this)

{
  cRBorder *pcVar1;
  cRBorder cVar2;
  cRBorder cVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  cRBorder cVar8;
  uint uVar9;
  undefined *puVar10;
  cRBorder *pcVar11;
  uint uVar12;
  bool bVar13;
  float fVar14;
  float fVar15;
  float fVar16;

  cVar2 = (cRBorder)RShellInkeyInput();
  if ((*(uint *)(this + 0x704) & 0xc) != 0) {
    iVar5 = *(int *)(this + 700);
    if ((*(uint *)(iVar5 + 0x704) & 4) == 0) {
      if ((*(uint *)(iVar5 + 0x704) & 8) == 0) {
        iVar7 = *(int *)(this + 0x2c0);
      }
      else {
        iVar7 = *(int *)(this + 0x2c0);
        fVar14 = *(float *)(iVar5 + 0x22c);
        *(undefined4 *)(iVar7 + 0x230) = *(undefined4 *)(iVar5 + 0x230);
        fVar14 = ((fVar14 - *(float *)(iVar7 + 0x23c)) - *(float *)(iVar5 + 0x20c)) +
                 *(float *)(iVar7 + 0x20c) * -2.0;
        *(float *)(iVar7 + 0x6ec) = fVar14;
        *(float *)(iVar7 + 0x22c) = fVar14;
        *(undefined4 *)(iVar7 + 0x6f0) = *(undefined4 *)(iVar5 + 0x6f0);
      }
    }
    else {
      fVar14 = *(float *)(iVar5 + 0x22c);
      fVar16 = *(float *)(iVar5 + 0x23c);
      iVar7 = *(int *)(this + 0x2c0);
      fVar15 = *(float *)(iVar5 + 0x20c);
      *(undefined4 *)(iVar7 + 0x230) = *(undefined4 *)(iVar5 + 0x230);
      fVar14 = fVar14 + fVar16 + fVar15 + *(float *)(iVar7 + 0x20c);
      *(float *)(iVar7 + 0x6ec) = fVar14;
      *(float *)(iVar7 + 0x22c) = fVar14;
      *(undefined4 *)(iVar7 + 0x6f0) = *(undefined4 *)(iVar5 + 0x6f0);
    }
    if ((*(uint *)(iVar7 + 0x194) & 0x20) != 0) goto LAB_0003ba00;
  }
  uVar9 = *(uint *)(this + 0x704);
  if ((cVar2 == (cRBorder)0x5) || ((*(uint *)(this + 0x194) & 0x8000000) != 0)) {
LAB_0003ba00:
    if (this[*(int *)(this + 0x6f4) + 0x2c4] != (cRBorder)0x0) {
      pcVar11 = this + *(int *)(this + 0x6f4) + 0x2c4;
      do {
        pcVar1 = pcVar11 + 1;
        *pcVar11 = *pcVar1;
        pcVar11 = pcVar11 + 1;
      } while (*pcVar1 != (cRBorder)0x0);
    }
    *(int *)(this + 0x708) = *(int *)(this + 0x708) + -1;
    uVar9 = *(uint *)(this + 0x194);
    *(uint *)(this + 0x194) = uVar9 & 0xffffdfff;
    *(uint *)(this + 0x194) = uVar9 & 0xffffdfff | 0x4000;
    RePosition(this);
    if ((*(uint *)(this + 0x704) & 0xc) == 0) {
      return;
    }
    iVar7 = *(int *)(this + 0x2c0);
    iVar5 = *(int *)PTR__Game_001b60b8;
    puVar10 = PTR__Game_001b60b8;
    if (iVar7 != 0) {
      puVar10 = *(undefined **)(iVar7 + 0x194);
    }
    if (iVar7 == 0 || puVar10 == (undefined *)0x0) {
      return;
    }
    if (((uint)puVar10 & 0x400) != 0) {
      return;
    }
    *(uint *)(iVar7 + 0x194) = (uint)puVar10 & 0xffffff09 | 0x200;
    if (((uint)puVar10 & 0x100000) == 0) {
      return;
    }
    pcVar11 = (cRBorder *)(iVar5 + 0xd14);
    cRBorderManager::Kill(pcVar11);
    cRBorderManager::Kill(pcVar11);
    cRBorderManager::Kill(pcVar11);
    return;
  }
  uVar12 = uVar9 & 2;
  if (cVar2 == (cRBorder)0x6) {
    if ((uVar9 & 1) != 0) {
LAB_0003bb38:
      if (((cVar2 == (cRBorder)0x0) || (*(int *)(this + 0x70c) <= *(int *)(this + 0x708))) ||
         ((cVar2 == (cRBorder)0x20 && ((uVar9 & 1) != 0)))) {
        iVar5 = *(int *)(this + 0x6f4);
        goto LAB_0003bce0;
      }
      if ((uVar12 != 0) && (cVar2 == (cRBorder)0x2e || cVar2 == (cRBorder)0x2c)) goto LAB_0003c224;
      iVar5 = *(int *)(this + 0x6f4);
      this[iVar5 + 0x2c4] = cVar2;
      pcVar11 = this + iVar5 + 0x2c5;
      *(int *)(this + 0x6f4) = iVar5 + 1;
      if (this[iVar5 + 0x2c5] == (cRBorder)0x0) goto LAB_0003c3c0;
      cVar2 = this[iVar5 + 0x2c5];
      cVar3 = (cRBorder)0x20;
      do {
        cVar8 = cVar2;
        *pcVar11 = cVar3;
        pcVar11 = pcVar11 + 1;
        cVar2 = *pcVar11;
        cVar3 = cVar8;
      } while (*pcVar11 != (cRBorder)0x0);
LAB_0003bbbc:
      *pcVar11 = cVar8;
      pcVar11[1] = (cRBorder)0x0;
      *(int *)(this + 0x708) = *(int *)(this + 0x708) + 1;
LAB_0003bbd4:
      iVar5 = *(int *)(this + 0x6f4);
      uVar12 = *(uint *)(this + 0x704) & 2;
      goto LAB_0003bce0;
    }
    if (uVar12 == 0) {
      iVar5 = *(int *)(this + 0x6f4);
      this[iVar5 + 0x2c4] = (cRBorder)0x3e;
      pcVar11 = this + iVar5 + 0x2c5;
      *(int *)(this + 0x6f4) = iVar5 + 1;
      if (this[iVar5 + 0x2c5] == (cRBorder)0x0) {
LAB_0003c3c0:
        cVar8 = (cRBorder)0x20;
      }
      else {
        cVar2 = this[iVar5 + 0x2c5];
        cVar3 = (cRBorder)0x20;
        do {
          cVar8 = cVar2;
          *pcVar11 = cVar3;
          pcVar11 = pcVar11 + 1;
          cVar2 = *pcVar11;
          cVar3 = cVar8;
        } while (*pcVar11 != (cRBorder)0x0);
      }
      goto LAB_0003bbbc;
    }
LAB_0003c224:
    iVar5 = *(int *)(this + 0x6f4);
LAB_0003bce8:
    cVar2 = this[0x2c4];
    if (cVar2 != (cRBorder)0x0) {
      pcVar11 = this + 0x2c4;
      iVar7 = 0;
      do {
        if (cVar2 == (cRBorder)0x20) {
          if (iVar5 != iVar7) {
            do {
              pcVar1 = pcVar11 + 1;
              *pcVar11 = *pcVar1;
              pcVar11 = pcVar11 + 1;
            } while (*pcVar1 != (cRBorder)0x0);
            iVar5 = *(int *)(this + 0x6f4);
            if (iVar7 <= iVar5) {
              iVar5 = iVar5 + -1;
              *(int *)(this + 0x6f4) = iVar5;
            }
            *(int *)(this + 0x708) = *(int *)(this + 0x708) + -1;
          }
        }
        else if (iVar5 != iVar7) break;
        pcVar11 = this + iVar7 + 0x2c5;
        cVar2 = this[iVar7 + 0x2c5];
        iVar7 = iVar7 + 1;
      } while (cVar2 != (cRBorder)0x0);
    }
  }
  else {
    if (cVar2 == (cRBorder)0x3) {
      iVar5 = *(int *)(this + 0x6f4);
      if (0 < iVar5) {
        cVar2 = this[iVar5 + 0x2c4];
        this[iVar5 + 0x2c4] = this[iVar5 + 0x2c3];
        this[iVar5 + 0x2c3] = cVar2;
        uVar12 = *(uint *)(this + 0x704) & 2;
        iVar5 = *(int *)(this + 0x6f4) + -1;
        *(int *)(this + 0x6f4) = iVar5;
      }
    }
    else {
      if (cVar2 != (cRBorder)0x4) {
        if (cVar2 == (cRBorder)0x7) {
          iVar5 = *(int *)(this + 0x6f4);
          iVar7 = iVar5;
          if (iVar5 < 1) {
            iVar6 = -1;
LAB_0003bff4:
            if (this[iVar7 + 0x2c4] == (cRBorder)0x3e) goto LAB_0003c21c;
          }
          else {
            if (this[iVar5 + 0x2c4] == (cRBorder)0x3e) {
              iVar6 = -1;
            }
            else {
              pcVar11 = this + iVar5 + 0x2c4;
              iVar6 = -1;
              do {
                iVar7 = iVar7 + -1;
                iVar6 = iVar6 + 1;
                if (iVar7 == 0) goto LAB_0003bff4;
                pcVar11 = pcVar11 + -1;
              } while (*pcVar11 != (cRBorder)0x3e);
            }
LAB_0003c21c:
            iVar7 = iVar7 + -1;
          }
          if (iVar7 == 0) goto LAB_0003bce0;
          if (iVar7 < 1) {
            iVar4 = 0;
LAB_0003c050:
            if (this[iVar7 + 0x2c4] == (cRBorder)0x3e) goto LAB_0003c2f8;
          }
          else {
            if (this[iVar7 + 0x2c4] == (cRBorder)0x3e) {
              iVar4 = 0;
            }
            else {
              pcVar11 = this + iVar7 + 0x2c4;
              iVar4 = 0;
              do {
                iVar7 = iVar7 + -1;
                iVar4 = iVar4 + 1;
                if (iVar7 == 0) goto LAB_0003c050;
                pcVar11 = pcVar11 + -1;
              } while (*pcVar11 != (cRBorder)0x3e);
            }
LAB_0003c2f8:
            iVar7 = iVar7 + 1;
          }
          if (this[iVar5 + 0x2c4] != (cRBorder)0x0) {
            pcVar11 = this + iVar5 + 0x2c4;
            do {
              pcVar1 = pcVar11 + 1;
              *pcVar11 = *pcVar1;
              pcVar11 = pcVar11 + 1;
            } while (*pcVar1 != (cRBorder)0x0);
          }
          if (iVar6 < iVar4) {
            iVar4 = iVar6;
          }
          iVar7 = iVar7 + iVar4;
          *(int *)(this + 0x6f4) = iVar7;
          pcVar11 = this + iVar7 + 0x2c4;
          cVar2 = this[iVar7 + 0x2c4];
          do {
            cVar3 = pcVar11[1];
            bVar13 = cVar2 != (cRBorder)0x0;
            pcVar11 = pcVar11 + 1;
            *pcVar11 = cVar2;
            cVar2 = cVar3;
          } while (bVar13);
        }
        else if (cVar2 == (cRBorder)0x8) {
          iVar5 = *(int *)(this + 0x6f4);
          if (iVar5 < 1) {
            iVar7 = 0;
            iVar6 = iVar5;
LAB_0003c118:
            cVar2 = this[iVar6 + 0x2c4];
            if (cVar2 == (cRBorder)0x3e) goto LAB_0003c22c;
          }
          else {
            if (this[iVar5 + 0x2c4] == (cRBorder)0x3e) {
              iVar7 = -1;
              iVar4 = iVar5;
            }
            else {
              pcVar11 = this + iVar5 + 0x2c4;
              iVar7 = 0;
              do {
                iVar7 = iVar7 + 1;
                iVar6 = iVar5 - iVar7;
                if (iVar7 == iVar5) goto LAB_0003c118;
                pcVar11 = pcVar11 + -1;
              } while (*pcVar11 != (cRBorder)0x3e);
LAB_0003c22c:
              iVar7 = iVar7 + -1;
              iVar4 = iVar6;
            }
            iVar6 = iVar4 + 1;
            cVar2 = this[iVar4 + 0x2c5];
          }
          if (cVar2 != (cRBorder)0x0 && cVar2 != (cRBorder)0x3e) {
            pcVar11 = this + iVar6 + 0x2c4;
            do {
              pcVar11 = pcVar11 + 1;
              cVar2 = *pcVar11;
              iVar6 = iVar6 + 1;
            } while (cVar2 != (cRBorder)0x0 && cVar2 != (cRBorder)0x3e);
          }
          if (cVar2 != (cRBorder)0x3e) goto LAB_0003bce0;
          if (this[iVar6 + 0x2c5] == (cRBorder)0x0 || this[iVar6 + 0x2c5] == (cRBorder)0x3e) {
            iVar4 = 0;
          }
          else {
            pcVar11 = this + iVar6 + 0x2c4;
            iVar4 = 0;
            do {
              pcVar1 = pcVar11 + 2;
              iVar4 = iVar4 + 1;
              pcVar11 = pcVar11 + 1;
            } while (*pcVar1 != (cRBorder)0x0 && *pcVar1 != (cRBorder)0x3e);
          }
          if (this[iVar5 + 0x2c4] != (cRBorder)0x0) {
            pcVar11 = this + iVar5 + 0x2c4;
            do {
              pcVar1 = pcVar11 + 1;
              *pcVar11 = *pcVar1;
              pcVar11 = pcVar11 + 1;
            } while (*pcVar1 != (cRBorder)0x0);
          }
          if (iVar7 < iVar4) {
            iVar4 = iVar7;
          }
          iVar6 = iVar6 + iVar4;
          *(int *)(this + 0x6f4) = iVar6;
          pcVar11 = this + iVar6 + 0x2c4;
          cVar2 = this[iVar6 + 0x2c4];
          do {
            cVar3 = pcVar11[1];
            bVar13 = cVar2 != (cRBorder)0x0;
            pcVar11 = pcVar11 + 1;
            *pcVar11 = cVar2;
            cVar2 = cVar3;
          } while (bVar13);
        }
        else if (cVar2 == (cRBorder)0x9) {
          iVar7 = *(int *)(this + 0x6f4);
          cVar2 = this[iVar7 + 0x2c4];
          iVar5 = iVar7;
          if (cVar2 != (cRBorder)0x3e && cVar2 != (cRBorder)0x0) {
            pcVar11 = this + iVar7 + 0x2c4;
            do {
              pcVar11 = pcVar11 + 1;
              iVar5 = iVar5 + 1;
            } while (*pcVar11 != (cRBorder)0x0 && *pcVar11 != (cRBorder)0x3e);
          }
          if (cVar2 != (cRBorder)0x0) {
            pcVar11 = this + iVar7 + 0x2c4;
            do {
              pcVar1 = pcVar11 + 1;
              *pcVar11 = *pcVar1;
              pcVar11 = pcVar11 + 1;
            } while (*pcVar1 != (cRBorder)0x0);
          }
          *(int *)(this + 0x6f4) = iVar5 + -1;
          pcVar11 = this + iVar5 + 0x2c3;
          cVar2 = this[iVar5 + 0x2c3];
          do {
            cVar3 = pcVar11[1];
            bVar13 = cVar2 != (cRBorder)0x0;
            pcVar11 = pcVar11 + 1;
            *pcVar11 = cVar2;
            cVar2 = cVar3;
          } while (bVar13);
        }
        else {
          if (cVar2 != (cRBorder)0xa) {
            if (cVar2 == (cRBorder)0x1) {
              iVar5 = *(int *)(this + 0x6f4);
              if (0 < iVar5) {
                *(int *)(this + 0x6f4) = iVar5 + -1;
                if (this[iVar5 + 0x2c3] != (cRBorder)0x0) {
                  pcVar11 = this + iVar5 + 0x2c3;
                  do {
                    pcVar1 = pcVar11 + 1;
                    *pcVar11 = *pcVar1;
                    pcVar11 = pcVar11 + 1;
                  } while (*pcVar1 != (cRBorder)0x0);
                  uVar9 = *(uint *)(this + 0x704);
                }
                iVar5 = *(int *)(this + 0x6f4);
                uVar12 = uVar9 & 2;
                *(int *)(this + 0x708) = *(int *)(this + 0x708) + -1;
              }
            }
            else {
              if (cVar2 != (cRBorder)0x2) goto LAB_0003bb38;
              iVar5 = *(int *)(this + 0x6f4);
              iVar7 = *(int *)(this + 0x708);
              if (iVar5 < iVar7) {
                if (this[iVar5 + 0x2c4] != (cRBorder)0x0) {
                  pcVar11 = this + iVar5 + 0x2c4;
                  do {
                    pcVar1 = pcVar11 + 1;
                    *pcVar11 = *pcVar1;
                    pcVar11 = pcVar11 + 1;
                  } while (*pcVar1 != (cRBorder)0x0);
                  uVar9 = *(uint *)(this + 0x704);
                  iVar5 = *(int *)(this + 0x6f4);
                  iVar7 = *(int *)(this + 0x708);
                }
                uVar12 = uVar9 & 2;
                *(int *)(this + 0x708) = iVar7 + -1;
              }
            }
            goto LAB_0003bce0;
          }
          iVar7 = *(int *)(this + 0x6f4);
          iVar5 = iVar7;
          if (iVar7 < 1) {
            cVar2 = this[iVar7 + 0x2c4];
            cVar3 = cVar2;
LAB_0003c288:
            if (cVar3 == (cRBorder)0x3e) {
              cVar2 = this[iVar7 + 0x2c4];
              goto LAB_0003c360;
            }
          }
          else {
            cVar2 = this[iVar7 + 0x2c4];
            if (cVar2 == (cRBorder)0x3e) {
              iVar5 = iVar7 + 1;
            }
            else {
              pcVar11 = this + iVar7 + 0x2c4;
              do {
                iVar5 = iVar5 + -1;
                if (iVar5 == 0) {
                  cVar3 = this[0x2c4];
                  goto LAB_0003c288;
                }
                pcVar11 = pcVar11 + -1;
              } while (*pcVar11 != (cRBorder)0x3e);
LAB_0003c360:
              iVar5 = iVar5 + 1;
            }
          }
          if (cVar2 != (cRBorder)0x0) {
            pcVar11 = this + iVar7 + 0x2c4;
            do {
              pcVar1 = pcVar11 + 1;
              *pcVar11 = *pcVar1;
              pcVar11 = pcVar11 + 1;
            } while (*pcVar1 != (cRBorder)0x0);
          }
          *(int *)(this + 0x6f4) = iVar5;
          pcVar11 = this + iVar5 + 0x2c4;
          cVar2 = this[iVar5 + 0x2c4];
          do {
            cVar3 = pcVar11[1];
            bVar13 = cVar2 != (cRBorder)0x0;
            pcVar11 = pcVar11 + 1;
            *pcVar11 = cVar2;
            cVar2 = cVar3;
          } while (bVar13);
        }
        goto LAB_0003bbd4;
      }
      iVar5 = *(int *)(this + 0x6f4);
      if (iVar5 < *(int *)(this + 0x708)) {
        cVar2 = this[iVar5 + 0x2c4];
        this[iVar5 + 0x2c4] = this[iVar5 + 0x2c5];
        this[iVar5 + 0x2c5] = cVar2;
        iVar5 = *(int *)(this + 0x6f4) + 1;
        uVar12 = *(uint *)(this + 0x704) & 2;
        *(int *)(this + 0x6f4) = iVar5;
      }
    }
LAB_0003bce0:
    if (uVar12 != 0) goto LAB_0003bce8;
  }
  pcVar11 = this + 0x6fc;
  fVar14 = *(float *)pcVar11;
  *(float *)pcVar11 = fVar14 + *(float *)(this + 0x700);
  if (fVar14 + *(float *)(this + 0x700) <= 1.0) {
    if (*(int *)(this + 0x6f8) == 1) goto LAB_0003bdb0;
  }
  else {
    *(undefined4 *)pcVar11 = 0;
    if (*(int *)(this + 0x6f8) == 0) {
      *(undefined4 *)(this + 0x6f8) = 1;
LAB_0003bdb0:
      this[iVar5 + 0x2c4] = (cRBorder)0x7c;
      goto LAB_0003bdbc;
    }
    *(undefined4 *)(this + 0x6f8) = 0;
  }
  this[iVar5 + 0x2c4] = (cRBorder)0x20;
LAB_0003bdbc:
  cVar2 = this[0x2c4];
  if (cVar2 != (cRBorder)0x0) {
    pcVar11 = this + 0x2c4;
    iVar5 = 0;
    do {
      if (iVar5 == 0) {
        if ((byte)((char)cVar2 + 0x9fU) < 0x1a) {
          *pcVar11 = (cRBorder)((char)cVar2 + -0x20);
        }
LAB_0003bdec:
        cVar2 = pcVar11[iVar5 + 1];
      }
      else {
        if (*(int *)(this + 0x6f4) == iVar5 + -1) {
          if (iVar5 == 1) {
            if ((byte)((char)cVar2 + 0x9fU) < 0x1a) {
              this[0x2c5] = (cRBorder)((char)cVar2 + -0x20);
            }
          }
          else if (this[iVar5 + 0x2c2] == (cRBorder)0x20) goto LAB_0003be2c;
          goto LAB_0003bdec;
        }
        if (this[iVar5 + 0x2c3] != (cRBorder)0x20) goto LAB_0003bdec;
LAB_0003be2c:
        if ((byte)((char)cVar2 + 0x9fU) < 0x1a) {
          pcVar11[iVar5] = (cRBorder)((char)cVar2 + -0x20);
        }
        cVar2 = pcVar11[iVar5 + 1];
      }
      if (cVar2 == (cRBorder)0x0) break;
      iVar5 = iVar5 + 1;
    } while( true );
  }
  RePosition(this);
  return;
}
