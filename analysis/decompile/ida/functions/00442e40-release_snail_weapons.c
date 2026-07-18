/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: release_snail_weapons @ 0x442e40 */
/* selector: release_snail_weapons */

// Authored `cRSnail::ReleaseWeapons()`: constructs and scales one random/forward `Vector3` release step for each embedded weapon and jetpack animation channel, raises the one-shot Invincible gate, and ends the active Player jetpack hover.
void __thiscall release_snail_weapons(Snail *snail)
{
  double v2; // st7
  double v3; // st7
  double v4; // st7
  double v5; // st7
  Player *owner_player; // eax
  float v7; // [esp+4h] [ebp-1Ch]
  float v8; // [esp+4h] [ebp-1Ch]
  float v9; // [esp+4h] [ebp-1Ch]
  float v10; // [esp+8h] [ebp-18h]
  float v11; // [esp+8h] [ebp-18h]
  float v12; // [esp+8h] [ebp-18h]
  float v13; // [esp+8h] [ebp-18h]
  float v14; // [esp+Ch] [ebp-14h]
  float v15; // [esp+Ch] [ebp-14h]
  float v16; // [esp+Ch] [ebp-14h]
  float v17; // [esp+Ch] [ebp-14h]
  float v18; // [esp+10h] [ebp-10h]
  float v19; // [esp+10h] [ebp-10h]
  float v20; // [esp+10h] [ebp-10h]
  float v21; // [esp+10h] [ebp-10h]
  float v22; // [esp+14h] [ebp-Ch]
  float z; // [esp+1Ch] [ebp-4h]
  float v24; // [esp+1Ch] [ebp-4h]
  float v25; // [esp+1Ch] [ebp-4h]
  float v26; // [esp+1Ch] [ebp-4h]

  if ( !snail->invincible_shell.channel_release_steps_active )
  {
    v22 = ((double)next_math_random_value() - 16384.0) * 0.000061035156;
    v2 = random_float_below(1.0);
    z = snail->owner_player->velocity.z;
    v10 = v22 * 0.30000001;
    snail->jetpack_channel.release_step.x = v10;
    v14 = (v2 + 0.5) * 0.30000001;
    snail->jetpack_channel.release_step.y = v14;
    v18 = z * 0.30000001;
    snail->jetpack_channel.release_step.z = v18;
    v7 = ((double)next_math_random_value() - 16384.0) * 0.000061035156;
    v3 = random_float_below(1.0);
    v24 = snail->owner_player->velocity.z;
    v11 = v7 * 0.30000001;
    snail->weapon_channels[0].release_step.x = v11;
    v15 = (v3 + 0.5) * 0.30000001;
    snail->weapon_channels[0].release_step.y = v15;
    v19 = v24 * 0.30000001;
    snail->weapon_channels[0].release_step.z = v19;
    v8 = ((double)next_math_random_value() - 16384.0) * 0.000061035156;
    v4 = random_float_below(1.0);
    v25 = snail->owner_player->velocity.z;
    v12 = v8 * 0.30000001;
    snail->weapon_channels[2].release_step.x = v12;
    v16 = (v4 + 0.5) * 0.30000001;
    snail->weapon_channels[2].release_step.y = v16;
    v20 = v25 * 0.30000001;
    snail->weapon_channels[2].release_step.z = v20;
    v9 = ((double)next_math_random_value() - 16384.0) * 0.000061035156;
    v5 = random_float_below(1.0);
    owner_player = snail->owner_player;
    v26 = owner_player->velocity.z;
    v13 = v9 * 0.30000001;
    snail->weapon_channels[1].release_step.x = v13;
    v17 = (v5 + 0.5) * 0.30000001;
    snail->weapon_channels[1].release_step.y = v17;
    v21 = v26 * 0.30000001;
    snail->weapon_channels[1].release_step.z = v21;
    end_jetpack_hover(&owner_player->sub_hover);
  }
  snail->invincible_shell.channel_release_steps_active = 1;
}
