# Exact cRTutorial::AI

`0x448de0` is the authored `cRTutorial::AI()` method. Android and iOS
`Tutorial.o` preserve the same owner and method with one body each. VC6 emits
`?AI@cRTutorial@@QAEXXZ`; all five instructions and the call relocation match.

The thunk uses the borrowed cRSubGame at `+0x0c` to sample the embedded
cRSubGoldy's live transform position through `cRSubGame::LocFromPos`. Its sole
Windows caller discards the lookup result, proving the natural void contract;
EAX is only residue from the final call.
