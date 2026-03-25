/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: set_backdrop_texture_target @ 0x410f40 */
/* selector: set_backdrop_texture_target */

// Captures the current and next backdrop texture ids and resets the internal crossfade counters inside the shared backdrop renderer.
int __thiscall sub_410F40(int this, int a2)
{
  double v2; // st7
  int v3; // edx
  double v5; // st7

  v2 = 1.0 - *(float *)(this + 1676);
  v3 = *(_DWORD *)(this + 1720);
  *(_DWORD *)(this + 1684) = *(_DWORD *)(this + 1688);
  *(_DWORD *)(this + 1688) = a2;
  *(_DWORD *)(this + 1716) = v3;
  *(float *)(this + 1676) = v2;
  v5 = 1.0 - *(float *)(this + 1708);
  *(_DWORD *)(this + 1720) = a2;
  *(float *)(this + 1708) = v5;
  return a2;
}

