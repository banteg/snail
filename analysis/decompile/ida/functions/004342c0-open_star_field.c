/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: open_star_field @ 0x4342c0 */
/* selector: open_star_field */

// Allocates the persistent star-field controller storage and, when the global star-pass flag is enabled, immediately initializes one sprite-based streak entry per requested slot.
char __thiscall sub_4342C0(_DWORD *this, int a2)
{
  char result; // al

  *(this + 15) = allocate_tracked_memory(44 * a2, (int)aStarfield);
  *(this + 16) = a2;
  result = byte_4DF934;
  if ( (byte_4DF934 & 4) != 0 )
  {
    *(this + 14) = 1;
    return initialize_star_field(this);
  }
  else
  {
    *(this + 14) = 0;
  }
  return result;
}

