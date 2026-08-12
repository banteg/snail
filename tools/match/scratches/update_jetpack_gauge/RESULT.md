# cRSubHover authored-surface result

The exact 0x214-byte hover/jet owner is now declared primarily as
`cRSubHover`; `SubHover` remains a compatibility typedef. Each lifecycle
scratch defines its mobile-authored method and selects the exact VC6 decorated
symbol instead of relying on the descriptive Windows scratch name.

| Windows scratch | Authored method | Focused result | Operand audit |
| --- | --- | ---: | ---: |
| `end_jetpack_hover` | `cRSubHover::End()` | 100.00%, 9/9 | 1 clean |
| `update_jetpack_gauge` | `cRSubHover::AI()` | 94.66%, 131/131 | 34 clean |
| `uninit_jet_particles` | `cRSubHover::JetUnInit()` | 100.00%, 17/17 | 1 clean |
| `initialize_jet_particles` | `cRSubHover::JetInit()` | 100.00%, 73/73 | 3 clean |
| `update_jet_particles` | `cRSubHover::Jets()` | 100.00%, 181/181 | 17 clean |
| `initialize_jetpack_gauge` | `cRSubHover::Init(int)` | 100.00%, 15/15 | 3 clean |
| `arm_jetpack_gauge` | `cRSubHover::On()` | 100.00%, 18/18 | 4 clean |

The `AI` score is intentionally unchanged. Its six recorded sweeps still cover
47 variants and validate cleanly.
This ownership slice did not reopen state-ladder, threshold, completion-owner,
or wobble-lifetime hypotheses.

## Native and cross-port evidence

Live Binary Ninja target `78613:2:15749352994627851210` retains the complete
Windows caller graph: Goldy initialization calls `Init`, collision calls `On`,
Goldy AI calls `AI`, presentation calls `Jets`, `AI` calls `End` and
`JetUnInit`, and `On` calls `JetInit`. The `AI` call at `0x43a536` reaches the
same one-instruction body at `0x43d880` as `cRSubGame::AddSpeedUp`.

Android independently preserves all seven lifecycle methods plus
`cRSubHover::Hover(tVector&, float)`, proving the folded eighth call surface.
A temporary VC6 probe confirms its exact Windows object symbol is
`?Hover@cRSubHover@@QAEXAAUtVector@@M@Z` and that the empty method remains an
exact one-instruction match.

## Shared propagation

Every live matcher caller now uses the authored lifecycle surface, and
`sub_hover.h` retains only those methods plus the `SubHover` compatibility type
alias. The collision mutation specification was updated mechanically so its
future variants still build against `On()`; the six `update_jetpack_gauge`
specifications contained no retired method names.

The stable Windows function names remain canonical in the gameplay manifest,
with collision-safe `cRSubHover_*` semantic aliases. Owner-qualified decorated
references cover all seven lifecycle entries. The folded `0x43d880` reference
has both `cRSubGame::AddSpeedUp` and `cRSubHover::Hover` object symbols, so the
authored `Hover(player->transform.position, progress)` call audits to the same
native body without confusing method owners.

Focused mobile/matcher tests protect the primary class, compatibility typedef,
method definitions and configs, caller propagation, and dual folded-symbol
resolution. Analyzer-wide `SubHover` vocabulary remains deliberately stable;
that compatibility surface should only move in a separate atomic replay/export
slice.
