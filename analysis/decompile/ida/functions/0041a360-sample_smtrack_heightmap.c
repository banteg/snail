/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: sample_smtrack_heightmap @ 0x41a360 */
/* selector: sample_smtrack_heightmap */

// Samples retained TGA bytes from a replacement `TextureRef` into the active SMTrack object's vertex-y grid, using the object's sample-count/aspect metadata, independently converting and averaging RGB channels, applying the optional cubic curve, and scaling the result.
void __cdecl sample_smtrack_heightmap(Object *source, float base, float scale, TextureRef *replacement, char cubic)
{
  unsigned __int16 *texture_ref; // esi
  double heightmap_sample_count; // st7
  Vec3 *vertices; // ebp
  double i; // st7
  double j; // st6
  unsigned __int8 *v11; // eax
  double v12; // st5
  float v13; // [esp+Ch] [ebp-8h]
  float v14; // [esp+10h] [ebp-4h]
  float sourcea; // [esp+18h] [ebp+4h]
  float replacementa; // [esp+24h] [ebp+10h]

  texture_ref = (unsigned __int16 *)replacement->texture_ref;
  heightmap_sample_count = (double)source->heightmap_sample_count;
  replacementa = heightmap_sample_count;
  sourcea = (float)(int)(__int64)(heightmap_sample_count
                                * source->heightmap_sample_scale
                                / source->heightmap_sample_divisor);
  vertices = source->vertices;
  v14 = (double)texture_ref[6] / (replacementa + 1.0);
  v13 = (double)texture_ref[7] / (sourcea + 1.0);
  for ( i = 0.0; i <= sourcea; i = i + 1.0 )
  {
    for ( j = 0.0; j <= replacementa; j = j + 1.0 )
    {
      v11 = (unsigned __int8 *)texture_ref
          + (*((unsigned __int8 *)texture_ref + 16) >> 3)
          * ((__int64)(j * v14) + texture_ref[6] * (texture_ref[7] - (unsigned int)(__int64)(i * v13) - 1));
      v12 = ((double)v11[20] + (double)v11[19] + (double)v11[18]) * 0.0039215689 * 0.33333334;
      if ( cubic )
        v12 = v12 * (v12 * v12);
      ++vertices;
      vertices[-1].y = v12 * scale + base;
    }
  }
}
