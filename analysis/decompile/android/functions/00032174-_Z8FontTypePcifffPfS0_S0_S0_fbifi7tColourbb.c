/*
 * mangled: _Z8FontTypePcifffPfS0_S0_S0_fbifi7tColourbb
 * demangled: FontType(char*, int, float, float, float, float*, float*, float*, float*, float, bool, int, float, int, tColour, bool, bool)
 * address: 00032174
 * size: 772
 */

/* FontType(char*, int, float, float, float, float*, float*, float*, float*, float, bool, int,
   float, int, tColour, bool, bool) */

void FontType(int param_1,int param_2,float param_6,float param_7,float param_8,float *param_9,
             float *param_11,float *param_12,float *param_14,undefined4 param_10,byte param_11_00,
             int param_12_00,float param_13,undefined4 param_14_00,undefined4 param_15,
             undefined4 param_16,undefined4 param_17,undefined4 param_18,byte param_19,byte param_20
             )

{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  char cVar6;
  int iVar7;
  int iVar8;
  char *pcVar9;
  float fVar10;
  float extraout_s0;
  float fVar11;
  float fVar12;
  undefined4 local_4b0 [4];
  undefined4 local_4a0;
  uint local_49c;
  undefined4 *local_494;
  tColour *local_490;
  int local_48c;
  uint local_488;
  float *local_484;
  int local_480;
  float *local_47c;
  uint local_478;
  uint local_474;
  float *local_470;
  float *local_46c;
  undefined4 local_464;
  undefined4 uStack_460;
  undefined4 uStack_45c;
  undefined4 local_458;
  char cStack_454;
  char local_453 [1023];
  int local_54;

  local_480 = 0x1d4;
  local_54 = __stack_chk_guard;
  local_490 = (tColour *)&local_464;
  local_470 = param_11;
  local_474 = (uint)param_20;
  local_484 = param_9;
  local_494 = local_4b0;
  local_46c = param_14;
  local_488 = (uint)param_19;
  iVar7 = 0;
  local_478 = (uint)param_11_00;
  local_47c = param_12;
  fVar10 = (float)tColour::tColour(local_490);
  local_48c = 0x268;
  local_464 = param_15;
  uStack_460 = param_16;
  uStack_45c = param_17;
  local_458 = param_18;
  pcVar9 = &cStack_454;
  fVar11 = param_8;
  fVar12 = param_7;
  do {
    for (; cVar6 = *(char *)(param_1 + iVar7), cVar6 != '>' && cVar6 != '\0'; iVar7 = iVar7 + 1) {
      *pcVar9 = cVar6;
      pcVar9 = pcVar9 + 1;
    }
    do {
      iVar8 = iVar7;
      *pcVar9 = '\0';
      if (pcVar9 != &cStack_454) {
        fVar10 = (float)FontGetStringX(&cStack_454,param_2,fVar10);
        if (fVar12 < param_7 + fVar10) {
          fVar12 = param_7 + fVar10;
        }
        fVar10 = extraout_s0;
        if (local_488 == 0) {
          if (local_474 != 0) {
            local_458 = Sin(extraout_s0);
          }
          puVar1 = local_494;
          uVar2 = *(undefined4 *)(local_490 + 4);
          uVar3 = *(undefined4 *)(local_490 + 8);
          uVar4 = *(undefined4 *)(local_490 + 0xc);
          *local_494 = *(undefined4 *)local_490;
          puVar1[1] = uVar2;
          puVar1[2] = uVar3;
          puVar1[3] = uVar4;
          local_4a0 = param_10;
          local_49c = local_478;
          fVar10 = (float)FontPrint(&cStack_454,param_2,param_6,param_7,fVar11,param_12_00,param_13,
                                    param_14_00);
        }
      }
      iVar7 = iVar8 + 1;
      iVar5 = *(int *)((int)&__DT_PLTGOT + local_48c) + param_2 * 0xa28;
      fVar11 = fVar11 + (*(float *)(iVar5 + 0xa08) * *(float *)(iVar5 + 0xa14) *
                         *(float *)(iVar5 + 0xa1c) * param_6) / *(float *)(iVar5 + 0xa24);
      if (cVar6 == '\0') {
        if (local_484 != (float *)0x0) {
          *local_484 = param_7;
          *local_470 = param_8;
          *local_47c = fVar12 - param_7;
          *local_46c = fVar11 - param_8;
          if (param_12_00 == 1) {
            *local_484 = param_13 + 320.0;
          }
          else if (param_12_00 == 3) {
            *local_484 = (param_13 + 320.0) - *local_47c;
          }
          else if (param_12_00 == 2) {
            *local_484 = param_13 + 320.0 + *local_47c * -0.5;
          }
        }
        if (local_54 != **(int **)((int)&__DT_PLTGOT + local_480)) {
                    /* WARNING: Subroutine does not return */
          __stack_chk_fail();
        }
        return;
      }
      cVar6 = *(char *)(param_1 + iVar7);
      pcVar9 = &cStack_454;
    } while (cVar6 == '>' || cVar6 == '\0');
    iVar7 = iVar8 + 2;
    pcVar9 = local_453;
    cStack_454 = cVar6;
  } while( true );
}
