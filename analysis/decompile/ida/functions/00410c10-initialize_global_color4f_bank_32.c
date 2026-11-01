/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* export: isolated copy with manifest symbols applied */
/* function: initialize_global_color4f_bank_32 @ 0x410c10 */
/* selector: initialize_global_color4f_bank_32 */

// Runs the folded no-op tColour constructor across the exact 32-entry global allocation at `data_4f6e50`. No runtime consumer or cross-port symbol supports a more specific semantic owner.
ObjectVertexBufferVtbl *initialize_global_color4f_bank_32()
{
  ObjectVertexBufferVtbl *v0; // esi
  int i; // edi
  ObjectVertexBufferVtbl *result; // eax

  v0 = &g_color4f_bank_32;
  for ( i = 32; i != 0; --i )
  {
    result = (ObjectVertexBufferVtbl *)noop_this_constructor(v0);
    v0 = (ObjectVertexBufferVtbl *)((char *)v0 + 16);
  }
  return result;
}
