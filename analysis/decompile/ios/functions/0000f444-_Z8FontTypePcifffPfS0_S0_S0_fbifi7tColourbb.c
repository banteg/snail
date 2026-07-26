/*
 * mangled: _Z8FontTypePcifffPfS0_S0_S0_fbifi7tColourbb
 * demangled: FontType(char*, int, float, float, float, float*, float*, float*, float*, float, bool, int, float, int, tColour, bool, bool)
 * address: 0000f444
 * size: 1808
 */

/* WARNING: Restarted to delay deadcode elimination for space: stack */
/* FontType(char*, int, float, float, float, float*, float*, float*, float*, float, bool, int,
   float, int, tColour, bool, bool) */

void FontType(char *param_1,int param_2,float param_3,float param_4,undefined4 param_5,
             float *param_6,float *param_7,float *param_8,float *param_9,undefined4 param_10,
             undefined1 param_11,int param_12,undefined4 param_13,uint param_14,undefined4 param_15,
             undefined4 param_16,undefined4 param_17,undefined4 param_18,char param_19,char param_20
             )

{
  char cVar1;
  int iVar2;
  char cVar3;
  char *pcVar4;
  char *pcVar5;
  char *pcVar6;
  char cVar7;
  int iVar8;
  char *pcVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  undefined8 uVar16;
  char local_458 [1024];
  undefined4 local_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined4 local_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 local_3c;

  uVar16 = CONCAT44(param_13,param_5);
  tColour::tColour((tColour *)&local_48);
  fVar14 = (float)uVar16;
  local_48 = param_15;
  uStack_44 = param_16;
  uStack_40 = param_17;
  local_3c = param_18;
  pcVar5 = local_458;
  fVar15 = param_4;
  do {
    cVar1 = *param_1;
    if (cVar1 == '\0' || cVar1 == '>') {
      *pcVar5 = '\0';
      if (local_458 == pcVar5) {
        fVar12 = *(float *)(&DAT_0026f228 + param_2 * 0xa28);
        fVar13 = (float)(&DAT_0026f238)[param_2 * 0x28a];
      }
      else {
        if (local_458[0] == '\0') {
          fVar10 = 0.0;
          fVar12 = *(float *)(&DAT_0026f228 + param_2 * 0xa28);
          fVar11 = *(float *)(&DAT_0026f22c + param_2 * 0xa28);
          fVar13 = (float)(&DAT_0026f238)[param_2 * 0x28a];
        }
        else {
          fVar10 = 0.0;
          pcVar5 = local_458;
          fVar12 = *(float *)(&DAT_0026f228 + param_2 * 0xa28);
          fVar11 = *(float *)(&DAT_0026f22c + param_2 * 0xa28);
          fVar13 = (float)(&DAT_0026f238)[param_2 * 0x28a];
          cVar7 = local_458[0];
          do {
            if ((byte)(cVar7 + 0xbfU) < 0x1a) {
              cVar3 = -0x26;
LAB_0000f99c:
              if ((byte)(cVar7 - 0x30U) < 10) {
LAB_0000f9b0:
                iVar8 = 0x36;
              }
              else {
                iVar8 = (int)(char)(cVar7 + cVar3);
              }
            }
            else {
              if ((byte)(cVar7 + 0x9fU) < 0x1a) {
                cVar3 = -0x60;
                goto LAB_0000f99c;
              }
              if ((byte)(cVar7 - 0x30U) < 10) goto LAB_0000f9b0;
              if (cVar7 == ' ') goto LAB_0000f724;
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
                  if (cVar7 != '=') goto LAB_0000f724;
                  cVar7 = '^';
                }
              }
              else {
LAB_0000f724:
                cVar7 = '5';
              }
              iVar8 = (int)cVar7;
            }
            pcVar5 = pcVar5 + 1;
            cVar7 = *pcVar5;
            fVar10 = fVar10 + fVar13 * param_3 * fVar11 * fVar12 * *(float *)(&DAT_0026f01c +
                                                                             (param_2 * 0x28a +
                                                                             iVar8) * 4);
          } while (cVar7 != '\0');
        }
        fVar10 = fVar15 + fVar10 + fVar13 * param_3 * fVar12 * *(float *)(&DAT_0026f0f0 +
                                                                         param_2 * 0xa28) *
                                                      (1.0 - fVar11);
        if (fVar10 <= param_4) {
          fVar10 = param_4;
        }
        param_4 = fVar10;
        if (param_19 == '\0') {
          if (param_20 != '\0') {
            local_3c = Sin((fVar14 * 3.1415927) / 480.0);
          }
          iVar8 = _FontPrintIndex;
          local_58 = local_48;
          uStack_54 = uStack_44;
          uStack_50 = uStack_40;
          uStack_4c = local_3c;
          param_4 = fVar10;
          if ((*PTR__G0RenderNextFlag_001b60f4 == '\0') || (_FontPrintIndex == 0x200)) {
            fVar12 = *(float *)(&DAT_0026f228 + param_2 * 0xa28);
            fVar13 = (float)(&DAT_0026f238)[param_2 * 0x28a];
          }
          else {
            iVar2 = _FontPrintIndex * 0x84;
            *(uint *)(&_FontPrintBuffer + iVar2) = param_14 | 1;
            *(int *)(&DAT_00270e78 + iVar2) = param_2;
            *(float *)(&DAT_00270e7c + iVar2) = param_3;
            *(float *)(&DAT_00270e40 + iVar2) = fVar15;
            *(float *)(&DAT_00270e44 + iVar2) = fVar14;
            *(int *)(&DAT_00270e88 + iVar2) = (int)((ulonglong)uVar16 >> 0x20);
            *(int *)(&DAT_00270e84 + iVar2) = param_12;
            pcVar5 = _FontPrintBufferIndex;
            *(char **)(&DAT_00270e80 + iVar2) = _FontPrintBufferIndex;
            *(undefined4 *)(&DAT_00270ea8 + iVar2) = local_48;
            *(undefined4 *)(&DAT_00270eac + iVar2) = uStack_44;
            *(undefined4 *)(&DAT_00270eb0 + iVar2) = uStack_40;
            *(undefined4 *)(&DAT_00270eb4 + iVar2) = local_3c;
            *(undefined4 *)(&DAT_00270e70 + iVar2) = param_10;
            (&DAT_00270e74)[iVar2] = param_11;
            if (local_458[0] == '\0') {
LAB_0000f8f4:
              *_FontPrintBufferIndex = '\0';
              _FontPrintIndex = iVar8 + 1;
            }
            else {
              pcVar4 = pcVar5 + -0x270a3c;
              if ((int)pcVar4 < 0x3ff) {
                pcVar6 = local_458;
                pcVar9 = pcVar5;
                cVar7 = local_458[0];
                do {
                  pcVar5 = pcVar9 + 1;
                  *pcVar9 = cVar7;
                  cVar7 = pcVar6[1];
                  _FontPrintBufferIndex = pcVar5;
                  if (cVar7 == '\0') goto LAB_0000f8f4;
                  pcVar4 = pcVar4 + 1;
                  pcVar6 = pcVar6 + 1;
                  pcVar9 = pcVar5;
                } while ((int)pcVar4 < 0x3ff);
              }
              *pcVar5 = '\0';
              _FontPrintBufferIndex = pcVar5;
            }
            _FontPrintBufferIndex = _FontPrintBufferIndex + 1;
            fVar12 = *(float *)(&DAT_0026f228 + param_2 * 0xa28);
            fVar13 = (float)(&DAT_0026f238)[param_2 * 0x28a];
          }
        }
      }
      pcVar4 = local_458;
      fVar14 = fVar14 + (fVar12 * *(float *)(&DAT_0026f21c + param_2 * 0xa28) *
                         *(float *)(&DAT_0026f230 + param_2 * 0xa28) * param_3) / fVar13;
    }
    else {
      pcVar4 = pcVar5 + 1;
      *pcVar5 = cVar1;
    }
    if (cVar1 == '\0') {
      if (param_6 != (float *)0x0) {
        *param_6 = fVar15;
        *param_7 = (float)uVar16;
        *param_8 = param_4 - fVar15;
        *param_9 = fVar14 - (float)uVar16;
        fVar15 = (float)((ulonglong)uVar16 >> 0x20);
        if (param_12 == 1) {
          *param_6 = fVar15 + 320.0;
        }
        else if (param_12 == 3) {
          *param_6 = (fVar15 + 320.0) - *param_8;
        }
        else if (param_12 == 2) {
          *param_6 = fVar15 + 320.0 + *param_8 * -0.5;
        }
      }
      return;
    }
    param_1 = param_1 + 1;
    pcVar5 = pcVar4;
  } while( true );
}
