/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: allocate_fringe_object @ 0x4470a0 */
/* selector: allocate_fringe_object */

// Allocates the next 0x38-byte object from the shared 7000-entry fringe-manager pool, or raises the `Too many Fringes` error if the pool overflows. Cross-port Android symbols match this helper to `cRFringeManager::GetFringe()`.
Fringe *__thiscall allocate_fringe_object(FringeManager *manager)
{
  int32_t count; // edx

  count = manager->count;
  if ( count == 7000 )
  {
    report_errorf(aTooManyFringes);
    return nullptr;
  }
  else
  {
    manager->count = count + 1;
    return &manager->objects[count];
  }
}
