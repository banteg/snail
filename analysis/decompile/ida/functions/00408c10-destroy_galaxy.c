/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: destroy_galaxy @ 0x408c10 */
/* selector: destroy_galaxy */

// Tears down the active Star Map galaxy-screen widgets before replay launch, route handoff, or return to the owning front-end state. Cross-port Android symbols match this helper to `cRGalaxy::UnInit()`.
void __thiscall sub_408C10(_DWORD **this)
{
  kill_border(*(this + 17374));
  kill_border(*(this + 17375));
  kill_border(*(this + 17373));
  kill_border(*(this + 17379));
  kill_border(*(this + 17380));
  kill_border(*(this + 17382));
  kill_border(*(this + 17381));
  kill_border(*(this + 17383));
  kill_border(*(this + 17384));
}

