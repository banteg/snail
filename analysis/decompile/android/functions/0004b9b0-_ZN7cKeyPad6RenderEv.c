/*
 * mangled: _ZN7cKeyPad6RenderEv
 * demangled: cKeyPad::Render()
 * address: 0004b9b0
 * size: 436
 */

/* cKeyPad::Render() */

void __thiscall cKeyPad::Render(cKeyPad *this)

{
  uint in_fpscr;
  undefined4 uVar1;
  float fVar2;
  undefined4 local_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 local_1c;

  tColour::tColour((tColour *)&local_28);
  tColour::White();
  if (*(int *)this != 0) {
    if (*(int *)(this + 0x1c) == 0) {
      fVar2 = (float)VectorSignedToFloat((*(undefined4 **)(this + 4))[1],
                                         (byte)(in_fpscr >> 0x16) & 3);
      uVar1 = VectorSignedToFloat(**(undefined4 **)(this + 4),(byte)(in_fpscr >> 0x16) & 3);
      FontType("Richard Evans",0,0x3fc00000,uVar1,
               (fVar2 + *(float *)(this + 0x18)) - *(float *)(this + 0x14),0,0,0,0,0,0,0,0,0x1000000
               ,local_28,uStack_24,uStack_20,local_1c,0,0);
    }
    else {
      fVar2 = (float)VectorSignedToFloat((*(undefined4 **)(this + 4))[1],
                                         (byte)(in_fpscr >> 0x16) & 3);
      uVar1 = VectorSignedToFloat(**(undefined4 **)(this + 4),(byte)(in_fpscr >> 0x16) & 3);
      FontType(*(int *)(this + 0x1c) + 0x2c4,0,0x3fc00000,uVar1,
               (fVar2 + *(float *)(this + 0x18)) - *(float *)(this + 0x14),0,0,0,0,0,0,0,0,0x1000000
               ,local_28,uStack_24,uStack_20,local_1c,0,0);
    }
    local_1c = *(undefined4 *)(this + 0xc);
    OSDPrintUV(0x8b,0,*(undefined4 *)(this + 0x18),0x44200000,0x43c00000,0x1000000,local_28,
               uStack_24,uStack_20,local_1c,0,0,0x3f700000,0x3f800000,1,0);
  }
  return;
}
