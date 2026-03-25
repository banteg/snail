/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_directx_loader @ 0x405c90 */
/* selector: initialize_directx_loader */

_BYTE *__thiscall sub_405C90(_DWORD *this)
{
  *(this + 1) = 0;
  *this = load_file_bytes(aXAnimationTxt, nullptr);
  return initialize_duplicate_vertices(this + 6018, 2000);
}

