/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_star_field @ 0x434310 */
/* selector: initialize_star_field */

// Builds the live star-field streak sprites: allocates one sprite per entry, seeds camera-relative positions, randomizes direction and speed, tints them pale blue-white, and primes the per-streak length or fade fields.
int32_t __thiscall initialize_star_field(StarManager *manager)
{
  int32_t v2; // edi
  int v3; // ebx
  int32_t count; // eax
  int32_t v5; // ebx
  int32_t v6; // edi
  Vec3 *p_position; // ecx
  Vec3 *p_velocity; // edx
  int v9; // eax
  StarManagerEntry *entries; // edx
  double v11; // st7
  float *p_x; // eax
  double v13; // st7
  double v14; // st7
  StarManagerEntry *v15; // ecx
  double travel_distance; // st7
  float *v17; // eax
  double speed; // st6
  double v19; // st7
  Sprite *sprite; // eax
  Sprite *v21; // eax
  StarManagerEntry *v22; // eax
  Vec3 *v23; // edx
  Vec3 *v24; // eax
  StarManagerEntry *v25; // eax
  Vec3 *v26; // edx
  int math_random_value; // [esp+10h] [ebp-60h]
  float v29; // [esp+14h] [ebp-5Ch]
  float v30; // [esp+18h] [ebp-58h]
  float v31; // [esp+1Ch] [ebp-54h]
  float v32; // [esp+20h] [ebp-50h]
  float v33; // [esp+24h] [ebp-4Ch]
  float v34; // [esp+30h] [ebp-40h]
  float v35; // [esp+34h] [ebp-3Ch]
  float v36; // [esp+38h] [ebp-38h]
  float v37; // [esp+40h] [ebp-30h]
  float v38; // [esp+44h] [ebp-2Ch]
  float v39; // [esp+48h] [ebp-28h]
  float v40; // [esp+4Ch] [ebp-24h]
  float v41; // [esp+54h] [ebp-1Ch]
  float v42; // [esp+58h] [ebp-18h]
  Color4f color; // [esp+60h] [ebp-10h] BYREF

  v2 = 0;
  if ( manager->count > 0 )
  {
    v3 = 0;
    do
    {
      ++v2;
      manager->entries[v3++].sprite = (Sprite *)allocate_sprite(g_sprite_manager, 2, 32, -1, -1);
    }
    while ( v2 < manager->count );
  }
  count = manager->count;
  v5 = 0;
  manager->fade = 1.0;
  if ( count > 0 )
  {
    do
    {
      v6 = v5;
      manager->entries[v5].active = 1;
      if ( v5 )
        manager->entries[v6].alpha_scale = ((double)next_math_random_value() - 16384.0) * 0.0000061035157 + 0.40000001;
      else
        manager->entries->alpha_scale = 0.40000001;
      v37 = *((float *)g_game_base + 438) * 50.0;
      v38 = *((float *)g_game_base + 439) * 50.0;
      v30 = *((float *)g_game_base + 437) * 50.0 + *((float *)g_game_base + 441);
      v31 = v37 + *((float *)g_game_base + 442);
      p_position = &manager->entries[v6].position;
      v32 = v38 + *((float *)g_game_base + 443);
      p_position->x = v30;
      p_position->y = v31;
      p_position->z = v32;
      v29 = ((double)next_math_random_value() - 16384.0) * 0.000061035156;
      math_random_value = next_math_random_value();
      p_velocity = &manager->entries[v6].velocity;
      v33 = ((double)math_random_value - 16384.0) * 0.000061035156;
      p_velocity->x = v33;
      p_velocity->y = v29;
      p_velocity->z = 0.0;
      normalize_vector(&manager->entries[v6].velocity);
      v9 = next_math_random_value();
      entries = manager->entries;
      v11 = (double)v9;
      p_x = &entries[v6].velocity.x;
      v13 = v11 * 0.000018310548 + 0.30000001;
      *p_x = v13 * *p_x;
      p_x[1] = v13 * entries[v6].velocity.y;
      v14 = v13 * entries[v6].velocity.z;
      p_x[2] = v14;
      manager->entries[v6].velocity.z = 0.0;
      vector_magnitude(&manager->entries[v6].velocity.x);
      manager->entries[v6].speed = v14;
      manager->entries[v6].travel_distance = (double)next_math_random_value() * 0.0010681152;
      v15 = manager->entries;
      travel_distance = v15[v6].travel_distance;
      v17 = &v15[v6].position.x;
      v39 = travel_distance * v15[v6].velocity.x;
      v40 = travel_distance * v15[v6].velocity.y;
      speed = v15[v6].speed;
      v41 = v39 / speed;
      v42 = v40 / speed;
      v34 = v41 + *v17;
      v35 = v42 + v15[v6].position.y;
      v19 = travel_distance * v15[v6].velocity.z / speed + v15[v6].position.z;
      *v17 = v34;
      v17[1] = v35;
      v36 = v19;
      v17[2] = v36;
      sprite = manager->entries[v6].sprite;
      sprite->flags |= 0x402u;
      manager->entries[v6].sprite->progress = 0.0;
      manager->entries[v6].sprite->progress_step = 0.0;
      manager->entries[v6].sprite->gravity_step = 0.0;
      manager->entries[v6].sprite->color = *set_color_rgba(&color, 0.80000001, 0.80000001, 1.0, 0.40000001);
      manager->entries[v6].sprite->size_start = 0.80000001;
      v21 = manager->entries[v6].sprite;
      v21->size_end = v21->size_start;
      manager->entries[v6].sprite->corner_scale = (manager->entries[v6].speed + 1.0) * 4.0;
      v22 = &manager->entries[v6];
      v23 = &v22->velocity;
      v24 = &v22->sprite->velocity;
      v24->x = v23->x;
      v24->y = v23->y;
      v24->z = v23->z;
      v25 = &manager->entries[v6];
      v26 = &v25->sprite->position;
      ++v5;
      v26->x = v25->position.x;
      v26->y = v25->position.y;
      v26->z = v25->position.z;
      manager->entries[v6].sprite->facing_refresh_progress = 0.0;
    }
    while ( v5 < manager->count );
  }
  return (*(int32_t (__thiscall **)(StarManager *))manager->bod.bod.vtable)(manager);
}

