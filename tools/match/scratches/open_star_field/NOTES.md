# open_star_field @ 0x4342c0

Allocates `count * 0x2c` star entries under the native `StarField` allocation
label. The label describes the visual effect; the authored owner is
`cRStarManager`.
If render feature bit `0x04` is already enabled, opens directly into state `1`
and initializes sprites; otherwise leaves the lifecycle state at `0`.

## 2026-08-09 primary cRStarManager::Open promotion

Android and iOS preserve `void cRStarManager::Open(int)`. The primary matcher
symbol is `?Open@cRStarManager@@QAEXH@Z`; `open_star_field` remains the stable
harness name. Instruction matching stays exact at 26/26. During the bounded
owner-only replay, three references are clean and the authored `Init()` call
awaits its shared decorated reference alias.
