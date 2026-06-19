# iOS IPA Symbol Recovery

Inputs:

- `artifacts/ios/Snail Mail.ipa` (`iSM`, version 1.5.0, iPhone)
- `artifacts/4pda/snail_mail_v1.9.0.ipa` (`iSM`, version 1.9.0, iPhone)
- `artifacts/ios/SnailMailforiPad-v1.0.5.ipa` (`PSM-iPad`, actual version 1.0.6, iPad)

Method:

- Extracted Mach-O symbol tables with `rabin2 -sj`.
- Extracted Objective-C class metadata with `rabin2 -cj`.
- Extracted string evidence with `rabin2 -zzj`.
- Demangled retained C++ names with `c++filt`.

Compact machine-readable extraction:
`analysis/symbols/ios-ipa-gameplay-names.json`.
It dedupes repeated architecture/build records into name-level rows and omits
ARM addresses, ordinals, and raw mangled spellings.

These are ARM/iOS names and addresses. Treat them as provenance and candidate
vocabulary until a Windows x86 function is structurally matched by control flow,
strings, call graph, or existing cross-port evidence. Do not apply these as
canonical Windows renames by address alone.

## Build Signal

| IPA | total symbols | non-imports | object path markers | ObjC methods | C++ mangled | auto funcs | authored candidates | ObjC classes | note |
| --- | ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: | --- |
| `Snail Mail.ipa` / v1.5.0 iPhone | 11197 | 10839 | 480 | 5734 | 1529 | 0 | 597 | 364 | Richest symbol source; includes STABS-style object file paths. |
| `snail_mail_v1.9.0.ipa` / v1.9.0 iPhone | 1487 | 1306 | 0 | 115 | 891 | 0 | 741 | 6 | Best newer gameplay/Game Center symbol source; no leaked object paths. |
| `SnailMailforiPad-v1.0.5.ipa` / v1.0.6 iPad | 1646 | 1455 | 0 | 0 | 0 | 1448 | 0 | 9 | C/C++ symbols are stripped; useful for ObjC shell classes and strings only. |

The v1.5 iPhone build leaks this source-object root:

```text
/Users/brian/Desktop/Project_1_3_0_02/iSMu/build/iSMu.build/Distribution-iphoneos/Snail Mail.build/Objects-normal/armv6/
```

## High-Value Object Grouping

The v1.5 local symbol table includes object-file separators, which can group
nearby symbols by original compilation unit. The most useful authored buckets
are:

| object file | candidate symbols |
| --- | ---: |
| `SubGame.o` | 93 |
| `RShell.o` | 53 |
| `Path.o` | 47 |
| `RMaths.o` | 29 |
| `RObject.o` | 29 |
| `Mac.o` | 28 |
| `EAGLView.o` | 28 |
| `Border.o` | 26 |
| `Game.o` | 26 |
| `iSMAppDelegate.o` | 26 |
| `GL.o` | 23 |
| `MacAudio.o` | 18 |
| `HighScore.o` | 15 |
| `RSprite.o` | 13 |
| `MacFile.o` | 10 |
| `Galaxy.o` | 9 |
| `LoadingBar.o` | 9 |
| `Mouse.o` | 9 |
| `RString.o` | 8 |
| `BassPlay.o` | 6 |
| `Golb.o` | 6 |
| `Logo.o` | 6 |
| `RSound.o` | 6 |
| `Star.o` | 6 |
| `Tips.o` | 6 |
| `Subtrack.o` | 5 |

This is useful for resolving ambiguous Windows functions by neighborhood. For
example, a Windows function that structurally matches a v1.5 ARM function in the
`SubGame.o` span should be weighed against nearby `cRSubGame::*` and subgame
helper names before assigning a generic scratch name.

## Stable Phone-Symbol Evidence

Both iPhone builds retain these `cRSubGame` names:

