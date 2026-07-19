/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: explode_slug_hazard @ 0x43f680 */
/* selector: explode_slug_hazard */

// Side-effect-only `Slug` explosion emitter that creates the 70-particle goo burst from a raw random/forward velocity vector scaled by the live SubgameRuntime rate. Android retains `cRSlug::Explode()`; iOS v1.5 has the same form and v1.9 adds `cRSubGoldy*`.
void __thiscall explode_slug_hazard(Slug *slug)
{
  Sprite *sprite; // esi
  SpriteFlag flags; // edx
  double v4; // st7
  double subgame_rate; // st7
  int math_random_value; // eax
  SubgameRuntime *owner_game; // ebx
  double v8; // st7
  double v9; // st6
  double v10; // st7
  float intensity; // [esp+0h] [ebp-54h]
  float v12; // [esp+14h] [ebp-40h]
  float v13; // [esp+18h] [ebp-3Ch]
  int v14; // [esp+1Ch] [ebp-38h]
  float v15; // [esp+3Ch] [ebp-18h]
  float v16; // [esp+40h] [ebp-14h]
  float v17; // [esp+48h] [ebp-Ch]
  float v18; // [esp+4Ch] [ebp-8h]
  Vec3 v19; // 0:^30.12
  Vec3 v20; // 0:^3C.12

  v14 = 70;
  do
  {
    v13 = (double)next_math_random_value() * 0.0000061035157 + 0.2;
    v12 = (double)next_math_random_value() * 0.000030517578 * 0.75 + 0.25;
    sprite = allocate_sprite(&g_sprite_manager, 1, 129, -1, -1);
    flags = sprite->flags;
    sprite->progress = 0.0;
    sprite->flags = flags | 0x802;
    sprite->corner_scale = v12 + v12;
    v4 = 1.0
       / (((double)next_math_random_value() * 0.000015258789 + 0.60000002)
        * 60.0)
       * slug->owner_game->subgame_rate;
    sprite->lifetime = 0.0;
    sprite->lifetime_step = 0.0;
    sprite->progress_step = v4;
    intensity = (double)next_math_random_value() * 0.0000091552738 + 0.69999999;
    set_color_grayscale(&sprite->color, intensity);
    sprite->size_start = v12 * 0.30000001;
    sprite->size_end = v12 * 1.2;
    subgame_rate = slug->owner_game->subgame_rate;
    sprite->gravity_step = subgame_rate * subgame_rate * -0.0099999998 * 2.2;
    v15 = ((double)next_math_random_value() - 16384.0) * v13 * 0.000061035156;
    math_random_value = next_math_random_value();
    owner_game = slug->owner_game;
    v16 = (double)math_random_value * (v13 + 0.30000001) * 0.000030517578;
    v8 = (double)next_math_random_value() * v13 * 0.000030517578 + owner_game->player.velocity.z;
    v9 = owner_game->subgame_rate;
    v19.x = v9 * v15;
    v19.y = v16 * v9;
    v19.z = v8 * v9;
    sprite->velocity = v19;
    v10 = (double)next_math_random_value() * 0.00030517578;
    v17 = v10 * sprite->velocity.x;
    v18 = v10 * sprite->velocity.y;
    v20.x = v17 + slug->body.transform.position.x;
    v20.y = v18 + slug->body.transform.position.y;
    v20.z = v10 * sprite->velocity.z + slug->body.transform.position.z;
    sprite->position = v20;
    --v14;
  }
  while ( v14 );
}
