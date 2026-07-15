/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_garbage_hazard @ 0x408550 */
/* selector: initialize_garbage_hazard */

// Exact Windows constructor for one authored `SubGarbage` (`cRSubGarbage` cross-port): constructs the inherited renderable BOD and installs the table whose entry is `update_garbage_hazard`. `initialize_runtime_pools_and_path_template_bank` walks 50 inline 0xc4-byte records, and the resulting 0x2648 extent exactly matches the native `Size of cRSubGarbage` ledger.
SubGarbage *__thiscall initialize_garbage_hazard(SubGarbage *sub_garbage)
{
  initialize_renderable_bod(sub_garbage);
  sub_garbage->body.bod.bod.vtable = &g_sub_garbage_vtable;
  return sub_garbage;
}
