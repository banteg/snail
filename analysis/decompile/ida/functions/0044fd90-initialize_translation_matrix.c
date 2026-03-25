/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_translation_matrix @ 0x44fd90 */
/* selector: initialize_translation_matrix */

// Builds a 4x4 identity matrix with the supplied xyz translation in slots `+0x30/+0x34/+0x38`. `draw_sprite_quad` uses this helper to place one sprite quad in world space before submission.
int __stdcall sub_44FD90(int a1, int a2, int a3, int a4)
{
  *(float *)(a1 + 44) = 0.0;
  *(_DWORD *)(a1 + 48) = a2;
  *(float *)(a1 + 36) = 0.0;
  *(_DWORD *)(a1 + 52) = a3;
  *(float *)(a1 + 32) = 0.0;
  *(_DWORD *)(a1 + 56) = a4;
  *(float *)(a1 + 28) = 0.0;
  *(float *)(a1 + 24) = 0.0;
  *(float *)(a1 + 16) = 0.0;
  *(float *)(a1 + 12) = 0.0;
  *(float *)(a1 + 8) = 0.0;
  *(float *)(a1 + 4) = 0.0;
  *(float *)(a1 + 60) = 1.0;
  *(float *)(a1 + 40) = 1.0;
  *(float *)(a1 + 20) = 1.0;
  *(float *)a1 = 1.0;
  return a1;
}

