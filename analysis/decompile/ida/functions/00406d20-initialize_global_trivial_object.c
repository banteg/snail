/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* export: isolated copy with manifest symbols applied */
/* function: initialize_global_trivial_object @ 0x406d20 */
/* selector: initialize_global_trivial_object */

// Invokes the folded no-op default constructor for the otherwise-unreferenced 16-byte global object at 0x4df848; no surviving consumer distinguishes its original class.
void *initialize_global_trivial_object()
{
  return noop_this_constructor(&g_startup_trivial_object);
}
