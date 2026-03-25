/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: begin_frontend_fade_out @ 0x40abc0 */
/* selector: begin_frontend_fade_out */

// Requests the shared front-end black transition overlay to fade from clear to full black and hold before a screen handoff.
int __thiscall sub_40ABC0(_DWORD *this, int a2)
{
  *this = 2;
  *(this + 1) = 0;
  *(this + 4) = a2;
  return a2;
}

