# FontLoad

`FontLoad(char*, int, float, float)` owns the Windows routine at `0x449f50`.
The recovery is semantic-complete at 75.41%: 275 candidate versus 274 target
instructions, with all 57 references clean.

The Windows version scans marker pixels, fills the 128 glyph lanes, handles a
split texture page, stores scale/shadow metadata, and returns the registered
font index. Android and iOS export the same authored `Font.o` name but use a
metadata-driven `0xa28` sheet and a void return; Windows locally proves its
integer result and `0x828` sheet. The remaining delta is compiler allocation
of the glyph slot versus split coordinate, not missing behavior.

## 2026-08-13 per-sample font owner snapshot

Live Windows instructions expose one source lifetime that the earlier broad
classification missed. Immediately after every top-row pixel sample,
`0x44a02b` loads `g_registered_font_count` before testing whether the sampled
pixel is a white glyph boundary. The loaded index then owns every glyph-lane
write on that iteration. Keeping a scoped `font_index` snapshot before the
branch recovers that native load placement and improves focused Wibo from
75.41% to **76.14%** (785/1031 fuzzy bytes), with the same 275/274 instruction
extent and fully clean 57/0/0/0 reference audit.

The snapshot is not extended into the later vertical-marker pass: native
reloads the global on each exit from that call-bearing scan, and retaining one
source local across it regresses to 65.33% while losing two reference pairs.
Function-scope scan declarations are byte-neutral, and a retained
`FontSheet&` changes the native structure-of-arrays addressing and regresses to
54.98%. The remaining opening cascade is still the honest allocation split:
native keeps `split_x` in EBX and the glyph slot on the stack, whereas VC6
chooses the inverse roles for the recovered source.

The directory and manifest retain `register_font_texture_sheet` as the stable
matcher identifier.

## 2026-08-14 runtime-to-prebuilt atlas revision

The recovered RealArcade-derived build contains the predecessor of this
routine. It allocates two TGA buffers labelled `Font Tga0` and `Font Tga1`,
copies the source header into both, halves their widths, and carries a complete
per-pixel split loop before scanning glyph markers. The canonical build removes
that runtime image construction and instead derives `...0.tga`/`...1.tga`
paths for two archive-backed texture registrations.

The paired archives make the source change exact: the earlier DAT lacks only
`FONT-MENU-HOVER0.TGA` and `FONT-MENU-HOVER1.TGA`, while the canonical files are
pixel-exact crops of the shared 2048x64 atlas at x=0 and x=`0x3c0`. This
independently validates the current split-page ownership, filename derivation,
and `split_x = 0x3c0`; it does not change the canonical compiler-allocation
residual.

Two predecessor immediates are not trusted source constants. The redistributed
EXE tests width `0x5001` and its otherwise unreachable copy path uses x=`0x384`,
both inconsistent with the extracted 0x800-wide source and exact canonical
x=`0x3c0` crop. Keep them as a post-link-integrity warning, not a mutation lead.

## 2026-09-05 whole-function source-lifetime probes

Three glyph-scan products compare direct global font indexing and a structured for loop. The for loop alone is neutral at 76.50%, while direct bank indexing regresses. No source change is retained.

## 2026-09-05 continued loop-owner campaign

Seven whole glyph-run forms test a start-index owner, a literal split offset, and removal of the last-X snapshot. None improves 76.50%; canonical source is unchanged.

## 2026-09-05 glyph boundary operation

Four ordinary inline glyph-boundary operations borrow the consumed slot and
run counters through references or pointers. All inline and remain neutral at
76.50%, with all 57 references clean. No helper is retained. The stack-owned
glyph slot versus register-owned split coordinate remains unresolved.

## 2026-09-05 glyph endpoint and run-consumption lifetimes

