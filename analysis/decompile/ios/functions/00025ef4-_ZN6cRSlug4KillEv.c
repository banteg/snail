/*
 * mangled: _ZN6cRSlug4KillEv
 * demangled: cRSlug::Kill()
 * address: 00025ef4
 * size: 352
 */

/* cRSlug::Kill() */

void __thiscall cRSlug::Kill(cRSlug *this)

{
  undefined *puVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint in_fpscr;
  float fVar6;

  if (*(int *)(this + 0x74) == 1) {
    uVar2 = gRMathRand2();
    puVar1 = PTR__Game_001b60b8;
    if (this[0xcc] == (cRSlug)0x0) {
      iVar5 = *(int *)PTR__Game_001b60b8;
      if (*(char *)(iVar5 + 0x7b14c) == '\0') {
        fVar6 = (float)VectorSignedToFloat(uVar2,(byte)(in_fpscr >> 0x16) & 3);
        *(undefined4 *)(iVar5 + 0x7b150) = *(undefined4 *)((int)&DAT_0007b154 + iVar5);
        *(undefined1 *)(*(int *)puVar1 + 0x7b14c) = 1;
        this[0xcc] = (cRSlug)0x1;
        *(undefined4 *)(this + 0xd0) = 0;
        RShellVoicePlay((int)(fVar6 * 3.0517578e-05 + fVar6 * 3.0517578e-05) + 0x1c,1.0,-1.0,0.0);
      }
    }
    iVar5 = *(int *)(this + 0x7c);
    *(undefined4 *)(this + 0x74) = 2;
    if (0.0 < *(float *)(this + 0x5c)) {
      *(undefined4 *)(this + 0x78) = 1;
    }
    else {
      *(undefined4 *)(this + 0x78) = 2;
    }
    *(int *)(iVar5 + 0xf744) = *(int *)(iVar5 + 0xf744) + 500;
    iVar4 = *(int *)(iVar5 + 0xf714);
    iVar3 = iVar4 + 500;
    *(int *)(iVar5 + 0xf714) = iVar3;
    if ((iVar4 / 50000 != iVar3 / 50000) && (*(int *)(iVar5 + 0x13434) < 9)) {
      *(int *)(iVar5 + 0x13434) = *(int *)(iVar5 + 0x13434) + 1;
      if ((*(int *)(*(int *)PTR__Game_001b60b8 + 0x72bd0) == 0) &&
         (*(int *)(*(int *)PTR__Game_001b60b8 + 0x24) == 0)) {
        cRSound::Play((cRSound *)PTR__gRSound_001b61e0,0x2d);
      }
    }
    Explode(this);
    return;
  }
  return;
}
