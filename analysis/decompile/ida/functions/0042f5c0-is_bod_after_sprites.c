/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: is_bod_after_sprites @ 0x42f5c0 */
/* selector: is_bod_after_sprites */

// Returns whether one body should draw after sprites; iOS RObject.o names this `cRBod::IsAfterSprites()`.
bool __thiscall is_bod_after_sprites(BodBase *bod)
{
  return SLOBYTE(bod->bod.list_flags) < 0;
}
