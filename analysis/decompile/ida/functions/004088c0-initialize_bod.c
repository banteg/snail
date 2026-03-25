/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_bod @ 0x4088c0 */
/* selector: initialize_bod */

// Constructs one `cRBod` record by clearing its shared list links, installing the body update selector, and incrementing the global Bod-count ledger used by `construct_game_runtime`.
_DWORD *__thiscall sub_4088C0(_DWORD *this)
{
  initialize_bod_base(this);
  *this = &off_497368;
  ++unk_4DFADC;
  return this;
}

