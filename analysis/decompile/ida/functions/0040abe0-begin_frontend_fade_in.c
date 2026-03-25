/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: begin_frontend_fade_in @ 0x40abe0 */
/* selector: begin_frontend_fade_in */

// Seeds the shared front-end black transition overlay at full black so the next screen fades in over 18 updates.
void __thiscall sub_40ABE0(_DWORD *this)
{
  *this = 1;
  *(this + 1) = 1065353216;
}

