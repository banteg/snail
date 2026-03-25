/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: destroy_loading_screen @ 0x418e50 */
/* selector: destroy_loading_screen */

// Tears down the loading-screen textures and preserves the last measured loading budget for the next loader pass.
int __thiscall sub_418E50(_DWORD *this)
{
  int result; // eax

  unk_4DF9C4 = *(this + 2);
  (*(void (__stdcall **)(int))(*(_DWORD *)MEMORY[0x503288] + 8))(MEMORY[0x503288]);
  result = (*(int (__stdcall **)(int))(*(_DWORD *)MEMORY[0x503280] + 8))(MEMORY[0x503280]);
  *this = 0;
  return result;
}

