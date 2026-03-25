/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: stop_warning_sample @ 0x446f60 */
/* selector: stop_warning_sample */

int sub_446F60()
{
  int v0; // eax

  v0 = play_warning_sample_backend(50);
  return stop_warning_sample_handle(v0);
}

