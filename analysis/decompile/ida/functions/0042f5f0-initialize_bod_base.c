/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_bod_base @ 0x42f5f0 */
/* selector: initialize_bod_base */

// Initializes the shared bod header and default state: noop runtime AI callback, default flags, white color block, cleared linkage fields, and the global bod counter increment.
_DWORD *__thiscall sub_42F5F0(_DWORD *this)
{
  _DWORD *v2; // edi

  v2 = this + 10;
  Iostream_init::Iostream_init((#93 *)(this + 10));
  *this = off_4974FC;
  *(this + 1) = 33554464;
  sub_44DBB0(v2, 1065353216, 1065353216, 1065353216, 1065353216);
  ++MEMORY[0x50331C];
  *(this + 6) = 0;
  *(this + 5) = 0;
  *(this + 4) = 0;
  *(this + 7) = 0;
  *(this + 8) = 0;
  return this;
}

