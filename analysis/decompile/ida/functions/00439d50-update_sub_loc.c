/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_sub_loc @ 0x439d50 */
/* selector: update_sub_loc */

// Windows `cRSubLoc::AI()`: updates one runtime `TrackRowCell`/SubLoc. Wall2 tile 14 fires through the owned 20-slot `SubLazerPool` after `first_block_row_count` passes Goldy's z; tiles 22/29/30 and the default path cull against the embedded player's interaction plane, while skirt tiles refresh `runtime_rows[row].attachment_body.color`. The Windows constructor callback and cross-port iOS symbol independently prove the owner.
void __thiscall update_sub_loc(SubLoc *cell)
{
  GameRoot *v2; // ecx
  uint8_t tile_id; // al
  double v4; // st7
  float z; // ecx
  uint32_t v6; // edx
  double v7; // st7
  float y; // edx
  double v9; // st7
  double v10; // st7
  tColour *track_skirt_color; // edi
  Vec3 vector; // [esp+4h] [ebp-34h] BYREF
  Vec3 v13; // [esp+10h] [ebp-28h] BYREF
  Vec3 v14; // [esp+1Ch] [ebp-1Ch]
  tColour out; // [esp+28h] [ebp-10h] BYREF

  if ( (cell->lane_and_flags & 0x2000) != 0 )
  {
    v2 = g_game_base;
    if ( !g_game_base->subgame.subgame_pause_gate )
    {
      tile_id = cell->tile_id;
      switch ( tile_id )
      {
        case 0xEu:
          if ( (double)g_game_base->subgame.first_block_row_count >= g_game_base->subgame.player.body.transform.position.z )
            goto LABEL_9;
          if ( random_float_below(100.0) < 4.0 )
          {
            v4 = cell->anchor_position.y + 8.0;
            z = cell->anchor_position.z;
            v13.x = cell->anchor_position.x;
            v6 = cell->lane_and_flags >> 8;
            v14.y = v4;
            v14.x = v13.x;
            *(_QWORD *)&vector.x = v6 & 0xF;
            v14.z = z;
            v13.y = v14.y;
            v13.z = z;
            v13.x = (double)*(__int64 *)&vector.x * 0.5 + v13.x;
            v7 = random_signed_float_below(3.0);
            v2 = g_game_base;
            y = g_game_base->subgame.player.body.transform.position.y;
            v9 = v7 + 8.0 + g_game_base->subgame.player.body.transform.position.z;
            out.r = g_game_base->subgame.player.body.transform.position.x;
            out.g = y;
            v14.x = out.r - v13.x;
            v14.y = y - v14.y;
            v10 = v9 - v13.z;
            v14.z = v10;
            vector = v14;
            if ( v10 >= -4.0 )
              goto LABEL_9;
            normalize_vector(&vector);
            vector.x = vector.x * 0.40000001;
            vector.y = vector.y * 0.40000001;
            vector.z = vector.z * 0.40000001;
            shoot_subgoldy(&g_game_base->subgame.sub_lazers, &v13, &vector);
          }
          v2 = g_game_base;
LABEL_9:
          if ( cell->anchor_position.z < (double)v2->subgame.player.interaction_max_z )
            remove_sub_loc(cell);
          return;
        case 0x16u:
          if ( cell->anchor_position.z >= (double)g_game_base->subgame.player.interaction_max_z )
            return;
          goto LABEL_13;
        case 0x1Du:
        case 0x1Eu:
          if ( cell->attachment_template_record->kind == PATH_TEMPLATE_KIND_WORM )
          {
            cell->render_arg_20 = cell->render_arg_20 - g_game_base->subgame.subgame_rate * 0.033333335;
            set_color_alpha(&cell->color, 0.80000001);
            v2 = g_game_base;
          }
          track_skirt_color = get_track_skirt_color(&v2->subgame, &out);
          *(tColour *)((char *)&unk_6411B8 + (_DWORD)g_game_base + 244 * get_track_cell_row_index(cell)) = *track_skirt_color;
          if ( g_game_base->subgame.player.interaction_max_z
             - ((double)(int)cell->attachment_template_record->row_span_count
              + 5.0) > cell->anchor_position.z )
            remove_sub_loc(cell);
          break;
        default:
          if ( cell->anchor_position.z < (double)g_game_base->subgame.player.interaction_max_z
            && (double)(g_game_base->subgame.completion_row_start - 5) > cell->anchor_position.z )
          {
LABEL_13:
            remove_sub_loc(cell);
          }
          break;
      }
    }
  }
}
