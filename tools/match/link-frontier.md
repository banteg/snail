# Canonical source-object linkage frontier

```sh
UV_CACHE_DIR=/private/tmp/snail-mail-uv-cache uv run tools/match/link_frontier.py
```

This inventories the actual COFF objects produced by every canonical scratch.
It uses the ordinary compiler cache and does not re-score native functions.
The default JSON receipt is `artifacts/match/link-frontier.json`; `--out` and
`--jobs` select another destination or compilation concurrency.

Each edge is a relocation within the selected function's object extent.
Definitions are collected from every emitted code/data section in the same
set of objects, so an emitted helper or storage definition can satisfy an
edge. Relocations in auxiliary functions and data sections are counted
separately. Every undefined symbol absent from the selected function's
relocations is also listed per object. These exclusions prevent a main-body
inventory from being mistaken for complete object or executable closure.

The receipt distinguishes these outcomes:

| Result | Meaning |
| --- | --- |
| Exact external definition | One emitted definition has the identical COFF spelling. This closes that symbol edge only. |
| Function link-name mismatch | The unresolved spelling is an explicit native manifest alias, and a canonical source defines that native function under another symbol. |
| Possible function link-name mismatch | The same candidate relationship uses the matcher's canonical-name fallback. It needs independent target and ABI evidence. |
| Missing canonical function owner | The manifest names a function, but none of the selected scratches supplies its owned definition. |
| Missing data/storage owner | The named data reference has no corresponding external storage definition among these canonical objects. |
| Data link-name mismatch | An explicit manifest alias identifies emitted storage under another link name. |
| Runtime/platform external | The raw symbol matches an explicit runtime spelling or a native PE import. No provider library is assumed. |
| COMMON, weak, or multiple definitions | Additional COFF allocation or selection semantics remain unresolved. |

Raw COFF spellings determine symbol resolution. The matcher's canonicalization
can discard a C++ owner/signature or a C/stdcall decoration, so it is used
only to suggest candidate native owners. For example, both a genuine legacy
Cross declaration and a fabricated declaration on another class can collapse
to `cross_vectors`. The tool deliberately keeps fallback candidates separate
from explicit alias evidence and never treats either as a linker alias.

Static definitions remain object-local. COMMON symbols are storage requests,
not ordinary unresolved imports. COMDAT duplicates are reported without
assuming a linker selection policy. Weak references and unsupported relocation
forms remain visible. Debug, removed, and informational sections supply no
runtime definitions.

The receipt binds native manifests/image, source/header/compiler inputs, the
compiler launcher and resolved Wibo executable, and every compiled object.
Input contents are hashed again before publication; changing an input during
the inventory fails the run. Compilation failures also fail the inventory
instead of silently treating an unavailable object as an absent source owner.

Integration support objects under `tools/match/link/` are intentionally
outside this canonical-source inventory. The tool does not infer original
translation units, original BSS placement, runtime correctness, new exact
matches, or public game-linked credit.
