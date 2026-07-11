/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: find_segment_path_index_by_name @ 0x429ae0 */
/* selector: find_segment_path_index_by_name */

// Implements cRPathManager::NameCode(char*): linearly searches the hardcoded 51-entry Path= name table and returns the matching index or -1. This pre-sync decompile presents the call as stdcall because the one-byte PathManager receiver is unused; the thiscall method has the same emitted body and ret 4 ABI.
int __stdcall find_segment_path_index_by_name(char *a1)
{
  int v1; // edi
  char **v2; // esi

  v1 = 0;
  v2 = off_4A3D6C;
  while ( !sub_44E6C0(a1, *v2) )
  {
    ++v2;
    ++v1;
    if ( (int)v2 >= (int)aToadpair1 )
      return -1;
  }
  return v1;
}
