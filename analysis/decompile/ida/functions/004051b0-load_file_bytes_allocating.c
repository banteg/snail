/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: load_file_bytes_allocating @ 0x4051b0 */
/* selector: load_file_bytes_allocating */

// Loads one filesystem file into a freshly allocated byte buffer and optionally returns the byte length through the out parameter.
void *__cdecl sub_4051B0(char *FileName, #83 *a2)
{
  return load_file_bytes_into_optional_buffer(FileName, nullptr, a2);
}

