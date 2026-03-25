/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: allocate_path_template_samples @ 0x41b0a0 */

0041b0bb        struct PathTemplateSample* eax_4 = allocate_tracked_memory(self->segment_count * 0xa8, "Path Tile Nodes")
0041b0c0        uint32_t segment_count = self->segment_count
0041b0c3        self->primary_samples = eax_4
0041b0e3        self->secondary_samples = allocate_tracked_memory(segment_count * 0xa8, "Path Ball nodes")
0041b0e7        return
