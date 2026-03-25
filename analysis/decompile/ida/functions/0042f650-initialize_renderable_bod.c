/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_renderable_bod @ 0x42f650 */
/* selector: initialize_renderable_bod */

// Builds the shared renderable bod shell on top of the base bod header, seeding its object-oriented vtable, default render flags, and identity local transform.
_DWORD *__thiscall sub_42F650(_DWORD *this)
{
  initialize_bod_base(this);
  *this = &off_497500;
  *(this + 1) = 33555488;
  set_matrix_identity(this + 14);
  return this;
}

