/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_frontend_transition_overlay @ 0x40abf0 */
/* selector: update_frontend_transition_overlay */

// Updates and draws the shared full-screen black front-end transition overlay, including fade-in, fade-out, three-tick black hold, and the handoff sentinel state.
void __thiscall sub_40ABF0(float *this)
{
  double v1; // st7
  double v2; // st7
  double v3; // st7
  int *v4; // eax
  _DWORD v5[4]; // [esp+4h] [ebp-10h] BYREF

  switch ( *(_DWORD *)this )
  {
    case 0:
      return;
    case 1:
      v3 = *(this + 1) - 0.055555552;
      *(this + 1) = v3;
      if ( v3 <= 0.0 )
      {
        *(this + 1) = 0.0;
        *this = 0.0;
      }
      goto LABEL_9;
    case 2:
      v1 = *(this + 1) + 0.055555552;
      *(this + 1) = v1;
      if ( v1 > 1.0 )
      {
        *(this + 1) = 1.0;
        *(_DWORD *)this = 3;
        *(this + 2) = 0.0;
        *(this + 3) = 0.33333334;
      }
      goto LABEL_9;
    case 3:
      v2 = *(this + 3) + *(this + 2);
      *(this + 2) = v2;
      if ( v2 > 1.0 )
        *(_DWORD *)this = 4;
      goto LABEL_9;
    case 4:
      *(_DWORD *)this = 1;
      goto LABEL_9;
    default:
LABEL_9:
      if ( *(this + 1) > 0.0099999998 )
      {
        v4 = set_color_rgba(v5, 0, 0, 0, COERCE_INT(*(this + 1)));
        queue_axis_aligned_textured_quad(2, 0, 0, 1142947840, 1139802112, 0x1000000, v4, 14);
      }
      return;
  }
}

