# Matching Islands

Function-level matching decompilation against the original image, in the style
of isledecomp/decomp.me: write candidate C++ for a contested function, compile
it with the original-era compiler, and diff normalized asm against the function
in `artifacts/bin/SnailMail_unwrapped.exe`. A 100% match is proof-grade ground
truth for porting — it ends ownership/semantics debates that decompile reading
cannot settle.

## Toolchain provenance

The Rich header of the unwrapped exe (see `snail inspect`) pins the original
build environment:

- game C/C++ objects: VC6 cl 12.00 builds 8168 (RTM), 8447 (service-pack era),
  8966 (Processor Pack); linked with link 6.0 on 2004-12-04
- statically linked VC6 CRT (MASM 6.13/6.14 + C objects)
- third-party objects built with VC7 build 9178: the D3DX8 static library from
  the DirectX 8.x SDK (plus zlib 1.2.1 / libpng 1.2.x) — link the original
  libs, never decompile these
- no RTTI, 25 C++ EH functions

`change_snail_skin` matched 100% with `msvc6.5` at `/O2 /G5`, so start every
scratch from that configuration before trying other compiler/flag pairs.

## Setup

1. Wine: `brew install --cask wine-stable` (runs x86 win32 under Rosetta).
   The wrappers use the dedicated prefix `~/.wine-snail`; initialize it once
   with `WINEPREFIX=~/.wine-snail wineboot -i`.
2. Compilers (gitignored, ~40 MB each) — the decomp.me production bundles:

   ```sh
   cd tools/match/compilers
   for v in msvc6.0 msvc6.5 msvc6.5pp msvc6.6; do
     curl -sL -o $v.tar.gz https://github.com/OmniBlade/decomp.me/releases/download/msvcwin9x/$v.tar.gz
     mkdir -p $v && tar xzf $v.tar.gz -C $v && rm $v.tar.gz
   done
   ```

## Workflow

1. Create `scratches/<function>/` with:
   - `scratch.cpp` — candidate implementation; use a class member function to
     get thiscall, mirror struct layouts at native offsets
   - `scratch.conf` — `FUNCTION=<manifest name>`, optional `COMPILER`,
     `CFLAGS`, `MATCH_ARGS`
2. Run `tools/match/match.sh scratches/<function>` (append `--full` for a
   side-by-side listing instead of a unified diff).
3. Iterate the source until the diff is empty. Exit code 0 means 100%.

The differ (`snail match`, `src/snail/match.py`) normalizes both sides before
comparing: relocated immediates/displacements in the object and absolute VAs
in the image become `ADDR`, intra-function branch targets become `L<offset>`
labels. Struct offsets, register allocation, and instruction scheduling all
still count — only link-time layout is forgiven.

Function extents come from the symbol manifest: start at the curated address,
end at the next curated address with int3/nop padding trimmed. When uncurated
functions sit in the gap, pass an explicit end through `MATCH_ARGS="--end 0x..."`.

## Notes

- x87-heavy functions are the hardest to match; near-misses that differ only
  in fld/fstp scheduling are still strong evidence — record the residual diff
  in the scratch directory rather than forcing source contortions.
- A matched scratch is the porting reference for the Zig side; link it from
  the function's PORT comment and the relevant analysis note.
