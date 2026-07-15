/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_smtracks @ 0x441f60 */

00441f66        advance_frame_sequence(&animator->frame_sequence)
00441f79        animator->bod.object->facequads->texture_ref = animator->frame_sequence.current_texture_ref
00441f8e        sample_smtrack_heightmap(animator->bod.object, 0f, 5f, animator->frame_sequence.current_texture_ref, 0)
00441f97        return
