/*
 * mangled: _ZN7cKeyPad6RenderEv
 * demangled: cKeyPad::Render()
 * address: 00076460
 * size: 436
 */

/* cKeyPad::Render() */

void __thiscall cKeyPad::Render(cKeyPad *this)

{
  uint in_fpscr;
  float fVar1;
  undefined4 uVar2;
  undefined4 local_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 local_18;

  tColour::tColour((tColour *)&local_24);
  tColour::White((tColour *)&local_24);
  if (*(int *)this != 0) {
    if (*(int *)(this + 0x1c) == 0) {
      fVar1 = (float)VectorSignedToFloat((*(undefined4 **)(this + 4))[1],
                                         (byte)(in_fpscr >> 0x16) & 3);
      uVar2 = VectorSignedToFloat(**(undefined4 **)(this + 4),(byte)(in_fpscr >> 0x16) & 3);
      FontType("Richard Evans",0,0x3fc00000,uVar2,
               (fVar1 + *(float *)(this + 0x18)) - *(float *)(this + 0x14),0,0,0,0,0,0,0,0,0x1000000
               ,local_24,uStack_20,uStack_1c,local_18,0,0);
    }
    else {
      fVar1 = (float)VectorSignedToFloat((*(undefined4 **)(this + 4))[1],
                                         (byte)(in_fpscr >> 0x16) & 3);
      uVar2 = VectorSignedToFloat(**(undefined4 **)(this + 4),(byte)(in_fpscr >> 0x16) & 3);
      FontType(*(int *)(this + 0x1c) + 0x2c4,0,0x3fc00000,uVar2,
               (fVar1 + *(float *)(this + 0x18)) - *(float *)(this + 0x14),0,0,0,0,0,0,0,0,0x1000000
               ,local_24,uStack_20,uStack_1c,local_18,0,0);
    }
    local_18 = *(undefined4 *)(this + 0xc);
    OSDPrintUV(0x8b,0,*(undefined4 *)(this + 0x18),0x44200000,0x43c00000,0x1000000,local_24,
               uStack_20,uStack_1c,local_18,0,0,0x3f700000,0x3f800000,1,0);
  }
  return;
}
