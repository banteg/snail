/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_border_record @ 0x408410 */
/* selector: initialize_border_record */

// Constructs one 0x724-byte front-end border/widget pool record by seeding the shared BOD header, no-op-constructing the constructor-proven color/style blocks, and installing the front-end widget callback table. `construct_game_runtime` uses it for the 150-entry `BorderManager::borders` pool at `game + 0x11d0`.
_DWORD *__thiscall initialize_border_record(_DWORD *this)
{
  initialize_bod_base(this);
  noop_this_constructor((ObjectVertexBufferVtbl *)(this + 27));
  noop_this_constructor((ObjectVertexBufferVtbl *)(this + 107));
  noop_this_constructor((ObjectVertexBufferVtbl *)(this + 111));
  noop_this_constructor((ObjectVertexBufferVtbl *)(this + 115));
  noop_this_constructor((ObjectVertexBufferVtbl *)(this + 119));
  noop_this_constructor((ObjectVertexBufferVtbl *)(this + 123));
  noop_this_constructor((ObjectVertexBufferVtbl *)(this + 127));
  *this = &g_frontend_widget_vtable;
  return this;
}
