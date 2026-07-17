/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: show_times_up_message @ 0x445e90 */
/* selector: show_times_up_message */

// Exact Windows `TimesUp::show_times_up_message`: spawns the floating `Time's Up` widget and seeds its progress lanes once the subgame timer reaches its terminal threshold. Android and iOS retain this member as `cRTimesUp::Init()`.
void __thiscall show_times_up_message(TimesUp *times_up)
{
  tColour *v2; // eax
  Color4f color; // [esp+4h] [ebp-10h] BYREF

  if ( times_up->state == TIMES_UP_STATE_INACTIVE )
  {
    times_up->border = allocate_border(&g_game_base->border_manager);
    v2 = set_color_rgba((tColour *)&color, 1.0, 1.0, 1.0, 0.029999999);
    initialize_frontend_widget(times_up->border, 0x400002u, aTimeSUp, 20, 0.0, 200.0, v2, 2, 0.0);
    times_up->progress = 0.0;
    times_up->progress_step = 0.0055555557;
    times_up->state = TIMES_UP_STATE_DISPLAYING;
  }
}
