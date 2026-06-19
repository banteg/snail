# initialize_turnoverdouble_path_template_pair

Honest starter scratch for `initialize_turnoverdouble_path_template_pair @ 0x427640`.

This target uses the same six-argument stack shape as turnover (`ret 0x18`),
but the interior curve performs a double roll and returns to the same lateral
side. The scratch models the recovered double-turnover angle folding, secondary
up-vector offset, deltas, strip mesh, and finalization.

Residuals are expected; the source is semantic starter code.
