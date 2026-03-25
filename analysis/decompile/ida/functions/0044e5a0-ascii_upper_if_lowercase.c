/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: ascii_upper_if_lowercase @ 0x44e5a0 */
/* selector: ascii_upper_if_lowercase */

char __cdecl sub_44E5A0(char a1)
{
  char result; // al

  result = a1;
  if ( a1 >= 97 && a1 <= 122 )
    return a1 - 32;
  return result;
}

