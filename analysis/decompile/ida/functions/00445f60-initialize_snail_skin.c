/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_snail_skin @ 0x445f60 */
/* selector: initialize_snail_skin */

void __thiscall initialize_snail_skin(SnailSkinTransitionState *state)
{
  char *v1; // eax

  v1 = (char *)MEMORY[0x4DF904];
  state->selected_slot = 0;
  state->active = 0;
  state->owner_render_state = v1 + 4400896;
}

