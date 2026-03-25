/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: get_track_cell_row_index @ 0x447040 */
/* selector: get_track_cell_row_index */

int __thiscall sub_447040(_DWORD *this)
{
  return ((char *)(this - 21 * (*(this + 16) & 7)) - (_BYTE *)MEMORY[0x4DF904] - 4407520) / 84 / 8;
}

