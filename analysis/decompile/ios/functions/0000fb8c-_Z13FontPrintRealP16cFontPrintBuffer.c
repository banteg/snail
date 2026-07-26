/*
 * mangled: _Z13FontPrintRealP16cFontPrintBuffer
 * demangled: FontPrintReal(cFontPrintBuffer*)
 * address: 0000fb8c
 * size: 3044
 */

/* FontPrintReal(cFontPrintBuffer*) */

void FontPrintReal(cFontPrintBuffer *param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  char *pcVar4;
  int iVar5;
  int iVar6;
  char cVar7;
  int iVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  char cVar13;
  uint in_fpscr;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  char *local_4c;
  tColour atStack_48 [40];

  tColour::tColour(atStack_48);
  tColour::Set(atStack_48,0.0,0.0,0.0,0.8);
  iVar8 = *(int *)(param_1 + 0x48);
  fVar16 = *(float *)(param_1 + 4);
  if (iVar8 == 2) {
    local_4c = *(char **)(param_1 + 0x44);
    iVar8 = *(int *)(param_1 + 0x3c);
    cVar13 = *local_4c;
    if (cVar13 == '\0') {
      fVar16 = 0.0;
      fVar17 = *(float *)(&DAT_0026f228 + iVar8 * 0xa28);
      fVar3 = *(float *)(&DAT_0026f22c + iVar8 * 0xa28);
      fVar2 = (float)(&DAT_0026f238)[iVar8 * 0x28a];
    }
    else {
      fVar16 = 0.0;
      fVar17 = *(float *)(&DAT_0026f228 + iVar8 * 0xa28);
      fVar3 = *(float *)(&DAT_0026f22c + iVar8 * 0xa28);
      fVar2 = (float)(&DAT_0026f238)[iVar8 * 0x28a];
      pcVar4 = local_4c;
      cVar7 = cVar13;
      do {
        if ((byte)(cVar7 + 0xbfU) < 0x1a) {
          cVar1 = -0x26;
LAB_00010348:
          if ((byte)(cVar7 - 0x30U) < 10) {
LAB_0001035c:
            iVar5 = 0x36;
          }
          else {
            iVar5 = (int)(char)(cVar7 + cVar1);
          }
        }
        else {
          if ((byte)(cVar7 + 0x9fU) < 0x1a) {
            cVar1 = -0x60;
            goto LAB_00010348;
          }
          if ((byte)(cVar7 - 0x30U) < 10) goto LAB_0001035c;
          if (cVar7 == ' ') goto LAB_000102b8;
          if (cVar7 == '\"') {
            cVar7 = '@';
          }
          else if (cVar7 == ':') {
            cVar7 = 'B';
          }
          else if (cVar7 == '(') {
            cVar7 = 'C';
          }
          else if (cVar7 == ')') {
            cVar7 = 'D';
          }
          else if (cVar7 == '!') {
            cVar7 = 'E';
          }
          else if (cVar7 == '@') {
            cVar7 = 'F';
          }
          else if (cVar7 == '#') {
            cVar7 = 'G';
          }
          else if (cVar7 == '$') {
            cVar7 = 'H';
          }
          else if (cVar7 == '%') {
            cVar7 = 'I';
          }
          else if (cVar7 == '?') {
            cVar7 = 'J';
          }
          else if (cVar7 == '&') {
            cVar7 = 'K';
          }
          else if (cVar7 == '*') {
            cVar7 = 'L';
          }
          else if (cVar7 == '+') {
            cVar7 = 'M';
          }
          else if (cVar7 == '-') {
            cVar7 = 'O';
          }
          else if (cVar7 == '/') {
            cVar7 = 'P';
          }
          else if (cVar7 == '\\') {
            cVar7 = 'Q';
          }
          else if (cVar7 == ',') {
            cVar7 = 'R';
          }
          else if (cVar7 == '.') {
            cVar7 = 'S';
          }
          else if (cVar7 == '\'') {
            cVar7 = 'T';
          }
          else if (cVar7 == '|') {
            cVar7 = 'U';
          }
          else if (_RFontTypeSet == 1) {
            if (cVar7 == '[') {
              cVar7 = '_';
            }
            else if (cVar7 == '{') {
              cVar7 = '`';
            }
            else if (cVar7 == '}') {
              cVar7 = 'a';
            }
            else if (cVar7 == ']') {
              cVar7 = 'b';
            }
            else {
              cVar7 = '5';
            }
          }
          else if (_RFontTypeSet == 0) {
            if (cVar7 == '{') {
              cVar7 = 'V';
            }
            else if (cVar7 == '}') {
              cVar7 = 'W';
            }
            else if (cVar7 == '[') {
              cVar7 = 'X';
            }
            else if (cVar7 == ']') {
              cVar7 = 'Y';
            }
            else if (cVar7 == '~') {
              cVar7 = 'Z';
            }
            else if (cVar7 == ';') {
              cVar7 = '[';
            }
            else if (cVar7 == '_') {
              cVar7 = '\\';
            }
            else if (cVar7 == '^') {
              cVar7 = ']';
            }
            else {
              if (cVar7 != '=') goto LAB_000102b8;
              cVar7 = '^';
            }
          }
          else {
LAB_000102b8:
            cVar7 = '5';
          }
          iVar5 = (int)cVar7;
        }
        pcVar4 = pcVar4 + 1;
        cVar7 = *pcVar4;
        fVar16 = fVar16 + fVar2 * *(float *)(param_1 + 0x40) *
                                  fVar17 * *(float *)(&DAT_0026f01c + (iVar8 * 0x28a + iVar5) * 4) *
                                  fVar3;
      } while (cVar7 != '\0');
    }
    fVar16 = *(float *)(param_1 + 0x4c) + 320.0 +
             (fVar16 + fVar2 * *(float *)(param_1 + 0x40) *
                               fVar17 * *(float *)(&DAT_0026f0f0 + iVar8 * 0xa28) * (1.0 - fVar3)) *
             -0.5;
  }
  else if (iVar8 == 1) {
    local_4c = *(char **)(param_1 + 0x44);
    cVar13 = *local_4c;
    pcVar4 = local_4c;
    cVar7 = cVar13;
    while (cVar7 != '\0') {
      pcVar4 = pcVar4 + 1;
      cVar7 = *pcVar4;
    }
    fVar16 = *(float *)(param_1 + 0x4c) + 320.0;
  }
  else if (iVar8 == 3) {
    local_4c = *(char **)(param_1 + 0x44);
    iVar8 = *(int *)(param_1 + 0x3c);
    cVar13 = *local_4c;
    if (cVar13 == '\0') {
      fVar16 = 0.0;
      fVar17 = *(float *)(&DAT_0026f228 + iVar8 * 0xa28);
      fVar2 = *(float *)(&DAT_0026f22c + iVar8 * 0xa28);
      fVar3 = (float)(&DAT_0026f238)[iVar8 * 0x28a];
    }
    else {
      fVar16 = 0.0;
      fVar17 = *(float *)(&DAT_0026f228 + iVar8 * 0xa28);
      fVar2 = *(float *)(&DAT_0026f22c + iVar8 * 0xa28);
      fVar3 = (float)(&DAT_0026f238)[iVar8 * 0x28a];
      pcVar4 = local_4c;
      cVar7 = cVar13;
      do {
        if ((byte)(cVar7 + 0xbfU) < 0x1a) {
          cVar1 = -0x26;
LAB_00010650:
          if ((byte)(cVar7 - 0x30U) < 10) {
LAB_00010664:
            iVar5 = 0x36;
          }
          else {
            iVar5 = (int)(char)(cVar7 + cVar1);
          }
        }
        else {
          if ((byte)(cVar7 + 0x9fU) < 0x1a) {
            cVar1 = -0x60;
            goto LAB_00010650;
          }
          if ((byte)(cVar7 - 0x30U) < 10) goto LAB_00010664;
          if (cVar7 == ' ') goto LAB_000105c4;
          if (cVar7 == '\"') {
            cVar7 = '@';
          }
          else if (cVar7 == ':') {
            cVar7 = 'B';
          }
          else if (cVar7 == '(') {
            cVar7 = 'C';
          }
          else if (cVar7 == ')') {
            cVar7 = 'D';
          }
          else if (cVar7 == '!') {
            cVar7 = 'E';
          }
          else if (cVar7 == '@') {
            cVar7 = 'F';
          }
          else if (cVar7 == '#') {
            cVar7 = 'G';
          }
          else if (cVar7 == '$') {
            cVar7 = 'H';
          }
          else if (cVar7 == '%') {
            cVar7 = 'I';
          }
          else if (cVar7 == '?') {
            cVar7 = 'J';
          }
          else if (cVar7 == '&') {
            cVar7 = 'K';
          }
          else if (cVar7 == '*') {
            cVar7 = 'L';
          }
          else if (cVar7 == '+') {
            cVar7 = 'M';
          }
          else if (cVar7 == '-') {
            cVar7 = 'O';
          }
          else if (cVar7 == '/') {
            cVar7 = 'P';
          }
          else if (cVar7 == '\\') {
            cVar7 = 'Q';
          }
          else if (cVar7 == ',') {
            cVar7 = 'R';
          }
          else if (cVar7 == '.') {
            cVar7 = 'S';
          }
          else if (cVar7 == '\'') {
            cVar7 = 'T';
          }
          else if (cVar7 == '|') {
            cVar7 = 'U';
          }
          else if (_RFontTypeSet == 1) {
            if (cVar7 == '[') {
              cVar7 = '_';
            }
            else if (cVar7 == '{') {
              cVar7 = '`';
            }
            else if (cVar7 == '}') {
              cVar7 = 'a';
            }
            else if (cVar7 == ']') {
              cVar7 = 'b';
            }
            else {
              cVar7 = '5';
            }
          }
          else if (_RFontTypeSet == 0) {
            if (cVar7 == '{') {
              cVar7 = 'V';
            }
            else if (cVar7 == '}') {
              cVar7 = 'W';
            }
            else if (cVar7 == '[') {
              cVar7 = 'X';
            }
            else if (cVar7 == ']') {
              cVar7 = 'Y';
            }
            else if (cVar7 == '~') {
              cVar7 = 'Z';
            }
            else if (cVar7 == ';') {
              cVar7 = '[';
            }
            else if (cVar7 == '_') {
              cVar7 = '\\';
            }
            else if (cVar7 == '^') {
              cVar7 = ']';
            }
            else {
              if (cVar7 != '=') goto LAB_000105c4;
              cVar7 = '^';
            }
          }
          else {
LAB_000105c4:
            cVar7 = '5';
          }
          iVar5 = (int)cVar7;
        }
        pcVar4 = pcVar4 + 1;
        cVar7 = *pcVar4;
        fVar16 = fVar16 + fVar3 * *(float *)(param_1 + 0x40) *
                                  fVar2 * fVar17 * *(float *)(&DAT_0026f01c +
                                                             (iVar8 * 0x28a + iVar5) * 4);
      } while (cVar7 != '\0');
    }
    fVar16 = (*(float *)(param_1 + 0x4c) + 320.0) -
             (fVar16 + fVar3 * *(float *)(param_1 + 0x40) *
                               fVar17 * *(float *)(&DAT_0026f0f0 + iVar8 * 0xa28) * (1.0 - fVar2));
  }
  else {
    local_4c = *(char **)(param_1 + 0x44);
    cVar13 = *local_4c;
  }
  if (cVar13 == '\0') {
    return;
  }
  fVar17 = 0.0;
  iVar8 = *(int *)(param_1 + 0x3c);
  do {
    iVar5 = (int)cVar13;
    if ((byte)(cVar13 + 0xbfU) < 0x1a) {
      iVar5 = iVar5 + -0x26;
    }
    else if ((byte)(cVar13 + 0x9fU) < 0x1a) {
      iVar5 = iVar5 + -0x60;
    }
    else if ((byte)(cVar13 - 0x30U) < 10) {
      iVar5 = iVar5 + 6;
    }
    else {
      if (iVar5 == 0x20) goto LAB_0000fdc4;
      if (iVar5 == 0x22) {
        iVar5 = 0x40;
      }
      else if (iVar5 == 0x3a) {
        iVar5 = 0x42;
      }
      else if (iVar5 == 0x28) {
        iVar5 = 0x43;
      }
      else if (iVar5 == 0x29) {
        iVar5 = 0x44;
      }
      else if (iVar5 == 0x21) {
        iVar5 = 0x45;
      }
      else if (iVar5 == 0x40) {
        iVar5 = 0x46;
      }
      else if (iVar5 == 0x23) {
        iVar5 = 0x47;
      }
      else if (iVar5 == 0x24) {
        iVar5 = 0x48;
      }
      else if (iVar5 == 0x25) {
        iVar5 = 0x49;
      }
      else if (iVar5 == 0x3f) {
        iVar5 = 0x4a;
      }
      else if (iVar5 == 0x26) {
        iVar5 = 0x4b;
      }
      else if (iVar5 == 0x2a) {
        iVar5 = 0x4c;
      }
      else if (iVar5 == 0x2b) {
        iVar5 = 0x4d;
      }
      else if (iVar5 == 0x2d) {
        iVar5 = 0x4f;
      }
      else if (iVar5 == 0x2f) {
        iVar5 = 0x50;
      }
      else if (iVar5 == 0x5c) {
        iVar5 = 0x51;
      }
      else if (iVar5 == 0x2c) {
        iVar5 = 0x52;
      }
      else if (iVar5 == 0x2e) {
        iVar5 = 0x53;
      }
      else if (iVar5 == 0x27) {
        iVar5 = 0x54;
      }
      else if (iVar5 == 0x7c) {
        iVar5 = 0x55;
      }
      else if (_RFontTypeSet == 1) {
        if (iVar5 == 0x5b) {
          iVar5 = 0x5f;
        }
        else if (iVar5 == 0x7b) {
          iVar5 = 0x60;
        }
        else if (iVar5 == 0x7d) {
          iVar5 = 0x61;
        }
        else if (iVar5 == 0x5d) {
          iVar5 = 0x62;
        }
        else {
          iVar5 = 0x35;
        }
      }
      else if (_RFontTypeSet == 0) {
        if (iVar5 == 0x7b) {
          iVar5 = 0x56;
        }
        else if (iVar5 == 0x7d) {
          iVar5 = 0x57;
        }
        else if (iVar5 == 0x5b) {
          iVar5 = 0x58;
        }
        else if (iVar5 == 0x5d) {
          iVar5 = 0x59;
        }
        else if (iVar5 == 0x7e) {
          iVar5 = 0x5a;
        }
        else if (iVar5 == 0x3b) {
          iVar5 = 0x5b;
        }
        else if (iVar5 == 0x5f) {
          iVar5 = 0x5c;
        }
        else if (iVar5 == 0x5e) {
          iVar5 = 0x5d;
        }
        else {
          if (iVar5 != 0x3d) goto LAB_0000fdc4;
          iVar5 = 0x5e;
        }
      }
      else {
LAB_0000fdc4:
        iVar5 = 0x35;
      }
    }
    iVar8 = (iVar8 * 0x28a + iVar5) * 4;
    fVar14 = *(float *)(param_1 + 0x34);
    fVar9 = *(float *)(&DAT_0026e81c + iVar8);
    fVar11 = *(float *)(&DAT_0026ea1c + iVar8);
    fVar12 = *(float *)(&DAT_0026ec1c + iVar8);
    fVar10 = *(float *)(&DAT_0026ee1c + iVar8);
    fVar2 = (float)Sin(fVar17 + _FontWibbleX);
    fVar15 = *(float *)(param_1 + 0x34);
    fVar3 = (float)Cos(_FontWibbleX + fVar17 * 3.0);
    if (iVar5 != 0x35) {
      iVar6 = *(int *)(param_1 + 0x3c);
      iVar8 = iVar6 * 0xa28;
      fVar3 = (float)VectorSignedToFloat((int)(*(float *)(param_1 + 8) + fVar15 * 4.0 * fVar3),
                                         (byte)(in_fpscr >> 0x16) & 3);
      fVar2 = (float)VectorSignedToFloat((int)(fVar16 + (fVar14 + fVar14) * fVar2),
                                         (byte)(in_fpscr >> 0x16) & 3);
      G0RenderFont(*(cRTexture **)(&DAT_0026e818 + iVar8),fVar2,fVar3,0.0,0.0,0.0,0.0,0.0,0.0,
                   *(float *)(&DAT_0026f228 + iVar8) *
                   *(float *)(&DAT_0026f01c + (iVar6 * 0x28a + iVar5) * 4) *
                   *(float *)(param_1 + 0x40) * (float)(&DAT_0026f238)[iVar6 * 0x28a],
                   (*(float *)(param_1 + 0x40) *
                   *(float *)(&DAT_0026f228 + iVar8) * *(float *)(&DAT_0026f21c + iVar8)) /
                   (float)(&DAT_0026f238)[iVar6 * 0x28a],fVar9,fVar11,fVar12,fVar10,
                   (tColour *)(param_1 + 0x6c),7,0.0);
    }
    if ((byte)(*local_4c - 0x30U) < 10) {
      iVar8 = *(int *)(param_1 + 0x3c);
      iVar6 = iVar8 * 0xa28;
      fVar2 = (float)VectorSignedToFloat((int)*(float *)(&DAT_0026f0f4 + iVar6),
                                         (byte)(in_fpscr >> 0x16) & 3);
    }
    else {
      iVar8 = *(int *)(param_1 + 0x3c);
      iVar6 = iVar8 * 0xa28;
      fVar2 = (float)VectorSignedToFloat((int)*(float *)(&DAT_0026f01c + (iVar8 * 0x28a + iVar5) * 4
                                                        ),(byte)(in_fpscr >> 0x16) & 3);
    }
    local_4c = local_4c + 1;
    cVar13 = *local_4c;
    fVar16 = fVar16 + fVar2 * *(float *)(&DAT_0026f228 + iVar6) * *(float *)(&DAT_0026f22c + iVar6)
                      * *(float *)(param_1 + 0x40) * *(float *)((int)&DAT_0026f238 + iVar6);
    if (cVar13 == '\0') {
      return;
    }
    fVar17 = fVar17 + 1.0;
  } while( true );
}
