/*
 * mangled: _ZN6cRSlug9VoicePlayEi
 * demangled: cRSlug::VoicePlay(int)
 * address: 00077e3c
 * size: 148
 */

/* cRSlug::VoicePlay(int) */

void cRSlug::VoicePlay(int param_1)

{
  int iVar1;
  int in_r1;
  undefined4 *puVar2;
  float in_s0;
  float in_s1;
  float in_s2;
  undefined4 uVar3;

  iVar1 = Game;
  if ((*(char *)(param_1 + 0xcc) == '\0') && (*(char *)(Game + 0x7a4ec) == '\0')) {
    puVar2 = (undefined4 *)(Game + 0x7a4f4);
    *(undefined1 *)(Game + 0x7a4ec) = 1;
    uVar3 = *puVar2;
    *(undefined1 *)(param_1 + 0xcc) = 1;
    *(undefined4 *)(iVar1 + 0x7a4f0) = uVar3;
    *(undefined4 *)(param_1 + 0xd0) = 0;
    RShellVoicePlay(in_r1,in_s0,in_s1,in_s2);
    return;
  }
  return;
}
