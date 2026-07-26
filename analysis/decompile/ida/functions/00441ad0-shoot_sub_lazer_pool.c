/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: shoot_sub_lazer_pool @ 0x441ad0 */
/* selector: shoot_sub_lazer_pool */

// Exact `cRSubLazerManager::Shoot(tVector, tVector)`: scans the manager's 20 inline actors for SUB_LAZER_STATE_INACTIVE, dispatches that actor's Shoot method, and plays the positional fire cue. Android and iOS independently preserve the manager owner and signature. The formerly misassigned `shoot_subgoldy` alias now belongs to the actual Windows `cRSubGoldy::Shoot(cRSubGoldy*)` at 0x43a300.
void __thiscall shoot_sub_lazer_pool(SubLazerManager *manager, Vec3 *origin, const Vec3 *direction)
{
  int v4; // eax
  SubLazerState *i; // ecx
  float v6; // [esp+Ch] [ebp-14h]
  float z; // [esp+10h] [ebp-10h]
  Vec3 v8; // [esp+14h] [ebp-Ch] BYREF

  v4 = 0;
  for ( i = &manager->slots[0].state; *i != SUB_LAZER_STATE_INACTIVE; i += 44 )
  {
    if ( ++v4 >= 20 )
      return;
  }
  z = origin->z;
  v8.x = origin->x;
  v6 = (double)v4 * -0.0099999998 + origin->y;
  v8.y = v6;
  v8.z = z;
  spawn_sub_lazer_projectile(&manager->slots[v4], &v8, direction);
  play_sound_effect_at_position(&g_sound_effect_manager, 15, origin);
}
