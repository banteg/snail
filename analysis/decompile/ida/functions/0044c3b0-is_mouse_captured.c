/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: is_mouse_captured @ 0x44c3b0 */
/* selector: is_mouse_captured */

// Returns the capture-active byte at the head of the shared mouse-pointer state block stored at Game + 0x290.
char __thiscall sub_44C3B0(void *this)
{
  return *(_BYTE *)this;
}

