# cRSubGolb::Create @ 0x415280

Authored void `cRSubGolb::Create(cRSubGoldy*, int, int)` over one inactive slot
in the player's 12-entry cRSubGolb bank. Binary Ninja confirms the exact
three-argument `__thiscall`; the sole Windows caller supplies its cRSubGoldy,
spawn selector, and bank index. Android and iOS each retain one matching
`cRSubGolb::Create` body in `Golb.o`.

Create links the inherited zero-offset body, selects launch anchors and
velocity from the player's shoot flags, records the bank index, and installs
the kind-zero Sprite, embedded Vapour, or tertiary rocket/path-follow
presentation. The recovered owner layout includes the current/previous flight
matrices, kind-specific backlinks, target reservation, cRSubGame backlink, and
the cRPathFollowGolb child. `Kill` and `AI` account for every created branch.

The scratch exports `?Create@cRSubGolb@@QAEXPAVcRSubGoldy@@HH@Z`. It is
semantic-complete at 77.98%, 549/582 instructions, prefix 81, with 47 clean
references and one documented native-only constant. Recorded aggregate launch
vector lifetimes regress by perturbing function-wide allocation; the remaining
33-instruction factoring delta is classified as compiler/reference residue,
not filled with synthetic temporaries.

## 2026-09-05 coupled launch-vector scopes

Twelve `whole-launch-vector-scopes-20260905-mutations.json` forms couple
true-family velocity staging with the first forward offset's temporary,
narrow block, or complete spawn block. The existing velocity spelling is
neutral at 77.98%; all staged/constructor/shared-owner transfers regress.
The fully staged form with a temporary forward offset is 53.86%, 584/582
instructions, and all 48 references clean: it recovers the previously
missing constant and comes within two instructions, but moves the zero owner
from EBX to EBP, saves EBP earlier, and loses the 81-instruction prefix.
It is not retained. This is useful evidence that the aggregate velocity
operations and the opening list/kind lifetimes must be reconciled together.

Six `whole-shared-launch-vector-20260905-mutations.json` forms reuse the
initial work vector for the true launch family or all launch families, with
three declaration placements. All regress further to 46.51–51.45%, although
all 48 references remain clean. No shared work vector is retained, and the
recorded scope tests do not establish a compiler limitation.
