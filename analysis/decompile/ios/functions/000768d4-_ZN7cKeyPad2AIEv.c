/*
 * mangled: _ZN7cKeyPad2AIEv
 * demangled: cKeyPad::AI()
 * address: 000768d4
 * size: 1412
 */

/* cKeyPad::AI() */

void __thiscall cKeyPad::AI(cKeyPad *this)

{
  char cVar1;
  cKeyPad cVar2;
  undefined *this_00;
  uchar uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int *piVar7;
  int iVar8;
  uint in_fpscr;
  float fVar9;
  float fVar10;
  float fVar11;

  this_00 = PTR__gRSound_001b61e0;
  switch(*(undefined4 *)this) {
  case 0:
    goto switchD_000768ec_caseD_0;
  case 1:
    fVar11 = *(float *)(this + 0xc);
    *(float *)(this + 0xc) = fVar11 + *(float *)(this + 0x10);
    if (1.0 < fVar11 + *(float *)(this + 0x10)) {
      *(undefined4 *)(this + 0xc) = 0x3f800000;
      *(undefined4 *)this = 2;
    }
    break;
  case 2:
    iVar6 = *(int *)PTR__Game_001b60b8;
    if ((*(uint *)(*(int *)(iVar6 + 0x224) + 0x30) & 0x4000) != 0) {
      if (0 < *(int *)(this + 8)) {
        piVar7 = *(int **)(this + 4);
        iVar8 = 0;
        do {
          if ((((*piVar7 < (int)*(float *)(iVar6 + 0x234)) &&
               ((int)*(float *)(iVar6 + 0x234) < piVar7[2])) &&
              (piVar7[1] < (int)*(float *)(iVar6 + 0x238))) &&
             ((int)*(float *)(iVar6 + 0x238) < piVar7[3])) {
            cVar1 = (char)piVar7[4];
            if (cVar1 != '\0') {
              iVar6 = (int)cVar1;
              cRSound::Play((cRSound *)PTR__gRSound_001b61e0,8);
              if (cVar1 == '#') {
                cRSound::Play((cRSound *)this_00,0x19);
                *(undefined4 *)this = 3;
              }
              else {
                wprintf("KeyPad %c\n",iVar6);
                if (iVar6 == 0x61) {
                  uVar3 = '\x1e';
                }
                else if (iVar6 == 0x62) {
                  uVar3 = '0';
                }
                else if (iVar6 == 99) {
                  uVar3 = '.';
                }
                else if (iVar6 == 100) {
                  uVar3 = ' ';
                }
                else if (iVar6 == 0x65) {
                  uVar3 = '\x12';
                }
                else if (iVar6 == 0x66) {
                  uVar3 = '!';
                }
                else if (iVar6 == 0x67) {
                  uVar3 = '\"';
                }
                else if (iVar6 == 0x68) {
                  uVar3 = '#';
                }
                else if (iVar6 == 0x69) {
                  uVar3 = '\x17';
                }
                else if (iVar6 == 0x6a) {
                  uVar3 = '$';
                }
                else if (iVar6 == 0x6b) {
                  uVar3 = '%';
                }
                else if (iVar6 == 0x6c) {
                  uVar3 = '&';
                }
                else if (iVar6 == 0x6d) {
                  uVar3 = '2';
                }
                else if (iVar6 == 0x6e) {
                  uVar3 = '1';
                }
                else if (iVar6 == 0x6f) {
                  uVar3 = '\x18';
                }
                else if (iVar6 == 0x70) {
                  uVar3 = '\x19';
                }
                else if (iVar6 == 0x71) {
                  uVar3 = '\x10';
                }
                else if (iVar6 == 0x72) {
                  uVar3 = '\x13';
                }
                else if (iVar6 == 0x73) {
                  uVar3 = '\x1f';
                }
                else if (iVar6 == 0x74) {
                  uVar3 = '\x14';
                }
                else if (iVar6 == 0x75) {
                  uVar3 = '\x16';
                }
                else if (iVar6 == 0x76) {
                  uVar3 = '/';
                }
                else if (iVar6 == 0x77) {
                  uVar3 = '\x11';
                }
                else if (iVar6 == 0x78) {
                  uVar3 = '-';
                }
                else if (iVar6 == 0x79) {
                  uVar3 = '\x15';
                }
                else if (iVar6 == 0x7a) {
                  uVar3 = ',';
                }
                else if (iVar6 == 0x30) {
                  uVar3 = '\v';
                }
                else if (iVar6 == 0x31) {
                  uVar3 = '\x02';
                }
                else if (iVar6 == 0x32) {
                  uVar3 = '\x03';
                }
                else if (iVar6 == 0x33) {
                  uVar3 = '\x04';
                }
                else if (iVar6 == 0x34) {
                  uVar3 = '\x05';
                }
                else if (iVar6 == 0x35) {
                  uVar3 = '\x06';
                }
                else if (iVar6 == 0x36) {
                  uVar3 = '\a';
                }
                else if (iVar6 == 0x37) {
                  uVar3 = '\b';
                }
                else if (iVar6 == 0x38) {
                  uVar3 = '\t';
                }
                else if (iVar6 == 0x39) {
                  uVar3 = '\n';
                }
                else if (iVar6 == 0x20) {
                  uVar3 = '9';
                }
                else if (iVar6 == 0x21) {
                  this[0x120] = (cKeyPad)0x1;
                  uVar3 = '\0';
                }
                else if (iVar6 == 0x40) {
                  uVar3 = '\x0e';
                }
                else {
                  uVar3 = '\0';
                }
                KeySet(uVar3);
              }
            }
            if (iVar8 == -1) break;
            iVar6 = iVar8 * 0x14 + *(int *)(this + 4);
            iVar4 = *(int *)(iVar8 * 0x14 + *(int *)(this + 4));
            iVar8 = *(int *)(iVar6 + 4);
            fVar10 = (float)VectorSignedToFloat(iVar4,(byte)(in_fpscr >> 0x16) & 3);
            fVar9 = (float)VectorSignedToFloat(iVar8,(byte)(in_fpscr >> 0x16) & 3);
            iVar5 = *(int *)(iVar6 + 0xc);
            fVar11 = (float)VectorSignedToFloat(*(int *)(iVar6 + 8) - iVar4,
                                                (byte)(in_fpscr >> 0x16) & 3);
            iVar6 = 0;
            if (*(int *)(this + 0x20) != 0) {
              if (*(int *)(this + 0x40) == 0) {
                iVar6 = 1;
              }
              else if (*(int *)(this + 0x60) == 0) {
                iVar6 = 2;
              }
              else if (*(int *)(this + 0x80) == 0) {
                iVar6 = 3;
              }
              else if (*(int *)(this + 0xa0) == 0) {
                iVar6 = 4;
              }
              else if (*(int *)(this + 0xc0) == 0) {
                iVar6 = 5;
              }
              else if (*(int *)(this + 0xe0) == 0) {
                iVar6 = 6;
              }
              else {
                if (*(int *)(this + 0x100) != 0) break;
                iVar6 = 7;
              }
            }
            *(undefined4 *)(this + (iVar6 + 1) * 0x20) = 1;
            *(undefined4 *)(this + iVar6 * 0x20 + 0x24) = 0;
            *(float *)(this + iVar6 * 0x20 + 0x2c) = fVar10 + 8.0;
            *(undefined4 *)(this + iVar6 * 0x20 + 0x28) = 0x3d3da12f;
            *(float *)(this + iVar6 * 0x20 + 0x30) = fVar9 + 9.0;
            *(float *)(this + iVar6 * 0x20 + 0x34) = fVar11 - 16.0;
            fVar11 = (float)VectorSignedToFloat(iVar5 - iVar8,(byte)(in_fpscr >> 0x16) & 3);
            *(float *)(this + iVar6 * 0x20 + 0x38) = fVar11 - 18.0;
            break;
          }
          iVar8 = iVar8 + 1;
          piVar7 = piVar7 + 5;
        } while (iVar8 != *(int *)(this + 8));
      }
    }
    break;
  case 3:
    fVar11 = *(float *)(this + 0xc);
    *(float *)(this + 0xc) = fVar11 - *(float *)(this + 0x10);
    if (fVar11 - *(float *)(this + 0x10) < 0.0) {
      *(undefined4 *)(this + 0xc) = 0;
      *(undefined4 *)this = 0;
    }
    cVar2 = this[0x120];
    goto joined_r0x00076af4;
  }
  cVar2 = this[0x120];
joined_r0x00076af4:
  if (cVar2 != (cKeyPad)0x0) {
    KeySet('*');
  }
  *(float *)(this + 0x18) =
       *(float *)(this + 0xc) * *(float *)(this + 0x14) + (1.0 - *(float *)(this + 0xc)) * 480.0;
  if (*(int *)(this + 0x20) == 1) {
    cGlow::AI((cGlow *)(this + 0x20));
  }
  if (*(int *)(this + 0x40) == 1) {
    cGlow::AI((cGlow *)(this + 0x40));
    iVar6 = *(int *)(this + 0x60);
  }
  else {
    iVar6 = *(int *)(this + 0x60);
  }
  if (iVar6 == 1) {
    cGlow::AI((cGlow *)(this + 0x60));
  }
  if (*(int *)(this + 0x80) == 1) {
    cGlow::AI((cGlow *)(this + 0x80));
    if (*(int *)(this + 0xa0) != 1) goto LAB_00076a98;
LAB_00076be0:
    cGlow::AI((cGlow *)(this + 0xa0));
    if (*(int *)(this + 0xc0) != 1) goto LAB_00076aa4;
LAB_00076bf4:
    cGlow::AI((cGlow *)(this + 0xc0));
    iVar6 = *(int *)(this + 0xe0);
  }
  else {
    if (*(int *)(this + 0xa0) == 1) goto LAB_00076be0;
LAB_00076a98:
    if (*(int *)(this + 0xc0) == 1) goto LAB_00076bf4;
LAB_00076aa4:
    iVar6 = *(int *)(this + 0xe0);
  }
  if (iVar6 == 1) {
    cGlow::AI((cGlow *)(this + 0xe0));
  }
  if (*(int *)(this + 0x100) == 1) {
    cGlow::AI((cGlow *)(this + 0x100));
    return;
  }
switchD_000768ec_caseD_0:
  return;
}
