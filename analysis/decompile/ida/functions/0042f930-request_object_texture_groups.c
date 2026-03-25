/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: request_object_texture_groups @ 0x42f930 */
/* selector: request_object_texture_groups */

_BYTE *__thiscall sub_42F930(_DWORD *this, int a2)
{
  _BYTE *result; // eax

  if ( *(this + 25) )
  {
    result = (_BYTE *)*(this + 26);
    if ( a2 > (int)result )
      result = (_BYTE *)report_errorf(aFixedFacequadt);
    *(this + 25) = a2;
  }
  else
  {
    result = allocate_tracked_memory(4 * a2, (int)aObjectFacequad_1);
    *(this + 26) = a2;
    *(this + 25) = a2;
    *(this + 27) = result;
  }
  return result;
}

