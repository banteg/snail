/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_default_runtime_config @ 0x406c10 */
/* selector: initialize_default_runtime_config */

// Seeds the 0xc4-byte SnailMail.cfg blob with default sound volume, music volume, fullscreen, progression, and tuning values before any file overlay is loaded.
// attributes: thunk
int initialize_default_runtime_config()
{
  return sub_406C20();
}

