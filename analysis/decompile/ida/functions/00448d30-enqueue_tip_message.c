/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: enqueue_tip_message @ 0x448d30 */
/* selector: enqueue_tip_message */

// Allocates one of the three small gameplay tip-message slots, seeds it with the requested text payload, and warns if all slots are already occupied.
_DWORD *__thiscall sub_448D30(_DWORD *this, int a2, int a3)
{
  int v3; // eax
  _DWORD *i; // edx
  _DWORD *v6; // esi

  v3 = 0;
  for ( i = this + 14; *i; i += 8 )
  {
    if ( ++v3 >= 3 )
    {
      report_errorf(aRunOutOfTips);
      return nullptr;
    }
  }
  v6 = this + 8 * v3 + 14;
  initialize_tip(v6, a2, a3);
  return v6;
}