- `cRSubGame::AI()`
- `cRSubGame::AddGarbage(cRSubLoc*, cRSubGoldy*)`
- `cRSubGame::AddJetPack(cRSubLoc*, cRSubGoldy*)`
- `cRSubGame::AddSlug(cRSubLoc*, cRSubGoldy*)`
- `cRSubGame::BlinkRandInit()`
- `cRSubGame::BuildColours()`
- `cRSubGame::BuildLevel()`
- `cRSubGame::CalcRealPos(tVector&, float&)`
- `cRSubGame::Complete(bool)`
- `cRSubGame::CondenseTrack()`
- `cRSubGame::FringeEdgeTrack()`
- `cRSubGame::GenerateLevel(int)`
- `cRSubGame::GetSkirtColour(tColourSmall*)`
- `cRSubGame::GetSkirtColourRandomOpen()`
- `cRSubGame::HideScores()`
- `cRSubGame::Init()`
- `cRSubGame::LocFromPos(tVector)`
- `cRSubGame::PlaceParcels()`
- `cRSubGame::PlaceParcelsSurvival()`
- `cRSubGame::RemoveBods()`
- `cRSubGame::SetFeatures()`
- `cRSubGame::SetRate(float)`
- `cRSubGame::SlideSmoothTrack()`
- `cRSubGame::SmoothTrack()`
- `cRSubGame::StartLevel(int)`
- `cRSubGame::UnInit()`
- `cRSubGame::cRSubGame()`

Both iPhone builds also retain useful shell/platform names:

- `SaveFile(char*, void*, int, bool)`
- `LoadFile(char*, void*, int*)`
- `DatBuild()`
- `PngLoadImage(char*, char**, int*, int*, int*)`
- `MacSwapBuffers()`
- `G0MemoryValues()`
- `RShellConvertFileName(char*, char*)`
- `RShellReadDirectory(char*, char*, int*, char (*) [128])`
- `RShellLoadFile(char*, void*, int*)`
- `RShellLoadFile(char*, int*)`
- `RShellLoadFileHeader(char*, void*, int)`
- `RShellSaveFile(char*, void*, int)`
- `RShellSaveDirectory(char*, int, char (*) [128])`
- `RShellLoadDirectory(char*, int*, char (*) [128])`
- `RShellFindFile(char*, bool)`
- `RShellDatInit(char*)`
- `RShellInit()`

## v1.9-Only Gameplay Leads

The v1.9.0 iPhone build carries newer or more specific signatures that did not
appear in the v1.5.0 phone symbol set:

- `cRSubGame::AddHealth(cRSubLoc*, cRSubGoldy*)`
- `cRSubGame::AddParcel(cRSubRow*, tVector*, cRSubGoldy*)`
- `cRSubGame::AddRing(cRSubRow*, cRSubLoc*, int, cRSubGoldy*, float)`
- `cRSubGame::AddSpeedUp(cRSubLoc*, cRSubGoldy*)`
- `cRSubGame::AspectCorrectPlayerNames()`
- `cRSubGame::DividesAI()`
- `cRSubGame::GetControl(int)`
- `cRSubGame::GetY(tVector)`
- `cRSubGame::SetScores()`
- `cRSubGame::TrackBuild()`
- `cRSubGoldy::ReadMouse()`
- `cRSubGoldy::SpeedUpCollect()`
- `cRSubGoldy::FallingInit()`
- `cRSubGoldy::GoldyGoldy(cRSubGoldy*, cRSubGoldy*)`
- `cRSubGoldy::RessurectAIScore()`
- `cRSubHover::End()`
- `cRSubLoc::IsEmpty()`
- `cRSubLoc::IsFloor()`
- `cRSubLoc::IsRamp()`
- `cRSubLocEx::AI()`
- `cRSubLazer::Shoot(cRSubGoldy*, tVector, tVector)`
- `cRSubRingStar::Shower(cRSubGoldy*)`
- `cRSubTrampRingManager::AddRing(cRSubGoldy*, cRSubLoc*)`
- `cRSaltManager::Add(tVector&, cRSubGoldy*)`

