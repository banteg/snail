/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: zero_vector3 @ 0x410710 */
/* selector: zero_vector3 */

// Zeroes the x, y, and z components of one 12-byte Vector3. All five known callsites target embedded BodBase position vectors: four path/fringe positions in auxiliary loopout pair 60 and the shared barrier position.
int __thiscall zero_vector3(_DWORD *this)
{
  *(this + 2) = 0;
  *(this + 1) = 0;
  *this = 0;
  return 0;
}
