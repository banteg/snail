/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_twinkle @ 0x404080 */
/* selector: update_twinkle */

// Exact Windows `cRTwinkle::AI()`: advances one FrontendWidget-owned twinkle and borrows its containing authored `cRBorder` for widget flags and the current layout rectangle. Android `cRTwinkleManager::Init(cRBorder*)` independently proves that owner link.
void __thiscall update_twinkle(Twinkle *twinkle)
{
  double v2; // st7
  unsigned __int8 v4; // c0
  unsigned __int8 v5; // c3
  double v6; // st7
  double v7; // st7
  double v8; // st7
  FrontendWidgetFlag widget_flags; // eax
  double v10; // st7
  int math_random_value; // eax
  FrontendWidget *owner_widget; // edi
  double v13; // st7
  double v14; // st6
  FrontendWidget *v15; // edi
  int v16; // [esp+8h] [ebp-8h]

  v2 = twinkle->angle + twinkle->angle_step;
  twinkle->angle = v2;
  if ( v4 | v5 )
  {
    if ( v2 < 0.0 )
      twinkle->angle = v2 + 6.2831855;
  }
  else
  {
    twinkle->angle = v2 - 6.2831855;
  }
  switch ( twinkle->state )
  {
    case 1:
      widget_flags = twinkle->owner_widget->widget_flags;
      if ( (widget_flags & 2) != 0 && SBYTE1(widget_flags) >= 0 )
      {
        v10 = twinkle->delay_progress + twinkle->delay_step;
        twinkle->delay_progress = v10;
        if ( v10 > 1.0 )
        {
          twinkle->state = 2;
          twinkle->alpha = 0.0;
          twinkle->target_alpha = 0.89999998;
          twinkle->angle = ((double)next_math_random_value() - 16384.0) * 0.0001917476;
          if ( ((double)next_math_random_value() - 16384.0) * 0.000061035156 >= 0.0 )
            v16 = ((double)next_math_random_value() - 16384.0) * 0.000061035156 != 0.0;
          else
            v16 = -1;
          math_random_value = next_math_random_value();
          twinkle->delay_progress = 0.0;
          owner_widget = twinkle->owner_widget;
          twinkle->delay_step = 1.0;
          twinkle->angle_step = 1.0
                              / ((((double)math_random_value - 16384.0) * 0.000061035156 + 5.0)
                               * 60.0)
                              * (double)v16
                              * 6.2831855;
          v13 = (double)next_math_random_value() * (owner_widget->layout_width * 0.80000001) * 0.000030517578
              + owner_widget->layout_left;
          v14 = owner_widget->layout_width * 0.1;
          v15 = twinkle->owner_widget;
          twinkle->x = v13 + v14;
          twinkle->y = (double)next_math_random_value() * (v15->layout_height * 0.80000001) * 0.000030517578
                     + v15->layout_height * 0.1
                     + v15->layout_top;
          twinkle->size = ((double)next_math_random_value() - 16384.0) * 0.00073242188 + 25.0;
        }
      }
      break;
    case 2:
      v7 = (twinkle->target_alpha - twinkle->alpha) * 0.1 + twinkle->alpha;
      twinkle->alpha = v7;
      v8 = twinkle->target_alpha - v7;
      if ( v8 < 0.0 )
        v8 = -v8;
      if ( v8 < 0.0099999998 )
      {
        twinkle->target_alpha = 0.0;
        twinkle->state = 4;
      }
      draw_twinkle(twinkle);
      break;
    case 4:
      twinkle->alpha = (twinkle->target_alpha - twinkle->alpha) * 0.1 + twinkle->alpha;
      draw_twinkle(twinkle);
      v6 = twinkle->target_alpha - twinkle->alpha;
      if ( v6 < 0.0 )
        v6 = -v6;
      if ( v6 < 0.0099999998 )
      {
        twinkle->state = 1;
        twinkle->alpha = 0.0;
        twinkle->delay_progress = 0.0;
        twinkle->delay_step = 1.0 / (((double)next_math_random_value() * 0.000030517578 + 0.0099999998) * 60.0);
      }
      break;
  }
}
