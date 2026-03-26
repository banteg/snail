/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_snail_skin @ 0x445cd0 */
/* selector: update_snail_skin */

// Transforms the 19-entry local snail hotspot bank at `+0x16cc` into the live world-space hotspot bank at `+0x17b0`, using two cached matrices and feeding the cutscene anchor points later consumed by `update_cutscene`, including the authored `CameraSkidStop` and `CameraIntroTalk` hotspots.
void __thiscall update_snail_skin(PlayerPresentationController *presentation)
{
  int v1; // ebx
  Vec3 *snail_hotspots_world; // ebp
  TransformMatrix *p_snail_hotspot_source_matrix_b; // esi
  float v4; // eax
  float *p_x; // ecx
  float v6; // edx
  float v7[16]; // [esp-40h] [ebp-60h] BYREF
  PlayerPresentationController *v8; // [esp+10h] [ebp-10h]
  float x; // [esp+14h] [ebp-Ch] BYREF
  float y; // [esp+18h] [ebp-8h]
  float z; // [esp+1Ch] [ebp-4h]

  v8 = presentation;
  v1 = 0;
  snail_hotspots_world = presentation->snail_hotspots_world;
  while ( 1 )
  {
    p_snail_hotspot_source_matrix_b = &presentation->snail_hotspot_source_matrix_b;
    x = snail_hotspots_world[-19].x;
    y = snail_hotspots_world[-19].y;
    z = snail_hotspots_world[-19].z;
    if ( v1 >= 11 )
      p_snail_hotspot_source_matrix_b = &presentation->snail_hotspot_source_matrix_a;
    qmemcpy(v7, p_snail_hotspot_source_matrix_b, sizeof(v7));
    multiply_vector_by_matrix(
      &x,
      v7[0],
      v7[1],
      v7[2],
      SLODWORD(v7[3]),
      v7[4],
      v7[5],
      v7[6],
      SLODWORD(v7[7]),
      v7[8],
      v7[9],
      v7[10],
      SLODWORD(v7[11]),
      v7[12],
      v7[13],
      v7[14],
      SLODWORD(v7[15]));
    v4 = y;
    p_x = &snail_hotspots_world->x;
    ++v1;
    ++snail_hotspots_world;
    *p_x = x;
    v6 = z;
    p_x[1] = v4;
    p_x[2] = v6;
    if ( v1 >= 19 )
      break;
    presentation = v8;
  }
}

