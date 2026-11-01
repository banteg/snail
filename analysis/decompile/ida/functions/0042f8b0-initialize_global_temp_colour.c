/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* export: isolated copy with manifest symbols applied */
/* function: initialize_global_temp_colour @ 0x42f8b0 */
/* selector: initialize_global_temp_colour */

// Runs the folded no-op tColour constructor for the 16-byte global at `data_503308`. The matching symbol-preserving iOS owner is `GTempColour`, also exactly 16 bytes before its next global.
void *initialize_global_temp_colour()
{
  return noop_this_constructor(&g_temp_colour);
}
