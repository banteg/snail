/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: activate_landscape_entry @ 0x418870 */
/* selector: activate_landscape_entry */

// Selects one cached landscape script, activates up to ten repeated 0x90-byte landscape BOD slices for its object index, chooses the backdrop variant flag, and copies the script fog color into global render state.
void __thiscall activate_landscape_entry(LandscapeManager *manager, int32_t script_index)
{
  int32_t level_mode; // eax
  int v4; // ebp
  char *v5; // edi
  uint32_t *p_list_flags; // esi
  BodBase *p_landscape_slice_list_head; // eax
  uint32_t v8; // eax
  uint32_t v9; // eax
  uint32_t v10; // eax
  uint8_t flip; // [esp+Ch] [ebp-8h]
  int v12; // [esp+10h] [ebp-4h]

  level_mode = g_game_base->subgame.level_mode;
  if ( level_mode == 7 )
  {
    flip = 0;
  }
  else if ( level_mode == 1 )
  {
    flip = (double)next_math_random_value() * 0.000030517578 <= 0.5;
  }
  else
  {
    flip = g_runtime_config.landscape_backdrop_variant_selector & 1;
  }
  v4 = 0;
  v12 = 0;
  v5 = (char *)manager + 292 * script_index;
  p_list_flags = &manager->active_entries[0].bod.bod.bod.list_flags;
  do
  {
    if ( *((_DWORD *)v5 + 428) == -1 )
    {
      *p_list_flags &= ~0x20u;
      set_bod_object((BodBase *)(p_list_flags - 1), nullptr);
    }
    else
    {
      p_landscape_slice_list_head = &g_game_base->subgame.landscape_slice_list_head;
      if ( (*p_list_flags & 0x200) != 0 )
      {
        report_errorf(aListAddafter);
      }
      else
      {
        p_list_flags[1] = (uint32_t)p_landscape_slice_list_head;
        p_list_flags[2] = (uint32_t)p_landscape_slice_list_head->bod.list_next;
        p_landscape_slice_list_head->bod.list_next = (struct BodNode *)(p_list_flags - 1);
        v8 = p_list_flags[2];
        if ( v8 )
          *(_DWORD *)(v8 + 8) = p_list_flags - 1;
        v9 = *p_list_flags;
        BYTE1(v9) = BYTE1(*p_list_flags) | 2;
        *p_list_flags = v9;
      }
      p_list_flags[31] = 1;
      v10 = *p_list_flags;
      LOBYTE(v10) = *p_list_flags | 0x20;
      *p_list_flags = v10;
      set_bod_object(
        (BodBase *)(p_list_flags - 1),
        g_game_base->directx_loader.cached_x_mesh_slots[*((_DWORD *)v5 + 428)].object);
      *((float *)p_list_flags + 33) = *(float *)(p_list_flags[8] + 184) - *(float *)(p_list_flags[8] + 172);
      set_matrix_identity((TransformMatrix *)(p_list_flags + 13));
      *((float *)p_list_flags + 27) = ((double)v12 - 0.5) * *((float *)p_list_flags + 33);
      p_list_flags[34] = (uint32_t)&g_player_block + (_DWORD)g_game_base;
    }
    ++v4;
    p_list_flags += 36;
    v12 = v4;
  }
  while ( v4 < 10 );
  change_backdrop(&g_game_base->backdrop, (LandscapeScriptRecord *)(v5 + 1444), flip);
  set_border_justify_centre(&g_game_base->border_manager, 0.0);
  g_game_base->fog_color = *(FrameColor4f *)(v5 + 1716);
}
