/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_smtracks @ 0x441f60 */
/* selector: update_smtracks */

// Advances the embedded 0x128-byte SMTrack height-field animator, installs the current sequence `TextureRef*` on its borrowed mesh, and resamples that texture's retained TGA bytes into the mesh vertex-y grid.
void __thiscall update_smtracks(SmtrackHeightfieldAnimator *animator)
{
  advance_frame_sequence(&animator->frame_sequence);
  animator->bod.object->facequads->texture_ref = animator->frame_sequence.current_texture_ref;
  sample_smtrack_heightmap(animator->bod.object, 0.0, 5.0, animator->frame_sequence.current_texture_ref, 0);
}
