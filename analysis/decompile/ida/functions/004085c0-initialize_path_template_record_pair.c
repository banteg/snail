/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_path_template_record_pair @ 0x4085c0 */
/* selector: initialize_path_template_record_pair */

// Constructs both 0x18-byte record halves for one paired path-template object and installs the shared vtable.
_DWORD *__thiscall sub_4085C0(_DWORD *this)
{
  initialize_bod_base(this);
  initialize_bod_base(this + 24);
  *this = off_497334;
  return this;
}

