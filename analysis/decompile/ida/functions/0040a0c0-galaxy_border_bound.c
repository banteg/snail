/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: galaxy_border_bound @ 0x40a0c0 */
/* selector: galaxy_border_bound */

// Exact Windows `Galaxy::galaxy_border_bound`, matching Android `cRGalaxy::BorderBound(float&, float&, float&, float&, cRBorder*)`.
void __thiscall galaxy_border_bound(
        Galaxy *galaxy,
        float *min_x,
        float *max_x,
        float *min_y,
        float *max_y,
        FrontendWidget *widget)
{
  double v6; // st7
  double v7; // st7
  double v8; // st7
  double v9; // st7

  if ( widget->text_alignment == 2 )
  {
    v6 = *max_x - *min_x;
    if ( v6 < widget->layout_width )
    {
      v7 = *min_x - (widget->layout_width - v6) * 0.5;
      *min_x = v7;
      *min_x = (widget->layout_width - (*max_x - v7)) * 0.5 + v7;
    }
  }
  else
  {
    if ( widget->layout_left < (double)*min_x )
      *min_x = widget->layout_left;
    v9 = widget->layout_width + widget->layout_left;
    if ( v9 > *max_x )
      *max_x = v9;
  }
  if ( widget->layout_top < (double)*min_y )
    *min_y = widget->layout_top;
  v8 = widget->layout_height + widget->layout_top;
  if ( v8 > *max_y )
    *max_y = v8;
}
