/*
 * mangled: _ZN9cRSubGame12SwitchMirrorEv
 * demangled: cRSubGame::SwitchMirror()
 * address: 00073964
 * size: 124
 */

/* cRSubGame::SwitchMirror() */

void cRSubGame::SwitchMirror(void)

{
  int in_r0;
  float fVar1;
  int iVar2;
  float in_s0;

  fVar1 = (float)RAND(in_s0,(char *)0x3f800000);
  if ((bool)*(byte *)(in_r0 + 2) == 0.5 < fVar1) {
    iVar2 = *(int *)(in_r0 + 4) + 1;
    *(int *)(in_r0 + 4) = iVar2;
    if (3 < iVar2) {
      *(byte *)(in_r0 + 2) = *(byte *)(in_r0 + 2) ^ 1;
      *(undefined4 *)(in_r0 + 4) = 0;
      return;
    }
  }
  else {
    *(undefined4 *)(in_r0 + 4) = 0;
  }
  *(bool *)(in_r0 + 2) = 0.5 < fVar1;
  return;
}
