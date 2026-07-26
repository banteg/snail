/*
 * mangled: _ZN12cGlowManager7GetGlowEffff
 * demangled: cGlowManager::GetGlow(float, float, float, float)
 * address: 0004b59c
 * size: 180
 */

/* cGlowManager::GetGlow(float, float, float, float) */

cGlowManager * __thiscall
cGlowManager::GetGlow(cGlowManager *this,float param_1,float param_2,float param_3,float param_4)

{
  float in_r1;
  int iVar1;
  float in_r2;
  float in_r3;
  cGlowManager *pcVar2;
  int iVar3;
  float in_stack_00000000;

  iVar3 = 0;
  do {
    if (*(int *)(this + iVar3 * 0x20) == 0) {
      pcVar2 = this + iVar3 * 0x20;
      *(undefined4 *)(pcVar2 + 4) = 0;
      *(undefined4 *)(this + iVar3 * 0x20) = 1;
      iVar1 = iVar3 * 4 + 1;
      iVar3 = iVar3 * 2 + 1;
      *(undefined4 *)(this + iVar1 * 8) = 0x3d3da12f;
      *(float *)(this + iVar1 * 8 + 4) = in_r1 + 8.0;
      *(float *)(this + iVar3 * 0x10) = in_r2 + 9.0;
      *(float *)(this + iVar3 * 0x10 + 4) = in_r3 - 16.0;
      *(float *)(pcVar2 + 0x18) = in_stack_00000000 - 18.0;
      return pcVar2;
    }
    iVar3 = iVar3 + 1;
  } while (iVar3 != 8);
  return this;
}
