/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: show_times_up_message @ 0x445e90 */
/* selector: show_times_up_message */

// Spawns the floating `Time's Up` gameplay message once the subgame timer hits its terminal threshold.
void __thiscall sub_445E90(int *this)
{
  _DWORD *v2; // eax
  _DWORD v3[4]; // [esp+4h] [ebp-10h] BYREF

  if ( !*this )
  {
    *(this + 1) = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
    v2 = set_color_rgba(v3, 1065353216, 1065353216, 1065353216, 1022739087);
    initialize_frontend_widget(*(this + 1), 4194306, aTimeSUp, 20, 0, 200.0, (int)v2, 2, 0.0);
    *(this + 2) = 0;
    *(this + 3) = 1001786209;
    *this = 1;
  }
}

