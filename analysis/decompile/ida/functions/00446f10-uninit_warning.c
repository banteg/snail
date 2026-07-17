/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: uninit_warning @ 0x446f10 */
/* selector: uninit_warning */

// Releases the border owned by Player's embedded cRWarning. Android preserves this lifecycle edge as cRWarning::UnInit().
void __thiscall uninit_warning(Warning *warning)
{
  kill_border(&warning->border->list_kind);
}
