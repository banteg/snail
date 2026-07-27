/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: find_segment_path_index_by_name @ 0x429ae0 */
/* selector: find_segment_path_index_by_name */

// Implements `cRPathManager::NameCode(char*)`: the stateless one-byte PathManager linearly searches the hardcoded 51-entry Path= name table and returns the matching index or -1.
int32_t __thiscall find_segment_path_index_by_name(PathManager *manager, char *name)
{
  int32_t v2; // edi
  char **v3; // esi

  v2 = 0;
  v3 = g_segment_path_name_0;
  while ( strings_equal_case_insensitive_path(name, *v3) == 0 )
  {
    ++v3;
    ++v2;
    if ( (int)v3 >= (int)g_segment_path_names_end )
      return -1;
  }
  return v2;
}
