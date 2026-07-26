/*
 * mangled: _ZN7cKeyPad6RenderEv
 * demangled: cKeyPad::Render()
 * address: 0004b9b0
 * size: 436
 */

/* cKeyPad::Render() */

void __thiscall cKeyPad::Render(cKeyPad *this)

{
  int iVar1;
  uint in_fpscr;
  undefined4 uVar2;
  float fVar3;
  undefined4 local_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 local_1c;

  iVar1 = DAT_0004bb74;
  tColour::tColour((tColour *)&local_28);
  tColour::White();
  if (*(int *)this != 0) {
    if (*(int *)(this + 0x1c) == 0) {
      fVar3 = (float)VectorSignedToFloat((*(undefined4 **)(this + 4))[1],
                                         (byte)(in_fpscr >> 0x16) & 3);
      uVar2 = VectorSignedToFloat(**(undefined4 **)(this + 4),(byte)(in_fpscr >> 0x16) & 3);
      FontType(iVar1 + 0x4b9e0 + DAT_0004bb78,0,0x3fc00000,uVar2,
               (fVar3 + *(float *)(this + 0x18)) - *(float *)(this + 0x14),0,0,0,0,DAT_0004bb64,0,0,
               DAT_0004bb64,0x1000000,local_28,uStack_24,uStack_20,local_1c,0,0);
    }
    else {
      fVar3 = (float)VectorSignedToFloat((*(undefined4 **)(this + 4))[1],
                                         (byte)(in_fpscr >> 0x16) & 3);
      uVar2 = VectorSignedToFloat(**(undefined4 **)(this + 4),(byte)(in_fpscr >> 0x16) & 3);
      FontType(*(int *)(this + 0x1c) + 0x2c4,0,0x3fc00000,uVar2,
               (fVar3 + *(float *)(this + 0x18)) - *(float *)(this + 0x14),0,0,0,0,DAT_0004bb64,0,0,
               DAT_0004bb64,0x1000000,local_28,uStack_24,uStack_20,local_1c,0,0);
    }
    local_1c = *(undefined4 *)(this + 0xc);
    OSDPrintUV(0x8b,0,*(undefined4 *)(this + 0x18),0x44200000,DAT_0004bb68,0x1000000,local_28,
               uStack_24,uStack_20,local_1c,0,0,DAT_0004bb6c,DAT_0004bb70,1,0);
  }
  return;
}
