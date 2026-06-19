# initialize_start_path_template_pair

Honest starter scratch for `initialize_start_path_template_pair @ 0x426400`.

The callsite passes six stack arguments and the native tail is `ret 0x18`.
Unlike the simpler terminal-row templates, this constructor allocates one extra
sample, decrements `segment_count`, and uses the final allocated sample directly
for the mesh row. The scratch models that allocation shape, the raised starting
plateau, the cosine descent, the flat tail, deltas, mesh, and finalization.

Residuals are expected.
