/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: draw_frontend_overlay_color_lerp @ 0x40ab40 */
/* selector: draw_frontend_overlay_color_lerp */

// Advances and draws the secondary full-screen RGBA overlay interpolator stored at `data_4df904 + 0x2a8`.
void __thiscall sub_40AB40(void *this)
{
  double v1; // st7

  *((float *)this + 5) = (*((float *)this + 1) - *((float *)this + 5)) * 0.145 + *((float *)this + 5);
  *((float *)this + 6) = (*((float *)this + 2) - *((float *)this + 6)) * 0.145 + *((float *)this + 6);
  *((float *)this + 7) = (*((float *)this + 3) - *((float *)this + 7)) * 0.145 + *((float *)this + 7);
  v1 = (*((float *)this + 4) - *((float *)this + 8)) * 0.145 + *((float *)this + 8);
  *((float *)this + 8) = v1;
  if ( v1 > 0.0099999998 )
    queue_axis_aligned_textured_quad(2, 0, 0, 1142947840, 1139802112, *(_DWORD *)this & 0xFF000000, (int *)this + 5, 5);
}

