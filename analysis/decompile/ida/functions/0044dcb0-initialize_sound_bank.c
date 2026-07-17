/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_sound_bank @ 0x44dcb0 */
/* selector: initialize_sound_bank */

// Exact Windows `cRSound::Init(cRSoundBank*)` member: registers the 51 shipped `g_sound_bank_entries` records, stores each returned sample id at record `+0x04`, and stops at the 52nd record whose path points at an empty string. Android names the corresponding global `gSFXBank` and preserves the same 12-byte record layout.
void __thiscall initialize_sound_bank(SoundEffectManager *manager, SoundBankEntry *entries)
{
  SoundBankEntry *v2; // esi
  char *path; // eax
  SoundBankEntry *v4; // edi

  v2 = entries;
  path = entries->path;
  if ( *entries->path )
  {
    v4 = entries;
    do
    {
      ++v2;
      v4->sample_id = register_sound_sample(path, v4->normalization_class);
      v4 = v2;
      path = v2->path;
    }
    while ( *v2->path );
  }
}
