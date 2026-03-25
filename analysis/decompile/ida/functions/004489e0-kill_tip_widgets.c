/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: kill_tip_widgets @ 0x4489e0 */
/* selector: kill_tip_widgets */

// Kills the live border widgets owned by one gameplay tip slot, including the main tip body and any optional OK or Disable buttons, then clears the tip's active flag.
void __thiscall sub_4489E0(_DWORD **this)
{
  kill_border(*(this + 3));
  if ( *(this + 4) )
    kill_border(*(this + 4));
  if ( *(this + 5) )
    kill_border(*(this + 5));
  *this = nullptr;
}

