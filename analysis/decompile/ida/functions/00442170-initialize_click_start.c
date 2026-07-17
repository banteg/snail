/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_click_start @ 0x442170 */
/* selector: initialize_click_start */

// Exact Windows `ClickStart::initialize_click_start`, authored as `cRClickStart::Init(cRSubGoldy*)`: initializes the 0xac-byte child at Player +0xa0, stores its borrowed Player backlink, links it through `GameRoot::active_bod_list`, seeds the prompt and state, and applies `SubgameRuntime::replay_launch_active` as the initial hide gate.
void __thiscall initialize_click_start(ClickStart *click_start, Player *player)
{
  tColour *v3; // eax
  uint32_t list_flags; // eax
  BodNode **p_first; // eax
  BodNode *first; // ecx
  struct BodNode *list_prev; // ecx
  Player *owner_player; // edx
  FrontendWidget *prompt; // ecx
  Color4f color; // [esp+8h] [ebp-10h] BYREF

  click_start->prompt = allocate_border(&g_game_base->border_manager);
  v3 = set_color_rgba((tColour *)&color, 1.0, 1.0, 1.0, 0.029999999);
  initialize_frontend_widget(click_start->prompt, 0x400002u, aClickToStart, 20, 0.0, 200.0, v3, 2, 0.0);
  hide_border_init(click_start->prompt);
  list_flags = click_start->bod.bod.bod.list_flags;
  click_start->hide_prompt = 1;
  click_start->owner_player = player;
  if ( (list_flags & 0x200) != 0 )
  {
    report_errorf(aListAdd);
  }
  else
  {
    p_first = &g_game_base->active_bod_list.first;
    first = g_game_base->active_bod_list.first;
    if ( first )
    {
      first->list_prev = &click_start->bod.bod.bod;
      (*p_first)->list_prev->list_next = *p_first;
      list_prev = (*p_first)->list_prev;
      *p_first = list_prev;
      list_prev->list_prev = nullptr;
    }
    else
    {
      *p_first = &click_start->bod.bod.bod;
      click_start->bod.bod.bod.list_prev = nullptr;
      (*p_first)->list_next = nullptr;
    }
    click_start->bod.bod.bod.list_flags |= 0x200u;
  }
  owner_player = click_start->owner_player;
  click_start->state = CLICK_START_STATE_WAITING_FOR_START;
  owner_player->startup_track_index = 0;
  click_start->bod.bod.render_arg_1c = 0.0;
  click_start->bod.bod.render_arg_20 = 0.0;
  prompt = click_start->prompt;
  if ( g_game_base->subgame.selected_level_record_active )
    hide_border_init(prompt);
  else
    unhide_border_init(prompt);
}