The native marker branch finishes each endpoint before starting the next:
convert the centered left edge, publish `glyph_u0`, then convert the centered
right edge and publish `glyph_u1`. Delaying `centered_last` until the first
publication improves 76.50% to 76.87%. Resetting the consumed run counter after
both endpoints have been published restores the native reuse of its register
for the two unsigned image-width conversions and raises the result to
**79.78%, 275/274 instructions, prefix 0, all 57 references clean**. Neither
change alters the marker scan, split-page selection, or overflow checks.

Five recorded sweeps cover 27 compiling variants: six endpoint lifetimes,
five filename buffer/index owners, six split-coordinate scopes, five run-reset
boundaries, and five glyph-slot consumption lifetimes. The filename forms add
no gain to the endpoint recovery; later split-coordinate definitions regress.
The retained reset boundary is after `glyph_u1`; the other four tested reset
boundaries regress against it. Slot snapshots are neutral and early slot
consumption regresses. Only the two endpoint/run lifetime changes are retained.
The split-coordinate versus glyph-slot storage difference remains unresolved;
these source probes do not establish exhaustion.

## 2026-09-05 glyph-width destination ownership

A reference to the single `glyph_width[slot]` destination recovers the native
split-coordinate register and the complete 0x210-byte frame/prologue, lifting
79.78% to 84.52% with a 52-instruction prefix. A whole `FontSheet` borrow instead
regresses and introduces reference debt; it is not retained. Assigning the
converted run width directly to that destination removes an unnecessary float
snapshot and reaches 84.88%.

The old `last_x` local starts equal to `x`, is updated to `x` after every scan
increment, and has no independent meaning. Using the live X cursor for the
right edge removes that redundant owner and gives **88.32%, 274/274
instructions, prefix 55, all 57 references clean**. This is a fresh focused
compile of the retained source, not an inference from its fuzzy score.
The initial filename derivation and split-coordinate setup now reproduce the
native instruction sequence exactly. The remaining differences include glyph
counter and conversion spill lifetimes, the split-page zero store, and the
vertical-marker loop's initial height load.

Nine recorded sweeps cover 50 compiling forms: eight glyph destination owners,
five width/left consumption forms, seven coupled endpoint/reset scopes, seven
additional output-field borrow sets, six scan-entry lifetimes, four live-X
forms, four width/left declaration orders, four vertical-marker loops, and five
remaining scan-counter declaration orders. Other field references are neutral;
the whole-sheet borrows, earlier resets, and altered marker loops regress or
retain tradeoffs. The retained source adds only the individual width-field
reference, direct conversion, and live-X use. These results leave the remaining
native source shape open.

## 2026-09-05 complete glyph-width bank ownership probes

Eight `whole-glyph-width-bank-owners-20260905-mutations.json` variants replace
the retained individual glyph-width reference with a bank pointer or array
reference, including early/late declaration and commuted indexing. All retain
88.32%, 274/274 instructions, prefix 55, and 57 clean references. No bank
owner is retained; these results do not close the glyph publication schedule.

## 2026-09-05 separate horizontal and vertical scan scopes

Nine combinations bound the horizontal x/run-width locals separately from the
surviving slot count and vary the vertical scan's block/for scope. None improves
the 88.32% source; the best block/for-x plus vertical-for shape gives 86.65%,
with all 57 references clean. No source change is retained. These lexical
scopes do not reproduce the remaining glyph index and conversion-slot choices.

## 2026-09-05 additional bounded controls

Three current-baseline font-index lifetime forms do not improve 88.32%. Outer scope is neutral; direct global indexing and carrying the index into the final metrics regress and introduce reference debt. Canonical source is unchanged.


## 2026-09-07 five-function campaign evidence

Twenty-nine glyph-scan variable, loop, and width-publication forms do not
improve 88.32%. They preserve scan order while varying the ownership of X,
run width, and glyph slot. The native stack/register assignment remains open;
no source change is retained.

The committed recipes and hash-bound receipts describe the tested forms; they
do not establish source exhaustion.
