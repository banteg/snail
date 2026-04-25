/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_star_field @ 0x4346f0 */
/* selector: update_star_field */

// Runs the four-state star-field controller, fading the streak sprites in or out around the global star-pass flag and dispatching the per-frame camera-relative position update.
void __thiscall update_star_field(int this)
{
  double v2; // st7
  double v3; // st7

  switch ( *(_DWORD *)(this + 56) )
  {
    case 0:
      if ( (byte_4DF934 & 4) != 0 )
      {
        *(_DWORD *)(this + 56) = 2;
        initialize_star_field((_DWORD *)this);
        *(_DWORD *)(this + 56) = 2;
        *(_DWORD *)(this + 68) = 0;
        *(_DWORD *)(this + 72) = 1017817771;
        update_star_positions((_DWORD *)this, 0.0);
      }
      break;
    case 1:
      update_star_positions((_DWORD *)this, 1.0);
      if ( (byte_4DF934 & 4) == 0 )
      {
        *(_DWORD *)(this + 68) = 1065353216;
        *(_DWORD *)(this + 72) = 1017817771;
        goto LABEL_13;
      }
      break;
    case 2:
      update_star_positions((_DWORD *)this, *(float *)(this + 68));
      if ( (byte_4DF934 & 4) != 0 )
      {
        v2 = *(float *)(this + 72) + *(float *)(this + 68);
        *(float *)(this + 68) = v2;
        if ( v2 > 1.0 )
          *(_DWORD *)(this + 56) = 1;
      }
      else
      {
LABEL_13:
        *(_DWORD *)(this + 56) = 3;
      }
      break;
    case 3:
      update_star_positions((_DWORD *)this, *(float *)(this + 68));
      if ( (byte_4DF934 & 4) != 0 )
      {
        *(_DWORD *)(this + 56) = 2;
      }
      else
      {
        v3 = *(float *)(this + 68) - *(float *)(this + 72);
        *(float *)(this + 68) = v3;
        if ( v3 < 0.0 )
        {
          destroy_star_field((int *)this);
          *(_DWORD *)(this + 56) = 0;
        }
      }
      break;
    default:
      return;
  }
}

