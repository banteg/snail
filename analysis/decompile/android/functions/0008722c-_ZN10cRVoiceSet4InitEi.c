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
  char *pcVar3;
  int iVar4;

  iVar2 = DAT_000872d4;
  *(undefined4 *)(this + 4) = 0;
  *(int *)this = param_1;
  if (*(int *)(this + 8) == 0) {
    uVar1 = RShellMemoryMalloc(param_1 << 2,(char *)(iVar2 + 0x87250 + DAT_000872d8));
    pcVar3 = (char *)(iVar2 + 0x87250 + DAT_000872dc);
    *(undefined4 *)(this + 8) = uVar1;
    uVar1 = RShellMemoryMalloc(*(int *)this * 0x8c,pcVar3);
    *(undefined4 *)(this + 0xc) = uVar1;
  }
  *(undefined4 *)(this + 0x10) = DAT_000872cc;
  *(undefined4 *)(this + 0x14) = DAT_000872d0;
  if (0 < *(int *)this) {
    iVar2 = *(int *)(this + 8);
    iVar4 = 0;
    do {
      *(int *)(iVar2 + iVar4 * 4) = iVar4;
      iVar4 = iVar4 + 1;
    } while (iVar4 < *(int *)this);
  }
  Shuffle(this);
  return;
}
