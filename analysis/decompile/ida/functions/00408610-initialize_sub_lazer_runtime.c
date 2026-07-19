/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_sub_lazer_runtime @ 0x408610 */
/* selector: initialize_sub_lazer_runtime */

// Exact constructor wrapper for one authored `SubLazer` (`cRSubLazer` cross-port): constructs the renderable-body prefix, installs the table whose entry is update_sub_lazer_projectile, and returns the receiver. The 20 inline 0xb0-byte records owned by SubLazerManager total the native 0xdc0 size ledger.
SubLazer *__thiscall initialize_sub_lazer_runtime(SubLazer *sub_lazer)
{
  initialize_renderable_bod(&sub_lazer->body);
  sub_lazer->body.bod.bod.vtable = &g_sub_lazer_vtable;
  return sub_lazer;
}
