/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: destroy_completion_screen @ 0x406060 */
/* selector: destroy_completion_screen */

// Tears down the active completion-screen widgets and restores the owning front-end state once the current exit choice resolves. Cross-port Android and iOS symbols match this helper to `cRCompletion::UnInit()`.
int __thiscall destroy_completion_screen(CompletionPrompt *prompt)
{
  int result; // eax

  kill_border(prompt->prompt_title->_pad_00);
  kill_border(prompt->yes_button->_pad_00);
  kill_border(prompt->no_button->_pad_00);
  result = unhide_all_borders((int *)MEMORY[0x4DF904] + 723);
  *((_DWORD *)MEMORY[0x4DF904] + 110) = prompt->previous_frontend_state;
  return result;
}

