/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: project_position_onto_track_attachment @ 0x4444b0 */
/* selector: project_position_onto_track_attachment */

// Projects a mutable world-space position onto an active track attachment template in place. Android and iOS preserve the authored `cRSubGame::CalcRealPos(tVector&, float&)` signature; both Windows callers discard EAX, confirming the same void SubgameRuntime method rather than the decompiler's stale-return contract.
void __thiscall project_position_onto_track_attachment(SubgameRuntime *game, Vec3 *position, float *out_angle)
{
  SubRow *runtime_row; // eax
  TrackRowCell *primary_attachment_cell; // edi
  cRPath *attachment_template_record; // ebx
  PathTemplateSample *sample; // eax
  float y; // edx
  double v8; // st7
  double v9; // st6
  float v10; // [esp+Ch] [ebp-70h]
  float v11; // [esp+10h] [ebp-6Ch]
  float v12; // [esp+1Ch] [ebp-60h]
  float v13; // [esp+20h] [ebp-5Ch]
  float v14; // [esp+24h] [ebp-58h]
  float v15; // [esp+28h] [ebp-54h]
  float v16; // [esp+30h] [ebp-4Ch]
  float v17; // [esp+34h] [ebp-48h]
  TransformMatrix transform; // [esp+3Ch] [ebp-40h] BYREF
  Vec3 projected_position; // 0:^20.12

  runtime_row = &game->runtime_rows[(__int64)position->z];
  *out_angle = 0.0;
  if ( (runtime_row->flags & 0x40) != 0 )
  {
    primary_attachment_cell = runtime_row->primary_attachment_cell;
    attachment_template_record = primary_attachment_cell->attachment_template_record;
    sample = &attachment_template_record->primary_samples[(__int64)position->z
                                                        - get_track_cell_row_index(primary_attachment_cell)];
    if ( attachment_template_record->kind == PATH_TEMPLATE_KIND_NONLINEAR_42 )
    {
      compute_kind42_attachment_transform(
        attachment_template_record,
        sample->special_scalar,
        position->x,
        position->y,
        &transform,
        out_angle);
      y = transform.position.y;
      position->x = transform.position.x;
      position->y = y;
    }
    else
    {
      v8 = position->y;
      v16 = v8 * sample->transform.basis_up.x;
      v17 = v8 * sample->transform.basis_up.y;
      v9 = position->x - sample->center_x;
      v10 = v9 * sample->transform.basis_right.x;
      v11 = v9 * sample->transform.basis_right.y;
      v12 = sample->transform.position.y + primary_attachment_cell->anchor_position.y;
      v13 = sample->transform.position.z + primary_attachment_cell->anchor_position.z;
      v14 = sample->transform.position.x + primary_attachment_cell->anchor_position.x + v10;
      v15 = v12 + v11;
      projected_position.x = v14 + v16;
      projected_position.y = v15 + v17;
      projected_position.z = v9 * sample->transform.basis_right.z + v13 + v8 * sample->transform.basis_up.z;
      *position = projected_position;
    }
  }
}
