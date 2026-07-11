/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_star_positions @ 0x434800 */
/* selector: update_star_positions */

// Advances each star-field streak along its cached direction, resets wrapped entries against the current camera origin, and scales the visible sprite trail by both per-streak speed and the controller fade factor.
void *__thiscall update_star_positions(StarManager *manager, float fade_alpha)
{
  void *result; // eax
  int32_t v3; // edi
  int v4; // edx
  float *p_travel_distance; // esi
  Vec3 *p_position; // eax
  StarManagerEntry *v7; // eax
  Vec3 *p_velocity; // esi
  Vec3 *v9; // eax
  StarManagerEntry *v10; // eax
  double v11; // st7
  double v12; // st6
  float *p_x; // eax
  StarManagerEntry *v14; // eax
  double v15; // st7
  float v16; // [esp+4h] [ebp-24h]
  float v17; // [esp+8h] [ebp-20h]
  float v18; // [esp+Ch] [ebp-1Ch]
  float v19; // [esp+14h] [ebp-14h]
  float v20; // [esp+18h] [ebp-10h]
  float v21; // [esp+20h] [ebp-8h]
  float v22; // [esp+24h] [ebp-4h]

  result = (void *)manager->count;
  v3 = 0;
  if ( (int)result > 0 )
  {
    v4 = 0;
    do
    {
      manager->entries[v4].travel_distance = manager->entries[v4].speed + manager->entries[v4].travel_distance;
      p_travel_distance = &manager->entries[v4].travel_distance;
      if ( *p_travel_distance > 35.0 )
      {
        *p_travel_distance = 0.0;
        manager->entries[v4].sprite->facing_refresh_progress = 0.0;
        v19 = *((float *)g_game_base + 438) * 50.0;
        v20 = *((float *)g_game_base + 439) * 50.0;
        v16 = *((float *)g_game_base + 437) * 50.0 + *((float *)g_game_base + 441);
        v17 = v19 + *((float *)g_game_base + 442);
        v18 = v20 + *((float *)g_game_base + 443);
        p_position = &manager->entries[v4].sprite->position;
        p_position->x = v16;
        p_position->y = v17;
        p_position->z = v18;
        v7 = &manager->entries[v4];
        p_velocity = &v7->velocity;
        v9 = &v7->sprite->velocity;
        v9->x = p_velocity->x;
        v9->y = p_velocity->y;
        v9->z = p_velocity->z;
        v10 = &manager->entries[v4];
        v11 = v10->velocity.x * 10.0;
        v21 = v10->velocity.y * 10.0;
        v12 = v10->velocity.z * 10.0;
        p_x = &v10->sprite->position.x;
        v22 = v12;
        *p_x = v11 + *p_x;
        p_x[1] = v21 + p_x[1];
        p_x[2] = v22 + p_x[2];
        manager->entries[v4].travel_distance = manager->entries[v4].speed * 10.0 + manager->entries[v4].travel_distance;
      }
      v14 = &manager->entries[v4];
      ++v3;
      ++v4;
      v15 = (v14->travel_distance - 2.0) * v14->alpha_scale;
      result = v14->sprite;
      *((float *)result + 14) = v15 * 0.011428571 * fade_alpha;
    }
    while ( v3 < manager->count );
  }
  return result;
}

