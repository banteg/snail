/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: allocate_fringe_object @ 0x4470a0 */
/* selector: allocate_fringe_object */

// Allocates the next 0x38-byte object from the shared 7000-entry fringe-manager pool, or raises the `Too many Fringes` error if the pool overflows. Cross-port Android symbols match this helper to `cRFringeManager::GetFringe()`.
_DWORD *__thiscall sub_4470A0(_DWORD *this)
{
  int v1; // edx

  v1 = *(this + 98000);
  if ( v1 == 7000 )
  {
    report_errorf(aTooManyFringes);
    return nullptr;
  }
  else
  {
    *(this + 98000) = v1 + 1;
    return this + 14 * v1;
  }
}

