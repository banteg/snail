# noop_runtime_ai @ 0x407b50

Exact match: 100.00%, 1/1 instruction.

This scratch maps the shared empty per-frame callback used by runtime object
types that do not need standalone AI work. It appears in subgame init/build,
collision fallback, render-cache, and startup/main-loop callsites.

2026-06-20 type note: subgame/player embedded-slot callsites now use the shared
`RuntimeSlot::noop_runtime_ai()` declaration instead of scratch-local
`RuntimeCallback` shells. This keeps the empty callback separate from the
frame-loop virtual `RuntimeCallback::update()` rows and removes the
`RuntimeCallback` ABI-conflict group from `snail match types --paths`.

2026-07-11 receiver-typed lifecycle recovery: the calls at 0x437f6c and
0x43ae48 pass the empty `ProgressBar` embedded at cRSubGame +0x3bbb54 /
Player +0x3f0. Android independently calls the one-instruction
`cRProgressBar::Init()` from `cRSubGame::StartLevel()` and
`cRSubGoldy::Init()`. These Windows callsites are now spelled through
`ProgressBar::noop_runtime_ai()` while the stable shared function identifier
remains unchanged for unrelated folded no-op owners. The body stays exact at
1/1 instruction.

2026-07-26 mobile collision ownership recovery: Windows collision callsite
0x445536 passes the enclosing Player in `ecx` before calling this folded body.
The iOS symbol corpus names the same authored operation
`cRSubGoldy::SpeedUpCollect()`, and Android calls `SpeedUpCollect()` in the
corresponding pickup branch. `Player::noop_runtime_ai()` now preserves that
receiver-typed call surface while retaining the stable Windows identifier for
the folded address. This is a Player method borrow, not a free global callback.

2026-07-26 weapon callback ownership: Binary Ninja reads the sole pointer at
the dedicated `g_weapon_noop_vtable` (`0x49735c`) as this exact body and finds
four constructor stores, one for each of Snail's three weapon channels plus its
jetpack Weapon. Android and iOS independently preserve empty
`cRWeapon::AI()` bodies. The crosswalk therefore records cRWeapon as one exact
authored owner of this folded address without collapsing the other proven
ProgressBar and SubGoldy identities into it. The scratch remains exact at 1/1.

2026-07-27 audio-owner recovery: the frame loop passes
`g_audio_backend @ 0x753c58` in `ECX` to this same folded one-byte body. iOS
`BassPlay.o` independently names the process global `gBass` and calls its
four-byte empty `cRBass::AI()` method once per frame. This adds cRBass as
another proven owner of the folded address without changing the representative
cRWeapon crosswalk row or collapsing unrelated no-op methods.

## 2026-07-27 mobile vtable owner sweep

Four dedicated Windows callback edges recover four more authored identities:

- the base and renderable BOD tables at `0x4974fc` and `0x497500` both contain
  this address; Android and iOS retain explicit four-byte `cRBod::AI()` bodies,
  and their `cRBodPos` vtables inherit that same base method;
- `initialize_game_player` installs the shared `0x4972b0` table on the complete
  camera subobject at `GamePlayer +0xa0`; both mobile ports retain the empty
  `cRCamera::AI()` method;
- `initialize_golb_shot` installs the dedicated `0x497350` table only on the
  kind-2 body whose model is `rocket-base-000.x`; both mobile ports retain
  `cRGolbRocket::AI()` in `Golb.o`; and
- `initialize_player_presentation_controller` installs `0x497354` on the
  complete Snail owner; both mobile ports retain `cRSnail::AI()`.

Each mobile body is exactly four ARM bytes. The Windows manifest therefore
records distinct aliases on the one-byte folded body while keeping
`noop_runtime_ai` as its stable address name. No alias is transferred to an
unproved callsite or to either neighboring Windows audio overload.
