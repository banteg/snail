/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_intro_logo_renderable @ 0x408490 */
/* selector: initialize_intro_logo_renderable */

// Constructs one 0x90-byte Windows cRLogoLetter by running the shared renderable-BOD constructor and installing the callback table whose first entry is `update_intro_logo_renderable`. `construct_game_runtime` seeds both of the cRLogo owner's fixed child banks with this constructor.
cRLogoLetter *__thiscall initialize_intro_logo_renderable(cRLogoLetter *letter)
{
  initialize_renderable_bod(&letter->renderable);
  letter->renderable.bod.bod.vtable = g_logo_letter_vtable;
  return letter;
}
