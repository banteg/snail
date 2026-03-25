/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: close_galaxy_route @ 0x409bf0 */
/* selector: close_galaxy_route */

// Closes the currently open Star Map route card, clears its active replay or play controls, and resets the open-route selection before another route is opened. Cross-port Android and iOS symbols match this helper to `cRGalaxy::BoxOff()`.
void __thiscall sub_409BF0(int this)
{
  _DWORD *v2; // ecx

  v2 = *(_DWORD **)(this + 69516);
  *(_DWORD *)(this + 8) = 0;
  *(_DWORD *)(this + 69504) = -1;
  hide_border_init(v2);
  hide_border_init(*(_DWORD **)(this + 69520));
  hide_border_init(*(_DWORD **)(this + 69524));
  hide_border_init(*(_DWORD **)(this + 69528));
  hide_border_init(*(_DWORD **)(this + 69532));
  hide_border_init(*(_DWORD **)(this + 69536));
}

