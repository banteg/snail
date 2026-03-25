/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: build_track_colours @ 0x435d40 */
/* selector: build_track_colours */

int sub_435D40()
{
  int i; // esi
  int result; // eax

  for ( i = 0; i < 816; i += 16 )
  {
    set_color_white((char *)&unk_74E7E8 + i);
    set_color_white((char *)&unk_6437F8 + i);
    set_color_white((char *)&unk_643B28 + i);
    set_color_white((char *)&MEMORY[0x53CB30] + i);
    set_color_white((char *)&MEMORY[0x53CE60] + i);
    set_color_white((char *)&unk_6434C8 + i);
    set_color_white((char *)&unk_6444B8 + i);
    set_color_white((char *)&unk_644188 + i);
    set_color_white((char *)&unk_643E58 + i);
    set_color_white((char *)&MEMORY[0x53C800] + i);
    set_color_white((char *)&MEMORY[0x53C800] + i);
    set_color_white((char *)&unk_643198 + i);
    result = set_color_white((char *)&unk_643198 + i);
  }
  return result;
}

