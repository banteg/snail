/*
 * mangled: _ZN7cKeyPad2AIEv
 * demangled: cKeyPad::AI()
 * address: 0004bbe8
 * size: 544
 */

/* cKeyPad::AI() */

void __thiscall cKeyPad::AI(cKeyPad *this)

{
  cKeyPad cVar1;
  uchar uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint in_fpscr;
  float extraout_s0;
  float extraout_s0_00;
  float extraout_s0_01;
  float extraout_s1;
  float extraout_s1_00;
  float extraout_s1_01;
  float extraout_s2;
  float fVar6;
  float extraout_s2_00;
  float extraout_s2_01;
  float extraout_s3;
  float fVar7;
  float extraout_s3_00;
  float extraout_s3_01;
  float fVar8;
  float fVar9;
  int local_1c [2];

  fVar8 = DAT_0004be08;
  iVar4 = DAT_0004be14 + 0x4bc04;
  switch(*(undefined4 *)this) {
  case 0:
    return;
  case 1:
    fVar9 = *(float *)(this + 0xc);
    *(float *)(this + 0xc) = fVar9 + *(float *)(this + 0x10);
    if (fVar8 < fVar9 + *(float *)(this + 0x10)) {
      *(float *)(this + 0xc) = fVar8;
      *(undefined4 *)this = 2;
    }
    break;
  case 2:
    iVar3 = **(int **)(iVar4 + DAT_0004be18);
    if ((*(uint *)(*(int *)(iVar3 + 0x224) + 0x30) & 0x4000) == 0) {
      iVar3 = RShellInkey();
      if (iVar3 == 5) {
        cRSound::Play(*(int *)(iVar4 + DAT_0004be1c));
        *(undefined4 *)this = 3;
      }
    }
    else {
      iVar3 = KeyTest(this,(int)*(float *)(iVar3 + 0x234),(int)*(float *)(iVar3 + 0x238),local_1c);
      fVar8 = extraout_s0;
      fVar9 = extraout_s1;
      fVar6 = extraout_s2;
      fVar7 = extraout_s3;
      if (iVar3 != 0) {
        iVar5 = *(int *)(iVar4 + DAT_0004be1c);
        cRSound::Play(iVar5);
        if (iVar3 == 0x23) {
          cRSound::Play(iVar5);
          *(undefined4 *)this = 3;
          fVar8 = extraout_s0_01;
          fVar9 = extraout_s1_01;
          fVar6 = extraout_s2_01;
          fVar7 = extraout_s3_01;
        }
        else {
          wprintf((char *)(iVar4 + DAT_0004be20),iVar3);
          uVar2 = ConvertCode(this,(char)iVar3);
          KeySet(uVar2);
          fVar8 = extraout_s0_00;
          fVar9 = extraout_s1_00;
          fVar6 = extraout_s2_00;
          fVar7 = extraout_s3_00;
        }
      }
      if (local_1c[0] != -1) {
        iVar4 = *(int *)(this + 4) + local_1c[0] * 0x14;
        iVar3 = *(int *)(*(int *)(this + 4) + local_1c[0] * 0x14);
        VectorSignedToFloat(iVar3,(byte)(in_fpscr >> 0x16) & 3);
        VectorSignedToFloat(*(int *)(iVar4 + 8) - iVar3,(byte)(in_fpscr >> 0x16) & 3);
        VectorSignedToFloat(*(int *)(iVar4 + 4),(byte)(in_fpscr >> 0x16) & 3);
        VectorSignedToFloat(*(int *)(iVar4 + 0xc) - *(int *)(iVar4 + 4),(byte)(in_fpscr >> 0x16) & 3
                           );
        cGlowManager::GetGlow((cGlowManager *)(this + 0x20),fVar8,fVar9,fVar6,fVar7);
      }
    }
    break;
  case 3:
    fVar8 = *(float *)(this + 0xc);
    *(float *)(this + 0xc) = fVar8 - *(float *)(this + 0x10);
    if (fVar8 - *(float *)(this + 0x10) < 0.0) {
      *(undefined4 *)(this + 0xc) = DAT_0004be10;
      *(undefined4 *)this = 0;
      cVar1 = this[0x120];
      goto joined_r0x0004bcbc;
    }
  }
  cVar1 = this[0x120];
joined_r0x0004bcbc:
  if (cVar1 != (cKeyPad)0x0) {
    KeySet('*');
  }
  *(float *)(this + 0x18) =
       *(float *)(this + 0xc) * *(float *)(this + 0x14) +
       (DAT_0004be08 - *(float *)(this + 0xc)) * DAT_0004be0c;
  cGlowManager::AI((cGlowManager *)(this + 0x20));
  return;
}
