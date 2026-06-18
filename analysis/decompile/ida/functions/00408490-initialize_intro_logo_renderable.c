/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_intro_logo_renderable @ 0x408490 */
/* selector: initialize_intro_logo_renderable */

// Constructs one 0x90-byte intro/logo renderable by running the shared renderable-BOD constructor and installing the callback table whose first entry is `update_intro_logo_renderable`. `construct_game_runtime` seeds both the 1024-entry intro/credits text bank and the 32-entry logo row bank with this constructor.
_DWORD *__thiscall initialize_intro_logo_renderable(_DWORD *this)
{
  initialize_renderable_bod(this);
  *this = g_intro_logo_renderable_vtable;
  return this;
}
