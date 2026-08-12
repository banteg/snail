/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: validate_config_tail_stub @ 0x42f5b0 */
/* selector: validate_config_tail_stub */

// Exact Windows `gRegisterTestRegisterKey(char*)`: the registration-disabled build ignores the key/config-tail pointer and returns true. Android preserves the same symbol, argument, and unconditional-success body.
unsigned __int8 __cdecl validate_config_tail_stub(char *registration_key)
{
  return 1;
}
