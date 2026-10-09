# Shockwave web demo ("Snail Mail Online")

A cut-down Windows build of Snail Mail that shockwave.com served to Internet
Explorer through an ActiveX web installer. It survives in the
[Flashpoint Archive](https://flashpointarchive.org/). The Wayback Machine has no
capture of its Shockwave pages, so Flashpoint's package is the only known copy.

## Provenance

| | |
|---|---|
| Flashpoint entry | `5bf7c2d8-68fe-4811-acf5-55d3a4cb857a`, "Snail Mail", platform ActiveX, library arcade |
| Credited | developer "Sandlot Games; Alpha72 Games", publisher shockwave.com |
| Original page | `http://www.shockwave.com/content/snailmail/sis/index.html` |
| Added to Flashpoint | 2024-08-12 |
| Package | [`5bf7c2d8-68fe-4811-acf5-55d3a4cb857a-1723501378830.zip`](https://download.flashpointarchive.org/gib-roms/Games/5bf7c2d8-68fe-4811-acf5-55d3a4cb857a-1723501378830.zip), 2,577,504 bytes, SHA-256 `3b2d26722a1954f231dd77408e8bbf50c818568da712a4af82584b9794aa296a` |
| Downloaded | 2026-10-09, kept locally in `artifacts/flashpoint/` (not committed) |
| Lead | kilicool64 on the [Chromadrome 2 Steam thread](https://steamcommunity.com/app/378350/discussions/0/1327844097112596303/), 2026-10-09 |

Flashpoint renamed the installer from `smosetup.exe` to `smosetup` "to prevent
issue with services preventing infinity to download zips with exe files". Its
`index.html` differs from the kept `index_original.html` only in those two
references.

## Contents

The package mirrors the page's directory:

| File | Bytes | SHA-256 |
|---|---:|---|
| `index.html` | 1,820 | `777db2b56ef3bf7994746fa141f128cf9b240a8d967b33d47787a6d3dbdbb528` |
| `index_original.html` | 1,828 | `95082d6f42fd61c215313f83ad7583a3b32a41f1a2f7764a3f57ab03b536f8f0` |
| `javawi.js` | 914 | `f0b52657459edf95350a57df987d5beac17fef984d69e848eb55946a39c7e8e3` |
| `slgwebinstall.cab` | 196,945 | `a32bcf7a9c461da144ea0c39c7dcbe1fb5f306eef65e4ca0b54fdcbe1d63d115` |
| `smosetup` | 2,394,019 | `ca160e3b758abefe587881cdf6a9c3a4ba572fce5c396e00fe786b80c7be3b15` |
| `webinstall1.gif` | 10,681 | `a347085c41992ecc2c87c29c89b2b78b2dd93a5b634dc556744d43aeb8bdd7ba` |

**The page** embeds Sandlot's ActiveX loader (`Sgloader1`, CLSID
`{7D731A83-6C80-4EA4-9646-5E06A0513274}`) with `GameCab` pointing at
`smosetup.exe`, and closes itself on the loader's `GamePlayDone()` event.

**The loader cab** (`slgwebinstall.inf`) installs two components:

| File | Bytes | SHA-256 | Version |
|---|---:|---|---|
| `slgwebinstall.dll` | 114,688 | `fcb5c2e6bc1b2b72967eafb17bb06b5eda5982e97b8cb67bdfb6e8ab71e1053c` | 1,0,0,1 |
| `slghex.dll` | 315,392 | `e144d8a741c1ad482eb11dcb85f418f3558610188f150f37d709e516142c80e0` | 2,0,0,6 |

`slghex.dll` has CLSID `{205FF73B-CA67-11D5-99DD-444553540011}`.

**The installer** is Inno Setup (setup data 4.2.6), titled "Snail Mail
Online". `innoextract` unpacks it to `app/`:

| File | Bytes | Date | SHA-256 |
|---|---:|---|---|
| `SnailMailWeb.exe` | 724,992 | 2005-06-01 | `3d81f8fc0a57fcd391b5c26c9c6d7fb7715b970976a5ef92a8156ebb0a968824` |
| `SnailMailWeb.dam` | 3,678,033 | 2005-06-01 | `3d8fed02dd53d2eb68ed2e53aa538a2595df6f0d683d2ceb502dd86253518ad0` |
| `SnailMailWeb.dat` | 0 | 2005-06-08 | (empty) |
| `SnailMailWeb.cfg` | 0 | 2005-03-04 | (empty) |

## The executable

`SnailMailWeb.exe` is a separate build, not a copy of the retail executable.

- **Linked:** PE timestamp 2005-05-31 19:19:53 UTC, linker 6.0. That is six
  months after the retail build (2004-12-04).
- **Compiled with a newer compiler.** Its Rich header lists 55 C++ objects
  from backend 8966 (VC6 SP5) and C objects from 8047. The retail game's 56
  C++ objects come from 8447 (VC6 SP3; see
  `tools/match/compiler-identification-20261005.md`).
- **Trimmed.** It has none of the retail strings for the galaxy map
  (`_Galaxy.txt`, "Intergalactic Delivery Route"), the high-score tables,
  Challenge or Time Trial, or the full-screen option.
- **Web-only.** It adds `Sprites/LoadingShockwave.tga`,
  `Menubg_Shockwave.txt`, `ShellExecuteA`, a `SnailMailWebWindowClass`
  window, and an upsell:

  > Download the game for more levels, more power ups and more action! Play
  > Time Trial and Challenge Modes, track your high scores, and watch instant
  > replays!

## The archive

`SnailMailWeb.dam` has the same index layout as `SnailMail.dat` (see
[archive container](archive-container.md)): an entry count, then
`(path offset, data offset, size)` records, then the path strings. The mask
differs: every byte is XORed with the constant `0x80`, not the
offset-dependent mask. With that mask the index decodes cleanly. There are 408
entries, and the last payload ends exactly at the end of the file.

| Root | Entries |
|---|---:|
| SEGMENTS | 128 |
| X | 128 |
| SPRITES | 46 |
| VOICE | 40 |
| SFX2 | 35 |
| OBJECTS | 16 |
| LEVELS | 7 |
| BACKGROUNDS | 5 |
| MUSIC | 2 |
| BASS.DLL | 1 |

```python
data = bytes(b ^ 0x80 for b in open("SnailMailWeb.dam", "rb").read())
# then parse as an archive index: u32 count, count x (u32 path, u32 offset, u32 size)
```

**Levels.** The levels are the tutorial and `ARCADE000`–`005`.
- The tutorial and the first five postal levels have the same parameters
  and segment lists as retail.
- The only background shipped is `SpaceRed`, so levels that use
  `SpacePurple` in retail use `SpaceRed` here.
- `ARCADE000` is a developer test level ("Test", speed 100, a loop-heavy
  segment list) that differs from retail's.

**Segments.** All 128 segment files are byte-identical to retail's.

The data holds no levels beyond retail's first five, so whatever felt
exclusive in the demo is not in its level or segment files. The test level,
the red backdrop on every level, and the trimmed menus are the visible
differences. The slowdown on modern PCs that players report was not
investigated.
