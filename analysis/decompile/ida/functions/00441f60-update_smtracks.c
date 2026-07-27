/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_smtracks @ 0x441f60 */
/* selector: update_smtracks */

// Exact Windows `cRFace::AI()`: advances the embedded 0x128-byte Face owner's authored `Movie`, installs its current `TextureRef*` on the borrowed mesh's first facequad, and invokes `ObjectProcLandScapeUpdate` to resample the retained image into the mesh vertex-y grid. The callback table at `0x4972f8` points directly here.
void __thiscall update_smtracks(Face *face)
{
  advance_frame_sequence(&face->movie);
  face->bod.object->facequads->texture_ref = face->movie.current_texture_ref;
  sample_smtrack_heightmap(face->bod.object, 0.0, 5.0, face->movie.current_texture_ref, false);
}
