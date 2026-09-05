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
