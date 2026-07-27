/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: ascii_upper_if_lowercase @ 0x44e5a0 */
/* selector: ascii_upper_if_lowercase */

// Exact Windows `RstrASC(char)`: folds one lowercase ASCII byte to uppercase and leaves all other byte values unchanged.
char __cdecl ascii_upper_if_lowercase(char value)
{
  char result; // al

  result = value;
  if ( value >= 97 && value <= 122 )
    return value - 32;
  return result;
}
