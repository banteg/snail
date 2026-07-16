/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: find_registered_sound_sample_id_by_name @ 0x432fc0 */
/* selector: find_registered_sound_sample_id_by_name */

// Scans the registered sound-sample path/name table populated by `register_sound_sample` and returns the matching sample id for level `Sample="..."` message audio, reporting an error and returning 0 on miss.
int __cdecl find_registered_sound_sample_id_by_name(char *sample_name)
{
  int v1; // esi
  char *v2; // edi

  v1 = 0;
  if ( g_registered_sound_sample_count <= 0 )
  {
LABEL_5:
    report_errorf("Cannot Find Sample %s", sample_name);
    return 0;
  }
  else
  {
    v2 = g_registered_sound_sample_names[0];
    while ( !find_case_insensitive_substring(sample_name, v2) )
    {
      ++v1;
      v2 += 128;
      if ( v1 >= g_registered_sound_sample_count )
        goto LABEL_5;
    }
    return v1;
  }
}
