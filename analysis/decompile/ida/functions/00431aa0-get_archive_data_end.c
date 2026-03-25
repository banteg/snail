/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: get_archive_data_end @ 0x431aa0 */
/* selector: get_archive_data_end */

// Returns the end pointer of the fixed-size loaded archive payload window; current Windows callers use it as the upper bound when walking archive-backed texture-group buffers.
int sub_431AA0()
{
  return MEMORY[0x53C7EC] + 0x200000;
}

