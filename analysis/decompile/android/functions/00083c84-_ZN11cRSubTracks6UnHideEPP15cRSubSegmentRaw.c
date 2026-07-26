/*
 * mangled: _ZN11cRSubTracks6UnHideEPP15cRSubSegmentRaw
 * demangled: cRSubTracks::UnHide(cRSubSegmentRaw**)
 * address: 00083c84
 * size: 68
 */

/* cRSubTracks::UnHide(cRSubSegmentRaw**) */

void __thiscall cRSubTracks::UnHide(cRSubTracks *this,cRSubSegmentRaw **param_1)

{
  int iVar1;
  cRSubSegmentRaw *pcVar2;

  pcVar2 = *param_1;
  if (**(char **)(pcVar2 + 0x28) == '\0') {
    return;
  }
  iVar1 = *(int *)(DAT_00083cc8 + 0x83c98 + DAT_00083ccc);
  do {
    *(cRSubSegmentRaw **)(iVar1 + *(int *)(pcVar2 + 0x1c) * 4) = pcVar2;
    param_1 = param_1 + 1;
    pcVar2 = *param_1;
  } while (**(char **)(pcVar2 + 0x28) != '\0');
  return;
}
