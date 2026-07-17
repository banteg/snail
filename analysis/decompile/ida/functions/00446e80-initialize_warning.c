/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_warning @ 0x446e80 */
/* selector: initialize_warning */

// Initializes the exact 0x10-byte Windows cRWarning owner embedded in Player at +0x3f4: allocates and hides its border, then resets the phase state. Android and iOS retain cRWarning::Init, with wider mobile presentation layouts.
void __thiscall initialize_warning(Warning *warning)
{
  tColour *v2; // eax
  Color4f color; // [esp+4h] [ebp-10h] BYREF

  warning->border = allocate_border(&g_game_base->border_manager);
  v2 = set_color_rgba((tColour *)&color, 1.0, 1.0, 1.0, 0.99900001);
  initialize_frontend_sprite_button((int)warning->border, 4196354, 94, 1133510656, 1115684864, v2, 0.0, 4);
  warning->border->sprite_shadow_offset = 0.0;
  hide_border_init(warning->border);
  warning->phase_step = 0.083333336;
  warning->phase = 0.0;
  warning->state = WARNING_STATE_INACTIVE;
}
