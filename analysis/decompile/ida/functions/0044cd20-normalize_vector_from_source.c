/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: normalize_vector_from_source @ 0x44cd20 */
/* selector: normalize_vector_from_source */

// Copies a source vector and normalizes it in place. Android symbols match this helper to `tVector::Normalize(const tVector&)`.
void __thiscall normalize_vector_from_source(int this, _DWORD *a2)
{
  *(_DWORD *)this = *a2;
  *(_DWORD *)(this + 4) = a2[1];
  *(_DWORD *)(this + 8) = a2[2];
  normalize_vector((float *)this);
}

