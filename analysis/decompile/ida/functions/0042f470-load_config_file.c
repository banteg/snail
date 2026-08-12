/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: load_config_file @ 0x42f470 */
/* selector: load_config_file */

// Exact Windows `gRegisterLoadFile(char*, void*)` overload: forwards the file name and caller buffer to the four-argument Register.o loader with null size output and a zero byte-count override. Android preserves the same overload chain, while iOS Register.o forwards this overload directly to MacLoadFile.
void *__cdecl load_config_file(char *file_name, void *buffer)
{
  return load_file_bytes_from_path(file_name, buffer, nullptr, 0);
}
