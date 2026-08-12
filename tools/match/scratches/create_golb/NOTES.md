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
