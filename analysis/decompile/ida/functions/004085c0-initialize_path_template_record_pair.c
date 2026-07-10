/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_path_template_record_pair @ 0x4085c0 */
/* selector: initialize_path_template_record_pair */

// Constructs one 0xa8-byte path-template record by initializing its leading BodBase and embedded fringe BodBase at +0x60, then installs the shared callback table. The retained historical name says pair, but the primary/secondary path pair consists of two adjacent calls/records.
_DWORD *__thiscall initialize_path_template_record_pair(_DWORD *this)
{
  initialize_bod_base(this);
  initialize_bod_base(this + 24);
  *this = g_path_template_record_vtable;
  return this;
}

