/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: play_registered_sound_sample_scaled @ 0x4499a0 */
/* selector: play_registered_sound_sample_scaled */

// Plays one registered runtime sample through the BASS sample backend with the supplied normalized gain scale and the default extra playback parameters.
void __stdcall sub_4499A0(int a1, float a2)
{
  if ( a2 >= 0.0 )
  {
    if ( a2 <= 1.0 )
    {
      if ( a2 == 0.0 )
        return;
    }
    else
    {
      a2 = 1.0;
    }
    MEMORY[0x7527B4](unk_7537E0[a1], 0, -1, (__int64)(a2 * 100.0), 0, -1);
  }
}

