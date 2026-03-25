/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: get_archive_data_base @ 0x431a90 */
/* selector: get_archive_data_base */

// Returns the base pointer of the loaded SnailMail.dat payload buffer used by archive-backed mesh, voice, and object-definition readers.
int sub_431A90()
{
  return MEMORY[0x53C7EC];
}

