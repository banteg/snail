/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_smtracks @ 0x441f60 */

00441f66        advance_frame_sequence(&face->movie)
00441f79        face->bod.object->facequads->texture_ref = face->movie.current_texture_ref
00441f8e        sample_smtrack_heightmap(face->bod.object, 0f, 5f, face->movie.current_texture_ref, false)
00441f97        return
