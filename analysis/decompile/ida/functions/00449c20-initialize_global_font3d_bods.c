/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_global_font3d_bods @ 0x449c20 */
/* selector: initialize_global_font3d_bods */

// Runs the BodBase constructor over all 128 entries of the global 3D-font BOD pool at a 0x38-byte stride.
void __cdecl initialize_global_font3d_bods()
{
  BodBase *v0; // esi
  int v1; // edi

  v0 = g_font3d_bods;
  v1 = 128;
  do
  {
    initialize_bod_base(v0++);
    --v1;
  }
  while ( v1 );
}
