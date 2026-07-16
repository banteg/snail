/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: reset_registered_sound_sample_count @ 0x432d40 */
/* selector: reset_registered_sound_sample_count */

// Resets the registered runtime sound-sample table count before archive-backed audio registration begins.
void __cdecl reset_registered_sound_sample_count()
{
  g_registered_sound_sample_count = 0;
}
