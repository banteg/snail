/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_help_screen @ 0x4168d0 */
/* selector: update_help_screen */

// Handles the Help-screen Back action, tears down the shell-font scene, and returns control to the New Game front-end flow via state `2`. Cross-port Android and iOS symbols match this helper to `cRHelp::AI()`.
void *__thiscall sub_4168D0(void *this)
{
  void *result; // eax

  result = *(void **)(*(_DWORD *)this + 416);
  if ( ((unsigned __int8)result & 0x20) != 0 )
  {
    LOBYTE(result) = (unsigned __int8)result & 0xDF;
    *(_DWORD *)(*(_DWORD *)this + 416) = result;
    destroy_help_screen();
    result = MEMORY[0x4DF904];
    *((_DWORD *)MEMORY[0x4DF904] + 110) = 2;
    *((_BYTE *)MEMORY[0x4DF904] + 780) = 1;
  }
  return result;
}

