/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: explode_slug_hazard @ 0x43f680 */
/* selector: explode_slug_hazard */

// Side-effect-only `Slug` explosion emitter that creates the 70-particle goo burst from a raw random/forward velocity vector scaled by the live SubgameRuntime rate. Android retains `cRSlug::Explode()`; iOS v1.5 has the same form and v1.9 adds `cRSubGoldy*`.
void __thiscall explode_slug_hazard(Slug *slug)
{
  char *sprite; // esi
  int v3; // edx
  double v4; // st7
  double subgame_rate; // st7
  int math_random_value; // eax
  SubgameRuntime *owner_game; // ebx
  double v8; // st7
  double v9; // st6
  float *v10; // ebx
  double v11; // st7
  double v12; // st7
  float intensity; // [esp+0h] [ebp-54h]
  float v14; // [esp+14h] [ebp-40h]
  float v15; // [esp+18h] [ebp-3Ch]
  int v16; // [esp+1Ch] [ebp-38h]
  float v17; // [esp+24h] [ebp-30h]
  float v18; // [esp+28h] [ebp-2Ch]
  float v19; // [esp+2Ch] [ebp-28h]
  float v20; // [esp+30h] [ebp-24h]
  float v21; // [esp+34h] [ebp-20h]
  float v22; // [esp+38h] [ebp-1Ch]
  float v23; // [esp+3Ch] [ebp-18h]
  float v24; // [esp+40h] [ebp-14h]
  float v25; // [esp+48h] [ebp-Ch]
  float v26; // [esp+4Ch] [ebp-8h]

  v16 = 70;
  do
  {
    v15 = (double)next_math_random_value() * 0.0000061035157 + 0.2;
    v14 = (double)next_math_random_value() * 0.000030517578 * 0.75 + 0.25;
    sprite = (char *)allocate_sprite(g_sprite_manager, 1, 129, -1, -1);
    v3 = *((_DWORD *)sprite + 1);
    *((_DWORD *)sprite + 26) = 0;
    *((_DWORD *)sprite + 1) = v3 | 0x802;
    *((float *)sprite + 34) = v14 + v14;
    v4 = 1.0
       / (((double)next_math_random_value() * 0.000015258789 + 0.60000002)
        * 60.0)
       * slug->owner_game->subgame_rate;
    *((_DWORD *)sprite + 28) = 0;
    *((_DWORD *)sprite + 29) = 0;
    *((float *)sprite + 27) = v4;
    intensity = (double)next_math_random_value() * 0.0000091552738 + 0.69999999;
    set_color_grayscale((tColour *)(sprite + 44), intensity);
    *((float *)sprite + 24) = v14 * 0.30000001;
    *((float *)sprite + 25) = v14 * 1.2;
    subgame_rate = slug->owner_game->subgame_rate;
    *((float *)sprite + 30) = subgame_rate * subgame_rate * -0.0099999998 * 2.2;
    v23 = ((double)next_math_random_value() - 16384.0) * v15 * 0.000061035156;
    math_random_value = next_math_random_value();
    owner_game = slug->owner_game;
    v24 = (double)math_random_value * (v15 + 0.30000001) * 0.000030517578;
    v8 = (double)next_math_random_value() * v15 * 0.000030517578 + owner_game->player.velocity.z;
    v9 = owner_game->subgame_rate;
    v10 = (float *)(sprite + 84);
    v17 = v9 * v23;
    *((float *)sprite + 21) = v17;
    v18 = v24 * v9;
    *((float *)sprite + 22) = v18;
    v19 = v8 * v9;
    *((float *)sprite + 23) = v19;
    sprite += 72;
    v11 = (double)next_math_random_value() * 0.00030517578;
    v25 = v11 * *v10;
    v26 = v11 * v10[1];
    v20 = v25 + slug->body.transform.position.x;
    v21 = v26 + slug->body.transform.position.y;
    v12 = v11 * v10[2] + slug->body.transform.position.z;
    *(float *)sprite = v20;
    *((float *)sprite + 1) = v21;
    v22 = v12;
    *((float *)sprite + 2) = v22;
    --v16;
  }
  while ( v16 );
}
