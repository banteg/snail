/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_cutscene_ai @ 0x446130 */
/* selector: initialize_cutscene_ai */

// Authored `cRCutScene::Init()`: initializes the exact 0x5c-byte CutScene embedded at `Snail + 0x1958` (`Player + 0x42dc`), wiring its Snail/Player backlinks and clearing state.
void __thiscall initialize_cutscene_ai(CutScene *cutscene)
{
  Player *p_player; // edx

  cutscene->presentation = &g_game_base->subgame.player.presentation;
  p_player = &g_game_base->subgame.player;
  cutscene->state = CUT_SCENE_STATE_INACTIVE;
  cutscene->player = p_player;
}
