/*
 * mangled: _ZN12cRCompletion14RegisterParcelEv
 * demangled: cRCompletion::RegisterParcel()
 * address: 00060b4c
 * size: 180
 */

/* cRCompletion::RegisterParcel() */

void __thiscall cRCompletion::RegisterParcel(cRCompletion *this)

{
  int iVar1;
  int *piVar2;

  iVar1 = DAT_00060c00 + 0x60b6c;
  if (*(int *)(this + 0x24) == *(int *)(this + 0x18)) {
    return;
  }
  piVar2 = *(int **)(iVar1 + DAT_00060c04);
  cRSubGoldy::ScoreAdd((cRSubGoldy *)(*piVar2 + 0x81364),4,0);
  OFAddParcelDelivered();
  iVar1 = *(int *)(iVar1 + DAT_00060c08);
  *(int *)(this + 0x24) = *(int *)(this + 0x24) + 1;
  cRSound::Play(iVar1);
  if (*(int *)(this + 0x24) != *(int *)(this + 0x18)) {
    return;
  }
  if (*(int *)(this + 0x1c) != 0) {
    cRSubGoldy::ScoreAdd((cRSubGoldy *)(*piVar2 + 0x81364),5,*(int *)(this + 0x44));
    cRSound::Play(iVar1);
  }
  *(undefined4 *)(this + 0x10) = 3;
  return;
}
