# cRFireWork::Shoot @ 0x441dd0

Current recovery: semantic-complete (`compiler` residual). Live Windows
analysis establishes a void `thiscall` on the exact one-byte `cRFireWork`
owner, with a `tVector*` and three integers. Android and iOS retain the same
method in `SubGame.o`; their ABI presents the vector by value. The receiver is
unused by the body but supplied by every native caller.

The recovered loop allocates each sprite, seeds render flags, lifetime, color,
size, randomized velocity, source position, owner, and texture, then emits the
requested count. The runtime particle-effects gate and all random ranges match
the native body.

Focused VC6 result: **94.17%**, exact 103/103 instruction parity, prefix
78/103, with all 21 relocation operands audited and clean. Remaining drift is
x87 lifetime and loop-register scheduling after velocity construction.

The matcher source now uses authored `Shoot` and exact VC6 symbol
`?Shoot@cRFireWork@@QAEXPAUtVector@@HHH@Z`; `firework_shoot` remains only the
stable scratch and Windows-address identity.

## Countdown lifetime before position publication (2026-08-13)

Live Windows disassembly shows the loop countdown becoming dead while the
final trivial `Vector3` position copy is still being published: VC6 loads and
decrements `remaining` between the three position-lane stores. Expressing that
ordinary local lifetime by decrementing before the copy improves focused Wibo
from **94.17% to 95.15%** (+4 fuzzy bytes), with exact 103/103 instruction
parity, the same 78-instruction prefix, and all 21 references clean.

A recorded six-variant sweep covers the natural depth, velocity, countdown,
and position publication orders. Only the two spellings that end the countdown
lifetime before the position copy improve; moving the depth write after the
copy regresses. Follow-up direct-copy, reference, source-pointer, and subtraction
spellings are byte-identical to the accepted form, while component-wise copying
regresses sharply. The remaining five-instruction tail drift begins where VC6
chooses when to advance the sprite base while the last x87 multiply is live;
no artificial storage or register constraint is justified.

## 2026-09-04 source-expression diagnostics

Two recorded products against `94f05adb8` test position/count lifetimes
(8 alternatives) and velocity temporary/count interaction (5 alternatives).
Direct position assignment and direct velocity construction can preserve the
95.15% baseline; moving the decrement to the loop condition gives 94.17%.
The float-pointer position constructor changes allocation more broadly. No
source is promoted; the specifications preserve the tested source forms.

## 2026-09-05 goal-600 source ownership campaign

Sixteen whole-motion publication forms test named velocity construction, depth publication, position-copy shape and count-decrement lifetime. None improves 95.15%; canonical source is unchanged.

The recorded probes describe the tested source forms only; they do not establish exhaustion.

## 2026-09-05 continued loop-owner campaign

Four loop-vector scope combinations and eight emitter counter/position ownership combinations do not improve 95.15%. Moving the velocity outside the loop is neutral here, unlike the two fringe builders. Canonical source is unchanged.

## 2026-09-05 continued source-shape investigation

Two diagnostic XYZ constructor-body forms are non-improving. XYZ assignment is neutral and reversed assignment regresses. The shared vector header remains unchanged.

## 2026-09-07 borrowed vector and complete random operations

The five independent compiler fixtures in
`vector-parameter-abi-controls-20260907.md` distinguish the native borrowed
vector argument from an ordinary by-value vector. Trivial value, explicit
copy-constructor, destructor, and combined copy/destructor controls all return
with 0x18 bytes of argument cleanup; a const-reference control returns with
the native 0x10. No vector parameter or shared type contract changes.

`whole-random-velocity-operations-20260907.json` records eight complete
random-velocity alternatives: four scalar helper result forms, each used
directly or through a vector factory. They retain the actual table RNG;
the separately recovered `SRAND` uses the CRT RNG and is not substituted.
All eight compile and none improves 95.15%. The float-scaled form falls to
76.47%, 101/103 instructions, prefix 4, with 21 clean references. Its complete
diff changes earlier random-value lifetimes and still advances the sprite
position base too early. The factory boundary does not change each scalar
form's generated code. Canonical source remains unchanged.

## 2026-09-25 scheduler trace of the loop tail

Unchanged at **95.15%**. This entry explains the tail with
`tools/match/c2/schedtrace.py firework_shoot --line 50` (rules in
`c2/scheduler.md`).

**The loop body is two scheduling windows.** The 81-tuple window limit cuts
it at `mov eax, [edx]`, the first position-copy load. Tuples 76–81 are the
countdown load, dec and store, `lea esi, [esi+0x48]`, the position-parameter
reload and that first copy load. The flags stay live from `dec` to `jne`, so
the sprite advance becomes a flag-free `lea`. It has height 1 and no earlier
dependence, so the list scheduler hoists it into the velocity stores. Native
instead keeps `add esi, 0x48` next to the copy. That means native's IL has the
advance **before** the decrement (`out_position` / copy / `--remaining`
order), as in `n_v0_t1`, which scores 94.17%.

In that order our window 3 still holds the copy's first two lanes. Native's
tail matches, cycle by cycle, one window made of

```
mov edx,[position]; add esi; copy x, y, z; countdown; jne
```

A hand replay of the rule reproduces native's order
(`P S | A | B G | C H | D I | E | F J`) only if two things hold:

1. The window starts at the advance or the reload.
2. Each copy load waits one cycle for the preceding copy store (a latency-1
   load edge).

Our current load edges through `position` have latency 0 (the alias-analysis
path). Latency 1 arises only when the location is a direct local or stack
temporary. So native reaches the copy through something the scheduler treats
as a direct slot, and it has about six more tuples before the velocity-Z store
(for example `IL_FROUND` conversions). Neither has been identified.

Controls, all unchanged or worse:

| Variant | Result |
| --- | --- |
| named velocity components (+`IL_FROUND` tuples) | 73.53%, 101/103 |
| tail orders `--remaining` before or after the copy, direct `sprite->position` | 94.17–95.15% |

## 2026-09-25 follow-up: moving the window cut with IL_FROUND

**95.15% → 96.12%** (103/103, prefix 78 → 85). The change names the
single-use colour and random intermediates:

```cpp
float duration = (float)RAND(0.5f, 0);
duration += 0.800000012f;
...
float red = (float)RAND(0.300000012f, 0);
red += 0.699999988f;
float green = red * 0.5f;
sprite->color.Set(red, green, 0.0f);
```

Each adds one `IL_FROUND` (no code), so window 3 now ends at the countdown
store. The advance and the position reload move into window 4 next to the
copy, matching native's `mov edx, [position]` placement.

Remaining (structural 4/4): our IL still has the countdown **before** the
copy, so the advance is a flag-free `lea` and the decrement is not
interleaved. With the copy-then-decrement order (`fdrt`/`fg` variants, the
same neutral spellings) the cut must move 3–5 tuples further, to after the
velocity-Z store. Two routes fail:

- `float green = red; green *= 0.5f` adds two tuples but reorders the colour
  arguments (97.09%, prefix 46; with the copy-first order the cut lands after
  the position reload).
- `duration *= 60.0f` adds two instructions.

No other neutral single-use float intermediate exists in the loop body. The
velocity components cross RNG calls, and naming them changes the code.
