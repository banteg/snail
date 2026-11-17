/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* export: isolated copy with manifest symbols applied */
/* function: initialize_global_noop_renderable_bods_thunk @ 0x406bc0 */
/* selector: initialize_global_noop_renderable_bods_thunk */

// CRT initializer-table thunk that tail-calls the adjacent constructor body for three otherwise-unreferenced renderable-derived globals.
// attributes: thunk
RenderableBod *initialize_global_noop_renderable_bods_thunk()
{
  return initialize_global_noop_renderable_bods();
}
