/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_star_positions @ 0x434800 */
/* selector: update_star_positions */

// Advances each star-field streak along its cached direction, resets wrapped entries against the current camera origin, and scales the visible sprite trail by both per-streak speed and the controller fade factor. Cross-port Android and iOS symbols match this member to `cRStarManager::UpdateStars(float)`.
void __thiscall update_star_positions(cRStarManager *manager, float fade_alpha)
{
  int32_t v2; // edi
  int v3; // edx
  float *p_travel_distance; // esi
  StarManagerEntry *v5; // eax
  Vec3 *p_velocity; // esi
  Vec3 *v7; // eax
  StarManagerEntry *v8; // eax
  double v9; // st7
  double v10; // st6
  float *p_x; // eax
  StarManagerEntry *v12; // eax
  float v13; // [esp+14h] [ebp-14h]
  float v14; // [esp+18h] [ebp-10h]
  float v15; // [esp+20h] [ebp-8h]
  float v16; // [esp+24h] [ebp-4h]
  Vec3 v17; // 0:^C.12

  v2 = 0;
  if ( manager->count > 0 )
  {
    v3 = 0;
    do
    {
      manager->entries[v3].travel_distance = manager->entries[v3].speed + manager->entries[v3].travel_distance;
      p_travel_distance = &manager->entries[v3].travel_distance;
      if ( *p_travel_distance > 35.0 )
      {
        *p_travel_distance = 0.0;
        manager->entries[v3].sprite->facing_refresh_progress = 0.0;
        v13 = g_game_base->overlay_0.bod.transform.basis_forward.y * 50.0;
        v14 = g_game_base->overlay_0.bod.transform.basis_forward.z * 50.0;
        v17.x = g_game_base->overlay_0.bod.transform.basis_forward.x * 50.0
              + g_game_base->overlay_0.bod.transform.position.x;
        v17.y = v13 + g_game_base->overlay_0.bod.transform.position.y;
        v17.z = v14 + g_game_base->overlay_0.bod.transform.position.z;
        manager->entries[v3].sprite->position = v17;
        v5 = &manager->entries[v3];
        p_velocity = &v5->velocity;
        v7 = &v5->sprite->velocity;
        v7->x = p_velocity->x;
        v7->y = p_velocity->y;
        v7->z = p_velocity->z;
        v8 = &manager->entries[v3];
        v9 = v8->velocity.x * 10.0;
        v15 = v8->velocity.y * 10.0;
        v10 = v8->velocity.z * 10.0;
        p_x = &v8->sprite->position.x;
        v16 = v10;
        *p_x = v9 + *p_x;
        p_x[1] = v15 + p_x[1];
        p_x[2] = v16 + p_x[2];
        manager->entries[v3].travel_distance = manager->entries[v3].speed * 10.0 + manager->entries[v3].travel_distance;
      }
      v12 = &manager->entries[v3];
      ++v2;
      ++v3;
      v12->sprite->color.a = (v12->travel_distance - 2.0) * v12->alpha_scale * 0.011428571 * fade_alpha;
    }
    while ( v2 < manager->count );
  }
}
