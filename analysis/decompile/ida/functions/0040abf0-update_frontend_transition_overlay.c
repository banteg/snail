/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_frontend_transition_overlay @ 0x40abf0 */
/* selector: update_frontend_transition_overlay */

// Exact void Windows cRFade::AI() projection: updates the owned alpha, three-tick opaque hold, externally polled state-4 handoff, and full-screen black draw. Android independently preserves the cRFade owner, alpha lane, state-1/state-2 step, and draw while using port-specific handoff gates.
void __thiscall update_frontend_transition_overlay(FrontendFade *fade)
{
  double v1; // st7
  double v2; // st7
  double v3; // st7
  tColour *v4; // eax
  Color4f color; // [esp+4h] [ebp-10h] BYREF

  switch ( fade->state )
  {
    case 0:
      return;
    case 1:
      v3 = fade->alpha - 0.055555552;
      fade->alpha = v3;
      if ( v3 <= 0.0 )
      {
        fade->alpha = 0.0;
        fade->state = 0;
      }
      goto LABEL_9;
    case 2:
      v1 = fade->alpha + 0.055555552;
      fade->alpha = v1;
      if ( v1 > 1.0 )
      {
        fade->alpha = 1.0;
        fade->state = 3;
        fade->hold_progress = 0.0;
        fade->hold_progress_step = 0.33333334;
      }
      goto LABEL_9;
    case 3:
      v2 = fade->hold_progress_step + fade->hold_progress;
      fade->hold_progress = v2;
      if ( v2 > 1.0 )
        fade->state = 4;
      goto LABEL_9;
    case 4:
      fade->state = 1;
      goto LABEL_9;
    default:
LABEL_9:
      if ( fade->alpha > 0.0099999998 )
      {
        v4 = set_color_rgba((tColour *)&color, 0.0, 0.0, 0.0, fade->alpha);
        queue_axis_aligned_textured_quad(2, 0.0, 0.0, 640.0, 480.0, 0x1000000u, v4, 14);
      }
      return;
  }
}
