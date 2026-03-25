/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: save_file_bytes_with_optional_archive_scramble @ 0x4052a0 */
/* selector: save_file_bytes_with_optional_archive_scramble */

// Writes one byte buffer to the filesystem and optionally applies the archive rebuild scramble before the write.
int __cdecl save_file_bytes_with_optional_archive_scramble(char *FileName, void *Buffer, int ElementCount, char a4)
{
  #91 *v4; // esi
  char DstBuf[512]; // [esp+10h] [ebp-200h] BYREF

  if ( a4 )
    scramble_archive_bytes_in_place((int)Buffer, ElementCount);
  v4 = fopen(FileName, aWb);
  if ( v4 )
  {
    printf("Saving file :%s %i bytes\n", FileName, ElementCount);
    fwrite(Buffer, 1, ElementCount, v4);
    return fclose(v4);
  }
  else
  {
    _getcwd(DstBuf, 512);
    return printf("ERROR:Cannot save file : %s (from %s)\n", FileName, DstBuf);
  }
}

