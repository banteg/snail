/*
 * mangled: _ZN11cRSubTracks6UnHideEPP15cRSubSegmentRaw
 * demangled: cRSubTracks::UnHide(cRSubSegmentRaw**)
 * address: 00083c84
 * size: 68
 */

/* cRSubTracks::UnHide(cRSubSegmentRaw**) */

void __thiscall cRSubTracks::UnHide(cRSubTracks *this,cRSubSegmentRaw **param_1)

{
  cRSubSegmentRaw *pcVar1;

  pcVar1 = *param_1;
  if (**(char **)(pcVar1 + 0x28) != '\0') {
    do {
      *(cRSubSegmentRaw **)(gSegmentIndex + *(int *)(pcVar1 + 0x1c) * 4) = pcVar1;
      param_1 = param_1 + 1;
      pcVar1 = *param_1;
    } while (**(char **)(pcVar1 + 0x28) != '\0');
    return;
  }
  return;
}
