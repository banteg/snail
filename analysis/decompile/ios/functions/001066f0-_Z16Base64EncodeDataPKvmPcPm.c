/*
 * mangled: _Z16Base64EncodeDataPKvmPcPm
 * demangled: Base64EncodeData(void const*, unsigned long, char*, unsigned long*)
 * address: 001066f0
 * size: 724
 */

/* Base64EncodeData(void const*, unsigned long, char*, unsigned long*) */

undefined4 Base64EncodeData(void *param_1,ulong param_2,char *param_3,ulong *param_4)

{
  uint uVar1;
  undefined4 uVar2;
  uint uVar3;
  uint uVar4;
  void *pvVar5;
  uint uVar6;
  uint uVar7;
  uint in_fpscr;
  double dVar8;
  undefined8 uVar9;
  int iVar10;

  dVar8 = (double)VectorUnsignedToFloat(param_2,(byte)(in_fpscr >> 0x16) & 3);
  uVar9 = _ceil(SUB84(dVar8 / 3.0,0),(int)((ulonglong)(dVar8 / 3.0) >> 0x20));
  iVar10 = VectorFloatToSigned(uVar9,3);
  uVar4 = iVar10 * 4 + ((uint)(iVar10 * 4) / 0x48) * 2;
  if (*param_4 < uVar4) {
    uVar2 = 0;
  }
  else {
    *param_4 = uVar4;
    iVar10 = ((uint)((ulonglong)param_2 * 0xaaaaaaab >> 0x20) & 0xfffffffe) + param_2 / 3;
    if (iVar10 == 0) {
      uVar3 = 0;
      uVar4 = 0;
      uVar7 = 0;
    }
    else {
      uVar3 = 0;
      uVar1 = ((iVar10 - 1U) / 3 + 1) * 3;
      pvVar5 = param_1;
      uVar6 = 0;
      do {
        while( true ) {
          param_3[uVar6] =
               "?ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
               [(*(byte *)(uVar3 + (int)param_1) >> 2) + 1];
          param_3[uVar6 + 1] =
               "?ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
               [((*(byte *)(uVar3 + (int)param_1) & 3) << 4 |
                (uint)(*(byte *)((int)pvVar5 + 1) >> 4)) + 1];
          uVar7 = uVar6 + 4;
          param_3[uVar6 + 2] =
               "?ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
               [((*(byte *)((int)pvVar5 + 1) & 0xf) << 2 | (uint)(*(byte *)((int)pvVar5 + 2) >> 6))
                + 1];
          param_3[uVar6 + 3] =
               "?ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
               [(*(byte *)((int)pvVar5 + 2) & 0x3f) + 1];
          uVar4 = uVar7 % 0x4a;
          if (uVar4 != 0x48) break;
          param_3[uVar7] = '\r';
          uVar3 = uVar3 + 3;
          uVar4 = uVar6 + 5;
          param_3[uVar4] = '\n';
          uVar7 = uVar6 + 6;
          pvVar5 = (void *)((int)pvVar5 + 3);
          uVar6 = uVar7;
          if (uVar3 == uVar1) goto LAB_0010688c;
        }
        uVar3 = uVar3 + 3;
        pvVar5 = (void *)((int)pvVar5 + 3);
        uVar6 = uVar7;
      } while (uVar3 != uVar1);
    }
LAB_0010688c:
    iVar10 = param_2 - uVar3;
    if (iVar10 == 1) {
      param_3[uVar7] =
           "?ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
           [(*(byte *)((int)param_1 + uVar3) >> 2) + 1];
      param_3[uVar7 + 1] =
           "?ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
           [(*(byte *)((int)param_1 + uVar3) & 3) * 0x10 + 1];
      param_3[uVar7 + 2] = '=';
      param_3[uVar7 + 3] = '=';
      if ((uVar7 + 4) % 0x4a == 0x48) {
        param_3[uVar7 + 4] = '\r';
        param_3[uVar7 + 5] = '\n';
      }
      uVar2 = 1;
    }
    else {
      if (iVar10 == 2) {
        param_3[uVar7] =
             "?ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
             [(*(byte *)((int)param_1 + uVar3) >> 2) + 1];
        param_3[uVar7 + 1] =
             "?ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
             [((*(byte *)((int)param_1 + uVar3) & 3) << 4 |
              (uint)(*(byte *)((int)param_1 + uVar3 + 1) >> 4)) + 1];
        param_3[uVar7 + 2] =
             "?ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
             [(*(byte *)((int)param_1 + uVar3 + 1) & 0xf) * 4 + 1];
        uVar3 = uVar7 + 4;
        param_3[uVar7 + 3] = '=';
        uVar4 = uVar3 % 0x4a;
      }
      if (iVar10 == 2 && uVar4 == 0x48) {
        param_3[uVar3] = (char)uVar4 + -0x3b;
        param_3[uVar3 + 1] = (char)uVar4 + -0x3e;
        uVar2 = 1;
      }
      else {
        uVar2 = 1;
      }
    }
  }
  return uVar2;
}
