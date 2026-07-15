/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: select_level_track_texture_set @ 0x410730 */
/* selector: select_level_track_texture_set */

// Windows cRTrack::Change(int): selects one of four root-owned track/slide texture pairs, with selector 5 choosing a random pair. Symbol-preserving iOS and Android builds independently retain the authored cRTrack owner and Change(int) method.
void __thiscall select_level_track_texture_set(Track *track, int32_t texture_set)
{
  int32_t v3; // edi
  int32_t current_texture_set; // eax

  switch ( texture_set )
  {
    case 0:
      v3 = 0;
      break;
    case 1:
      v3 = 1;
      break;
    case 2:
      v3 = 2;
      break;
    case 3:
      v3 = 3;
      break;
    case 5:
      v3 = (__int64)random_float_below(4.0);
      break;
    default:
      v3 = texture_set;
      break;
  }
  current_texture_set = track->current_texture_set;
  if ( v3 != current_texture_set )
  {
    replace_object_list_texture_refs(
      &g_object_list,
      track->track_textures[v3],
      track->track_textures[current_texture_set]);
    replace_object_list_texture_refs(
      &g_object_list,
      track->slide_textures[v3],
      track->slide_textures[track->current_texture_set]);
    track->current_texture_set = v3;
  }
}
