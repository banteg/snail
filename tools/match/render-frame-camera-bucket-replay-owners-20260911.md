# Exact camera, bucket and replay recovery in the frame renderer

`render_game_frame @ 0x40a490` (`cRGame::Render`) now has **normalized and
relocation-audited encoded-body equality**. Agreement improves from
**69.77272727% to 100%**, with **439/439 instructions**, **1,460 compared bytes**
and **34 strict positional references**. The previous candidate had 441
instructions. The **0x80 stack allocation** is unchanged.

The [complete receipt](render-frame-camera-bucket-replay-owners-20260911.json)
contains both full sources and byte arrays, same-index references, encoded
branch destinations, all formal control sources, decompiler witnesses and
measurement identities. Compiler, flags, headers, ABI, function extent and
matcher are unchanged.

## Recovered source

The camera-order array is initialized in the same traversal that counts active
viewports, as preserved by Android. The insertion loop shifts by predecessor
index: `camera_order[shift + 1] = camera_order[shift]`, starting at the penultimate
slot and stopping at the insertion index. This recovers native's index and
countdown relationship without an explicit shift-count owner or redundant
outer guard. All five Windows slots remain. The unusual original insertion
behavior is preserved: the first active camera seeds the array, later cameras
are inserted only when their sort key exceeds an existing key, and there is no
fallback append. This recovery does not correct that behavior.

The first BOD pass traverses a nonempty list with a guarded `do` loop and stages
objects directly through `g_post_sprite_bods[post_sprite_count++]`. The
`AFTER_SPRITES` flag still stages a second pass while retaining the first render.
Animation synchronization, scene filtering and render arguments are unchanged.

For a nonempty sprite bucket, traversal acquires its cursor from the bucket
table. The compiler keeps native's separate nonempty-head and traversal tests.
No extra guard, volatile access or register hint is introduced. Depth projection,
x87 lifetimes and node writes remain as before. Draining a bucket now clears its
head only after traversing a nonempty list; the native empty-bucket branch skips
that store. Both mobile bodies corroborate the guarded drain.

Replay acquires its one-past end cursor before resetting the staged count. It
then decrements the cursor and accesses the current staged slot directly. The
fallback transform receives the BOD position directly, replacing the transient
vector copy. This combination recovers native's body reload, component stores,
shared call tail and counter schedule. Its authored shift indices and reverse
cursor updates stay within the intended array bounds; original assumptions about
valid camera order, object lists and capacities remain unchanged.

These changes are coupled. The earlier source had been documented as partial
after bounded experiments. Those outcomes were evidence for their recorded
parents, not a compiler limit. Eight independent reversals from the exact source
show the role of each recovered group:

| Reversal | Normalized agreement | Candidate instructions |
| --- | ---: | ---: |
| Separate camera initialization and active count | 86.3636% | 441 |
| Explicit shift pointer and count | 85.1642% | 444 |
| Initialize bucket cursor from local head | 93.3790% | 437 |
| Clear empty buckets too | 99.7722% | 439 |
| Unguarded first-pass traversal and carried staging cursor | 99.0888% | 439 |
| Acquire replay cursor after count reset | 91.8182% | 441 |
| Carry one local replay BOD | 91.5332% | 435 |
| Copy replay position through a temporary | 97.8385% | 440 |
| Restore complete baseline | 69.7727% | 441 |

All reversals retain 34 clean references, and the complete reversal restores the
baseline function fingerprint. Equivalent exact spellings and byte-neutral
formatting controls remain in the receipt. The Windows instructions establish
exact layout and ABI; the later mobile ports support the control graph but use
three viewports and include additional platform/backdrop behavior. Original
variable names and a unique authored spelling are not proved.

## Full encoded proof

The native extent is **1,472 bytes**, `[0x40a490,0x40aa50)`. The compared body
is **1,460 bytes**, `[0,1460)` or `[0x40a490,0x40aa44)`. Only the twelve
recognized terminal-padding bytes, `[1460,1472)`, are excluded. There are no
unexplained or inline data ranges.

All 439 instruction pairs agree at the same index, offset and size. All 34
references pass strict operand-slot, kind and target-identity checks before
their external relocation fields are masked. All **56 local branches** target
mapped instruction boundaries inside the body, and their actual encoded
displacements agree. No ordinary instruction bytes or SIB bytes are masked.
Concatenating the independently audited bytes reproduces both encoded-body
hashes:

`ef6188e79809a83bb68a03967bd6d0aeaed2d1801cec37e28378319d7c5dd752`

This certifies the compiled function body under the recorded build. It does not
establish linked-game placement, rendering output or arbitrary input safety;
no renderer execution-harness result is claimed.

## Controls and validation

The receipt preserves **76 forward observations / 74 distinct sources**, two
source aliases, **nine reverse controls**, and one additional recorded
whitespace-only formatting control. All measured sources compile. One rejected
standalone direct-index replay control has 34 aligned references plus one
unaudited candidate `render_object` call. Its full diagnostic is retained; it
receives no credit. All other controls have zero reference debt.

All **785 scratch checks** pass with **zero type findings**. The strict ledger
has **2,513 records**, zero malformed/current errors and **14/14 active specs
runnable**, with no stale active specs. Full public refresh, separate saved-report
validation and `git diff --check` pass.

Core normalized-exact functions rise **605 to 606 out of 662**. Core fuzzy
agreement rises **93.70% to 93.85%**, and the rounded residual gap falls
**13,443 to 12,998 bytes**. The source-weighted gain is **444.9455 bytes**.
Core status credits the curated 1,472-byte extent; public body credit excludes
its twelve padding bytes.

Public normalized credit rises **717 to 718 functions**, **171,014 to 172,474
bytes**. Encoded-body credit rises **705 to 706 functions**, **153,654 to 155,114
bytes**. Both gain **1,460 exact body bytes**. Linked credit remains zero.
Only this renderer changes ratio or exact classification; all other
classifications, target ranges and measurement identities stay unchanged, with
zero regressed public bytes. The receipt binds the actual post-refresh canonical
COFF to the public row and independently compiled full-body proof.
