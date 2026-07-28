/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: find_segment_path_index_by_name @ 0x429ae0 */
/* selector: find_segment_path_index_by_name */

// Implements `cRPathManager::NameCode(char*)`: Android and iOS preserve the exact authored class and member name, while Windows independently proves the empty one-byte owner at `SubgameRuntime +0xff2910`, the thiscall ABI, and the linear search over the hardcoded 51-entry Path= table. `PathManager` is retained only as a compatibility alias.
int32_t __thiscall find_segment_path_index_by_name(cRPathManager *manager, char *name)
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
