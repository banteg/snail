/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_star_positions @ 0x434800 */
/* selector: update_star_positions */

// Advances each star-field streak along its cached direction, resets wrapped entries against the current camera origin, and scales the visible sprite trail by both per-streak speed and the controller fade factor.
void __thiscall update_star_positions(StarManager *manager, float fade_alpha)
{
  int32_t v2; // edi
  int v3; // edx
  float *p_travel_distance; // esi
  Vec3 *p_position; // eax
  StarManagerEntry *v6; // eax
  Vec3 *p_velocity; // esi
  Vec3 *v8; // eax
  StarManagerEntry *v9; // eax
  double v10; // st7
  double v11; // st6
  float *p_x; // eax
  StarManagerEntry *v13; // eax
  float v14; // [esp+4h] [ebp-24h]
  float v15; // [esp+8h] [ebp-20h]
  float v16; // [esp+Ch] [ebp-1Ch]
  float v17; // [esp+14h] [ebp-14h]
  float v18; // [esp+18h] [ebp-10h]
  float v19; // [esp+20h] [ebp-8h]
  float v20; // [esp+24h] [ebp-4h]

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
        v17 = *((float *)g_game_base + 438) * 50.0;
        v18 = *((float *)g_game_base + 439) * 50.0;
        v14 = *((float *)g_game_base + 437) * 50.0 + *((float *)g_game_base + 441);
        v15 = v17 + *((float *)g_game_base + 442);
        v16 = v18 + *((float *)g_game_base + 443);
        p_position = &manager->entries[v3].sprite->position;
        p_position->x = v14;
        p_position->y = v15;
        p_position->z = v16;
        v6 = &manager->entries[v3];
        p_velocity = &v6->velocity;
        v8 = &v6->sprite->velocity;
        v8->x = p_velocity->x;
        v8->y = p_velocity->y;
        v8->z = p_velocity->z;
        v9 = &manager->entries[v3];
        v10 = v9->velocity.x * 10.0;
        v19 = v9->velocity.y * 10.0;
        v11 = v9->velocity.z * 10.0;
        p_x = &v9->sprite->position.x;
        v20 = v11;
        *p_x = v10 + *p_x;
        p_x[1] = v19 + p_x[1];
        p_x[2] = v20 + p_x[2];
        manager->entries[v3].travel_distance = manager->entries[v3].speed * 10.0 + manager->entries[v3].travel_distance;
      }
      v13 = &manager->entries[v3];
      ++v2;
      ++v3;
      v13->sprite->color.a = (v13->travel_distance - 2.0) * v13->alpha_scale * 0.011428571 * fade_alpha;
    }
    while ( v2 < manager->count );
  }
}

