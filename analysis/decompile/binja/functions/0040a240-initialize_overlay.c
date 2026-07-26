/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_overlay @ 0x40a240 */

0040a247        overlay->camera.tail.overlay_rotation_angle = 0
0040a253        overlay->rotation_step = 0.000365471933f
0040a25d        set_matrix_identity(&overlay->bod.transform)
0040a268        overlay->camera.fov_degrees = 38f
0040a272        set_matrix_identity(&overlay->camera.bod.transform)
0040a27e        invert_matrix_from_source(&overlay->camera.view_matrix, &overlay->bod.transform)
0040a285        return
