/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: shoot_subgoldy @ 0x441ad0 */
/* selector: shoot_subgoldy */

// Exact `cRSubLazerManager::Shoot(tVector, tVector)`: finds a free SubLazer in the manager's 20 inline slots, dispatches its Shoot method, and plays the positional fire cue. Cross-port iOS v1.5 preserves the manager signature.
void __thiscall shoot_subgoldy(SubLazerManager *manager, Vec3 *origin, const Vec3 *direction)
{
  int v4; // eax
  uint32_t *i; // ecx
  float v6; // [esp+Ch] [ebp-14h]
  float z; // [esp+10h] [ebp-10h]
  Vec3 v8; // [esp+14h] [ebp-Ch] BYREF

  v4 = 0;
  for ( i = &manager->slots[0].state; *i; i += 44 )
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
