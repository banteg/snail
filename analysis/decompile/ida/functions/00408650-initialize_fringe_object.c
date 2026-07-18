/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_fringe_object @ 0x408650 */
/* selector: initialize_fringe_object */

// Exact constructor wrapper for one authored `Fringe` (`cRFringe` cross-port): runs the shared body constructor, installs the Windows fringe vtable whose callback is 0x439b00, and returns the receiver. The runtime-pool constructor invokes it over the 7000-entry inline cRFringeManager array.
Fringe *__thiscall initialize_fringe_object(Fringe *fringe)
{
  initialize_bod_base(&fringe->bod);
  fringe->bod.bod.vtable = &g_fringe_vtable;
  return fringe;
}
