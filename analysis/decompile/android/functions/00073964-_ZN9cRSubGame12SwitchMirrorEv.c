/*
 * mangled: _ZN9cRSubGame12SwitchMirrorEv
 * demangled: cRSubGame::SwitchMirror()
 * address: 00073964
 * size: 124
 */

/* cRSubGame::SwitchMirror() */

void cRSubGame::SwitchMirror(void)

{
  bool bVar1;
  int in_r0;
  float fVar2;
  int iVar3;
  float in_s0;

  fVar2 = (float)RAND(in_s0,(char *)0x3f800000);
  bVar1 = DAT_000739e0 < fVar2;
  if ((bool)*(byte *)(in_r0 + 2) == bVar1) {
    iVar3 = *(int *)(in_r0 + 4) + 1;
    *(int *)(in_r0 + 4) = iVar3;
    if (3 < iVar3) {
      *(byte *)(in_r0 + 2) = *(byte *)(in_r0 + 2) ^ 1;
      *(undefined4 *)(in_r0 + 4) = 0;
      return;
    }
  }
  else {
    *(undefined4 *)(in_r0 + 4) = 0;
  }
  *(bool *)(in_r0 + 2) = bVar1;
  return;
}
