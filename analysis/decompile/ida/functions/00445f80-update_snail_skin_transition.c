/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_snail_skin_transition @ 0x445f80 */
/* selector: update_snail_skin_transition */

// Applies the currently selected snail-skin object to the shared player render owner and, when a timed skin change is armed, advances the transition progress until the swap completes.
void __thiscall sub_445F80(float *this)
{
  double v1; // st7

  *(_DWORD *)(*(_DWORD *)(*((_DWORD *)this + 4) + 36) + 16) |= 8u;
  *(float *)(*(_DWORD *)(*((_DWORD *)this + 4) + 36) + 24) = *(this + *(_DWORD *)this + 1);
  if ( *((_DWORD *)this + 5) == 1 )
  {
    v1 = *(this + 7) + *(this + 6);
    *(this + 6) = v1;
    if ( v1 > 1.0 )
    {
      *(this + 6) = 0.0;
      *(this + 5) = 0.0;
      *this = 0.0;
    }
  }
}

