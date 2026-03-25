/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_active_bod @ 0x4085e0 */
/* selector: initialize_active_bod */

// Initializes one shared active-bod runtime header by clearing its list links and installing the common subtype callback table at `data_497338`.
_DWORD *__thiscall sub_4085E0(_DWORD *this)
{
  initialize_bod_base(this);
  *this = &off_497338;
  return this;
}

