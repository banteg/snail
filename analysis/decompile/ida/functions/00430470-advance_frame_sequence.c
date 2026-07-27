/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: advance_frame_sequence @ 0x430470 */
/* selector: advance_frame_sequence */

// Exact Windows `cRMovie::AI()`: advances the Object-derived Movie by its fractional step, handling complete, pause, loop, reverse, and ping-pong flags before publishing the current face quad's `TextureRef*`. Android and iOS preserve the same state machine and the cRFace-owned call edge.
void __thiscall advance_frame_sequence(Movie *movie)
{
  int32_t current_frame_index; // esi
  ObjectFaceQuad *facequads; // edi
  int32_t sequence_flags; // edx
  double v4; // st7
  unsigned __int8 v6; // c0
  unsigned __int8 v7; // c3
  int32_t v8; // eax
  int32_t facequad_count; // esi

  current_frame_index = movie->current_frame_index;
  facequads = movie->object.facequads;
  movie->current_texture_ref = facequads[current_frame_index].texture_ref;
  sequence_flags = movie->sequence_flags;
  if ( (sequence_flags & 0x11) == 0 )
  {
    v4 = movie->phase_step + movie->phase;
    movie->phase = v4;
    if ( (v6 | v7) == 0 )
    {
      movie->phase = v4 - 1.0;
      if ( (sequence_flags & 8) == 0 )
      {
        v8 = current_frame_index + 1;
        facequad_count = movie->object.facequad_count;
        movie->current_frame_index = v8;
        if ( v8 != facequad_count )
          goto LABEL_15;
        if ( (sequence_flags & 4) != 0 )
        {
          movie->current_frame_index = facequad_count - 2;
          movie->sequence_flags = sequence_flags | 8;
          goto LABEL_15;
        }
        if ( (sequence_flags & 2) != 0 )
        {
LABEL_14:
          movie->current_frame_index = 0;
          goto LABEL_15;
        }
LABEL_13:
        movie->sequence_flags = sequence_flags | 1;
        goto LABEL_14;
      }
      movie->current_frame_index = current_frame_index - 1;
      if ( current_frame_index == 0 )
      {
        if ( (sequence_flags & 4) != 0 )
        {
          movie->current_frame_index = 1;
          movie->sequence_flags = sequence_flags & 0xFFFFFFF7;
          goto LABEL_15;
        }
        if ( (sequence_flags & 2) != 0 )
        {
          movie->current_frame_index = movie->object.facequad_count - 1;
          goto LABEL_15;
        }
        goto LABEL_13;
      }
    }
LABEL_15:
    movie->current_texture_ref = facequads[movie->current_frame_index].texture_ref;
  }
}
