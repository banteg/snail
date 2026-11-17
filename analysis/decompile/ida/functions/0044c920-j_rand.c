/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* export: isolated copy with manifest symbols applied */
/* function: j_rand @ 0x44c920 */
/* selector: j_rand */

// Game-code jump thunk to the statically linked CRT rand body, shared by the signed and unsigned random-float scaling helpers.
// attributes: thunk
int __cdecl j_rand()
{
  return rand();
}
