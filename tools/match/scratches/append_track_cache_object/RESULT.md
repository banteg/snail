# Exact cache face emission

`SegmentCache::append_track_cache_object` at `0x433960` matches all **167 native
instructions** and **six audited references**, using `msvc6.5 /O2 /G5 /W3`.

The missing source property was its return contract. The helper publishes
indices and counts through output pointers; all five native callers discard
EAX. Removing the unsupported integer return recovers the native capacity-check
load order exactly. Success-path EAX holds the comparison operand; overflow
leaves the error-report call residue. The shared declaration and analyzer
prototype replays now use `void`.

The earlier 98.80% residual was not evidence of a compiler limitation. Exact
compilation and caller/data-flow evidence support this source reconstruction
without claiming the original author's declaration is uniquely recoverable.
