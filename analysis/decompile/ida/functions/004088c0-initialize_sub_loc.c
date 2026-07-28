/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_sub_loc @ 0x4088c0 */
/* selector: initialize_sub_loc */

// Exact Windows `cRSubLoc` constructor wrapper: runs the shared `cRBod` base constructor, installs the cell-specific vtable, increments the global `LocCount`, and returns the receiver. The runtime-pool constructor calls it 25,600 times at a 0x54 stride over the complete cRSubLoc grid.
cRSubLoc *__thiscall initialize_sub_loc(cRSubLoc *cell)
{
  initialize_bod_base((BodBase *)cell);
  cell->bod.vtable = &g_sub_loc_vtable;
  ++g_sub_loc_count;
  return cell;
}
