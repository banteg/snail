/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_global_identity_matrix @ 0x44c880 */
/* selector: initialize_global_identity_matrix */

// Startup wrapper that seeds the shared matrix at `data_77ff40` by calling `initialize_uniform_scale_matrix(..., 1.0)`. It is only referenced from the CRT constructor table.
_DWORD *sub_44C880()
{
  return initialize_uniform_scale_matrix(MEMORY[0x77FF40], 1065353216);
}

