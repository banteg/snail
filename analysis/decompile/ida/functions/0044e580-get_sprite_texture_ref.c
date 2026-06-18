/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: get_sprite_texture_ref @ 0x44e580 */
/* selector: get_sprite_texture_ref */

int __stdcall sub_44E580(int a1)
{
  return *(_DWORD *)(LODWORD(g_sprite_texture_table[a1]) + 152);
}

