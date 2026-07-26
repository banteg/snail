/*
 * mangled: _ZN10cRVoiceSet4InitEi
 * demangled: cRVoiceSet::Init(int)
 * address: 0008722c
 * size: 160
 */

/* cRVoiceSet::Init(int) */

void __thiscall cRVoiceSet::Init(cRVoiceSet *this,int param_1)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;

  *(undefined4 *)(this + 4) = 0;
  *(int *)this = param_1;
  if (*(int *)(this + 8) == 0) {
    uVar1 = RShellMemoryMalloc(param_1 << 2,"Playlist");
    *(undefined4 *)(this + 8) = uVar1;
    uVar1 = RShellMemoryMalloc(*(int *)this * 0x8c,"VoiceBite");
    *(undefined4 *)(this + 0xc) = uVar1;
  }
  *(undefined4 *)(this + 0x10) = 0;
  *(undefined4 *)(this + 0x14) = 0x3b888889;
  if (0 < *(int *)this) {
    iVar2 = *(int *)(this + 8);
    iVar3 = 0;
    do {
      *(int *)(iVar2 + iVar3 * 4) = iVar3;
      iVar3 = iVar3 + 1;
    } while (iVar3 < *(int *)this);
  }
  Shuffle(this);
  return;
}
