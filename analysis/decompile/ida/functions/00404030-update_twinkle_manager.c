/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_twinkle_manager @ 0x404030 */
/* selector: update_twinkle_manager */

// Exact void cRTwinkleManager::AI(): walks the five inline 0x30-byte Twinkle records owned by one FrontendWidget while the manager is active. Its sole Windows and Android callers discard the result register; the native exits leave only state/count or nested-AI residue.
void __thiscall update_twinkle_manager(TwinkleManager *manager)
{
  int32_t v2; // esi
  TwinkleManager *v3; // edi

  if ( manager->active_state == 1 )
  {
    v2 = 0;
    if ( manager->twinkle_count > 0 )
    {
      v3 = manager;
      do
      {
        update_twinkle(v3->twinkles);
        ++v2;
        v3 = (TwinkleManager *)((char *)v3 + 48);
      }
      while ( v2 < manager->twinkle_count );
    }
  }
}
