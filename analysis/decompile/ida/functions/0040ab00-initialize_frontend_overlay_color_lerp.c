/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_frontend_overlay_color_lerp @ 0x40ab00 */
/* selector: initialize_frontend_overlay_color_lerp */

// Seeds the secondary full-screen RGBA overlay interpolator stored at `data_4df904 + 0x2a8`.
int __thiscall sub_40AB00(_DWORD *this, int a2)
{
  *this = a2;
  sub_44DBB0(this + 1, 1065353216, 1065353216, 1065353216, 0);
  return sub_44DBB0(this + 5, 1065353216, 1065353216, 1065353216, 0);
}

