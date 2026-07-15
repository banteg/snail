/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_slug_hazard_runtime @ 0x408530 */
/* selector: initialize_slug_hazard_runtime */

// Exact Windows constructor for one authored `Slug` (`cRSlug` cross-port): constructs the inherited renderable BOD and installs the table whose entry is `update_slug_hazard_ai`. `initialize_runtime_pools_and_path_template_bank` walks eight inline 0xec-byte records whose 0x760 extent exactly matches the native `Size of cRSlug` ledger.
Slug *__thiscall initialize_slug_hazard_runtime(Slug *slug)
{
  initialize_renderable_bod(slug);
  slug->body.bod.bod.vtable = g_slug_vtable;
  return slug;
}
