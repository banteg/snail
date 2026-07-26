/*
 * mangled: _ZN9cROptions2AIEv
 * demangled: cROptions::AI()
 * address: 00062304
 * size: 440
 */

/* cROptions::AI() */

void __thiscall cROptions::AI(cROptions *this)

{
  undefined *puVar1;
  int iVar2;
  uint uVar3;

  puVar1 = PTR__gConfig_001b60d4;
  *(undefined4 *)(PTR__gConfig_001b60d4 + 4) = *(undefined4 *)(*(int *)(this + 0x1c) + 0x170);
  *(undefined4 *)puVar1 = *(undefined4 *)(*(int *)(this + 0x18) + 0x170);
  if (*(float *)(*(int *)PTR__Game_001b60b8 + 0x3c) != *(float *)(*(int *)PTR__Game_001b60b8 + 0x44)
     ) {
    UnInit();
    Init(this);
  }
  iVar2 = *(int *)(this + 0x14);
  if ((*(uint *)(iVar2 + 0x194) & 0x20) == 0) {
    if (*(int *)(puVar1 + 8) == 0) {
      Rstrcpy((char *)(iVar2 + 0x2c4),"Tilt Mode");
      goto LAB_0006238c;
    }
  }
  else {
    *(uint *)(iVar2 + 0x194) = *(uint *)(iVar2 + 0x194) & 0xffffffdf;
    if (*(int *)(puVar1 + 8) != 0) {
      *(undefined4 *)(puVar1 + 8) = 0;
      Rstrcpy((char *)(*(int *)(this + 0x14) + 0x2c4),"Tilt Mode");
      goto LAB_0006238c;
    }
    *(undefined4 *)(puVar1 + 8) = 1;
    iVar2 = *(int *)(this + 0x14);
  }
  Rstrcpy((char *)(iVar2 + 0x2c4),"Touch Mode");
LAB_0006238c:
  uVar3 = *(uint *)(*(int *)(this + 0x18) + 0x194);
  if ((uVar3 & 0x20) != 0) {
    *(uint *)(*(int *)(this + 0x18) + 0x194) = uVar3 & 0xffffffdf;
  }
  uVar3 = *(uint *)(*(int *)(this + 0x10) + 0x194);
  if ((uVar3 & 0x20) != 0) {
    *(uint *)(*(int *)(this + 0x10) + 0x194) = uVar3 & 0xffffffdf;
    UnInit();
    puVar1 = PTR__Game_001b60b8;
    *(undefined1 *)(*(int *)PTR__Game_001b60b8 + 0x324) = 0;
    *(undefined4 *)(*(int *)puVar1 + 0x15c) = *(undefined4 *)this;
  }
  puVar1 = PTR__gConfig_001b60d4;
  MacAudioSetSampleVolume(*(float *)PTR__gConfig_001b60d4);
  MacAudioSetMusicVolume(*(float *)(puVar1 + 4) * *(float *)PTR__MacNormalizeMusic_001b61f0);
  if ((*(float *)(puVar1 + 4) != 0.0) || (MacAudioStopMusic(), *(float *)(puVar1 + 4) != 0.0)) {
    MacAudioStartMusic();
  }
  puVar1 = PTR__gConfig_001b60d4;
  if (*(float *)(this + 0x24) == *(float *)PTR__gConfig_001b60d4) {
    return;
  }
  cRSound::Play((cRSound *)PTR__gRSound_001b61e0,8);
  *(undefined4 *)(this + 0x24) = *(undefined4 *)puVar1;
  return;
}
