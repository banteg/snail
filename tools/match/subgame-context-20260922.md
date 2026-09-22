# Current SubGame source-context control

The 190 available `SubGame.o` scratch bodies now compile together in their
recorded native address order. None of the eleven remaining partials becomes
an encoded match. `SwitchMirror` retains the same extracted code identity,
27/30 instructions, prefix 20, and three clean references.

This closes an earlier failed experiment: the concatenation had stopped at
conflicting error-reporter declarations and an ambiguous debug-reporter cast.
Two callers now use the existing `rerror.h` compatibility declaration, and
score display explicitly selects its existing two-argument call view before
the final one-argument cast. Their standalone encoded matches remain intact:

| Changed caller | Instructions | Clean positional references |
| --- | ---: | ---: |
| `add_subgoldy_score` | 59/59 | 6 |
| `place_parcels_on_track` | 639/639 | 98 |
| `display_score_stats` | 67/67 | 16 |

All three changes preserve the complete extracted candidate bytes. The two
error callers change the report symbol's declaration to the shared contract;
score display also preserves every relocation record. None adds matching
credit. A direct shared-varargs rewrite of score display regresses to 74/67
instructions and is not retained.

The [receipt](subgame-context-20260922.json) records the 190 source hashes,
combined-source and build-dependency hashes, native image hash, and fresh
standalone/context measurements for all eleven partials. Only the track-cell
builder's fuzzy ratio changes, from 86.132455% to 86.205635%; its 1243/1246
instruction count and 76-instruction prefix remain partial. The other ten
ratios and instruction counts are unchanged.

This diagnostic concatenation is not registered as an original translation
unit. The remaining exact members have not all been certified in this context,
and the small track-cell change is not sufficient evidence to promote the
group. These results cover the recorded source epoch, not all possible source
contexts or compiler behavior.

All 785 scratch checks, 1,140 tests, extern lint, and the strict experiment/spec
audit pass. The documented context replay also passes. The refreshed public
report changes only its three source hashes, prior-evidence hash, and complete
COFF hashes; all function measurements and the 734 encoded-match total remain
unchanged.

Replay the context from this revision with the existing matcher. The hash
checks reject source or build-input drift instead of silently measuring a
different experiment:

```sh
UV_CACHE_DIR=/private/tmp/snail-mail-uv-cache uv run python - <<'PY'
import dataclasses, hashlib, json, tempfile
from pathlib import Path
from snail import match

root = Path.cwd()
receipt = json.loads((root / 'tools/match/subgame-context-20260922.json').read_text())
parts = []
for member in receipt['members']:
    data = (root / 'tools/match/scratches' / member['function'] / 'scratch.cpp').read_bytes()
    assert hashlib.sha256(data).hexdigest() == member['source_sha256']
    parts.append(data.decode())
source = '\n\n'.join(parts)
assert hashlib.sha256(source.encode()).hexdigest() == receipt['context_source_sha256']
manifest = match.load_function_symbol_manifest(match.DEFAULT_FUNCTION_SYMBOL_MANIFEST_PATH)
native = root / manifest.primary_target
assert hashlib.sha256(native.read_bytes()).hexdigest() == receipt['native_sha256']
with tempfile.TemporaryDirectory(prefix='snail-subgame-context-') as temp:
    directory = Path(temp)
    (directory / 'scratch.cpp').write_text(source)
    config = match.load_scratch_config(root / 'tools/match/scratches/switch_track_mirror')
    config = dataclasses.replace(config, directory=directory)
    assert match.scratch_dependency_sha256(config) == receipt['context_dependency_sha256']
    obj = match.compile_scratch(config)
    for saved in receipt['controls']:
        config = match.load_scratch_config(root / 'tools/match/scratches' / saved['function'])
        result = match.run_match(obj_path=obj, function_name=config.function,
            image_path=native, manifest=manifest, symbol_name=config.symbol, end_va=config.end_va)
        measured = match.match_result_payload(result)
        assert all(measured[key] == value for key, value in saved['context'].items())
        assert measured['masked_references'] == saved['context_reference_audit']
        print(config.function, measured['match_ratio'], measured['body_byte_exact'])
PY
```
