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
  uint in_fpscr;
  float extraout_s0;
  float extraout_s0_00;
  float extraout_s0_01;
  float extraout_s1;
  float fVar5;
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
  int local_1c [2];

  switch(*(undefined4 *)this) {
  case 0:
    return;
  case 1:
    fVar8 = *(float *)(this + 0xc);
    *(float *)(this + 0xc) = fVar8 + *(float *)(this + 0x10);
    if (1.0 < fVar8 + *(float *)(this + 0x10)) {
      *(undefined4 *)(this + 0xc) = 0x3f800000;
      *(undefined4 *)this = 2;
    }
    break;
  case 2:
    if ((*(uint *)(*(int *)(Game + 0x224) + 0x30) & 0x4000) == 0) {
      iVar3 = RShellInkey();
      if (iVar3 == 5) {
        cRSound::Play((int)&gRSound);
        *(undefined4 *)this = 3;
      }
    }
    else {
      iVar3 = KeyTest(this,(int)*(float *)(Game + 0x234),(int)*(float *)(Game + 0x238),local_1c);
      fVar8 = extraout_s0;
      fVar5 = extraout_s1;
      fVar6 = extraout_s2;
      fVar7 = extraout_s3;
      if (iVar3 != 0) {
        cRSound::Play((int)&gRSound);
        if (iVar3 == 0x23) {
          cRSound::Play((int)&gRSound);
          *(undefined4 *)this = 3;
          fVar8 = extraout_s0_01;
          fVar5 = extraout_s1_01;
          fVar6 = extraout_s2_01;
          fVar7 = extraout_s3_01;
        }
        else {
          wprintf("KeyPad %c\n",iVar3);
          uVar2 = ConvertCode(this,(char)iVar3);
          KeySet(uVar2);
          fVar8 = extraout_s0_00;
          fVar5 = extraout_s1_00;
          fVar6 = extraout_s2_00;
          fVar7 = extraout_s3_00;
        }
      }
      if (local_1c[0] != -1) {
        iVar3 = *(int *)(this + 4) + local_1c[0] * 0x14;
        iVar4 = *(int *)(*(int *)(this + 4) + local_1c[0] * 0x14);
        VectorSignedToFloat(iVar4,(byte)(in_fpscr >> 0x16) & 3);
        VectorSignedToFloat(*(int *)(iVar3 + 8) - iVar4,(byte)(in_fpscr >> 0x16) & 3);
        VectorSignedToFloat(*(int *)(iVar3 + 4),(byte)(in_fpscr >> 0x16) & 3);
        VectorSignedToFloat(*(int *)(iVar3 + 0xc) - *(int *)(iVar3 + 4),(byte)(in_fpscr >> 0x16) & 3
                           );
        cGlowManager::GetGlow((cGlowManager *)(this + 0x20),fVar8,fVar5,fVar6,fVar7);
      }
    }
    break;
  case 3:
    fVar8 = *(float *)(this + 0xc);
    *(float *)(this + 0xc) = fVar8 - *(float *)(this + 0x10);
    if (fVar8 - *(float *)(this + 0x10) < 0.0) {
      *(undefined4 *)(this + 0xc) = 0;
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
       *(float *)(this + 0xc) * *(float *)(this + 0x14) + (1.0 - *(float *)(this + 0xc)) * 480.0;
  cGlowManager::AI((cGlowManager *)(this + 0x20));
  return;
}
