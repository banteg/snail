/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: advance_frame_sequence @ 0x430470 */
/* selector: advance_frame_sequence */

// Advances one Object-derived frame sequence by its fractional step, handling wrap, restart, reverse, and ping-pong flags before publishing the current face quad's `TextureRef*`.
void __thiscall advance_frame_sequence(FrameSequence *sequence)
{
  int32_t current_frame_index; // esi
  ObjectFaceQuad *facequads; // edi
  int32_t sequence_flags; // edx
  double v4; // st7
  unsigned __int8 v6; // c0
  unsigned __int8 v7; // c3
  int32_t v8; // eax
  int32_t facequad_count; // esi

  current_frame_index = sequence->current_frame_index;
  facequads = sequence->object.facequads;
  sequence->current_texture_ref = facequads[current_frame_index].texture_ref;
  sequence_flags = sequence->sequence_flags;
  if ( (sequence_flags & 0x11) == 0 )
  {
    v4 = sequence->phase_step + sequence->phase;
    sequence->phase = v4;
    if ( !(v6 | v7) )
    {
      sequence->phase = v4 - 1.0;
      if ( (sequence_flags & 8) == 0 )
      {
        v8 = current_frame_index + 1;
        facequad_count = sequence->object.facequad_count;
        sequence->current_frame_index = v8;
        if ( v8 != facequad_count )
          goto LABEL_15;
        if ( (sequence_flags & 4) != 0 )
        {
          sequence->current_frame_index = facequad_count - 2;
          sequence->sequence_flags = sequence_flags | 8;
          goto LABEL_15;
        }
        if ( (sequence_flags & 2) != 0 )
        {
LABEL_14:
          sequence->current_frame_index = 0;
          goto LABEL_15;
        }
LABEL_13:
        sequence->sequence_flags = sequence_flags | 1;
        goto LABEL_14;
      }
      sequence->current_frame_index = current_frame_index - 1;
      if ( !current_frame_index )
      {
        if ( (sequence_flags & 4) != 0 )
        {
          sequence->current_frame_index = 1;
          sequence->sequence_flags = sequence_flags & 0xFFFFFFF7;
          goto LABEL_15;
        }
        if ( (sequence_flags & 2) != 0 )
        {
          sequence->current_frame_index = sequence->object.facequad_count - 1;
          goto LABEL_15;
        }
        goto LABEL_13;
      }
    }
LABEL_15:
    sequence->current_texture_ref = facequads[sequence->current_frame_index].texture_ref;
  }
}