The v1.9.0 build also exposes Game Center integration names such as:

- `MacGCLeaderboardDisplay()`
- `MacGCMatchInviteAccepted()`
- `MacGCMatchDisconnect()`
- `MacGCMatchSendData(unsigned char*, int, bool)`
- `MacGCMatchStart()`
- `MacGCGetAchievementDescription(int, char*, int*, bool)`
- `MacGCAchievementsStart()`
- `MacGCSessionInvite(int)`
- `MacGCLeaderboardStart()`
- `MacGCMatchSendContinue(int)`
- `MacGCMatchSendResult(int, int)`
- `MacGCMatchEndGame()`

These are probably less useful for Windows gameplay matching, but they help
explain the release-to-release platform wrapper drift.

## Objective-C Metadata

Useful non-framework classes recovered from ObjC metadata:

- v1.5.0 iPhone: `iSMAppDelegate`, `EAGLView`, `cPng`, `mMacFile`
- v1.9.0 iPhone: `MyUIViewController`, `iSMAppDelegate`, `EAGLView`, `cPng`, `mMacFile`, `GCDelegate`
- v1.0.6 iPad: `iSMAppDelegate`, `MyEAGLView`, `cPng`, `mMacFile`, `accelerometerDelegate`, `WebViewController`, `WebView`, `MoreGamesManager`, `TVUIViewController`

The iPad binary is stripped for C/C++ symbols, but its ObjC shell still confirms
AirPlay/iPad-specific wrapper methods including `AirPlayScreenCreate`,
`AirPlayRenderiPad`, `AirPlayRenderTV`, `AirPlaySwapBuffersiPad`,
`AirPlaySwapBuffersTV`, and `screenDidChange:`.

## Type and String Vocabulary

All three builds carry useful class-size and RTTI-like strings. These are strong
type-vocabulary evidence, especially where existing Windows analysis already has
matching strings:

- `Size of cRGame %i`
- `Size of cRSubGame %i`
- `Size of cRTutorial`
- `Size of cRSubTracks %i`
- `Size of cRSubSpeedUp %i`
- `Size of cRJetPack %i`
- `Size of cRSubHealth %i`
- `Size of cRSlug %i`
- `Size of cRSubLazerManager %i`
- `Size of cRSaltManager %i`
- `Size of cRSubGarbage %i`
- `Size of cRSubRing %i`
- `Size of cRSubGoldy %i`
- `Size of cRSubLoc %i`
- `Size of cRSubRow %i`
- `Size of cRSubHighScore %i`
- `Size of cRSubSolution %i`
- `Size of cRTimeTrial %i`
- `Size of cRPathManager %i`
- `Size of cRLandscapeManager %i`
- `Size of cRSMTracks %i`
- `Size of cRParcelManager %i`
- `Size of cRGUI %i`
- `Size of cRGalaxy %i`
- `Size of cREnemyManager %i`
- `Size of cRCompletion %i`
- `Size of cRTimesUp %i`

Resource strings also confirm route/data naming shared with other ports:

- `Levels/%s`
- `Levels/Default.txt`
- `Data/LevelsDir.txt`
- `HighScores.txt`
- `Challenge Scores`
- `Pro Scores`
- `Postal Scores`
- `Postal High Scores`
- `HighScores/TT_%03i.bin`
- `HighScores/SL_000.bin`
- `HighScores/HS_%08i.bin`

## Candidate Use

Recommended next use:

1. For a Windows function already structurally matched to iOS/Android, use this
   report to tighten the human-readable name or description.
2. For ambiguous `SubGame.o`, `Path.o`, `RObject.o`, `RSprite.o`, and shell
   functions, use the v1.5 object grouping as a candidate namespace constraint.
3. Keep the canonical manifests in `analysis/symbols/gameplay-functions.json`
   and `analysis/symbols/gameplay-references.json` unchanged until each candidate
   is backed by structural evidence.
