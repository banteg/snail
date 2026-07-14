/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_default_runtime_config_thunk @ 0x406c10 */
/* selector: initialize_default_runtime_config_thunk */

// CRT initializer-table thunk that tail-calls the adjacent SnailMail.cfg default-state initializer.
// attributes: thunk
void __cdecl initialize_default_runtime_config_thunk()
{
  initialize_default_runtime_config();
}
